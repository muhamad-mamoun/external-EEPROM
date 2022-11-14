/*
===========================================================================================================
Author       : Mamoun
Module       : I2C
File Name    : i2c.c
Date Created : Oct 28, 2022
Description  : Source file for the I2C driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "i2c.h"
#include "common_macros.h"
#include <avr/io.h>
#include <math.h>

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : I2C_init
 * [Description]   : Initialize the I2C with specific configurations.
 * [Arguments]     : <a_ptr2configuration>      -> Pointer to structure.
 *                                                 This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void I2C_init(const I2C_configurationsType* a_ptr2configuration)
{
	TWBR = a_ptr2configuration->bit_rate;      /* Set the I2C bit rate */
	TWAR = a_ptr2configuration->address;       /* Set the address of my device */
	TWSR = 0X00;                               /* Set the bit rate prescaler */
	TWCR |= (1<<TWEN);                         /* Enable the I2C operation */
}

/*===========================================================================================================
 * [Function Name] : I2C_startBit
 * [Description]   : Send the start bit to start the frame.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void I2C_startBit(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*===========================================================================================================
 * [Function Name] : I2C_stopBit
 * [Description]   : Send the stop bit to end the frame.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void I2C_stopBit(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

/*===========================================================================================================
 * [Function Name] : I2C_sendByte
 * [Description]   : Write a specific byte on the bus.
 * [Arguments]     : <a_data>      -> Indicates to the required byte.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void I2C_sendByte(uint8 a_data)
{
	TWDR = a_data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*===========================================================================================================
 * [Function Name] : I2C_receiveByteWithACK
 * [Description]   : Read a byte and Generate an acknowledge pulse.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the received byte.
 ==========================================================================================================*/
uint8 I2C_receiveByteWithACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}

/*===========================================================================================================
 * [Function Name] : I2C_receiveByteWithNACK
 * [Description]   : Read a byte WITHOUT Generating an acknowledge pulse.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the received byte.
 ==========================================================================================================*/
uint8 I2C_receiveByteWithNACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}

/*===========================================================================================================
 * [Function Name] : I2C_getStatus
 * [Description]   : Get the status of the I2C and the Two-wire Serial Bus.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the status of the I2C.
 ==========================================================================================================*/
uint8 I2C_getStatus(void)
{
	return (TWSR & 0xF8);
}
