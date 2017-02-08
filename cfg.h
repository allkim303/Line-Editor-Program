
#ifndef __cfg__
#define __cfg__
#include <cstdlib>

#define C_MAX_NO_FIELDS 100			// the maximum number of fields
#define C_BORDER_CHARS "/-\\|/-\\|"	// a C-style null-terminated string describing the 8 \
										default border characters on a frame
#define C_FULL_FRAME -1				// a non-positive integer value that identifies a frame with a border
#define C_NO_FRAME 0				// a non-positive integer value that identifies a frame without a border
#define C_NOT_EDITABLE 0			// the key code returned by a non-editable field 
#define C_BUTTON_HIT 1				// the key code that identifies a button press



enum CDirection{
    C_STATIONARY,	// no movement
    C_MOVED_LEFT,	// moved one column left
    C_MOVED_RIGHT,	// moved one column right
    C_MOVED_UP,		// moved one row up
    C_MOVED_DOWN	// moved one row down
};

#endif