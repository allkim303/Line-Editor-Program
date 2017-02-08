
#include "cfield.h"




namespace cio{

class CLabel : public CField{

	int clabel_field;
	void allocateAndCopy(const char*);

public:
	CLabel(const char*, int, int, int = -1);
	CLabel(int, int, int);
	CLabel(CLabel&);
	~CLabel();
	void draw(int = C_NO_FRAME);
	int edit();
	bool editable() const;
	void set(const void*);
}

}	// end of cio namespace

