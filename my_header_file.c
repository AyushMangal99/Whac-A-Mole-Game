#include "my_header_file.h"                       

// Converting decimal value into hexadecimal value
  unsigned int dec_to_hex(unsigned int index)
  {
    unsigned int value;
    switch(index){                                
              case 0: value=0x01;                 //0b0000 0001 0th LED will glow
                      break;
              case 1: value=0x02;                 //0b0000 0010 1st LED will glow
                      break;
              case 2: value=0x04;                 //0b0000 0100 2nd LED will glow
                      break;
              case 3: value=0x08;                 //0b0000 1000 3rd LED will glow
                      break;
              case 4: value=0x10;                 //0b0001 0000 4th LED will glow
                      break;
              case 5: value=0x20;                 //0b0010 0000 5th LED will glow
                      break;
              case 6: value=0x40;                 //0b0100 0000 6th LED will glow
                      break;
              case 7: value=0x80;                 //0b1000 0000 7th LED will glow
                      break;
          }
          return value;
  }
// Function used to generate delay
void delay(int iteration)
{
  int volatile counter;
  counter = 0;
  while(counter < iteration)
  ++counter;
}
