/*=====================================================================================================
	Minji Kim	
	OOP344A
	Feb.07.2014
=======================================================================================================*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "console.h"
#include "keys.h"
#include "consoleplus.h"

namespace cio{

/*=====================================================================================================
	This function displays the C-style, null-terminated string pointed to by str, starting at row (row)
	and column (col) of the console screen in a field of fieldLen characters.  
=======================================================================================================*/
void display(const char *str, int row, int col, int fieldLen)
{
	int lenofstr, colofcon, rowofcon, restofcol, numofprint, numofspace, flag=0;

	lenofstr = std::strlen(str);
	colofcon = console.getCols();
	rowofcon = console.getRows();
	restofcol=colofcon-col;

	if(row<0 || row>=rowofcon || col<0 || col>=colofcon || str==NULL) return;
	// If the fieldLen is 0 or less, displays whole string that fits on the field length.
	if(fieldLen<=0)
	{
		if(lenofstr<restofcol) 
		{
			numofprint=lenofstr;
			numofspace=0;
		}
		else 
		{
			numofprint=restofcol;
			numofspace=0;
			flag=1;
		}		
	}
	else if(fieldLen <= restofcol)
	{
		if(lenofstr <= fieldLen) 
		{
			numofprint = lenofstr; 
			numofspace = fieldLen-lenofstr;
		}		
		else if(lenofstr > fieldLen)
		{
			numofprint = fieldLen; 
			numofspace=0;
		}
		if(fieldLen == restofcol) flag=1;
	}
	else if(fieldLen > restofcol)
	{
		flag=1;
		if(lenofstr <= restofcol) 
		{
			numofprint = lenofstr; 
			numofspace = restofcol-lenofstr;
		}		
		else if(lenofstr > restofcol)
		{
			numofprint = restofcol;
			numofspace=0;
		}
	}
	for(int i=0; i<numofprint; i++)
	{
		console.setPosition(row, col+i);
		console.setCharacter(str[i]);
		console.setPosition(row, col+i);
		console.drawCharacter();
	}
	if(numofspace!=0)
	{
		for(int i=numofprint; i<fieldLen; i++)
		{
			console.setPosition(row, col+i);
			console.setCharacter(' ');
			console.setPosition(row, col+i);
			console.drawCharacter();
		}
	}
	// If the character is at the last column of the field length,
	// position the cursor under the last character
	if(flag==1)		console.setPosition(row, colofcon-1);
	if(numofspace!=0) console.setPosition(row, col+lenofstr);
}

/*=====================================================================================================
	This function edits the C-style, null-terminated string pointed to by str.  
	The parameter row holds the row(0 is the top row) of the string on the console screen.  
	The parameter col holds the starting column (0 is the left-most column) on the screen.  
	The parameter fieldLength holds the length of the editable field.
	The parameter maxStrLength holds the maximum length of the string, excluding the null byte.  
	The parameter insertMode points to a bool variable that holds the current insert mode of the string. - insert or overwrite. 
	The parameter strOffset points to an int variable that holds the initial offset of the string within the field.
	The parameter curPosition points to an int variable that holds the initial cursor position within the field.
	The function returns an int identifying the key that the user pressed to exit the function.
=======================================================================================================*/
int edit(char *str, int row, int col, int fieldLength, int maxStrLength, bool* insertMode, int* strOffset, int* curPosition)
{
	int lenofstr, colofcon, rowofcon, restofcol, userInput;
	char* tempstr=NULL;
	char* displaystr=NULL;
	bool flag=true;

	lenofstr = std::strlen(str);
	colofcon = console.getCols();
	rowofcon = console.getRows();
	restofcol=colofcon-col;
	if(fieldLength>restofcol) fieldLength=restofcol;
		
	// allocate dynamic memory to keep the original string
	tempstr = new char[std::strlen(str)+1];	
	// allocate dynamic memory to display the editable field.
	displaystr = new char[fieldLength+1];	
	std::strcpy(tempstr, str);							
	check_strOffset(strOffset, str);
	check_curPosition(strOffset, curPosition,str, fieldLength);
	std::strncpy(displaystr, (str+(*strOffset)), fieldLength);
	displaystr[fieldLength]='\0';
	display(displaystr, row, col, fieldLength);
	display_Mode(insertMode);

	while(flag)
	{		
		userInput= GetInput_fromUser(row, col, curPosition); 
		flag=handle_userInput(userInput, str, displaystr, strOffset, curPosition, fieldLength, maxStrLength, insertMode);
		if(flag)
		{
			std::strncpy(displaystr, str+(*strOffset), fieldLength);
			displaystr[fieldLength]='\0';
			display(displaystr, row, col, fieldLength);
		}
	}

	if(userInput==ESCAPE) strcpy(str,tempstr);		//If the user presses ESCAPE, replaces the string with the original string
	
	if(tempstr)		delete [] tempstr;				// deallocate dynamic memory
	if(displaystr)	delete [] displaystr;
	return userInput;

}

