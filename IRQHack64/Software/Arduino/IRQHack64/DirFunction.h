#ifndef _DIR_FUNCTION_H
#define _DIR_FUNCTION_H

#include <SdFat.h>
#include <SdFatUtil.h>
#include "StringPrint.h"
#include "CharStack.h"

class DirFunction  {

 protected:
   SdFat*  sd;
   SdFile   file;   
   StringStack stack;
   
   unsigned int count;
   unsigned int currentIndex;
 public:
    void SetSd(SdFat* sdFat);
    void ToRoot();
    void GoBack();
    void Rewind();
    void Prepare();
    void ChangeDirectory(char * directory);
    unsigned int GetCount();
    int Iterate();
    StringPrint CurrentFileName;  
    int  IsDirectory;
    int IsFinished;
    int IsHidden;
    int InSubDir;
	
};
#endif _DIR_FUNCTION_H
