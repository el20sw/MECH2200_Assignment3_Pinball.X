//VT100 command functions

#include "VT100.h"
#include "Comms.h"

#define     ESC     27

extern volatile unsigned char GLOBAL_VT100_String[VT100_STRING_LENGTH];

void    VT100_HomeCursor(void)
{
   //home cursor
    SendChar(ESC);
    SendChar('[');
    SendChar('H');
}


void    VT100_ClearScreen(void)
{
    //clear screen
    SendChar(ESC);
    SendChar('[');
    SendChar('2');
    SendChar('J');
}


void    VT100_EraseToEndOfLine(void)
{
    SendChar(ESC);
    SendChar('[');
    SendChar('K');
}


void    VT100_EraseToStartOfLine(void)
{
    SendChar(ESC);
    SendChar('[');
    SendChar('1');
    SendChar('K');
}


void    VT100_EraseLine(void)
{
    SendChar(ESC);
    SendChar('[');
    SendChar('2');
    SendChar('K');
}


void    VT100_SetDefaultFont(void)
{
    SendChar(ESC);
    SendChar('(');
    SendChar('B');
}


void    VT100_SetSpecialFont(void)
{
    SendChar(ESC);
    SendChar('(');
    SendChar('0');
}


void    VT100_PositionCursor(unsigned int y, unsigned int x)
{
    //position cursor to location row and column
    SendChar(ESC);
    SendChar('[');
    DecimalToResultString(y, GLOBAL_VT100_String, 0);
    SendMessage(GLOBAL_VT100_String);
    SendChar(';');
    DecimalToResultString(x, GLOBAL_VT100_String, 0);
    SendMessage(GLOBAL_VT100_String);
    SendChar('H');
}


void    VT100_CursorUp(unsigned int y)
{
    //move cursor up by defined number of lines
    SendChar(ESC);
    SendChar('[');
    DecimalToResultString(y, GLOBAL_VT100_String, 0);
    SendMessage(GLOBAL_VT100_String);
    SendChar('A');
}


void    VT100_CursorDown(unsigned int y)
{
    //move cursor down by defined number of lines
    SendChar(ESC);
    SendChar('[');
    DecimalToResultString(y, GLOBAL_VT100_String, 0);
    SendMessage(GLOBAL_VT100_String);
    SendChar('B');
}


void    VT100_CursorRight(unsigned int x)
{
    //move cursor right by defined number of rows
    SendChar(ESC);
    SendChar('[');
    DecimalToResultString(x, GLOBAL_VT100_String, 0);
    SendMessage(GLOBAL_VT100_String);
    SendChar('C');
}


void    VT100_CursorLeft(unsigned int x)
{
    //move cursor left by defined number of rows
    SendChar(ESC);
    SendChar('[');
    DecimalToResultString(x, GLOBAL_VT100_String, 0);
    SendMessage(GLOBAL_VT100_String);
    SendChar('D');
}


void    VT100_SetAttribute(unsigned int Value)
{
    //set the attribute as passed in 'Value'
    // 0 = reset all
    // 1 = Bright
    // 2 = Dim
    // 4 = Underscore
    // 5 = Blink
    // 7 = Negative

    //30 = foreground black
    //31 = foreground red
    //32 = foreground green
    //33 = foreground yellow
    //34 = foreground blue
    //35 = foreground magenta
    //36 = foreground cyan
    //37 = foreground white
    
    //40 = background black
    //41 = background red
    //42 = background green
    //43 = background yellow
    //44 = background blue
    //45 = background magenta
    //46 = background cyan
    //47 = background white
    
    SendChar(ESC);
    SendChar('[');
    DecimalToResultString(Value, GLOBAL_VT100_String, 0);
    SendMessage(GLOBAL_VT100_String);
    SendChar('m');
}



void    VT100_SingleHeightSingleWidth(void)
{
    SendChar(ESC);
    SendChar('#');
    SendChar('5');
}



void    VT100_SingleHeightDoubleWidth(void)
{
    SendChar(ESC);
    SendChar('#');
    SendChar('6');
}


void    VT100_DoubleHeightSingleWidthTop(void)
{
    SendChar(ESC);
    SendChar('#');
    SendChar('1');
}


void    VT100_DoubleHeightSingleWidthBottom(void)
{
    SendChar(ESC);
    SendChar('#');
    SendChar('2');
}



void    VT100_DoubleHeightDoubleWidthTop(void)
{
    SendChar(ESC);
    SendChar('#');
    SendChar('3');
}


void    VT100_DoubleHeightDoubleWidthBottom(void)
{
    SendChar(ESC);
    SendChar('#');
    SendChar('4');
}

