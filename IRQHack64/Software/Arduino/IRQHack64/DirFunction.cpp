#include <SdFat.h>
#include <SdFatUtil.h>
#include "Arduino.h"
#include "DirFunction.h"
#include "CharStack.h"


void DirFunction::SetSd(SdFat* sdFat) {
  sd = sdFat;
}

void DirFunction::GoBack() {
  count = 0;
  currentIndex = 0;
  IsFinished = 0;
  IsDirectory = 0;
  InSubDir = 0;

  if (!sd->chdir()) {    
    Serial.println("chdir(\) failed");
    sd->errorHalt();
  }
  
  if (stack.GetCount()>0) {
    stack.PopString();
    for (int i = 0;i<stack.GetCount();i++) {
      sd->chdir(stack.LookAt(i));
    }
  }  
 
}


void DirFunction::ToRoot() {
  count = 0;
  currentIndex = 0;
  IsFinished = 0;
  IsDirectory = 0;
  InSubDir = 0;
  if (!sd->chdir()) {    
    Serial.println("chdir(\) failed");
    sd->errorHalt();
  } 
}

void DirFunction::Prepare() {
  count = 0;
  currentIndex = 0;
  
  SdBaseFile* dirFile = (SdBaseFile*) sd->vwd();
  dirFile->rewind();

  if (stack.GetCount()>0) count++;
  //Count files
  while (file.openNext(dirFile, O_READ)) {  
    if (!file.isHidden()) {   
      //file.printName(&Serial); 
      count++;
      //Serial.println(); 
    } 
    file.close(); 
  }   

  
  dirFile->rewind();
  
  Serial.print(F("File count :  ")); Serial.println(count);
}

void DirFunction::ChangeDirectory(char * directory) {
  ToRoot();  
  
  for (int i = 0;i<stack.GetCount();i++) {
    if (!sd->chdir(stack.LookAt(i))) {
      Serial.print(F("From stack chdir(")); Serial.print(stack.LookAt(i)); Serial.println(F(") failed"));      
    } else {
      Serial.print(F("From stack Entered ")); Serial.println(stack.LookAt(i)); 
    }
  }
  
  InSubDir = 1;  
  if (!sd->chdir(directory)) {
    Serial.print("chdir("); Serial.print(directory); Serial.println(") failed");    
  } else {
    stack.PushString(directory);
  }
}

int DirFunction::Iterate() {
  //Serial.print(F("Current Index : "));Serial.println(currentIndex);
  SdBaseFile* dirFile = (SdBaseFile*) sd->vwd();  
  CurrentFileName.ResetIndex();  
  if (stack.GetCount()>0 && currentIndex == 0) {
    CurrentFileName.Copy("..");
    IsDirectory = 1;
    IsHidden = 0;
    currentIndex++;
    return 1;
  }
  
  if (currentIndex<count) {      
    if (file.openNext(dirFile, O_READ)) {        
      if (!file.isHidden()) {          
        file.printName(&CurrentFileName); 
        //Serial.println(CurrentFileName.value);
        currentIndex++;
        IsDirectory = file.isSubDir();
        IsHidden = 0;
        file.close();         
        return 1;
      }  else {
        IsHidden = 1;
        IsDirectory = file.isSubDir();
        file.close();         
        return 1;
      }      
    } else {
      IsFinished = 1;
      Serial.println(F("OpenNext failed! Finished"));
      return 0;
    }
  } else {
    IsFinished = 1;
    Serial.println(F("Finished"));
    return 0;
  }
  
  return 0;
}

unsigned int  DirFunction::GetCount() {
  return count;
}

void DirFunction::Rewind() {
  SdBaseFile* dirFile = (SdBaseFile*) sd->vwd(); 
  dirFile->rewind();
  currentIndex = 0;  
  IsDirectory = 0;
  IsHidden = 0;
  IsFinished = 0;
}
