/*
===========================================================================================================
Author       : Mamoun
Module       : I2C
File Name    : i2c.h
Date Created : Oct 28, 2022
Description  : Header file for the I2C driver.
===========================================================================================================
*/


#ifndef I2C_H_
#define I2C_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

//#define I2C_SCL_FREQ          (400000U)

/* I2C Status Bits in the TWSR Register */
#define I2C_START              (0x08)
#define I2C_REPEATED_START     (0x10)
#define I2C_MT_SLA_W_ACK       (0x18)
#define I2C_MT_SLA_R_ACK       (0x40)
#define I2C_MT_DATA_ACK        (0x28)
#define I2C_MR_DATA_ACK        (0x50)
#define I2C_MR_DATA_NACK       (0x58)

/*===========================================================================================================
                                       < User-defined Data Types >
===========================================================================================================*/

typedef unsigned char I2C_addressType;
typedef unsigned char I2C_bitRateType;

//typedef enum
//{
//	I2C_PRESCALER_1,I2C_PRESCALER_4,I2C_PRESCALER_16,I2C_PRESCALER_64
//}I2C_prescalerType;

typedef struct
{
	I2C_addressType address;
	I2C_bitRateType bit_rate;
}I2C_configurationsType;

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


/*===========================================================================================================
 * [Function Name] : I2C_init
 * [Description]   : Initialize the I2C with specific configurations.
 * [Arguments]     : <a_ptr2configuration>      -> Pointer to structure.
 *                                                 This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void I2C_init(const I2C_configurationsType* a_ptr2configuration);


/*===========================================================================================================
 * [Function Name] : I2C_startBit
 * [Description]   : Send the start bit to start the frame.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void I2C_startBit(void);


/*===========================================================================================================
 * [Function Name] : I2C_stopBit
 * [Description]   : Send the stop bit to end the frame.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void I2C_stopBit(void);


/*===========================================================================================================
 * [Function Name] : I2C_sendByte
 * [Description]   : Write a specific byte on the bus.
 * [Arguments]     : <a_data>      -> Indicates to the required byte.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void I2C_sendByte(uint8 a_data);


/*===========================================================================================================
 * [Function Name] : I2C_receiveByteWithACK
 * [Description]   : Read a byte and Generate an acknowledge pulse.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the received byte.
 ==========================================================================================================*/
uint8 I2C_receiveByteWithACK(void);


/*===========================================================================================================
 * [Function Name] : I2C_receiveByteWithNACK
 * [Description]   : Read a byte WITHOUT Generating an acknowledge pulse.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the received byte.
 ==========================================================================================================*/
uint8 I2C_receiveByteWithNACK(void);


/*===========================================================================================================
 * [Function Name] : I2C_getStatus
 * [Description]   : Get the status of the I2C and the Two-wire Serial Bus.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the status of the I2C.
 ==========================================================================================================*/
uint8 I2C_getStatus(void);

#endif /* I2C_H_ */
