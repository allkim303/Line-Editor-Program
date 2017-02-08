/*=====================================================================================================
	Allison Kim
	
	CField is a CFrame that can access data associated with the frame.  
	A field may or may not have a border and may or may not have a parent.  
=======================================================================================================*/
#ifndef __cfield__
#define __cfield__

#include "cframe.h"

namespace cio{

class CField : public CFrame{

	void* cfield_data;
	int fieldlen;

public:
	
	CField(int = 0, int =0, int = 0, int = 0, void* = NULL, bool = false, const char* = C_BORDER_CHARS );
	~CField(){  };	// empty	
	void* data() const;
	void data(void*);
	void setfieldlen(int);
	int getfieldlen();
	
	virtual void draw(int = C_NO_FRAME) =0;
	virtual int edit() =0;
	virtual bool editable() const =0;
	virtual void set(const void*) =0;

};

}	// end of cio namespace

#endif
