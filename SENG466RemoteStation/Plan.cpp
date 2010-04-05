/*
 * Plan.cpp
 *
 *  Created on: Mar 25, 2010
 *      Author: jensweber
 */

#include "Plan.h"
#include "radio/radio.h"
#include "radio/packet.h"

uint8_t rx_addr[RADIO_ADDRESS_LENGTH] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x88 };
uint8_t tx_addr[RADIO_ADDRESS_LENGTH] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x77 };

radiopacket_t packet;

extern int dirPos = 0;
extern int fanPos = 0;
extern int command = 0;

void plan()
{
	while( true )
	{
		//receive the packet
		Radio_Receive(&packet);

		//process the packet
		if (packet.type == MESSAGE && packet.payload.message.messageid == 41)
		{
			sscanf((char*)&packet.payload.message.messagecontent, "%d/%d", &dirPos, &fanPos);
		}

		//wait for next call
		task_next();
	}
}
