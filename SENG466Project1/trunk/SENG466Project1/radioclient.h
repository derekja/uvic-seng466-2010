/*
 * radioclient.h
 *
 *  Created on: Jan 26, 2010
 *      Author: derekja
 */

#ifndef RADIOCLIENT_H_
#define RADIOCLIENT_H_

void radioInitSetup();
void sendMsg(char msg[20]);
void radio_rxhandler(uint8_t pipenumber);

#endif /* RADIOCLIENT_H_ */
