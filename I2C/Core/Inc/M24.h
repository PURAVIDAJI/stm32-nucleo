#ifndef INC_M24_H_
#define INC_M24_H_
#include "main.h"
#include "i2c.h"
#define M24C02_I2C_ADDR 0xA8U
#define M24256_I2C_ADDR 0xAAU
#define M24M01_I2C_ADDR 0xACU
/**
* @brief Write a byte of data using I2C.
* @retval None.
* @param Address: The memory address. The address is assumed to
* be located in the lower 3 bytes.
* @param WriteData: The data to be written.
* @param M24Type: This is the I2C address for the memory device.
*
* The accepted values are:
* #define M24C02_I2C_ADDR 0xA8U
* #define M24256_I2C_ADDR 0xAAU
* #define M24M01_I2C_ADDR 0xACU
*/
void WriteByteM24(uint8_t M24Type, uint32_t Address, uint8_t WriteData);
/**
* @brief Read a byte of data using I2C.
* @param Address: The memory address. The address is assumed to
* be located in the lower 3 bytes.
* @param Address: The memory address.
* @param M24Type: This is the I2C address for the memory device.
*
* The accepted values are:
* #define M24C02_I2C_ADDR 0xA8U
* #define M24256_I2C_ADDR 0xAAU
* #define M24M01_I2C_ADDR 0xACU
*/
uint8_t ReadByteM24(uint8_t M24Type, uint32_t Address);
#endif /* INC_M24_H_ */
