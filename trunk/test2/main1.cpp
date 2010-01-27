/*
 * main.cpp
 *
 *  Created on: 9-Jan-2010
 *      Author: nrqm
 *
 * This example program sets up the radio, then builds a data packet and transmits it.
 *   The program waits for the packet to be transmitted, then turns on the LED.  The
 *   return value of Radio_Transmit isn't checked here; it will tell you if the
 *   transmission succeeded or failed, which might be useful in your projects (note:
 *   the function doesn't have the right return type, see the RADIO_TX_STATUS enumeration
 *   in radio.h for the correct values).
 *
 * The radio should be connected as follows:
 *
 * Radio		Seeeduino
 *  Vcc				48
 *   CE				8
 *  CSN				7
 *  SCK				52
 * MOSI				51
 * MISO				50
 *  IRQ				2
 *  GND				GND
 *
 * If you don't like the CE and CSN pins way off on the other side of the board then
 *  you can change them to another digital I/O port (they're defined at the top of
 *  radio.cpp).  The IRQ pin can be moved to another interrupt pin (see online docs
 *  for attachInterrupt function; also the interrupt number is hardcoded in the driver
 *  because I'm irresponsible).
 */

#include "radio/radio.h"
#include "radio/packet.h"
#include "WProgram.h"

extern "C" void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void) {}

uint8_t rx_addr[RADIO_ADDRESS_LENGTH] = { 0x12, 0x34, 0x56, 0x78, 0x90 };
uint8_t tx_addr[RADIO_ADDRESS_LENGTH] = { 0x98, 0x76, 0x54, 0x32, 0x10 };

radiopacket_t packet;

int main()
{
	init();
Serial.begin(57600);

	// Blink the LED once to indicate that the program has started (this step is useless).
	pinMode(13, OUTPUT);
	pinMode(48, OUTPUT);
	digitalWrite(13, HIGH);
	delay(1000);
	digitalWrite(13, LOW);
	delay(1000);

	digitalWrite(48, LOW);
	delay(50);
	digitalWrite(48, HIGH);

	// Initialize the SPI connection, configure the I/O pins, and set the register defaults
	Radio_Init();

	// Configure pipe 0 as a receiver.  Pipe 0 has to be enabled for the radio's link layer
	// protocol to work.  This line shouldn't be necessary since pipe 0 is enabled by
	// default, but it's nice to be explicit.
	Radio_Configure_Rx(RADIO_PIPE_0, rx_addr, ENABLE);
	// Configure the radio's data rate (must match the other radio) and the broadcast power
	Radio_Configure(RADIO_2MBPS, RADIO_HIGHEST_POWER);

	// set the address to send to, dangling prepositions be damned.
	Radio_Set_Tx_Addr(tx_addr);

	// give the packet type MESSAGE and populate the message type's data fields
	packet.type = MESSAGE;
	// The message type contains a return address.  In this demo the receiver doesn't
	// send anything back, so thie address field isn't used (but it's set here anyway).
	memcpy(packet.payload.message.address, rx_addr, RADIO_ADDRESS_LENGTH);
	packet.payload.message.messageid = 41;
	snprintf((char*)packet.payload.message.messagecontent, 20, "xazzy");

	// Send the packet to the address specified with Radio_Set_Tx_Addr above.
	Radio_Transmit(&packet, RADIO_WAIT_FOR_TX);

	// Indicate that the transmit function returned.  If the LED doesn't light up then the
	// Seeeduino probably didn't get the interrupt from the radio for some reason.
	digitalWrite(13, HIGH);

	// main() should never return, even if the program has completed.
	for (;;);

	return 0;
}

void radio_rxhandler(uint8_t pipenumber)
{
	// this station doesn't receive anything.
}
