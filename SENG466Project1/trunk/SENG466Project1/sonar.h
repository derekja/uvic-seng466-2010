#ifndef __SONAR_H__
#define __SONAR_H__

void sonarInit();
void sonarEcho();
void sonarMeasureDistance();

#define SET_RISING_EDGE()       (TCCR3B |= _BV(ICES3))
#define SET_FALLING_EDGE()      (TCCR3B &= ~(_BV(ICES3)))
#define IS_RISING_EDGE()        (TCCR3B & _BV(ICES3))
#define IS_FALLING_EDGE()       ~(TCCR3B & _BV(ICES3))
#define SET_IC_ENABLE()         (TIMSK3 |= _BV(ICIE3))
#define SET_IC_DISABLE()        (TIMSK3 &= ~_BV(ICIE3))
#define CLEAR_IC_FLAG()         (TIFR3 |= _BV(ICF3))

#endif
