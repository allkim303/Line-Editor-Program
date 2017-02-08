#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include "iframe.h"
#include "cfg.h"
#include "console.h"
#include "consoleplus.h"
#include "consolebackup.h"
#include "cframe.h"



namespace cio{

CFrame::CFrame(int r , int c, int w, int h, bool v , const char* str , CFrame* pa){

	if(h<0 || h>console.getRows()){
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
	sscanf(str, "%c%c%c%c%c%c%c%c", &top_left, &top_border, &top_right, &right_border, &bottom_right, &bottom_border, &bottom_left, &left_border);
	if(pa) cf_parent=pa;
	else cf_parent = (CFrame*) NULL;

}

void CFrame::setLine(char* str, char left, char fill, char right) const{
		
	for(int i=0; i<cf_width; i++){
		if(i == 0)					str[i]=left;
		else if(i>0 && i<cf_width-1)	str[i]=fill;
		else if(i == (cf_width-1))		str[i]=right;
	}
	str[cf_width]='\0';
}

void CFrame::capture(){

	if(capturedTemp == (char*)NULL){
		capturedTemp = (char*) cio::capture(absrow(), abscol(), cf_height, cf_width);
	}
}

int CFrame::absrow(){

	if(cf_parent && cf_parent->cf_visibility)	return (cf_row + cf_parent->cf_row + 1);
	else if(cf_parent) return (cf_row + cf_parent->cf_row);
	return cf_row;
}

int CFrame::abscol(){
	
	if(cf_parent && cf_parent->cf_visibility)	return (cf_col + cf_parent->cf_col + 1);
	else if(cf_parent)	return (cf_col + cf_parent->cf_col);
	return cf_col;
}

void CFrame::set_screenmode(){

	if(cf_height == console.getRows() && cf_width == console.getCols()) cf_screenmode = true;
	else cf_screenmode = false;
}

void CFrame::goMiddle(){

	console.setPosition(absrow()+cf_height/2, abscol()+cf_width/2);
}

void CFrame::bordered(bool v){

	cf_visibility = v;
}

bool CFrame::bordered() const{

	return cf_visibility;
}

void CFrame::frame(CFrame* pa){

	if(pa)	cf_parent = pa;
}

CFrame* CFrame::frame() const{

	return cf_parent;
}

void CFrame::row(int r){

	cf_row = r;
}

int CFrame::row() const{

	if(cf_screenmode || cf_parent==NULL)	return 0;
	return cf_row;
}

void CFrame::col(int c){

	cf_col = c;
}

int CFrame::col() const{

	if(cf_screenmode || cf_parent==NULL)	return 0;
	return cf_col;
}

void CFrame::height(int h){

	int _height=console.getRows();

	if(h<0 || h>=_height) cf_height = _height;
	else	cf_height = h;	

	set_screenmode();
}
int CFrame::height() const{

	return cf_height;
}

void CFrame::width(int w){

	int _width = console.getCols();

	if(w<0 || w>=_width) cf_width = _width;
	else	cf_width = w;

	set_screenmode();
}

int CFrame::width() const{

	return cf_width;
}

void CFrame::draw(int c){

	char* str;
	str = new char[cf_width+1];
	capture();
	if(c && cf_visibility ){
		for(int i=0; i<cf_height;i++){

			if(i==0) setLine(str, top_left, top_border, top_right);
			else if(i>0 && i<cf_height-1)	setLine(str, left_border, ' ', right_border);
			else setLine(str, bottom_left, bottom_border, bottom_right);

			cio::display(str, absrow()+i, abscol(), cf_width);
		}
	}
	delete [] str;
}

void CFrame::hide(CDirection dir){

	if(capturedTemp != NULL){
		restore(absrow(), abscol(), cf_height, cf_width, dir, capturedTemp);
		release((void **) &capturedTemp);
	}
}

void CFrame::move(CDirection dir){
	
	hide();

	if(cf_parent){
		if(dir==C_MOVED_UP && cf_row > 0)		cf_row -= 1;
		else if(dir==C_MOVED_DOWN && cf_row < cf_parent->cf_row + cf_parent->height)	cf_row += 1;
		else if(dir==C_MOVED_LEFT && cf_col )	cf_col -= 1;
		else if(dir==C_MOVED_RIGHT) cf_col += 1;


	}

	draw();
}

void move(iFrame& iF){

	CFrame* CF;
	int userInput,cur=0, row, col;
	char str[]="Moving! ESC: exit";
	cio::display(str, 0, 5, 0);
	
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
