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


namespace cio{

void CLine::allocateAndCopy(const char* src){

	char* Temp;
	if(src){
		Temp = new char[strlen(src)+1];
		strcpy(Temp, src);
	}
	else Temp=NULL;
	if(data()) delete [] data();
	data((void*) Temp);
}

CLine::CLine(const char* src, int row, int col, int len, int maxNumChar, bool insertmode, bool visibility, const char* border) 
											: CField ( row , col,(visibility==true? 3 : 1 ), len, src, visibility,  border){

	curposition = 0;
	stroffset = 0;
	maxnumchar = maxNumChar;
}

CLine::CLine( int row, int col, int len, int maxNumChar, bool insertmode, bool visibility, const char* border){

	curposition = 0;
	stroffset = 0;
	maxnumchar = maxNumChar;
}

CLine::~CLine(){

	if(data()) delete [] data();

}
void CLine::draw(int){

	int field;
	char* Temp = (char*) data();

	if(col()+clabel_field > width())	field=width()-col();
	display(Temp, row(), col(), field);


}
int CLine::edit(){



}

bool CLine::editable(){

	return true;
}
void CLine::set(const void*){


}


}	// end of cio namespace