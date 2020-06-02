//! \file utils_tiva.c
//! \brief Utility functions, structs for Tiva c.
//! \author Nguyen Trong Phuong (aka trongphuongpro)
//! \date 2020 April 8

#include "utils_tiva.h"

#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h" 
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"


volatile uint16_t counter = 0;

static void systick_isr();

void systick_isr() {
    if (counter > 0) {
        counter--;
    }
}

void delay_init() {
    SysTickPeriodSet(SysCtlClockGet()/1000); // period = 1 ms
    SysTickIntRegister(systick_isr);
    SysTickEnable();
}

void delay_ms(uint16_t ms) {
    counter = ms;

    while (counter);
}


void console_init(uint32_t baudrate) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTStdioConfig(0, baudrate, SysCtlClockGet());
}
/********************* End of File *******************************************/