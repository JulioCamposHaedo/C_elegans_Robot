#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LDR_Left
#define LDR_Left_TRIS                 TRISAbits.TRISA4
#define LDR_Left_LAT                  LATAbits.LATA4
#define LDR_Left_PORT                 PORTAbits.RA4
#define LDR_Left_WPU                  WPUAbits.WPUA4
#define LDR_Left_ANS                  ANSELAbits.ANSA4
#define LDR_Left_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define LDR_Left_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define LDR_Left_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define LDR_Left_GetValue()           PORTAbits.RA4
#define LDR_Left_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define LDR_Left_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define LDR_Left_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define LDR_Left_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define LDR_Left_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define LDR_Left_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set RC0 
#define RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RC0_GetValue()              PORTCbits.RC0
#define RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RC0_SetAnalogMode()         do { ANSELCbits.ANSC0 = 1; } while(0)
#define RC0_SetDigitalMode()        do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set RC1 
#define RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RC1_GetValue()              PORTCbits.RC1
#define RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define RC1_SetAnalogMode()         do { ANSELCbits.ANSC1 = 1; } while(0)
#define RC1_SetDigitalMode()        do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set LDR_Right
#define LDR_Right_TRIS                 TRISCbits.TRISC2
#define LDR_Right_LAT                  LATCbits.LATC2
#define LDR_Right_PORT                 PORTCbits.RC2
#define LDR_Right_ANS                  ANSELCbits.ANSC2
#define LDR_Right_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define LDR_Right_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define LDR_Right_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define LDR_Right_GetValue()           PORTCbits.RC2
#define LDR_Right_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define LDR_Right_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define LDR_Right_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define LDR_Right_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC3 
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC5 
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)

/**
 * \brief Inicialización de GPIO y periféricos I/O
 *
 * \param[in] Ninguno
 *
 * \return Vacío

 */
void PIN_MANAGER_Initialize (void);

#endif // PIN_MANAGER_H
