/*=====================================================================================================
	Allison Kim
	OOP344A
=======================================================================================================*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstring>
#include "iframe.h"
#include "keys.h"
#include "cfg.h"
#include "console.h"
#include "consoleplus.h"
#include "consolebackup.h"
#include "cframe.h"
#include "cfield.h"
#include "cbutton.h"

using namespace cio;

namespace cio{

/*=====================================================================================================
	 CButton constructor passes the row, col, border visibility, and border string values directly 
	 to the CField constructor.  The CButton constructor sets the height of the field depending on 
	 the border's visibility (3 or 1) and its width depending on the length of the string and the 
	 border's visibility.  This constructor also passes the NULL address to the CField constructor 
	 as the data's initial address.
=======================================================================================================*/
CButton::CButton(const char* str, int r, int c, bool visibility , const char* border) :
			CField( r, c, 0, 0, (void*) NULL, visibility, border){

    allocateAndCopy(str);

	if(visibility){
		height(3);		
	}
	else{
		height(1);
	}
	width(strlen(str) + 4);
}

/*=====================================================================================================
	CButton destructor
=======================================================================================================*/
CButton::~CButton(){

	if(data()) delete [] (char*)data();
}

/*=====================================================================================================
	This private method allocates dynamic memory for the data at the received address and copies that 
	data into the new memory.
=======================================================================================================*/
void CButton::allocateAndCopy(const char* src){
	
	char* Temp;
	int field;
	if(data()) delete [] (char*)data();
	if(src){
		setfieldlen(strlen(src)+2);
		field = getfieldlen();
		Temp = new char[field+1];
	    data((void*) Temp);
		Temp[0]=' ';
		for(int i = 0; i<field-2; i++){
			Temp[i+1]=src[i];
		}
		Temp[field-1]=' ';
		Temp[field]='\0';		
		toggledata(bordered());
	}
	else Temp=NULL;	
}

/*=====================================================================================================
	This method changes the prefix and suffix on the label's string to [ and ] resepctively.
=======================================================================================================*/
void CButton::toggledata(bool mode){

	char* Temp = (char*) data();
	if(mode){
		Temp[0] = '[';
		Temp[getfieldlen()-1] = ']';
	}
	else{
		Temp[0] = ' ';
		Temp[getfieldlen()-1] = ' ';
	}
	Temp[getfieldlen()]='\0';
}

/*=====================================================================================================
	This method draws the button's frame according to the specified value (C_NO_FRAME) and displays 
	its data without offset.
=======================================================================================================*/
void CButton::draw(int framemode){

	int border=0;
	toggledata(false);
	CFrame::draw();
	if(bordered()) border=1;
	display((char*)data(), absrow()+border, abscol()+border, getfieldlen());
}

/*=====================================================================================================
	This method captures the press of the button. 
=======================================================================================================*/
int CButton::edit(){

	int userInput;
	int border=0;
	if(bordered()) border=1;
	toggledata(true);
	CFrame::draw();
	display((char*)data(), absrow()+border, abscol()+border, getfieldlen());
	goMiddle();

	console >> userInput;
	if( userInput == ENTER || userInput == SPACE) userInput = C_BUTTON_HIT;

	toggledata(false);
	CFrame::draw();
	goMiddle();
	display((char*)data(), absrow()+border, abscol()+border, getfieldlen());

	return userInput;
}

/*=====================================================================================================
	This method returns true.
=======================================================================================================*/
bool CButton::editable() const{

	return true;
}

/*=====================================================================================================
	This method deallocates the dynamic memory allocated for the button's label allocates dynamic 
	memory for the C-style null-terminated string at the address received, copies the string into the 
	newly allocated memory, and resets the width and the height of the button.
=======================================================================================================*/
void CButton::set(const void* str){
	
	allocateAndCopy((char*) str);

	if(bordered()){
		height(3);
		width(strlen((char*)data()) + 2);
	}
	else{
		height(1);
		width(strlen((char*)data()));
	}
}
}	// end of cio namespace
