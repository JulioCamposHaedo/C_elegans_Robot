#include "i2c_slave.h"
#include <xc.h>
#include "pwm1.h"
#include "pwm2.h"
#include "vertebra_slave.h"

#define I2C_SLAVE_ADDRESS      31
#define I2C_SLAVE_MASK         127

typedef enum
{
    I2C_IDLE,
    I2C_ADDR_TX,
    I2C_ADDR_RX,
    I2C_DATA_TX,
    I2C_DATA_RX
} i2c_slave_state_t;

typedef enum
{
    I2C_ADDR_M,
    I2C_REG,
}i2c_estado_t;


volatile uint8_t i2cWrData;
volatile uint8_t i2cRdData;
volatile uint8_t i2cSlaveAddr;
static volatile i2c_slave_state_t i2cSlaveState = I2C_IDLE;
volatile uint8_t datoParaLeer;
volatile uint8_t RegParaEscribir= 0;

static uint8_t master_read_data;

static void I2C_Isr(void);
static void I2C_SlaveDefRdInterruptHandler(void);
static void I2C_SlaveDefWrInterruptHandler(void);
static void I2C_SlaveDefAddrInterruptHandler(void);
static void I2C_SlaveDefWrColInterruptHandler(void);

static void I2C_SlaveRdCallBack(void);
static void I2C_SlaveWrCallBack(void);
static void I2C_SlaveAddrCallBack(void);

static inline bool I2C_SlaveOpen();
static inline void I2C_SlaveSetSlaveAddr(uint8_t slaveAddr);
static inline void I2C_SlaveSetSlaveMask(uint8_t maskAddr);
static inline void I2C_SlaveEnableIrq(void);
static inline bool I2C_SlaveIsAddr(void);
static inline bool I2C_SlaveIsRead(void);
static inline void I2C_SlaveClearBuff(void);
static inline void I2C_SlaveClearIrq(void);
static inline void I2C_SlaveReleaseClock(void);
static inline bool I2C_SlaveIsTxBufEmpty(void);
static inline bool I2C_SlaveIsRxBufFull(void);
static inline void I2C_SlaveSendTxData(uint8_t data);
static inline uint8_t I2C_SlaveGetRxData(void);

void I2C_Initialize()
{
    SSP1STAT  = 0x00;
    SSP1CON1 |= 0x06;
    SSP1CON2  = 0x00;
    SSP1CON1bits.SSPEN = 0;
}


void I2C_Open() 
{
    I2C_SlaveOpen();
    I2C_SlaveSetSlaveAddr(I2C_SLAVE_ADDRESS);
    I2C_SlaveSetSlaveMask(I2C_SLAVE_MASK);
    I2C_SlaveSetIsrHandler(I2C_Isr);
    I2C_SlaveSetWriteIntHandler(I2C_SlaveDefWrInterruptHandler);
    I2C_SlaveSetReadIntHandler(I2C_SlaveDefRdInterruptHandler);
    //I2C_SlaveSetReadIntHandler(I2C_reg_Slave_InterruptHandler(1));
    I2C_SlaveSetAddrIntHandler(I2C_SlaveDefAddrInterruptHandler);
    I2C_SlaveSetWrColIntHandler(I2C_SlaveDefWrColInterruptHandler);
    I2C_SlaveEnableIrq();    
}


static void I2C_Isr() 
{ 
    I2C_SlaveClearIrq();

    if(I2C_SlaveIsAddr())
    {
        if(I2C_SlaveIsRead())
        {
            i2cSlaveState = I2C_ADDR_TX;
        }
        else
        {
            i2cSlaveState = I2C_ADDR_RX;
        }
    }
    else
    {
        if(I2C_SlaveIsRead())
        {
            i2cSlaveState = I2C_DATA_TX;
        }
        else
        {
            i2cSlaveState = I2C_DATA_RX;
        }
    }

    switch(i2cSlaveState)
    {
        case I2C_ADDR_TX:
            I2C_SlaveAddrCallBack();
            if(I2C_SlaveIsTxBufEmpty())
            {
                I2C_SlaveWrCallBack();
            }
            break;
        case I2C_ADDR_RX:
            I2C_SlaveAddrCallBack();
            break;
        case I2C_DATA_TX:
            if(I2C_SlaveIsTxBufEmpty())
            {
                I2C_SlaveWrCallBack();
            }
            break;
        case I2C_DATA_RX:
            if(I2C_SlaveIsRxBufFull())
            {
                I2C_reg_Slave_InterruptHandler(I2C_SlaveGetRxData());
                I2C_SlaveRdCallBack();
            }
            break;
        default:
            break;
    }
    I2C_SlaveReleaseClock();
}

