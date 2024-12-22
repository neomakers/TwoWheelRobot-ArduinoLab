#ifndef  MSERIAL_H_
#define  MSERIAL_H_
#include <Arduino.h>

#define OLED_CMD  0  // Command mode
#define OLED_DATA 1 // Data mode

class MSerial
{
  public:
    // Test function: Input a string
    void setstr(String str);

    // Test function: Get the string
    String getstr();

    // Inverse function: Switch between normal and inverse display
    void OLED_ColorTurn(u8 i);

    // Rotate the screen by 180 degrees
    void OLED_DisplayTurn(u8 i);

    // Send one byte to the OLED
    // mode: data/command flag; 0 means command; 1 means data
    void OLED_WR_Byte(u8 dat, u8 mode);

    // Set the position for displaying on the OLED
    void OLED_Set_Pos(u8 x, u8 y);

    // Turn on the OLED display
    void OLED_Display_On(void);

    // Turn off the OLED display
    void OLED_Display_Off(void);

    // Clear the OLED screen
    // After clearing, the screen will be all black, like it is turned off!
    void OLED_Clear(void);

    // Display a character at the specified position
    // x: 0 to 127 (X position)
    // y: 0 to 63 (Y position)
    // sizey: font size, 6x8 or 8x16
    void OLED_ShowChar(u8 x, u8 y, const u8 chr, u8 sizey);

    // Power function: Calculate m raised to the power of n
    u32 oled_pow(u8 m, u8 n);

    // Display a number at a specified position
    // x, y: Starting coordinates
    // num: The number to display
    // len: Number of digits in the number
    // sizey: Font size
    void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 sizey);

    // Display a string at a specified position
    void OLED_ShowString(u8 x, u8 y, const char *chr, u8 sizey);

    // Display Chinese characters
    void OLED_ShowChinese(u8 x, u8 y, const u8 no, u8 sizey);

    // Display custom Chinese characters (Resource and Environmental Engineering)
    void OLED_ShowMyChines();

    // Display an image (bitmap) at a specified position
    // x, y: Coordinates to start drawing
    // sizex, sizey: Width and height of the image
    // BMP: The image in the form of a byte array
    void OLED_DrawBMP(u8 x, u8 y, u8 sizex, u8 sizey, const u8 BMP[]);

    // Initialize the OLED display
    void OLED_Init(void);

  private:
    String str = "";  // A private member to store the string
};

#endif
