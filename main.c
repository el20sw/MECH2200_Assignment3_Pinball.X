/*
 * File:   main.c
 * Author: samwi
 *
 * Created on 12 May 2022, 18:51
 */

#include "main.h"

void main(void) {
    
    unsigned int StringStatus;
    unsigned int Value;
    unsigned int SPIAddress;
    unsigned int SPIValue;
    unsigned int i;

    //wait for PLL to stabilise
    while(OSCSTATbits.PLLR == 0);
    
    InitialisePorts(); 
    InitialiseComms();
    InitialiseADC();
    InitialiseDAC();
    InitialisePWM_10Bit();
    InitialisePWM_16Bit();
    InitialiseTimers();
    InitialiseSPI();
    InitialiseDRV8711();
    
    //enable interrupts
    INTCONbits.PEIE = 1;        //enable peripheral interrupts
    INTCONbits.GIE = 1;         //enable interrupts
    
    while (1) {
        //display options list
        DisplaySystemOptionsList();

        //test for user input
        StringStatus = GetString(1, GLOBAL_RxString);
        if (StringStatus != STRING_OK) {
            //string error
            DisplayStringError(StringStatus);
        } else {
            //string OK
            //convert to binary
            Value = StringToInteger(GLOBAL_RxString);
            //switch statement to perform requested action
            switch(Value) {
                case 1:
                    TestVT100();
                    break;
                    
                default:
                    SendMessage(InvalidNumber);
                    
            }
        }
    }
    
    //end of main loop. Should never get to this point
    return;
}

//*********************************************
//display string error
void DisplayStringError(unsigned int ErrorValue) {
    switch(ErrorValue)
    {
        case TOO_LONG:  //string is too long
            SendMessage(MessageTooLong);
            break;
            
        case NO_DATA:  //string has no data
            SendMessage(MessageNoValue);
            break;
            
        case INVALID_STRING:  //string has too many decimal points
            SendMessage(TooManyDecimalPoints);
            break;
            
        case VALUE_TOO_LARGE:  //string exceeds maximum value
            SendMessage(TooLarge);
            break;
            
        case VALUE_TOO_SMALL:  //string exceeds minimum value
            SendMessage(TooSmall);
            break;
            
        //No default
    }
}

//*********************************************
//Display Main Menu
void DisplaySystemOptionsList(void) {
    SendMessage(OptionMessage);
    SendMessage(CRLF);
    SendMessage(OptionMessage1);
    SendMessage(OptionSelectMessage);
}

