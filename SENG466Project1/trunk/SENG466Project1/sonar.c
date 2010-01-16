#include <avr/io.h>
#include "sonar.h"

void sonar_init() {
	TCCR3B &= ~(_BV(CS32) | _BV(CS30));
	TCCR3B |= _BV(CS31);
	TCCR3B |= _BV(ICNC3);

}
