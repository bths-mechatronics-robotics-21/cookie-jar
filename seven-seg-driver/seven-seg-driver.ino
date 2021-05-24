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


#define REFRESH_RATE 60.0

#define SECOND_US    1000000
#define SEG_CNT      8
#define DIG_CNT      4
#define SEG_DELAY    ((int) (SECOND_US / (SEG_CNT * DIG_CNT) / REFRESH_RATE))


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
	0b01100111,  // 9
	0b01110111,  // A
	0b00111001,  // C
	0b01111001,  // E
	0b01110001,  // F
	0b01110110,  // H
	0b00000110,  // I
	0b00001110,  // J
	0b00111000,  // L
	0b00111111,  // O
	0b01110011,  // P
	0b01101101,  // S
	0b00111110,  // U
	0b01111100,  // b
	0b01011000,  // c
	0b01011110,  // d
	0b01101111,  // g
	0b01110100,  // h
	0b00000100,  // i
	0b00000110,  // l
	0b01011100,  // o
	0b01010000,  // r
	0b01111000,  // t
	0b00011100,  // u
	0b01101110   // y
};

volatile uint8_t ssd_buff[4];


void setup()
{
	DDRD  = 0xFF;
	DDRB |= 0x0F;

	memset(ssd_buff, 0, sizeof(ssd_buff));

	Wire.begin('d');  // 0x64
}

void loop()
{
}
