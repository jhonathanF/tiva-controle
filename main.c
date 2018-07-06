#include "bibliotecas/utilitarioTiva.h"
#include "bibliotecas/gpioUtils.h"
#include <tm4c123gh6pm.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trataST(void);
void trataPortA(void);
void trataPortB(void);
void trataPortC(void);
void trataPortD(void);
void trataPortE(void);
uint32_t microsAtual;
uint32_t millisAtual;
uint32_t leituraX;
uint32_t leituraY;
int pausado = 0;
int filaEnvios[20];
int index = 0;
#define UART_FR_TXFF            0x00000020          // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010
void setup()
{
    configurarSysTick(400000, 0x03);

    //-----ATIVAR OS PORTS-----//
    ativarRCGC(RCGC_PORT_A);
    ativarRCGC(RCGC_PORT_B);
    ativarRCGC(RCGC_PORT_C);
    ativarRCGC(RCGC_PORT_D);
    ativarRCGC(RCGC_PORT_E);
    ativarRCGC(RCGC_PORT_F);
    SYSCTL_RCGCADC_R |= 0x01;
    SYSCTL_RCGCADC_R |= 0x02;

    //-----CONFIGURAR ADC-----//
    habilitarADCPorts(&GPIO_PORTD_AFSEL_R, &GPIO_PORTD_AMSEL_R, 1);
    configurarADC0(0x0F, 0x06, 0x02, 0x01, 0x01, 0);
    configurarADC1(0x0F, 0x07, 0x02, 0x01, 0x01, 0);

    //-----CONFIGURAR INTERRUPÇÕES-----//
    configurarInterrupcao(&GPIO_PORTA_IS_R, &GPIO_PORTA_IEV_R,
                          &GPIO_PORTA_IBE_R, &GPIO_PORTA_IM_R, 2, 0, 1, 0);

    configurarInterrupcao(&GPIO_PORTA_IS_R, &GPIO_PORTA_IEV_R,
                          &GPIO_PORTA_IBE_R, &GPIO_PORTA_IM_R, 3, 0, 1, 0);

    configurarInterrupcao(&GPIO_PORTA_IS_R, &GPIO_PORTA_IEV_R,
                          &GPIO_PORTA_IBE_R, &GPIO_PORTA_IM_R, 4, 0, 1, 0);

    configurarInterrupcao(&GPIO_PORTB_IS_R, &GPIO_PORTB_IEV_R,
                          &GPIO_PORTB_IBE_R, &GPIO_PORTB_IM_R, 2, 0, 1, 1);

    configurarInterrupcao(&GPIO_PORTB_IS_R, &GPIO_PORTB_IEV_R,
                          &GPIO_PORTB_IBE_R, &GPIO_PORTB_IM_R, 3, 0, 1, 1);

    configurarInterrupcao(&GPIO_PORTC_IS_R, &GPIO_PORTC_IEV_R,
                          &GPIO_PORTC_IBE_R, &GPIO_PORTC_IM_R, 4, 0, 1, 2);

    configurarInterrupcao(&GPIO_PORTC_IS_R, &GPIO_PORTC_IEV_R,
                          &GPIO_PORTC_IBE_R, &GPIO_PORTC_IM_R, 5, 0, 1, 2);

    configurarInterrupcao(&GPIO_PORTC_IS_R, &GPIO_PORTC_IEV_R,
                          &GPIO_PORTC_IBE_R, &GPIO_PORTC_IM_R, 6, 0, 1, 2);

    configurarInterrupcao(&GPIO_PORTC_IS_R, &GPIO_PORTC_IEV_R,
                          &GPIO_PORTC_IBE_R, &GPIO_PORTC_IM_R, 7, 0, 1, 2);

    configurarInterrupcao(&GPIO_PORTD_IS_R, &GPIO_PORTD_IEV_R,
                          &GPIO_PORTD_IBE_R, &GPIO_PORTD_IM_R, 6, 0, 1, 3);

    configurarInterrupcao(&GPIO_PORTF_IS_R, &GPIO_PORTF_IEV_R,
                          &GPIO_PORTF_IBE_R, &GPIO_PORTF_IM_R, 4, 0, 1, 30);

    //-----CONFIGURAR PINOS-----//
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, 2, INPUT);
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, 3, INPUT);
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, 4, INPUT);
    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, 2, INPUT);
    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, 3, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, 4, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, 5, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, 6, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, 7, INPUT);
    configurarPino(&GPIO_PORTD_DIR_R, &GPIO_PORTD_DEN_R, 6, INPUT);

    configurarPino(&GPIO_PORTF_DIR_R, &GPIO_PORTF_DEN_R, 4, INPUT);

    configurarUART0(0x01, &GPIO_PORTA_AFSEL_R, &GPIO_PORTA_PCTL_R, 8, 44, 0x70,
                    0x00, 0x301);
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, 0, INPUT);
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, 1, INPUT);
}
int main(void)
{
    setup();
    while (1)
    {

    }
}

