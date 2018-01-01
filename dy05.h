#ifndef DY05_H
#define DY05_H

#include "Arduino.h"

/// Handles encoding and transmitting of the commands.
class DY05 {
	public:
		/// All possible sockets withing group.
		enum Socket {
			Socket1,
			Socket2,
			Socket3,
			Socket4,
			/// All sockets within group (with same address)
			AllSockets,
		};

		/// How state of the socket should be changed.
		enum Action {
			TurnOff = 0,
			TurnOn = 1,
		};

		/// pin is number of pin to which transmitter is connected.
		/// transmitCount specifies number of repeats.
		/// Warning: Setting transmitCount to too low will make the process unreliable!
		///
		/// Default value is 5, which seems reliable based on experience.
		DY05(int pin, unsigned int transmitCount = 5);

		/// Transmits command to the socket(s)
		/// Addresses are sent encoded as big endian (both byte-wise and bit-wise).
		/// Only addresses 0x00000-0xFFFFF are supported (other bits will be masked)
		void control(uint32_t address, Socket socket, Action action);
	private:
		void transmitBit(uint8_t b);
		void transmitByte(uint8_t b);

		int mPin;
		unsigned int mTransmitCount;
};

#endif
