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
#include "cfield.h"
#include "clabel.h"

using namespace cio;

namespace cio{

/*=====================================================================================================
	This private method allocates dynamic memory for the C-style null-terminated string at the 
	received address and copies that data into the newly allocated memory.
=======================================================================================================*/
void CLabel::allocateAndCopy(const char* src){

	char* Temp;
	if(src){
		Temp = new char[strlen(src)+1];
		strcpy(Temp, src);
	}
	else Temp=NULL;
	if(data()) delete [] (char*)data();
	data((void*) Temp);
}

/*=====================================================================================================
	The first constructor receives four values in its parameters.
=======================================================================================================*/
CLabel::CLabel(const char* src, int _row, int _col, int len){

	row(_row);
	col(_col);
	setfieldlen(len);
	allocateAndCopy(src);
}

/*=====================================================================================================
	The second constructor receives three values in its parameters and stores an empty string as 
	the label's data.
=======================================================================================================*/
CLabel::CLabel(int r, int c, int len){

	row(r);
	col(c);
	setfieldlen(len);
	data(NULL);
}

/*=====================================================================================================
	The CLabel copy constructor copies the source object's data into the dynamic memory that stores 
	the label's data.
=======================================================================================================*/
CLabel::CLabel(CLabel& src){

	*this = src;
	allocateAndCopy((char*)src.data());
}

/*=====================================================================================================
	The CLabel destructor deallocates the dynamic memory that stored the label's data.
=======================================================================================================*/
CLabel::~CLabel(){

	if(data()) delete [] (char*)data();
}

/*=====================================================================================================
	displays the label
=======================================================================================================*/
void CLabel::draw(int c){
	
	int field = getfieldlen();
	char* Temp = (char*) data();
	if(col()+getfieldlen() >= frame()->width()){
		field = (frame()->width()) - col();
		if(frame()->bordered()) field -= 2;
	}
	display(Temp, absrow(), abscol(), field);
}

/*=====================================================================================================
	 draws the label and returns the key code
=======================================================================================================*/
int CLabel::edit(){

	draw();
	return C_NOT_EDITABLE;
}

/*=====================================================================================================
	 returns false
=======================================================================================================*/
bool CLabel::editable() const{

	return false;
}

/*=====================================================================================================
	This method deallocates the dynamic memory where the label's data has been stored, resets the 
	width of the field to the length of the C-style null-terminated string at the received address, 
	allocates dynamic memory for that data, and copies the data in the newly allocated memory.
=======================================================================================================*/
void CLabel::set(const void* src){

	allocateAndCopy((char*) src);
}

}// end of cio namespace

