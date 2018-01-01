#include "dy05.h"

DY05::DY05(int pin, unsigned int transmitCount) :
	mPin(pin),
	mTransmitCount(transmitCount)
{
	pinMode(mPin, OUTPUT);
}


void DY05::transmitBit(uint8_t b) {
	digitalWrite(mPin, HIGH);
	if(b) {
		delayMicroseconds(840);
	} else {
		delayMicroseconds(340);
	}
	digitalWrite(mPin, LOW);
	if(b) {
		delayMicroseconds(340);
	} else {
		delayMicroseconds(840);
	}
}

void DY05::transmitByte(uint8_t b) {
	for(uint8_t i = 0; i < 8; ++i) {
		transmitBit(b & 128);
		b <<= 1;
	}
}

void DY05::control(uint32_t address, DY05::Socket socket, DY05::Action action) {
	// Mask unneeded bits
	address &= 0xFFFFF;

	for(uint8_t i = 0; i < mTransmitCount; ++i) {
		delayMicroseconds(9600);

		transmitByte(address >> 12);
		transmitByte(address >> 4);

		uint8_t last_byte = (address << 4) & 0xF0;

		switch(socket) {
			case DY05::Socket1:
				transmitByte((last_byte | 0x0E) + action);
				break;
			case DY05::Socket2:
				transmitByte((last_byte | 0x0C) + action);
				break;
			case DY05::Socket3:
				transmitByte((last_byte | 0x0A) + action);
				break;
			case DY05::Socket4:
				transmitByte((last_byte | 0x06) + action);
				break;
			case AllSockets:
				transmitByte((last_byte | 0x01) + action);
				break;
		}

		transmitBit(0);
	}
}
