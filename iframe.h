/*=====================================================================================================
	Allison Kim

	iFrame is the hierarchy's interface. It is an abstract base class that does not have 
	any instance variables and an abstract base class is a class that lacks a complete implementation.
=======================================================================================================*/
#ifndef _FS_IFRAME_H_
#define _FS_IFRAME_H_

 // iFrame Header
 // iframe.h
 //
 // Fardad Soleimanloo, Chris Szalwinski
 // August 27 2011
 // Version 1.0
 //

 #include "cfg.h"  // for C_FULL_FRAME, CDirection, and C_STATIONARY

 namespace cio {

     class iFrame {
       public:
         virtual void draw(int fn = C_FULL_FRAME)         = 0;
         virtual void move(CDirection dir)                = 0;
         virtual void hide(CDirection dir = C_STATIONARY) = 0;
     };

     void move(iFrame &cf);

 }  // end of cio namespace for now

 #endif