void trataST()
{
    int i = 0;
    if (pausado != 1)
    {
        for (i = 0; i < 20; i++)
        {
            if (filaEnvios[i] > 0)
            {
                escreverUART0(filaEnvios[i]);
            }
        }
        leituraX = ADC0_SSFIFO0_R;
        leituraY = ADC1_SSFIFO0_R;

        if (leituraX < 1500)
        {

            escreverUART0(60); // < (60)
        }
        else if (leituraX > 2400)
        {
            escreverUART0(62); // > (62)
        }

        if (leituraY < 1500)
        {

            escreverUART0(95); // _ (95)
        }
        else if (leituraY > 2400)
        {
            escreverUART0(94); // ^ (94)
        }
    }
    memset(filaEnvios, 0, sizeof(filaEnvios));
    index = 0;

}

void trataPortA()
{
    if (lerBit(&GPIO_PORTA_RIS_R, 2)) //Verificação de qual pino gerou a inten
    {
        setarBit(&GPIO_PORTA_ICR_R, 2, 1); //Limpa flag de int do pino que gerou a inten
        filaEnvios[index] = 79; // O (79)
        index++;
    }
    if (lerBit(&GPIO_PORTA_RIS_R, 3))
    {
        setarBit(&GPIO_PORTA_ICR_R, 3, 1);
        filaEnvios[index] = 60; // < (60)
        index++;
    }
    if (lerBit(&GPIO_PORTA_RIS_R, 4))
    {
        setarBit(&GPIO_PORTA_ICR_R, 4, 1);
        filaEnvios[index] = 62; // > (62)
        index++;

    }
}

void trataPortB()
{
    if (lerBit(&GPIO_PORTB_RIS_R, 3))
    {
        setarBit(&GPIO_PORTB_ICR_R, 3, 1);
        escreverUART0(36); // $(36)
        index++;
    }
    if (lerBit(&GPIO_PORTB_RIS_R, 2))
    {
        setarBit(&GPIO_PORTB_ICR_R, 2, 1);
        filaEnvios[index] = 95;  // _ (95)
        index++;
    }
}

void trataPortC()
{
    if (lerBit(&GPIO_PORTC_RIS_R, 4)) //Verificação de qual pino gerou a inten
    {
        setarBit(&GPIO_PORTC_ICR_R, 4, 1); //Limpa flag de int do pino que gerou a inten
        filaEnvios[index] = 45; // - (45)
        index++;
    }
    if (lerBit(&GPIO_PORTC_RIS_R, 5))
    {
        setarBit(&GPIO_PORTC_ICR_R, 5, 1);
        if (pausado == 0)
        {
            escreverUART0(32);
            escreverUART0(83);
            escreverUART0(116);
            escreverUART0(111);
            escreverUART0(112);
            escreverUART0(32);

            pausado = 1;
        }
        else
        {
            escreverUART0(32);
            escreverUART0(83);
            escreverUART0(116);
            escreverUART0(97);
            escreverUART0(114);
            escreverUART0(116);
            escreverUART0(32);
            pausado = 0;
        }
        index++;
    }
    if (lerBit(&GPIO_PORTC_RIS_R, 6))
    {
        setarBit(&GPIO_PORTC_ICR_R, 6, 1);
        filaEnvios[index] = 47; // /\ (47 e 92)
        index++;
        filaEnvios[index] = 92;
        index++;
    }
    if (lerBit(&GPIO_PORTC_RIS_R, 7))
    {
        setarBit(&GPIO_PORTC_ICR_R, 7, 1);
        filaEnvios[index] = 35; // # (35)
        index++;
    }
}

void trataPortD()
{
    if (lerBit(&GPIO_PORTD_RIS_R, 6))
    {
        setarBit(&GPIO_PORTD_ICR_R, 6, 1);
        filaEnvios[index] = 94; // ^ (94)
        index++;
    }

}

void trataPortE()
{
}

void trataPortF()
{
    if (lerBit(&GPIO_PORTF_RIS_R, 4))
        setarBit(IEV, pino, subidaDescidaAmbos); //Define evento - 0 descida | baixo - 1 subida | alto

    {
        setarBit(&GPIO_PORTF_ICR_R, 4, 1);
        filaEnvios[index] = 88; // X (88)
        index++;
    }
}

