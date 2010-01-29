/*
 * radioclient.cpp
 *
 *  Created on: Jan 26, 2010
 *      Author: derekja
 */

#include "radio/radio.h"
#include "radio/packet.h"
#include "Wprogram.h"
#include "radioclient.h"
#include "common.h"

uint8_t rx_addr[RADIO_ADDRESS_LENGTH] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x77 };
uint8_t tx_addr[RADIO_ADDRESS_LENGTH] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x88 };

radiopacket_t packet;

void radioInitSetup() {

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

}

void sendMsg(char msg[20]) {
	// give the packet type MESSAGE and populate the message type's data fields
	packet.type = MESSAGE;
	// The message type contains a return address.  In this demo the receiver doesn't
	// send anything back, so thie address field isn't used (but it's set here anyway).
	memcpy(packet.payload.message.address, rx_addr, RADIO_ADDRESS_LENGTH);
	packet.payload.message.messageid = 41;
	snprintf((char*) packet.payload.message.messagecontent, 20, msg);

	// Send the packet to the address specified with Radio_Set_Tx_Addr above.
	Radio_Transmit(&packet, RADIO_WAIT_FOR_TX);
}

void radio_rxhandler(uint8_t pipenumber) {
	Radio_Receive(&packet);
	if (packet.type == MESSAGE && packet.payload.message.messageid == 42) {
		GetSonarDistance((char *) packet.payload.message.messagecontent);
	}

}

