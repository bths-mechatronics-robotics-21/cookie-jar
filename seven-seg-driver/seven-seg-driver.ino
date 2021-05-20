/*
 * seven-seg-driver -- quad seven segment display driver over I2C
 * Copyright (C) 2021  Jacob Koziej <jacobkoziej@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/*
 * Wiring:
 * =======
 *
 * PD0 - segment a
 * PD1 - segment b
 * PD2 - segment c
 * PD3 - segment d
 * PD4 - segment e
 * PD5 - segment f
 * PD6 - segment g
 * PD7 - decimal point
 *
 * PB0 - digit 1
 * PB1 - digit 2
 * PB2 - digit 3
 * PB3 - digit 4
 */

#include <Wire.h>


const uint8_t SEG_LOOKUP[] = {
	0b00111111,  // 0
	0b00000110,  // 1
	0b01011011,  // 2
	0b01001111,  // 3
	0b01100110,  // 4
	0b01101101,  // 5
	0b01111101,  // 6
	0b00000111,  // 7
	0b01111111,  // 8
	0b01100111   // 9
};


void setup()
{
	DDRD  = 0xFF;
	DDRB |= 0x0F;

	Wire.begin('d');  // 0x64
}

void loop()
{
}