/*=======================================================================================================
	This function sets the position of the cursor and gets an input from a user.
	The parameters, row,col,and *curPosition set the current cursor position.
	The function returns the input that the user presses.
=========================================================================================================*/
int GetInput_fromUser( int row, int col, int* curPosition)
{
	int userInput;
		console.setPosition(row,col+(*curPosition));
		console>> userInput;	

	return userInput;
}

/*=======================================================================================================
	This function takes userinput as a parameter and edit the string. It returns false if the user 
	presses ENTER, TAB, ESCAPE, UP, DOWN, PGUP, PGDN or any od the Function keys F(1) through F(12) inclusive.
=========================================================================================================*/
bool handle_userInput(int userInput, char* str, char* displaystr, int* strOffset, int* curPosition, 
					int fieldLength, int maxStrLength, bool* insertMode)
{
	int lenofstr=std::strlen(str);
	// moves the cursor left one character
	if(userInput==RIGHT)		
	{
		if(*curPosition<fieldLength-1 && str[*strOffset+(*curPosition)] )		(*curPosition)++;
		else if((*strOffset+fieldLength)<maxStrLength && str[*strOffset+(*curPosition)])		(*strOffset)++;		
	}
	// moves the cursor right one character
	else if(userInput==LEFT)	
	{
		if(*curPosition>0)		(*curPosition)--;
		else if(*strOffset>0)	(*strOffset)--; 
	}
	// moves the cursor to the right last character in the string
	else if(userInput==HOME)			*curPosition = *strOffset = 0;	
	// moves the cursor to the right of the last character in the string
	else if(userInput==END)
	{
		if(lenofstr >= fieldLength)
		{
			*curPosition=fieldLength-1;
			*strOffset = lenofstr-fieldLength+1;
		}
		else
		{
			*strOffset=0;
			*curPosition=lenofstr;
		}
	}
	// discards the character at the current cursor position and moves all 
	// characters to the right on the cursor position one position to the left
	else if(userInput==DEL)
	{
		leftShift(str, *strOffset, *curPosition+1);	
	}
	// discards the character to the left of the current cursor position, if possible,
	// moves the characters at and to the right of the cursor position one position to the left
	else if(userInput==BACKSPACE)
	{
		if(*curPosition>0)
		{
			leftShift(str, *strOffset, *curPosition);
			(*curPosition)--;
		}
		else if(*strOffset > 0)
		{
			leftShift(str, *strOffset, *curPosition);
			(*strOffset)--;		
		}
	}
	// call functions to change the current mode and diplay the mode on the right corner of the console
	else if(userInput==INSERT)
	{
		change_Mode(insertMode);
		display_Mode(insertMode);
	}	
	// terminates editing if the userinput is one of these keys
	else if(userInput==ENTER || userInput==TAB || userInput==ESCAPE || userInput==UP || userInput==DOWN
				|| userInput==PGUP || userInput==PGDN || (userInput>=F(1) && userInput<=F(12)))
	{
			return false;
	}
	// handle the UNKNOWN key
	// display "Unknown key" under the mode display
	else if(userInput==UNKNOWN)
	{
		display("Unknown key", 3, 65, 0);						
	} 
	else
	{
		// In insert mode, inserts a printable character into the string at the current cursor position, 
		// moves the remainder of the string to the right to make room for the inserted character
		if(*insertMode)
		{
			rightShift(str, *strOffset, *curPosition);
			str[(*strOffset)+(*curPosition)]=userInput;

			if(*curPosition < fieldLength-1)	(*curPosition)++;
			else if((*curPosition==fieldLength-1) && ((*strOffset+fieldLength)<maxStrLength))	(*strOffset)++;	
		}
		// In overwrite mode, overwrites the chatacter ar the current cursor position with a printable chatacter
		// and advances the cursor just to the right of the new character.
		else
		{	
			if(*curPosition < fieldLength-1) 
			{
				str[(*strOffset)+(*curPosition)]=userInput;	
				(*curPosition)++;
			}
			else if((*strOffset+fieldLength)<maxStrLength)
			{
				str[(*strOffset)+(*curPosition)]=userInput;	
				str[(*strOffset)+(*curPosition)+1]='\0';
				(*strOffset)++; 
			}
		}
	}
	return true;
}
	
