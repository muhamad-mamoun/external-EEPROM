/*
===========================================================================================================
Author       : Mamoun
Module       : External EEPROM
File Name    : external_eeprom.h
Date Created : Oct 28, 2022
Description  : Header file for the I2C-drived External EEPROM driver.
===========================================================================================================
*/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

#define EEPROM_ERROR            (0)
#define EEPROM_SUCCESS          (1)

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


/*===========================================================================================================
 * [Function Name] : EEPROM_writeByte
 * [Description]   : Read a byte in a specific address in the EEPROM.
 * [Arguments]     : <a_address>      -> Indicates to the required address in the EEPROM.
 *                   <a_data>         -> Indicates to the required byte to be written.
 * [return]        : The function returns the state of the process (success or error).
 ==========================================================================================================*/
uint8 EEPROM_writeByte(uint16 a_address, uint8 a_data);


/*===========================================================================================================
 * [Function Name] : EEPROM_readByte
 * [Description]   : Read a byte from a specific address in the EEPROM.
 * [Arguments]     : <a_address>      -> Indicates to the required address in the EEPROM.
 *                   <a_data>      -> Pointer to a byte to store the received byte.
 * [return]        : The function returns the state of the process (success or error).
 ==========================================================================================================*/
uint8 EEPROM_readByte(uint16 a_address, uint8* a_data);

#endif /* EXTERNAL_EEPROM_H_ */
