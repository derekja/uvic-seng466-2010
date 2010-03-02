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
uint8_t tx_addr[RADIO_ADDRESS_LENGTH] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x77 };

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
	unsigned int dirVal = 0;
	unsigned int fanVal = 0;
	unsigned int fanVal1 = 0;
	int motor1Pin1 = 11;
	int motor1Pin2 = 12;
	int motor2Pin1 = 9;
	int motor2Pin2 = 10;
	int dirPos = 0;
	int fanPos = 0;
	int d = 0; // initial var for which motor pin


	//Serial.print("woohoo, a packet!");
	// Copy the received packet from the radio to the local data structure
	Radio_Receive(&packet);
	if (packet.type == MESSAGE && packet.payload.message.messageid == 41)
	{



	sscanf((char*)&packet.payload.message.messagecontent, "%d/%d", &dirPos, &fanPos);
	//itoa(packet.payload.message.messagecontent, &buf, 10);
	/*
	Serial.print("fullmsg: ");
	Serial.print((char*)&packet.payload.message.messagecontent);
	Serial.println();
	Serial.print("recmsg: ");
	Serial.print(servoPos);
	Serial.print("  ");
	Serial.print(fanPos);
	Serial.println();
	*/


	//set fan position
	 if (fanPos<750) {
		fanVal = map(fanPos,120,750,0,255);
		 d = 1;
		 fanVal = 255 - fanVal;
		 //s = 255-(fanPos/2);
	 }
	 if (fanPos>800) {
		fanVal = map(fanPos,800,1023,0,255);\
		 d = 2;
		 //s = fanPos/4;
	 }

	 fanVal1 = fanVal;

	 if (dirPos<425) {
		dirVal = map(dirPos,0,450,1000, 0);
		fanVal = (fanVal * dirVal)/1000;

	 }
	 if (dirPos>500) {
		dirVal = map(dirPos,500,1023,1000, 0);
		fanVal1 = (fanVal1 * dirVal)/1000;
	 }

	 Serial.print("fanPos:  ");
	 Serial.print(fanPos);
	 Serial.println();
	 Serial.print("dirPos:  ");
	 Serial.print(dirPos);
	 Serial.println();
	 Serial.print("dirVal:  ");
	 Serial.print(dirVal);
	 Serial.println();

	 switch (d) {
	 case 1 :
		 analogWrite(motor1Pin1, fanVal);
		 analogWrite(motor1Pin2, 0);
		 analogWrite(motor2Pin1, fanVal1);
		 analogWrite(motor2Pin2, 0);

		 break;

	 case 2 :
		 analogWrite(motor1Pin1, 0);
		 analogWrite(motor1Pin2, fanVal);
		 analogWrite(motor2Pin1, 0);
		 analogWrite(motor2Pin2, fanVal1);
		 break;

	 default :
		 analogWrite(motor1Pin1, 0);
		 analogWrite(motor1Pin2, 0);
		 analogWrite(motor2Pin1, 0);
		 analogWrite(motor2Pin2, 0);
	 }


	}

}


