#ifndef _STRING_PRINT_H
#define _STRING_PRINT_H

#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif

class StringPrint : public Print {
	
 public:
 	int index;
        char value[128];
#if ARDUINO >= 100
  virtual size_t write(uint8_t);
#else
  virtual void   write(uint8_t);
#endif

	void ResetIndex();
        void Copy(char * str);
	
};
#endif _STRING_PRINT_H

