// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef VT100_H
#define	VT100_H

#include <xc.h> // include processor files - each processor file is guarded.  

//define constants
#define     VT100_STRING_LENGTH 20

//define attributes
#define     RESET_ALL           0
#define     BRIGHT              1
#define     DIM                 2
#define     UNDERSCORE          4
#define     BLINK               5
#define     NEGATIVE            7

#define     FOREGROUND_BLACK    30
#define     FOREGROUND_RED      31
#define     FOREGROUND_GREEN    32
#define     FOREGROUND_YELLOW   33
#define     FOREGROUND_BLUE     34
#define     FOREGROUND_MAGENTA  35
#define     FOREGROUND_CYAN     36
#define     FOREGROUND_WHITE    37

#define     BACKGROUND_BLACK    40
#define     BACKGROUND_RED      41
#define     BACKGROUND_GREEN    42
#define     BACKGROUND_YELLOW   43
#define     BACKGROUND_BLUE     44
#define     BACKGROUND_MAGENTA  45
#define     BACKGROUND_CYAN     46
#define     BACKGROUND_WHITE    47


//list functions

void    VT100_HomeCursor(void);
void    VT100_ClearScreen(void);
void    VT100_EraseToEndOfLine(void);
void    VT100_EraseToStartOfLine(void);
void    VT100_EraseLine(void);
void    VT100_SetDefaultFont(void);
void    VT100_SetSpecialFont(void);
void    VT100_PositionCursor(unsigned int , unsigned int );
void    VT100_CursorUp(unsigned int);
void    VT100_CursorDown(unsigned int);
void    VT100_CursorRight(unsigned int);
void    VT100_CursorLeft(unsigned int);
void    VT100_SetAttribute(unsigned int);
void    VT100_SingleHeightSingleWidth(void);
void    VT100_SingleHeightDoubleWidth(void);
void    VT100_DoubleHeightSingleWidthTop(void);
void    VT100_DoubleHeightSingleWidthBottom(void);
void    VT100_DoubleHeightDoubleWidthTop(void);
void    VT100_DoubleHeightDoubleWidthBottom(void);


#endif	/* VT100_H */