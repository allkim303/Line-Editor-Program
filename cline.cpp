/*=====================================================================================================
	Minji Kim	067742122
	OOP344A
	
	Class CLine is a CField that holds editable data.  
	A CLine object may or may not have a border and has an editing state. 
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
#include "cline.h"

using namespace cio;

namespace cio{

/*=====================================================================================================
	This method allocates dynamic memory for the C-style null-terminated string at the received 
	address and copies that data into the newly allocated memory.
=======================================================================================================*/
void CLine::allocateAndCopy(const char* src){

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
	This constructor passes the address of the data string directly to the CField constructor 
	without allocating any further memory. 
=======================================================================================================*/
CLine::CLine(const char* str, int r, int c, int len, int maxNumChar, bool* insert, bool visibility, const char* border) 
											: CField ( r , c, 0, 0, (void*) str, visibility,  border){

	curposition = 0;
	stroffset = 0;
	maxnumchar = maxNumChar;
	setfieldlen(len);
	if(visibility){
		height(3);
		width(len + 2);
	}
	else{
		height(1);
		width(len);
	}

	insertmode=*insert;
	dynamic=false;
}

/*=====================================================================================================
	This constructor stores an empty string as the line field's data and allocates enough memory 
	to allow the data string to expand the string to one that contains the maximum number of characters 
	specified. 
=======================================================================================================*/
CLine::CLine( int row, int col, int len, int maxNumChar, bool* insert, bool visibility, const char* border)
											: CField ( row , col, 0, 0, NULL, visibility,  border){
	char* temp;
	temp = new char[maxNumChar];
	temp[0]='\0';
	data(temp);
	dynamic=true;

	insertmode=*insert;
	curposition = 0;
	stroffset = 0;
	setfieldlen(len);
	if(visibility){
		height(3);
		width(len + 2);
	}
	else{
		height(1);
		width(len);
	}

	maxnumchar = maxNumChar;
}

/*=====================================================================================================
	The CLine destructor deallocates the dynamic memory allocated for the data string.
=======================================================================================================*/
CLine::~CLine(){

	if(dynamic) delete [] (char*)data();

}

/*=====================================================================================================
	 draws the frame for the line field according to the specified value (C_NO_FRAME) and displays 
	 the data in that field starting at the current offset
=======================================================================================================*/
void CLine::draw(int c){

	int border=0;
	char* Temp = (char*) data();
	if(col()+getfieldlen() > frame()->width())	setfieldlen(frame()->width()-col());	
	CFrame::draw();
	if(bordered()) border = 1;
	display(Temp, absrow()+border, abscol()+border, getfieldlen());


}

/*=====================================================================================================
	edits the line field according to the editing state and returns the key that causes the editing 
	to finish
=======================================================================================================*/
int CLine::edit(){

	int border=0;

	CFrame::draw();
	if(bordered()) border = 1;
	return ::edit((char*) data(), absrow()+border, abscol()+border, getfieldlen(), maxnumchar, &insertmode, &stroffset, &curposition);
}

/*=====================================================================================================
	returns true
=======================================================================================================*/
bool CLine::editable() const{

	return true;
}

/*=====================================================================================================
	This method associates a new C-style null-terminated string with the line field.  
	If the current object allocated memory for the string currently associated with the field, 
	this method deallocates that memory.  The method allocates new dynamic memory for the new 
	string and copies it into the newly allocated memory. 
=======================================================================================================*/
void CLine::set(const void* src){

	allocateAndCopy((char*) src);
	dynamic = true;
}

}	// end of cio namespace
