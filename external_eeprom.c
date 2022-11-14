/*
===========================================================================================================
Author       : Mamoun
Module       : External EEPROM
File Name    : external_eeprom.c
Date Created : Oct 28, 2022
Description  : Source file for the I2C-drived External EEPROM driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "external_eeprom.h"
#include "i2c.h"

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : EEPROM_writeByte
 * [Description]   : Read a byte in a specific address in the EEPROM.
 * [Arguments]     : <a_address>      -> Indicates to the required address in the EEPROM.
 *                   <a_data>         -> Indicates to the required byte to be written.
 * [return]        : The function returns the state of the process (success or error).
 ==========================================================================================================*/
uint8 EEPROM_writeByte(uint16 a_address, uint8 a_data)
{
	uint8 slave_address = (uint8)(((a_address>>7)&0X000E)|(0X00A0));

	I2C_startBit();
	if(I2C_getStatus() != I2C_START)
		return EEPROM_ERROR;

	I2C_sendByte(slave_address);
	if(I2C_getStatus() != I2C_MT_SLA_W_ACK)
		return EEPROM_ERROR;

	I2C_sendByte((uint8)a_address);
	if(I2C_getStatus() != I2C_MT_DATA_ACK)
		return EEPROM_ERROR;

	I2C_sendByte(a_data);
	if(I2C_getStatus() != I2C_MT_DATA_ACK)
		return EEPROM_ERROR;

	I2C_stopBit();
	return EEPROM_SUCCESS;
}

/*===========================================================================================================
 * [Function Name] : EEPROM_readByte
 * [Description]   : Read a byte from a specific address in the EEPROM.
 * [Arguments]     : <a_address>      -> Indicates to the required address in the EEPROM.
 *                   <a_data>      -> Pointer to a byte to store the received byte.
 * [return]        : The function returns the state of the process (success or error).
 ==========================================================================================================*/
uint8 EEPROM_readByte(uint16 a_address, uint8* a_data)
{
	uint8 slave_address = (uint8)(((a_address>>7)&0X000E)|(0X00A0));

	I2C_startBit();
	if(I2C_getStatus() != I2C_START)
		return EEPROM_ERROR;

	I2C_sendByte(slave_address);
	if(I2C_getStatus() != I2C_MT_SLA_W_ACK)
		return EEPROM_ERROR;

	I2C_sendByte((uint8)a_address);
	if(I2C_getStatus() != I2C_MT_DATA_ACK)
		return EEPROM_ERROR;

	I2C_startBit();
	if(I2C_getStatus() != I2C_REPEATED_START)
		return EEPROM_ERROR;

	I2C_sendByte(slave_address|0X01);
	if(I2C_getStatus() != I2C_MT_SLA_R_ACK)
		return EEPROM_ERROR;

	*a_data = I2C_receiveByteWithNACK();
	if(I2C_getStatus() != I2C_MR_DATA_NACK)
		return EEPROM_ERROR;

	I2C_stopBit();
	return EEPROM_SUCCESS;
}
