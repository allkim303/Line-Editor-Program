
#include "cfield.h"

namespace cio{

class CLine : public CField{

	
	int curposition;
	int stroffset;
	int maxnumchar;

	void allocateAndCopy(const char*);
	int curPosition();
	int strOffset();

public:
	CLine(const char*, int, int, int, int, bool, bool = false, const char* = C_BORDER_CHARS);
	CLine(int, int, int, int, bool, bool = false, const char* = C_BORDER_CHARS);
	~CLine();
	void draw(int);
	int edit();
	bool editable();
	void set(const void*);

};





}	// end of cio namespace