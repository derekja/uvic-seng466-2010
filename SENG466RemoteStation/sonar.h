#ifndef SONAR_H_
#define SONAR_H_

void sonarInit();
void sonarEcho();
double sonarMeasureDistance();

/*
 * Macros to change Timer 3 settings when used for
 * input capture and measure the pulse width of
 * the PW pin from the sonar
 */
#define SET_RISING_EDGE()       (TCCR3B |= _BV(ICES3))
#define SET_FALLING_EDGE()      (TCCR3B &= ~(_BV(ICES3)))
#define IS_RISING_EDGE()        (TCCR3B & _BV(ICES3))
#define IS_FALLING_EDGE()       ~(TCCR3B & _BV(ICES3))
#define SET_IC_ENABLE()         (TIMSK3 |= _BV(ICIE3))
#define SET_IC_DISABLE()        (TIMSK3 &= ~_BV(ICIE3))
#define CLEAR_IC_FLAG()         (TIFR3 |= _BV(ICF3))

#endif /* SONAR_H_ */