// Handler de interrupción de evento común
void I2C_SlaveSetIsrHandler(i2cInterruptHandler handler)
{
    MSSP_InterruptHandler = handler;
}

// Handler de interrupción por lectura
void I2C_SlaveSetReadIntHandler(i2cInterruptHandler handler) {
    I2C_SlaveRdInterruptHandler = handler;
}

static void I2C_SlaveRdCallBack() {
    if (I2C_SlaveRdInterruptHandler) 
    {
        I2C_SlaveRdInterruptHandler();
    }
}

static void I2C_SlaveDefRdInterruptHandler() {
    i2cRdData = I2C_SlaveGetRxData();
}

// Handler de interrupción por escritura
void I2C_SlaveSetWriteIntHandler(i2cInterruptHandler handler) {
    I2C_SlaveWrInterruptHandler = handler;
}

static void I2C_SlaveWrCallBack() {

    if (I2C_SlaveWrInterruptHandler) 
    {
        I2C_SlaveWrInterruptHandler();
    }
}

static void I2C_SlaveDefWrInterruptHandler() {
    i2cWrData = Get_Data_to_master();
    I2C_SlaveSendTxData(i2cWrData);
}

//  Handler de interrupción por evento de matcheo de ADDRESS
void I2C_SlaveSetAddrIntHandler(i2cInterruptHandler handler){
    I2C_SlaveAddrInterruptHandler = handler;
}

static void I2C_SlaveAddrCallBack() {
    
    if (I2C_SlaveAddrInterruptHandler) {
        I2C_SlaveAddrInterruptHandler();
    }
}

static void I2C_SlaveDefAddrInterruptHandler() {
    i2cSlaveAddr = I2C_SlaveGetRxData();
}

// Handler de interrupción por evento de colisión al escribir
void I2C_SlaveSetWrColIntHandler(i2cInterruptHandler handler){
    I2C_SlaveWrColInterruptHandler = handler;
}

static void I2C_SlaveDefWrColInterruptHandler() {
}


static inline bool I2C_SlaveOpen()
{
    if(!SSP1CON1bits.SSPEN)
    {      
        SSP1STAT  = 0x00;
        SSP1CON1 |= 0x06;
        SSP1CON2  = 0x00;
        SSP1CON1bits.SSPEN = 1;
        return true;
    }
    return false;
}


static inline void I2C_SlaveSetSlaveAddr(uint8_t slaveAddr)
{
    SSP1ADD = (uint8_t) (slaveAddr << 1);
}

static inline void I2C_SlaveSetSlaveMask(uint8_t maskAddr)
{
    SSP1MSK = (uint8_t) (maskAddr << 1);
}

static inline void I2C_SlaveEnableIrq()
{
    PIE1bits.SSP1IE = 1;
}

static inline bool I2C_SlaveIsAddr()
{
    return !(SSP1STATbits.D_nA);
}

static inline bool I2C_SlaveIsRead()
{
    return (SSP1STATbits.R_nW);
}

static inline void I2C_SlaveClearIrq()
{
    PIR1bits.SSP1IF = 0;
}

static inline void I2C_SlaveReleaseClock()
{
    SSP1CON1bits.CKP = 1;
}


static inline bool I2C_SlaveIsTxBufEmpty()
{
    return !SSP1STATbits.BF;
}

static inline bool I2C_SlaveIsRxBufFull()
{
    return SSP1STATbits.BF;
}

static inline void I2C_SlaveSendTxData(uint8_t data)
{
    SSP1BUF = data;
}

static inline uint8_t I2C_SlaveGetRxData()
{
    return SSP1BUF;
}

void Data_to_master(uint8_t i2c_wr_data){
    master_read_data = i2c_wr_data;
    
}
uint8_t Get_Data_to_master(void){
    return master_read_data;
}