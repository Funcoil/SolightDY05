#include <dy05.h>

// Setup transmitter connected to pin 11.
DY05 transmitter(11);

void setup() {
	// We don't need to setup anything here
}

void loop() {
	// Turns on socket 1 in group with address 42.
	// Note: there are 4 sockets in group.
	// You can also turn on/off each socket in group if you pass DY05::AllSockets
	transmitter.control(42, DY05::Socket1, DY05::TurnOn);

	// Wait a second
	delay(1000);

	// Turn off the socket
	transmitter.control(42, DY05::Socket1, DY05::TurnOff);

	// Wait a second
	delay(1000);
}
