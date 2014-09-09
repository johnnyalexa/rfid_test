/*
 * main.h
 *
 * Created: 9/9/2014 10:42:54 AM
 *  Author: ionut.alexa
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "drivers.h"
#include <avr/io.h>
#include <string.h>
#include <stdio.h>


#define F_CPU 8000000
#include <util/delay.h>



typedef  uint8_t PinName;

#define MF_PORT		PORTB
#define MF_RESET    PB1 //D8
#define SPI_MOSI	PB3
#define SPI_MISO	PB4
#define SPI_SCK		PB5
#define SPI_CS		PB0

#endif /* MAIN_H_ */