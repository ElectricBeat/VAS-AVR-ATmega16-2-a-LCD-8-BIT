/*
 * LCD 8 BIT.c
 *
 * Created: 25-04-2024 11:42:28
 * Author : SRIDHAR
 */ 

#define F_CPU 1000000UL					/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include inbuilt defined Delay header file */

#define LCD_Data_Dir		DDRA		/* Define LCD data port direction */
#define LCD_Command_Dir		DDRC		/* Define LCD command port direction register */

#define LCD_Data_Port		PORTA		/* Define LCD data port */
#define LCD_Command_Port	PORTC		/* Define LCD data port */

#define RS PC6							/* Define Register Select (data/command reg.)pin */
#define EN PC7							/* Define Enable signal pin */

void LCD_Command(unsigned char cmnd)
{
	LCD_Command_Port &= ~(1<<RS);		/* RS=0 command reg. */
	LCD_Command_Port |= (1<<EN);
	LCD_Data_Port= cmnd;				/* Enable pulse */
	_delay_us(5);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}

void LCD_Char (unsigned char char_data)	/* LCD data write function */
{
	LCD_Command_Port |= (1<<RS);		/* RS=1 Data reg. */
	LCD_Command_Port |= (1<<EN);		/* Enable Pulse */	
	LCD_Data_Port= char_data;
	_delay_us(5);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}

void LCD_Init (void)					/* LCD Initialize function */
{
	LCD_Command_Dir = 0xFF;				/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;				/* Make LCD data port direction as o/p */
	_delay_ms(20);						/* LCD Power ON delay always >15ms */
	
	LCD_Command (0x38);					/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);					/* Display ON Cursor OFF */
	LCD_Command (0x06);					/* Auto Increment cursor */
	LCD_Command (0x01);					/* Clear display */
	LCD_Command (0x80);					/* Cursor at home position */
}

void LCD_String (char *str)				/* Send string to LCD function */
{	
	int i;
	for(i=0;str[i]!=0;i++)				/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_Clear()
{
	LCD_Command (0x01);					/* clear display */
	LCD_Command (0x80);					/* cursor at home position */
}

int main()
{
	LCD_Init();							/* Initialize LCD */

	while (1)
	{
		LCD_Command (0x80);				/* Go to 1st line*/
		LCD_String("VAS");				/* write string on 1st line of LCD*/
		LCD_Command (0x1C);
		_delay_ms(100);
	}
}