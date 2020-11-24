// CONFIG1
#pragma config FOSC = INTOSC    // Selección de Oscilador->INTOSC 
#pragma config WDTE = OFF    // Watchdog Timer ->Deshabilitado
#pragma config PWRTE = OFF    // Power-up Timer ->Desahabilitado
#pragma config MCLRE = ON    // Selección de pin para MCLR(MCLR o VPP)-> MCLR
#pragma config CP = OFF    // Protección del código de memoria flash del programa ->Deshabiliado
#pragma config BOREN = ON    // Brown-out Reset ->Habilitado
#pragma config CLKOUTEN = OFF    // Clock Out ->Deshabiliado
#pragma config IESO = ON    // Modo Switchover Interno/Externo -> Habilitado
#pragma config FCMEN = ON    // Monitor de seguro de fallo del Clock Monitor-> Habilitado

// CONFIG2
#pragma config WRT = OFF    // Protección de Auto-Escritura de la memoria flash-> Deshabilitado
#pragma config CPUDIV = NOCLKDIV    // División del Clock para sistema CPU -> Ninguna división
#pragma config USBLSCLK = 48MHz    // USB Low Speed Clock -> 48 MHz
#pragma config PLLMULT = 4x    // Multiplicador de PLL ->4x 
#pragma config PLLEN = DISABLED    // Habilitación de PLL -> Deshabilitado
#pragma config STVREN = ON    // Reset por Stack Overflow/Underflow ->Habilitado
#pragma config BORV = LO    // Voltaje de Brown-out Reset->Low trip
#pragma config LPBOR = OFF    //Reset Low-Power Brown Out->Deshabilitado
#pragma config LVP = ON    // Programción Low-Voltage ->Habilitado
