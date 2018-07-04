#include "utilitarioTiva.h"

void configurarSysTick(uint32_t reload, uint32_t ctrl)
{
    NVIC_ST_RELOAD_R = reload; //Pode dividir
    NVIC_ST_CTRL_R = ctrl;
}

void delay(uint32_t millis)
{
    uint32_t start = millisAtual;

    while ((millisAtual - start) <= millis)
    {

    }
}
uint32_t getMillis()
{
    return millisAtual;
}

uint32_t getMicro()
{
    return microsAtual;
}
