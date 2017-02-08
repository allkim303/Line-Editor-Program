/*=====================================================================================================
	Allison Kim
=======================================================================================================*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include "iframe.h"
#include "cfg.h"
#include "console.h"
#include "consoleplus.h"
#include "consolebackup.h"
#include "cframe.h"

using namespace cio;

namespace cio{

/*=====================================================================================================
	The CFrame constructor receives seven values.
	If the constructor receives a negative height, the frame is fullscreen no matter what values 
	of row, col, or width the caller specifies.  If the frame is fullscreen, then its width and height 
	are the number of rows and columns respectively that the console supports.  A fullscreen frame has 
	no border.  On construction, the frame does not draw itself or cover any area of the screen. 
=======================================================================================================*/
CFrame::CFrame(int r , int c, int w, int h, bool v , const char* str , CFrame* pa){

	char Temp[9];

    capturedTemp = NULL;

	if(w<0 || h<0 || h>console.getRows()){
		cf_row = 0;
		cf_col = 0;
		cf_width = console.getCols();
		cf_height = console.getRows();
		cf_screenmode=true;
	}
	else{
		cf_row = r;
		cf_col = c;
		cf_width = w;
		cf_height = h;
		cf_screenmode=false;
	}
	cf_visibility = v;

	if(str != NULL  && strlen(str)==8){

		sscanf(str, "%c%c%c%c%c%c%c%c", &top_left, &top_border, &top_right, &right_border, &bottom_right, &bottom_border, &bottom_left, &left_border);
	}
	else{

		strcpy(Temp, C_BORDER_CHARS);
		sscanf(Temp, "%c%c%c%c%c%c%c%c", &top_left, &top_border, &top_right, &right_border, &bottom_right, &bottom_border, &bottom_left, &left_border);
	}
	if(pa) cf_parent=pa;
	else cf_parent = NULL;
}

/*=====================================================================================================
		The CFrame destructor deallocates any memory that the frame has allocated to hold characters 
		hidden by the drawing of the frame.
=======================================================================================================*/
CFrame::~CFrame(){
	if(capturedTemp)	delete [] (char*)capturedTemp;
}

/*=====================================================================================================
	This method creates C-style null terminated string (str) equal in length to the width of the frame 
	and composed of the starting character (left), a sequence of the fill character (fill), and the 
	ending character (right).
=======================================================================================================*/
void CFrame::setLine(char* str, char left, char fill, char right) const{
		
	for(int i=0; i<cf_width; i++){
		if(i == 0)						str[i]=left;
		else if(i>0 && i<cf_width-1)	str[i]=fill;
		else if(i == (cf_width-1))		str[i]=right;
	}
	str[cf_width]='\0';
}

/*=====================================================================================================
	This method captures the characters in the console buffer that are within the rectangle where the 
	frame will draw itself, if those characters have not already been captured.
=======================================================================================================*/
void CFrame::capture(){

	if(capturedTemp == NULL){
		capturedTemp = (char*) cio::capture(absrow(), abscol(), cf_height, cf_width);
	}
}

/*=====================================================================================================
	This method returns the frame's top-most row position relative to the top-most row of the console.
=======================================================================================================*/
int CFrame::absrow(){

	if(cf_parent){

		if(cf_parent->bordered())	return (cf_parent->absrow() + cf_row + 1 );
		else						return (cf_parent->absrow() + cf_row );	
	}
	else	return cf_row;

}

/*=====================================================================================================
	This method returns the frame's left-most column position relative to the left-most column of 
	the console.
=======================================================================================================*/
int CFrame::abscol(){
	
	if(cf_parent){
		if(cf_parent->bordered())	return (cf_parent->abscol() + cf_col + 1 );
		else						return (cf_parent->abscol() + cf_col );	
	}
	else	return cf_col;
}

/*=====================================================================================================
	This method returns the screed mode.
=======================================================================================================*/
void CFrame::set_screenmode(){

	if(cf_height == console.getRows() && cf_width == console.getCols())		cf_screenmode = true;
	else																	cf_screenmode = false;
}

/*=====================================================================================================
	This method sets the position of the cursor to the middle of the frame.
=======================================================================================================*/
void CFrame::goMiddle(){

	if(bordered())	console.setPosition(absrow()+cf_height/2, abscol()+cf_width/2);
	else			console.setPosition(absrow()+cf_height/2-1, abscol()+cf_width/2-1);
}

/*=====================================================================================================
	This method sets the visibility of the border to the value received.
=======================================================================================================*/
void CFrame::bordered(bool v){

	cf_visibility = v;
}

