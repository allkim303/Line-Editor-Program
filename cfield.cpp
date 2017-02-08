	
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

CField::CField(int r , int c, int w, int h, void* d, bool v, const char* border): CFrame(r, c, w, h, v, border){

		if( d )		cfield_data = d;
		else		cfield_data = NULL;
}

void* CField::data() const{

	return cfield_data;
}

void CField::data(void* str){

	if(str)	cfield_data=str;
	else	cfield_data = NULL;
}


}	// end of cio namespace