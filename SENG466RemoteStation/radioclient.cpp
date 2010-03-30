/*
 * Radio client API
 */

#include "radio.h"
#include "packet.h"
#include "Wprogram.h"

static uint8_t RemoteStationAddr[RADIO_ADDRESS_LENGTH] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x88 };
static uint8_t BaseStationAddr[RADIO_ADDRESS_LENGTH] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x77 };

static radiopacket_t packet;

void radioInitSetup() {
	/*
	 * Initialize the SPI connection, configure the I/O pins,
	 * and set the register defaults
	 */
	Radio_Init();

	/*
	 * Configure pipe 0 as a receiver.  Pipe 0 has to be enabled
	 * for the radio's link layer protocol to work.  This line
	 * shouldn't be necessary since pipe 0 is enabled by default,
	 * but it's nice to be explicit.
	 */
	Radio_Configure_Rx(RADIO_PIPE_0, RemoteStationAddr, ENABLE);

	/*
	 * Configure the radio's data rate (must match the other radio)
	 * and the broadcast power
	 */
	Radio_Configure(RADIO_2MBPS, RADIO_HIGHEST_POWER);

	/*
	 * set the address to send to, dangling prepositions be damned.
	 */
	Radio_Set_Tx_Addr(BaseStationAddr);

}

void radioSend() {
	/*
	 * Remote Station should only send message of type SENSORDATA to the
	 * Base Station.
	 */
	packet.type = SENSORDATA;

	packet.payload.hovercraftData.command = NONE;

//	memcpy(packet.payload.message.address, RemoteStationAddr, RADIO_ADDRESS_LENGTH);
//	snprintf((char*)packet.payload.message.messagecontent, 20, msg);

	// Send the packet to the address specified with Radio_Set_Tx_Addr above.
	Radio_Transmit(&packet, RADIO_WAIT_FOR_TX);
}

/*
 * To be completed.
 * This is the side where we decompose the content of the packet
 * and find out what command was sent from the Base Station
 */
void radio_rxhandler(uint8_t pipenumber)
{
}


