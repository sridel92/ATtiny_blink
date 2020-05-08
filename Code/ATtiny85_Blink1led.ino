/*
                  --------
-- reset ----  1  /      / 8 ---- Vcc
---Analog----- 2  /      / 7 ---- 
-------------- 3  /      / 6 ----
-------------- 4  /      / 5 ---- led0
                  --------
                  
*/


#include <avr/sleep.h> //Needed for sleep_mode
#include <avr/wdt.h> //Needed to enable/disable watch dog timer

const byte Led0 = 0;    // Pin 5 PWM
const byte Led1 = 1;    // 
const byte Led2 = 2;    // 
const byte Led3 = 3;    //
const byte Led4 = 4;    //
const byte VoltADC = A3;  // PIN 2
int VoltCell = 0; 

int watchdog_counter = 0;

//This runs each time the watch dog wakes us up from sleep
ISR(WDT_vect) {
   watchdog_counter++;
  //Don't do anything. This is just here so that we wake up.
}


void setup() 
{
    pinMode(Led0, OUTPUT);
 
    analogWrite(Led0, 50); // Output analog reading to dimmable LED
    delay(250);
    analogWrite(Led0, 0);
    delay(250);
    analogWrite(Led0, 50);
    delay(250);
    analogWrite(Led0, 0);
    delay(250);
    digitalWrite(Led0, LOW);

    set_sleep_mode(SLEEP_MODE_PWR_DOWN); //Power down everything, wake up from WDT
    sleep_enable();
} // end of setup

void loop() 
{
    ADCSRA &= ~(1<<ADEN); //Disable ADC, saves ~230uA
    setup_watchdog(9);     // 9=8sec    
    //Sets the watchdog timer to wake us up, but not reset
    //0=16ms, 1=32ms, 2=64ms, 3=128ms, 4=250ms, 5=500ms
    //6=1sec, 7=2sec, 8=4sec, 9=8sec
  
    sleep_mode(); //Go to sleep! Wake up 1sec later and check water

    if (watchdog_counter > 3){ // > 3 (= 4) so 4 x 9 sec about 36 secondes
      
      watchdog_counter = 0;
      ADCSRA |= (1<<ADEN); //Enable ADC
      VoltCell = analogRead(VoltADC);
        if (VoltCell < 250){

          for ( int i=0; i<190; i++){               // pwm
               analogWrite(Led0, i);
               delay(5);
          }
          for ( int i=190; i>1; i--){               // pwm
               analogWrite(Led0, i);
               delay(20);
          }
          
          analogWrite(Led0, 0);

        }
        
      analogWrite(Led0, 0);
      digitalWrite(Led0, LOW);
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3, LOW);
      digitalWrite(Led4, LOW);            
      }
    
} // end of loop


//Sets the watchdog timer to wake us up, but not reset
//0=16ms, 1=32ms, 2=64ms, 3=128ms, 4=250ms, 5=500ms
//6=1sec, 7=2sec, 8=4sec, 9=8sec
//From: http://interface.khm.de/index.php/lab/experiments/sleep_watchdog_battery/
void setup_watchdog(int timerPrescaler) {

  if (timerPrescaler > 9 ) timerPrescaler = 9; //Limit incoming amount to legal settings

  byte bb = timerPrescaler & 7; 
  if (timerPrescaler > 7) bb |= (1<<5); //Set the special 5th bit if necessary

  //This order of commands is important and cannot be combined
  MCUSR &= ~(1<<WDRF);           //Clear the watch dog reset
  WDTCR |= (1<<WDCE) | (1<<WDE); //Set WD_change enable, set WD enable
  WDTCR = bb;                    //Set new watchdog timeout value
  WDTCR |= _BV(WDIE);            //Set the interrupt enable, this will keep unit from resetting after each int
}
