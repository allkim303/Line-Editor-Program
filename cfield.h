


#include "cframe.h"



namespace cio{
class CField : public CFrame{

	void* cfield_data;

public:
	
	CField(int = 0, int =0, int = 0, int = 0, void* = NULL, bool = false, const char* = C_BORDER_CHARS );
	~CField(){ };	
	void* data() const;
	void data(void*);
	
	virtual void draw(int) =0;
	virtual int edit() =0;
	virtual bool editable() const =0;
	virtual void set(const void*) =0;

};

}	// end of cio namespace