//*********************************************
//VT100 Testing Suite
void    TestVT100(void)
{
    unsigned int i;
    unsigned int StringStatus;
    
    VT100_SetDefaultFont();
    VT100_SetAttribute(FOREGROUND_WHITE);
    VT100_SetAttribute(BACKGROUND_BLACK);
    VT100_SingleHeightSingleWidth();

    //clear the screen
    VT100_ClearScreen();
    //Home the cursor to location 1,1
    VT100_HomeCursor();
    //send the character 'a'
    SendChar('a');
    //switch to the alternate /extended font
    VT100_SetSpecialFont();
    //send the checkerboard character
    SendChar('a');

    //return to the normal font
    VT100_SetDefaultFont();
    //position the cursor to line 2 column 20
    VT100_PositionCursor(2, 20);
    //change the colour of the background to blue and the text to red
    VT100_SetAttribute(FOREGROUND_RED);
    VT100_SetAttribute(BACKGROUND_BLUE);
    //send the test message
    SendMessage(VT100_TestMessage);

    //position the cursor to line 4 column 20
    VT100_PositionCursor(4, 20);
    //switch to single height double width characters on the current line
    //this affects the whole line and also the cursor position value
    //the lines are still correct but the x position is now halved 
    VT100_SingleHeightDoubleWidth();
    //set the text to white text on black background
    VT100_SetAttribute(FOREGROUND_WHITE);
    VT100_SetAttribute(BACKGROUND_BLACK);
    //send the test message
    SendMessage(VT100_TestMessage);
    //move the cursor down a single line
    VT100_CursorDown(1);
    //set the text to white text on black background
    VT100_SetAttribute(FOREGROUND_YELLOW);
    VT100_SetAttribute(BACKGROUND_RED);
    //send the test message
    SendMessage(VT100_TestMessage);

    //position the cursor to line 10 column 20
    VT100_PositionCursor(10, 20);
    //set this line to the top part of double height double width
    VT100_DoubleHeightDoubleWidthTop();
    //send the test message
    SendMessage(VT100_TestMessage);
    //reposition the cursor to line 11 column 20
    VT100_PositionCursor(11, 20);
    //set this line to the bottom part of double height double width
    VT100_DoubleHeightDoubleWidthBottom();
    //send the test message
    SendMessage(VT100_TestMessage);

    //add text to the single height double width line (line 4)
    VT100_PositionCursor(4, 40);
    //set the text colours
    VT100_SetAttribute(FOREGROUND_MAGENTA);
    VT100_SetAttribute(BACKGROUND_YELLOW);
    //send the test message
    SendMessage(VT100_TestMessage);

    //add text to the double height double width line (line 10 and 11)
    VT100_PositionCursor(10, 40);
    //set the text colours
    VT100_SetAttribute(FOREGROUND_YELLOW);
    VT100_SetAttribute(BACKGROUND_CYAN);
    //send the test message to the top line
    SendMessage(VT100_TestMessage);
    //position cursor to the bottom line
    VT100_PositionCursor(11, 40);
    //send the test message
    SendMessage(VT100_TestMessage);

    //draw a box using special characters
    //set the text colours
    VT100_SetAttribute(FOREGROUND_WHITE);
    VT100_SetAttribute(BACKGROUND_BLACK);
    VT100_SetSpecialFont();
    //set start position
    VT100_PositionCursor(14, 20);
    //place a top left corner box character
    SendChar('l');
    //create the upper line
    for (i = 0; i <= 20; i++)
    {
        SendChar('q');
    }
    //insert the upper right corner
    SendChar('k');
    // create the vertical line of the box
    for (i = 0; i <= 8; i++)
    {
        VT100_CursorLeft(1);
        VT100_CursorDown(1);
        SendChar('x');
    }
    //create the lower line
    //set start position
    VT100_PositionCursor(24, 20);
    //place a bottom left corner box character
    SendChar('m');
    //create the lower line
    for (i = 0; i <= 20; i++)
    {
        SendChar('q');
    }
    //create the lower right corner
    SendChar('j');
    // create the left vertical line of the box
    //set start position
    VT100_PositionCursor(14, 20);
    for (i = 0; i <= 8; i++)
    {
        VT100_CursorDown(1);
        SendChar('x');
        VT100_CursorLeft(1);
    }

    //place blinking text in the box
    //restore to normal font
    VT100_SetDefaultFont();
    //set start position
    VT100_PositionCursor(19, 29);
    //set the text colours
    VT100_SetAttribute(FOREGROUND_YELLOW);
    VT100_SetAttribute(BACKGROUND_BLUE);
    //set attribute to blink text
    VT100_SetAttribute(BLINK);
    //send message
    SendMessage(VT100_TestMessage);

    
    //Pinball Message
    VT100_SetAttribute(RESET_ALL);
    VT100_SetDefaultFont();
    VT100_PositionCursor(19, 50);
    VT100_SetAttribute(FOREGROUND_WHITE);
    VT100_SetAttribute(BACKGROUND_BLACK);
    SendMessage(VT100_TestMessage2);
    
    //move cursor back to the start
    VT100_PositionCursor(1, 1);
    VT100_SetAttribute(FOREGROUND_WHITE);
    VT100_SetAttribute(BACKGROUND_BLACK);
    
    //display return message
    //make blink
    VT100_SetAttribute(BLINK);
    //position the cursor to line 30 column 15
    VT100_PositionCursor(30, 15);
    //set this line to the top part of double height double width
    VT100_DoubleHeightDoubleWidthTop();
    //send the test message
    SendMessage(VT100_ReturnMessage);
    //reposition the cursor to line 11 column 20
    VT100_PositionCursor(31, 15);
    //set this line to the bottom part of double height double width
    VT100_DoubleHeightDoubleWidthBottom();
    //send the test message
    SendMessage(VT100_ReturnMessage);
    
    //wait for a any character press    
    StringStatus = GetString(2,GLOBAL_RxString);
    
    //clear the screen and all attributes
    VT100_SetAttribute(RESET_ALL);
    //clear the screen
    VT100_ClearScreen();
    //Home the cursor to location 1,1
    VT100_HomeCursor();
}