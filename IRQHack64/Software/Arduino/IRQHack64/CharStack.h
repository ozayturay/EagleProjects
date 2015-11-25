#ifndef _CHARSTACK_H
#define _CHARSTACK_H

#define STACK_TOP 197

class CharStack {	
 public: 
	void Push(char);
        char Pop();
        char Current();
        
 protected:
        char charBuffer[198]; // buffer to hold 6 folder names with max length 32 at least
 	int top = STACK_TOP;        
	
};


class StringStack : public CharStack {
 protected:
        int itemCount = 0;
        int itemArray[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
 public: 
	void PushString(char *);
        char * PopString();
        char * CurrentString(); 
        char * LookAt(int);
        int GetCount();   
        
};

#endif _CHARSTACK_H