/*=====================================================================================================
	This method returns the visibility of the border.
=======================================================================================================*/
bool CFrame::bordered() const{

	return cf_visibility;
}

/*=====================================================================================================
	This method sets the address of the parent to the address received.
=======================================================================================================*/
void CFrame::frame(CFrame* pa){

	if(pa)	cf_parent = pa;
}

/*=====================================================================================================
	This method returns the address of the parent, if any.
=======================================================================================================*/
CFrame* CFrame::frame() const{

	return cf_parent;
}

/*=====================================================================================================
	This method sets the top row to the value received.
=======================================================================================================*/
void CFrame::row(int r){

	cf_row = r;
}

/*=====================================================================================================
	Thie method returns the top row position relative to the parent frame, if any; 0 if fullsreen.
=======================================================================================================*/
int CFrame::row() const{

	return cf_row;
}

/*=====================================================================================================
	This method sets the left column to the value received.
=======================================================================================================*/
void CFrame::col(int c){

	cf_col = c;
}

/*=====================================================================================================
	returns the left column position relative to the parent frame, if any; 0 if fullsreen.
=======================================================================================================*/
int CFrame::col() const{

	return cf_col;
}

/*=====================================================================================================
	sets the height to the value received
=======================================================================================================*/
void CFrame::height(int h){

	int _height=console.getRows();

	if(h<0 || h>=_height)	cf_height = _height;
	else					cf_height = h;	

	set_screenmode();
}

/*=====================================================================================================
	returns the current height
=======================================================================================================*/
int CFrame::height() const{

	return cf_height;
}

/*=====================================================================================================
	sets the width to the value received
=======================================================================================================*/
void CFrame::width(int w){

	int _width = console.getCols();

	if(w<0 || w>=_width)	cf_width = _width;
	else					cf_width = w;

	set_screenmode();
}

/*=====================================================================================================
	returns the current width
=======================================================================================================*/
int CFrame::width() const{

	return cf_width;
}

/*=====================================================================================================
	draws the frame 
=======================================================================================================*/
void CFrame::draw(int c){

	char* str;
	str = new char[cf_width+1];
	hide(C_STATIONARY);
	capture();
	if(c == C_NO_FRAME || cf_visibility){
		for(int i=0; i<cf_height;i++){

			if(i==0) setLine(str, top_left, top_border, top_right);
			else if(i>0 && i<cf_height-1)	setLine(str, left_border, ' ', right_border);
			else setLine(str, bottom_left, bottom_border, bottom_right);

			cio::display(str, absrow()+i, abscol(), -1);
		}
	}
	delete [] str;
}

/*=====================================================================================================
	 hides the frame
=======================================================================================================*/
void CFrame::hide(CDirection dir){

	if(capturedTemp != NULL){
		restore(absrow(), abscol(), cf_height, cf_width, dir, capturedTemp);
		release((void **) &capturedTemp);
	}
}

/*=====================================================================================================
	 translates the frame one unit in the specified direction
=======================================================================================================*/
void CFrame::move(CDirection dir){
	
	hide();

	if(cf_parent){
		if(dir==C_MOVED_UP && cf_row > 0)																			cf_row -= 1;
		else if(dir==C_MOVED_DOWN && cf_row + cf_height < (cf_parent->cf_height)-(cf_parent->bordered() ? 2 : 0) )	cf_row += 1;
		else if(dir==C_MOVED_LEFT && cf_col > 0)																	cf_col -= 1;
		else if(dir==C_MOVED_RIGHT && cf_col + cf_width < (cf_parent->cf_width)-(cf_parent->bordered() ? 2 : 0))	cf_col += 1;
	}
	draw();
	console.setPosition(0,0);
}

/*=====================================================================================================
	moves the frame referred to in the parameter
=======================================================================================================*/
void move(iFrame& iF){

	CFrame* CF;
	int userInput,cur=0, row, col;
	char str[]="Moving! ESC: exit";
	cio::display(str, 0, 5, 50);
	
	CF=(CFrame*) &iF;

	do{
		CF->goMiddle();
		console.getPosition(row, col);
		userInput= GetInput_fromUser(row, col, &cur); 
		if(userInput==1001)			CF->move(C_MOVED_UP);	
		else if(userInput==1002)	CF->move(C_MOVED_DOWN);
		else if(userInput==1003)	CF->move(C_MOVED_LEFT);
		else if(userInput==1004)	CF->move(C_MOVED_RIGHT);
		else						CF->move(C_STATIONARY);		
	}while(userInput!=27);
}

}	// end of cio namespace
