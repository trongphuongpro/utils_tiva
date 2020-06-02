//! \file utils_tiva.h
//! \brief Utility functions, structs for Tiva c.
//! \author Nguyen Trong Phuong (aka trongphuongpro)
//! \date 2020 April 8

#ifndef __UTILS_TIVA__
#define __UTILS_TIVA__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "utils/uartstdio.h"
    
//! \brief Data type that contains GPIO port and pin.
//!
typedef struct PortPin {
    uint32_t base; //!< Memory base of GPIO port
    uint8_t pin; //!< GPIO pin
} PortPin_t;


//! \brief Initialize SysTick.
//! \return nothing.
//!
void delay_init(void);


//! \brief Delay in millisecond.
//! \param ms millisecond.
//! \return nothing.
//!
void delay_ms(uint16_t ms);


//! \brief Configure UART0 for console output
//! \return nothing.
//!
void console_init(uint32_t baudrate);


#ifdef __cplusplus
}
#endif

#endif

/********************* End of File *******************************************/