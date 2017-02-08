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

CButton::~CButton(){

	if(data()) delete [] data();

}

void CButton::allocateAndCopy(const char* src){
	
	char* Temp;
	int field;
	if(data()) delete [] data();
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

void CButton::draw(int framemode){

	int border=0;
	toggledata(false);
	CFrame::draw();
	if(bordered()) border=1;
	display((char*)data(), absrow()+border, abscol()+border, getfieldlen());
}

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

bool CButton::editable() const{

	return true;
}

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
