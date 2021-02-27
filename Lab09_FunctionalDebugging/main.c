// ***** 0. Documentation Section *****
// main.c for Lab 9
// Runs on LM4F120/TM4C123
// In this lab we are learning functional debugging by dumping
//   recorded I/O data into a buffer
// January 15, 2016

// Lab 9
//      Jon Valvano and Ramesh Yerraballi

// Completed by Osama Salem with a score of 100% (simulation and real board)

// ***** Requirements *****

/* 
You will make three changes. 
First, make the LED flash at 10 Hz. In other words, make it turn on for 0.05 seconds, 
and then turn off for 0.05 seconds. 
Second, make the LED flash if either switch SW1 or SW2 is pressed 
(this means flash the LED if either PF4 or PF0 is 0). 
Third, record PortF bits 4,1,0 every time the input changes or the output changes. 
For example, if your system detects a change in either PF4 or PF0 input, 
record PortF bits 4,1,0. If your system causes a change in PF1, record PortF bits 4,1,0. 

If both PF4 and PF0 switch are not pressed, the PF1 output should be low.  
If either PF4 or PF0 switches is pressed, the output toggles at 10 Hz (±10%). 
Information collected in the Data array matches the I/O on PortF.
50 data points are collected only on a change in input or a change in output.
This means no adjacent elements in the array should be equal.

*/

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void PortF_Init(void);
void SysTick_Init(void);
void Delay(unsigned long time);
void Dump_Debug(void);
void LED_Flash(void);
void Led_Off(void);
unsigned short int switch_pressed(void);

// GLOBAL VARIABLES DECLARATION
unsigned long Time[50]; // first data point is wrong, the other 49 will be correct
unsigned long Data[50]; // you must leave the Data array defined exactly as it is
unsigned long Led; // red LED outupt
unsigned long last_input,current_input;

// ***** 3. Subroutines Section *****

void PortF_Init(void){ 
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}

// Initialize SysTick with busy wait running at bus clock.
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = 0x00FFFFFF;        // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it             
  NVIC_ST_CTRL_R = 0x00000005;          // enable SysTick with core clock
}

// Subroutine to delay in units of 0.05s
// Inputs: Number of 0.05s to delay
// Outputs: None

// Delay function which delays time*50 milliseconds assuming 10 MHz clock
// The following C function can be used to delay. 
void Delay(unsigned long time1ms)
{static unsigned int i;
	
  while(time1ms > 0){
    i = 16000; 
    while(i > 0)
      i--;
    time1ms --;
  }
}

void Dump_Debug(void)
{static unsigned long i ;
	if (i < 50)
	{
			current_input = NVIC_ST_CURRENT_R;
			Time[i] = (last_input - current_input)&0x00FFFFFF;  // 24-bit time difference
			Data[i] = GPIO_PORTF_DATA_R & 0x13; // record PF 0 , 1 , 4
			last_input = current_input;
			++i;
		
	}
}


void LED_Flash(void){
    GPIO_PORTF_DATA_R ^= 0x02;            // red LED Toggle
		Dump_Debug();
		Delay(1);
}

void LED_Off(void){
	GPIO_PORTF_DATA_R &= ~0x02;
}

unsigned short int switch_pressed(void){
	unsigned long SW1; // input from PF4
	unsigned long SW2; // input from PF0
	SW1 = GPIO_PORTF_DATA_R&0x10; 
	SW2 = GPIO_PORTF_DATA_R&0x01;
	
	if((SW1 == 0x00) || (SW2 == 0x00))
		return 1;
	else return 0;
}

int main(void){  
	TExaS_Init(SW_PIN_PF40, LED_PIN_PF1);  // activate grader and set system clock to 80 MHz
  PortF_Init();   // initialize PF1 to output
  SysTick_Init(); // initialize SysTick, runs at 16 MHz
  last_input   = NVIC_ST_CURRENT_R;
  EnableInterrupts();           // enable interrupts for the grader
  
	while(1)
	{
		if (switch_pressed()){
			LED_Flash();
		}
		else LED_Off();
  }
}


// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06
