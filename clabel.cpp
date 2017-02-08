
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


namespace cio{

void CLabel::allocateAndCopy(const char* src){

	char* Temp;
	if(src){
		Temp = new char[strlen(src)+1];
		strcpy(Temp, src);
	}
	else Temp=NULL;
	if(data()) delete [] data();
	data((void*) Temp);
}

CLabel::CLabel(const char* src, int r, int c, int len){

	row(r);
	col(c);
	clabel_field = len;
	allocateAndCopy(src);
}

CLabel::CLabel(int r, int c, int len){

	row(r);
	col(c);
	clabel_field = len;
	data(NULL);
}

CLabel::CLabel(CLabel& src){

	*this = src;
	allocateAndCopy((char*)src.data());
}

CLabel::~CLabel(){

	if(data()) delete [] data();
}

void CLabel::draw(int c){
	
	int field;
	char* Temp = (char*) data();

	if(col()+clabel_field > width())	field=width()-col();
	display(Temp, row(), col(), field);
}

int CLabel::edit(){

	draw();
	return C_NOT_EDITABLE;
}

bool CLabel::editable() const{

	return false;
}

void CLabel::set(const void* src){

	allocateAndCopy((char*) src);
}



}// end of cio namespace

