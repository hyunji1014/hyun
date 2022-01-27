#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "nrfx_spim.h"
#include "intan_register.h"

typedef struct
{
    uint32_t rx_bank;
}rx_bank_t;

typedef struct
{
    uint8_t ch0;
    uint8_t ch1;
    uint8_t ch2;
    uint8_t ch3;
    uint8_t ch4;
    uint16_t ch5;
    uint16_t ch6;
    uint16_t ch7;
    uint16_t ch8;
    uint16_t ch9;
    uint16_t ch10;
    uint16_t ch11;
    uint16_t ch12;
    uint16_t ch13;
    uint16_t ch14;
    uint16_t ch15;
}ch_data_t;