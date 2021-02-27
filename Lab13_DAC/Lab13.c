// Lab13.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// edX Lab 13 
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC
// Port A bits 5-2 have 4 piano keys

// Completed by Osama Salem with a score of 100% (simulation and real board)

#include "..//tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "DAC.h"
#include "TExaS.h"

// functions declaration

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

void delay(unsigned long msec);



int main(void){ // Real Lab13 
	int input,prevInput; 
	
  Sound_Init(); 				// initialize SysTick timer and DAC
  Piano_Init();
  EnableInterrupts();  // enable after all initialization are done
	TExaS_Init(SW_PIN_PA5432, DAC_PIN_PB3210,ScopeOn); // activate grader and set system clock to 80 MHz																							 // PortA used for piano keys, PortB used for DAC        
	
  while(1){ 

			input = Piano_In();
			if(input != prevInput){
				if(input == 0x01){		
						//EnableInterrupts();
						Sound_Tone(DO_PERIOD);
				}else if(input == 0x02){
						//EnableInterrupts();
						Sound_Tone(RE_PERIOD);
				}else if(input == 0x04){
						//EnableInterrupts();
						Sound_Tone(MI_PERIOD);
				}else if(input == 0x08){
					//EnableInterrupts();
					Sound_Tone(SOL_PERIOD);
				}else{
					Sound_Off();
				}
				delay(10);  //SWITCH DEBOUNCE
			}
		
		prevInput = input;
  }
}
            

// Inputs: Number of msec to delay
// Outputs: None
void delay(unsigned long msec){ 
  unsigned long count;
  while(msec > 0 ) {  // repeat while there are still delay
    count = 16000;    // about 1ms
    while (count > 0) { 
      count--;
    } // This while loop takes approximately 3 cycles
    msec--;
  }
}


