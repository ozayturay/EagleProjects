#include "CharStack.h"
#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif

void CharStack::Push(char value) {
  if (top>0) {
    charBuffer[top] = value;
    top--;
  }
}

char CharStack::Pop() {
   if (top<STACK_TOP) {
     top++;
     return charBuffer[top-1];
   }
}

char CharStack::Current() {
  return charBuffer[top-1];
}


void StringStack::PushString(char * value) {
  //Determine end of string
  int length = 0;  
  
  while(value[length]!=0) length++;
  length = length+1; //Reserve space for null character
  
  for (int i=length-1;i>=0;i--) {
    CharStack::Push(value[i]);
  }  
  
  itemArray[itemCount] = top+1;
  
  itemCount++;
  //Serial.print("Top : "); Serial.println(top);

}

char * StringStack::PopString() {
   int topIndex = top+1;
   for (int i = topIndex;i<=STACK_TOP;i++) {
     CharStack::Pop();     
     if (charBuffer[i]==0) {
        break;      
     }
   } 
   
   itemCount--;
   
   //Serial.print("Top : "); Serial.println(top);

   return &charBuffer[topIndex];
}

char * StringStack::CurrentString() {
  return &charBuffer[top];
}

char * StringStack::LookAt(int item) {
  int itemTop = itemArray[item];
  return &charBuffer[itemTop];
}

int StringStack::GetCount() {
  return itemCount;
}  
