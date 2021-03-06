/*=====================================================================================================
	Allison Kim
	
	CButton is a CField that represents a clickable button.  
	It may have a border but does not have any state.
=======================================================================================================*/
#ifndef __cbutton__
#define __cbutton__

#include "cfield.h"

namespace cio{

class CButton : public CField{

	void toggledata(bool mode);

public:
	CButton(const char*, int, int, bool = true, const char* = C_BORDER_CHARS);
	~CButton();
	void allocateAndCopy(const char* str);
	void draw(int = C_NO_FRAME);
	int  edit();
	bool editable() const;
	void set(const void*);
};
}	// end of cio namespace

#endif
