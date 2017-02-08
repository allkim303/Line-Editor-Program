
#include "iframe.h"


namespace cio{

class CFrame : public iFrame {

	int cf_row, cf_col,cf_width, cf_height;
	bool cf_visibility, cf_screenmode;
	char top_left, top_border, top_right, right_border, bottom_right, bottom_border, bottom_left, left_border;
	char* capturedTemp;
	CFrame* cf_parent;
	

	void setLine(char* str, char left, char fill, char right) const;
	void capture();


protected:
	int absrow();
	int abscol();
	void set_screenmode();

public:
	CFrame(int = -1, int = -1, int = -1, int = -1, bool = false, const char* = C_BORDER_CHARS, CFrame* = NULL);
	void goMiddle();
	void bordered(bool);
	bool bordered() const;
	void frame(CFrame*);
	CFrame* frame() const;
	void row(int);
	int row() const;
	void col(int);
	int col() const;
	void height(int);
	int height() const;
	void width(int);
	int width() const;

	void draw(int = C_FULL_FRAME);
	void hide(CDirection = C_STATIONARY );
	void move(CDirection);
};
void move(iFrame&);

}	// end of cio namespace