//! \file utils.h
//! \brief Utility functions, structs for Tiva c.
//! \author Nguyen Trong Phuong (aka trongphuongpro)
//! \date 2020 April 8

#ifndef __UTILS__
#define __UTILS__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void delay_init();
void delay_ms(uint16_t ms);

#ifdef __cplusplus
}
#endif

#endif

/********************* End of File *******************************************/