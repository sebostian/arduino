#include <avr/io.h>
#include <avr/interrupt.h>

#define SinDivisions (200)// Sub divisions of sisusoidal wave.

static int microMHz = 16; // Micro clock frequency
static int freq = 50;     // Sinusoidal frequency
static long int period;   // Period of PWM in clock cycles.
static unsigned int lookUp[SinDivisions];
static char theTCCR1A = 0b10000010; //varible for TCCR1A

void setup(){
  double temp; //Double varible for <math.h> functions.
  
  period = microMHz*1e6/freq/SinDivisions;// Period of PWM in clock cycles
  
  for(int i = 0; i < SinDivisions/2; i++){ // Generating the look up table.
    temp = sin(i*2*M_PI/SinDivisions)*period;
    lookUp[i] = (int)(temp+0.5);       // Round to integer.    

	
}

ISR(TIMER1_OVF_vect){
    static int num;
    static int delay1;
    static char trig;
    
    if(delay1 == 1){/*delay by one period because the high time loaded into OCR1A:B values are buffered but can be disconnected immediately by TCCR1A. */
      theTCCR1A ^= 0b10100000;// Toggle connect and disconnect of compare output A and B.
      TCCR1A = theTCCR1A;
      delay1 = 0;             // Reset delay1
    } else if(num >= SinDivisions/2){
      num = 0;                // Reset num
      delay1++;
      trig ^=0b00000001;
      digitalWrite(13,trig);
    }
    // change duty-cycle every period.
    OCR1A = lookUp[num];
    OCR1B = lookUp[num];
    num++;
}