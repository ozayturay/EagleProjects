#include "IrqHack64.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include <avr/pgmspace.h>

unsigned int transferIndex;
unsigned int blockIndex;


#include "Transfer.h"

void InitTransfer() {
  transferIndex = 0;
  blockIndex = 0;
}

unsigned int GetTransferIndex() {
  return transferIndex;
}

unsigned int GetBlockIndex() {
  return blockIndex;
}

void setAddressPinsOutput() {
  #ifdef PORT_MANIPULATION  
  DDRD = DDRD | B11110000; // Set Pin 4..7 as outputs. A12, A13, A14, A15
  DDRC = DDRC | B00001111; // Set Analog pin 0..3 as outputs A8, A9, A10, A11
  #else
  for (int i=0;i<8;i++) {
    pinMode(addressPins[i], OUTPUT);
  }  
  #endif
}

void setPage(unsigned char value) {  
    #ifdef PORT_MANIPULATION
    PORTD = (PIND & 0x0F) | (value & 0xF0);
    PORTC = (PINC & 0xF0) | (value & 0x0F);
    #else
    unsigned char mask = 1;
    for (int i=0;i<8;i++) {
      digitalWrite(addressPins[i], value & mask);
      mask = mask<<1;
    }    
    #endif   
}

void ResetC64() {
  Serial.println(F("Resetting"));
  ResetLow();
  delayMicroseconds(100);  
  ResetHigh();
}

void TransmitByteSlow(unsigned char val) {
    setPage(val);
    NmiLow();
    delayMicroseconds(10); //Wait for interrupt to trigger
    NmiHigh();    
    delayMicroseconds(75);  //Wait for interrupt to finish it's job 
}

void TransmitByteBlockEnd(unsigned char val) {
    setPage(val);
    NmiLow();
    delayMicroseconds(6); //Wait for interrupt to trigger
    NmiHigh(); 
    delayMicroseconds(100);  //Wait for interrupt to finish it's job
}

void ResetIndex() {
  transferIndex = 0;
  blockIndex = 0;
}



