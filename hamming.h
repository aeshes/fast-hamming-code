#pragma once

#include <cstdint>

#define DATA_BITS 4
#define PARITY_BITS 3
#define CODE_BITS     (DATA_BITS + PARITY_BITS)
#define DATA_VALUES   (1 << DATA_BITS)
#define PARITY_VALUES (1 << PARITY_BITS)

uint8_t encode(uint8_t message);

uint8_t decode(uint8_t code);

uint8_t syndrome(uint8_t message);