/*=====================================================================================================
	This function displays the mode on the console.
=======================================================================================================*/	
void display_Mode(bool* insertMode)
{		
		if(*insertMode)	display("Insert", 2, 65, 9);
		else			display("Overwrite", 2, 65, 9);
}

/*=====================================================================================================
	This function changes the mode to insert or overwrite.
=======================================================================================================*/
void change_Mode(bool* insertMode)
{
			if(*insertMode)	*insertMode=false;
			else			*insertMode=true;			
}

/*=====================================================================================================
	This function checks if strOffset is valid. If it is not, it initializes 
=======================================================================================================*/
void check_strOffset(int *strOffset, char *str)
{
	int lenofstr=(std::strlen(str));
	if(str==NULL) *strOffset=0;
	else
	{
		if(strOffset==NULL) *strOffset=0;
		else if((*strOffset) > lenofstr)	*strOffset = lenofstr; 
	}
}

/*=====================================================================================================
	This function checks if curPosition is valid. If it is not, it initializes 
=======================================================================================================*/
void check_curPosition(int *strOffset, int *curPosition, char *str, int fieldLength )	
{
	int lenofstr=std::strlen(str);
	if(str==NULL) *curPosition=0;
	else
	{
		if( curPosition == NULL ) *curPosition = 0;
		else if( *curPosition > fieldLength-1 || (*curPosition) < 0 )
		{
			if((lenofstr-(*strOffset))<fieldLength)			*curPosition = lenofstr-(*strOffset);
			else if((lenofstr-(*strOffset)) >= fieldLength)		*curPosition = fieldLength;	
		}
		else if( *curPosition > (lenofstr-(*strOffset)))	*curPosition = lenofstr-(*strOffset);		
	}
}

/*=====================================================================================================
	This function shifts the string one position to the right.
=======================================================================================================*/
void rightShift(char* str, int strOffset, int curPosition)
{
		int position=strOffset+curPosition,
			lenofstr=std::strlen(str),
			i;
				
		for(i= lenofstr; i>=position;i--)
		{
				str[i+1]=str[i];
		}		
}

/*=====================================================================================================
	This function shifts the string one position to the left. 
=======================================================================================================*/
void leftShift(char* str, int strOffset, int curPosition)	
{
		int position=strOffset+curPosition,
			lenofstr=std::strlen(str),
			i;
		for(i=position; i<=lenofstr ; i++)
		{
					str[i-1]=str[i];
		}
		str[i]='\0';
}

} // end name space cio












