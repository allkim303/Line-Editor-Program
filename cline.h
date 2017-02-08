/*=====================================================================================================
	Minji Kim	067742122
	OOP344A
	
	Class CLine is a CField that holds editable data.  
	A CLine object may or may not have a border and has an editing state. 
=======================================================================================================*/
#ifndef __CLINE__
#define __CLINE__

#include "cfield.h"

namespace cio{

class CLine : public CField{
	
	int curposition;
	int stroffset;
	int maxnumchar;
	bool insertmode;
	bool dynamic;

	void allocateAndCopy(const char*);
	int curPosition();
	int strOffset();

public:
	CLine(const char*, int, int, int, int, bool*, bool = false, const char* = C_BORDER_CHARS);
	CLine(int, int, int, int, bool*, bool = false, const char* = C_BORDER_CHARS);
	~CLine();
	void draw(int = C_NO_FRAME);
	int edit();
	bool editable() const;
	void set(const void*);
};

}	// end of cio namespace
#endif