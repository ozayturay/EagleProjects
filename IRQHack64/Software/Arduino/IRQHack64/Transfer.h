#ifndef _TRANSFER_

#define _TRANSFER_

#include "Arduino.h"
#include "HardwareSerial.h"
#include "TransferConstants.h"

#define PORT_MANIPULATION
#define OPENCOLLECTORSTYLE

extern unsigned int transferIndex;
extern unsigned int blockIndex;

unsigned int GetTransferIndex();
unsigned int GetBlockIndex();
void setAddressPinsOutput();
void setPage(unsigned char value);
void ResetC64();
void TransmitByteSlow(unsigned char val);
void TransmitByteBlockEnd(unsigned char val);
void ResetIndex();

inline void ResetLow() {
    #ifdef OPENCOLLECTORSTYLE
     PORTB &= ~_BV(PB1); // turn off internal resistor 
     DDRB |= _BV(PB1); // set to output       
    #else
      //digitalWrite(RESET, LOW);    
      PORTB &= ~_BV (PB1);
    #endif  
}

inline void ResetHigh() {
    #ifdef OPENCOLLECTORSTYLE
      DDRB &= ~_BV(PB1); //switch to input while port is low. 
      PORTB |= _BV(PB1); //turn on internal resistor to Vcc 
    #else
      //digitalWrite(RESET, HIGH); 
      PORTB |= _BV (PB1);
    #endif  
}

inline void ResetSetup() {
    #ifdef OPENCOLLECTORSTYLE
      ResetHigh();
    #else  
      pinMode(RESET, OUTPUT);
      digitalWrite(RESET, HIGH);
    #endif  
}


inline void NmiLow() {
    #ifdef OPENCOLLECTORSTYLE
     PORTB &= ~_BV(PB0); // turn off internal resistor 
     DDRB |= _BV(PB0); // set to output       
    #else
      //digitalWrite(NMI, LOW);    
      PORTB &= ~_BV (PB0);
    #endif
}

inline void NmiHigh() {
    #ifdef OPENCOLLECTORSTYLE
      DDRB &= ~_BV(PB0); //switch to input while port is low. 
      PORTB |= _BV(PB0); //turn on internal resistor to Vcc 
    #else
      //digitalWrite(NMI, HIGH); 
      PORTB |= _BV (PB0);
    #endif
}

inline void NmiSetup() {
    #ifdef OPENCOLLECTORSTYLE
      NmiHigh();
    #else  
      pinMode(NMI, OUTPUT);
      digitalWrite(NMI, HIGH);
    #endif  
}

inline void  TransmitByteFast(unsigned char val) {
    #ifdef PORT_MANIPULATION
    PORTD = (PIND & 0x0F) | (val & 0xF0);
    PORTC = (PINC & 0xF0) | (val & 0x0F);
    #else
    unsigned char mask = 1;
    for (int i=0;i<8;i++) {
      digitalWrite(addressPins[i], val & mask);
      mask = mask<<1;
    }    
    #endif 


    NmiLow();
    delayMicroseconds(5); //Wait for interrupt to trigger
    NmiHigh();   
    delayMicroseconds(31);  //Wait for interrupt to finish it's job  
}

inline void  TransmitByteFastNew(unsigned char val) 
{ 
    #ifdef PORT_MANIPULATION
    PORTD = (PIND & 0x0F) | (val & 0xF0);
    PORTC = (PINC & 0xF0) | (val & 0x0F);
    #else
    unsigned char mask = 1;
    for (int i=0;i<8;i++) {
      digitalWrite(addressPins[i], val & mask);
      mask = mask<<1;
    }    
    #endif 

   if (transferIndex==255) {
      NmiLow();      
      delayMicroseconds(5); //Wait for interrupt to trigger
      NmiHigh();      
      delayMicroseconds(60);  //Wait for interrupt to finish it's job
      transferIndex = 0;
      blockIndex++;
   } else {
     
    NmiLow();     
    delayMicroseconds(5); //Wait for interrupt to trigger    
    NmiHigh();
    delayMicroseconds(31);  //Wait for interrupt to finish it's job     
    transferIndex++;
   }      
}

inline void EnableCartridge() {
  digitalWrite(EXROM, LOW);
}

inline void DisableCartridge() {
  digitalWrite(EXROM, HIGH);
}

#endif
