/*=====================================================================================================
	Allison Kim
=======================================================================================================*/
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


namespace cio{

/*=====================================================================================================
	The CField constructor receives seven values in its parameters and passes all values except 
	the data address to its base class constructor. 
=======================================================================================================*/
CField::CField(int r, int c, int width, int height, void* data, bool visibility, const char* border)
				: CFrame(r, c, width, height, visibility, border){

		if(data)	cfield_data = data;
		else		cfield_data = NULL;
}

/*=====================================================================================================
	This method returns the pointer to field's data.
=======================================================================================================*/
void* CField::data() const{

	return cfield_data;
}

/*=====================================================================================================
	This method sets the address of the field's data.
=======================================================================================================*/
void CField::data(void* str){

	if(str)	cfield_data = str;
	else	cfield_data = NULL;
}

/*=====================================================================================================
	This method sets the field length.
=======================================================================================================*/
void CField::setfieldlen(int len){

	fieldlen = len;

}

/*=====================================================================================================
	This method returns the field length.
=======================================================================================================*/
int CField::getfieldlen(){

	return fieldlen;

}

}	// end of cio namespace
