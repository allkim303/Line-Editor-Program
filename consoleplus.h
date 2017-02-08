/*=====================================================================================================
	Minji Kim	
	OOP344A
	Feb.07.2014
=======================================================================================================*/

namespace cio{

void display(const char *str, int row, int col, int fieldLen);
int edit(char *str, int row, int col, int fieldLength, int maxStrLength, bool* insertMode, 
			int* strOffset, int* curPosition) ;

void check_strOffset(int *stroffset, char *str);
void check_curPosition(int *strOffset, int *curPosition, char *str, int fieldLength );

int GetInput_fromUser( int row, int col, int* curPosition);
bool handle_userInput(int userInput, char* str, char* displaystr, int* strOffset, int* curPosition, 
					int fieldLength, int maxStrLength, bool* insertMode);
void display_Mode(bool* insertMode);
void change_Mode(bool* insertMode);

void rightShift(char* str, int strOffset, int curPosition);
void leftShift(char* str, int strOffset, int curPosition);

} // end name space cio
