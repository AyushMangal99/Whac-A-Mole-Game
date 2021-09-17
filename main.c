/* Whac-A-Mole Game Main Source File

ESD Course Project
 Developer: Gopal Agarwal & Ayush mangal
 Created: April 17, 2021

Hardware Resources:
 - TM4C123GH6PM Board
 - Switches and LED's

*/

#include "TM4C123GH6PM.h"       // Standard library for TM4C123GH6PM                  
#include "stdlib.h"             // Standard library for C used to access rand() function              
#include "my_header_file.h"     // User generated library

// Prototypes for user-defined functions
void Check_switch(unsigned int value);         
void Random_LED_On(void);
void next_round(void);

// Declared as global variables
unsigned int COUNT = 800000;
unsigned int STATUS = 0;         

// This function is  used to generate any random value in between 0-7 and the corresponding LED will turn ON 
void Random_LED_On(void)
{
       unsigned int index = rand() % 4;            // Generating a random value from 0-7
       unsigned int value = dec_to_hex(index);     // Converting random generated decimal value into hexadecimal using dec_to_hex user defined function
       
       GPIOE -> DATA = value;           // Make random LED ON     
       Check_switch(value);                    
}

// This function is used to check the input response of the user
void Check_switch(unsigned int value)         
{
  while(COUNT--)                        // Polling technique used to check input response
  {
    if(!(GPIOB->DATA & value ) )       // If correct switch pressed             
    {
      STATUS = 1;                                                     
      GPIOE -> DATA = 0x00;             // Make random LED OFF                       
      GPIOF -> DATA = 0X08;             // Make Green LED ON to show user win       
    }
  }
  
  COUNT = 800000;
  next_round();
}

// This function is used to call for next round
void next_round(void)                      
{    
      if(STATUS == 0)                   // If user presses wrong switch or run out of time
      {
        GPIOE -> DATA = 0x00;           // Make Random LED OFF
        GPIOF -> DATA = 0X02;           // Make RED LED ON to show user lose
      } 
     
      delay(1999999);                   // Approx 1sec delay given for next round
      GPIOF -> DATA = 0X00;             // Make RED LED OFF
      STATUS = 0;                      
      Random_LED_On();
}

int main()                                      
{  
    // RCGCGPIO Register Enables Clock.   Refer page:- 340
        SYSCTL -> RCGCGPIO = 0x32;            // 0b0011 0010 Ports B, E, F clock Enabled
 
  // Port E is used to connect LED matrix.
      // DIR Register sets pins as I/O,  0->input and 1->output,   Refer page:- 663
          GPIOE -> DIR = 0xFF;            // 0b1111 1111 all pins are set as output
          
      // DEN Register enables pins digitally  Refer page:- 682    
          GPIOE -> DEN = 0xFF;            // 0b1111 1111 all pins are digitally enabled                 
   
  // Port B is used to connect switch matrix.
      // LOCK register is used to unlock the pins of port E.   Refer page:- 684
          GPIOB -> LOCK       =0x4C4F434B;             
          
      // Commit Register is used to determine which bits of the GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN registers are committed.  Refer Page:- 685  
          GPIOB -> CR         =0xFF;              // 0b1111 1111  all 7 bits are unlocked and can be programmed.

      // PUR register enables internal pull up resistor  Refer page:- 677     
          GPIOB -> PUR = 0xFF;            //0b1111 1111  pull up resistor enabled on all pins
          
      // DIR Register sets pins as I/O,  0->input and 1->output,   Refer page:- 663    
          GPIOB -> DIR = 0x00;            // 0b0000 0000 all pins are set as input
          
      // DEN Register enables pins digitally  Refer page:- 682  
          GPIOB -> DEN = 0xFF;            // 0b1111 1111 all pins are digitally enabled
       
  // Port F is used to show the output
      // DIR Register sets pins as I/O,  0->input and 1->output,   Refer page:- 663    
          GPIOF -> DIR = 0x0A;            //0b0000 1010 PF.1 and PF.3 pins are set as output
          
      // DEN Register enables pins digitally  Refer page:- 682    
          GPIOF -> DEN = 0x0A;            //0b0000 1010  PF.1 and PF.3 pins are digitally enabled
   
    while(1)
    {
       Random_LED_On();
    }
}