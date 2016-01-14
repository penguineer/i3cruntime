/*
 * CRC Implementation and Test Runtime
 *
 * Author: Stefan Haun <tux@netz39.de>
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * See http://users.ece.cmu.edu/~koopman/crc/ for details.
 *
 * The CRC polynomial is
 * 	0x12 => x^5 + x^2 + 1
 * 	which is 0x25 in explicit +1 notation,
 * 	then moved to the beginning of the byte
 */
#define POLYNOMIAL (0x25 << 2)

/**
 * Calculate a 5-bit CRC based on the generator polynom 0x12 (see definition of POLYNOMIAL).
 *
 * The result is in the first 5 bits of the returned byte and must be shifted for final evaluation!
 *
 * http://www.barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code
 *
 * Initial: 0x00
 * 	I3C check messages always start with an I2C-address, which is never 0
 */
uint8_t CRC5x12(uint8_t const crc, uint8_t const data)
{
    uint8_t remainder = crc;

    remainder ^= data;

    for (uint8_t bit = 8; bit; bit--) {
        // if uppermost bit is '1'
        if (remainder & 0x80)
            remainder = remainder ^ POLYNOMIAL;

        // next bit
        remainder <<= 1;
    }

    return remainder;
}

int main()
{
    uint8_t crc = 0;

    /*
     * Complies with
     * https://ghsi.de/CRC/index.php?Polynom=100101&Message=AFFEaffe
     */
    crc = CRC5x12(crc, 0xaf);
    crc = CRC5x12(crc, 0xfe);
    crc = CRC5x12(crc, 0xaf);
    crc = CRC5x12(crc, 0xfe);
    printf("CRC of 0xaffeaffe is 0x%x.\n", crc >> 3);

    /*
     * Complies with
     * https://ghsi.de/CRC/index.php?Polynom=100101&Message=12345678
     */
    crc = 0;
    crc = CRC5x12(crc, 0x12);
    crc = CRC5x12(crc, 0x34);
    crc = CRC5x12(crc, 0x56);
    crc = CRC5x12(crc, 0x78);
    printf("CRC of 0x12345678 is 0x%x.\n", crc >> 3);


    return 0;
}
