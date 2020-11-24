#include "pin_manager.h"


void PIN_MANAGER_Initialize(void)
{
    //registros LATx 
    LATA = 0x00;
    LATC = 0x02;

    //registros TRISx 
    TRISA = 0x30;
    TRISC = 0x17;

    //registros ANSELx 
    ANSELC = 0x04;
    ANSELA = 0x10;

    //registros WPUx
    WPUA = 0x00;
    OPTION_REGbits.nWPUEN = 1;

  //registros APFCONx
    APFCON = 0x00; 
}
