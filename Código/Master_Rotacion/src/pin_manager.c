#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    /**
    Registros LATx
    */
    LATA = 0x00;
    LATC = 0x02;

    /**
    Registros TRISx
    */
    TRISA = 0x30;
    TRISC = 0x3F;

    /**
    Registros ANSELx
    */
    ANSELC = 0x0C;
    ANSELA = 0x10;

    /**
    Registros WPUx
    */
    WPUA = 0x00;
    OPTION_REGbits.nWPUEN = 1;

    /**
    Registros APFCONx 
    */
    APFCON = 0x00;
    
}
