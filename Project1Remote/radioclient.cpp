/*
 * radioclient.cpp
 *
 *  Created on: Jan 26, 2010
 *      Author: derekja
 */

#include "radio/radio.h"
#include "radio/packet.h"
#include "Wprogram.h"
#include "servo.h"

uint8_t rx_addr[RADIO_ADDRESS_LENGTH] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x88 };
uint8_t tx_addr[RADIO_ADDRESS_LENGTH] = { 0x98, 0x76, 0x54, 0x32, 0x10 };

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
	// send anything back, so this address field isn't used (but it's set here anyway).
	memcpy(packet.payload.message.address, rx_addr, RADIO_ADDRESS_LENGTH);
	packet.payload.message.messageid = 42;
	snprintf((char*)packet.payload.message.messagecontent, 20, msg);

	// Send the packet to the address specified with Radio_Set_Tx_Addr above.
	Radio_Transmit(&packet, RADIO_WAIT_FOR_TX);
}

void radio_rxhandler(uint8_t pipenumber)
{
	unsigned int servoVal = 0; //hold servo value in microseconds
	int motor1Pin1 = 11;
	int motor1Pin2 = 12;
	int servoPos = 0;
	int fanPos = 0;
	int d = 0; // initial var for which motor pin
	int s = 0; // initial var for speed
	int v = 0; //hold value of pot
	char buf(20);

	//Serial.print("woohoo, a packet!");
	// Copy the received packet from the radio to the local data structure
	Radio_Receive(&packet);
	if (packet.type == MESSAGE && packet.payload.message.messageid == 41)
	{



	sscanf((char*)&packet.payload.message.messagecontent, "%d/%d", &servoPos, &fanPos);
	//itoa(packet.payload.message.messagecontent, &buf, 10);
	Serial.print("fullmsg: ");
	Serial.print((char*)&packet.payload.message.messagecontent);
	Serial.println();
	Serial.print("recmsg: ");
	Serial.print(servoPos);
	Serial.print("  ");
	Serial.print(fanPos);
	Serial.println();

	servoVal = map(v,0,1024,1800, 4200);
	v = v/4;
	 if (v<80) {
		 d = 1;
		 s = 255-(v*2);
	 }
	 if (v>110) {
		 d = 2;
		 s = v;
	 }
	 switch (d) {
	 case 1 :
		 analogWrite(motor1Pin1, s);
		 analogWrite(motor1Pin2, 0);
		 break;

	 case 2 :
		 analogWrite(motor1Pin1, 0);
		 analogWrite(motor1Pin2, s);
		 break;

	 default :
		 analogWrite(motor1Pin1, 0);
		 analogWrite(motor1Pin2, 0);
		 servoVal = 3000;
	 }
	servoSet(servoVal);
	}

}


