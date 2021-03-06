#include "ysf_golay.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

uint32_t golay_generator_matrix[12] = {
    0b100000000000110001110101,
    0b010000000000011000111011,
    0b001000000000111101101000,
    0b000100000000011110110100,
    0b000010000000001111011010,
    0b000001000000110110011001,
    0b000000100000011011001101,
    0b000000010000001101100111,
    0b000000001000110111000110,
    0b000000000100101010010111,
    0b000000000010100100111110,
    0b000000000001100011101011
/*                100000000000
                  010000000000
                  001000000000
                  000100000000
                  000010000000
                  000001000000
                  000000100000
                  000000010000
                  000000001000
                  000000000100
                  000000000010
                  000000000001 */
};

uint32_t golay_parity_check_matrix[12] = {
    0b101001001111100000000000,
    0b111101101000010000000000,
    0b011110110100001000000000,
    0b001111011010000100000000,
    0b000111101101000010000000,
    0b101010111001000001000000,
    0b111100010011000000100000,
    0b110111000110000000010000,
    0b011011100011000000001000,
    0b100100111110000000000100,
    0b010010011111000000000010,
    0b110001110101000000000001
};

uint32_t decode_golay(uint8_t *input, uint8_t *output) {
    // GOLAY checksum
    uint32_t checksum = 0;
    uint8_t k;
    for (k = 0; k < 12; k++) {
        uint32_t value = input[0] << 16 | input[1] << 8 | input[2];
        uint32_t masked = value & golay_parity_check_matrix[k];
        int l; bool syndrome = 0;
        for (l = 0; l < 24; l++) syndrome ^= (masked >> l) & 1;
        checksum = (checksum << 1) | syndrome;
    }
    output[0] = input[0];
    output[1] = input[1] & 0b11110000;
    return checksum;
}
