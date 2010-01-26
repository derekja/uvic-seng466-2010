
#include <avr/io.h>
#include <avr/interrupt.h>
#include "servotmp.h"
//#include "WProgram.h"

void servoInit() {

	unsigned char sreg;

    TCCR4A = 0b000001;    // COM4B1, COM4B0, COM4C1, COM4C0, WGM41, and WGM40
	//set OCR4A to top (just using an arbitrary value for now)
    sreg = SREG;
    cli();
    OCR4A = 0x09FF;
    SREG = sreg;

	//set ICR4 to top (just using an arbitrary value for now)
    sreg = SREG;
    cli();
    ICR4 = 0x06FC;
    SREG = sreg;

    //put a comparator value in OCR4B (again, arbitrary for now)
    sreg = SREG;
    cli();
    OCR4B = 0x0352;
    SREG = sreg;

    //set registers - mode 15, fast PWM, non-inverted
	//TCCR4A |= (_BV(WGM40) | _BV(WGM41));
	//TCCR4A &= ~(_BV(COM4B0) | _BV(COM4B1) );
	//TCCR4B |= ( _BV(WGM42) |  _BV(WGM43));
	//TCCR4B &= ~();

	//set a prescale of 8 for now
	//TCCR4B |= ( _BV(CS40));
	//TCCR4B &= ~(_BV(CS42) | _BV(CS41));

    TCCR4A = 0b000001;    // COM4B1, COM4B0, COM4C1, COM4C0, WGM41, and WGM40
    TCCR4A = 0b100011;    // COM4B1, COM4B0, COM4C1, COM4C0, WGM41, and WGM40
    TCCR4B = 0b11001;     // WGM43, WGM42, CD42, CS41, and CS40

    //enable interrupts
	//TIMSK4 |= (_BV(OCIE4B));

	// set PWM7 to an output pin (OC4B), PH4
	DDRH |= (_BV(DDH4));

	//Serial.print("servoInit done");
	//Serial.println();
	return;
}

void servoSet(unsigned int value) {


	unsigned int tmp;
	unsigned int tmp1 = 0;
	unsigned char sreg;

	sreg = SREG;
	cli();
	//OCR4B = value;
	tmp = OCR4B;
	tmp1 = ICR4;
	SREG = sreg;

	//Serial.print("servoSet done: ");
	//Serial.print(tmp);
	//Serial.print("  ");
	//Serial.print(tmp1);
	//Serial.println();
	return;
}
