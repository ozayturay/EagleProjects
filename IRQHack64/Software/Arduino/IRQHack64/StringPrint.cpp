#include "StringPrint.h"

#if ARDUINO >= 100
size_t StringPrint::write(uint8_t c) {
#else
void StringPrint::write(uint8_t c) {
#endif
      if (index<127) {
        value[index] = c;
        value[index+1] = 0x00;
        index++;
      }
#if ARDUINO >= 100
  return 1;
#endif
}

void StringPrint::ResetIndex(void) {
  
	index = 0;
}

void StringPrint::Copy(char * str) {
  strcpy(value, str);
  index = strlen(str);
}

