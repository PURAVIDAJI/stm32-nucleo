/*
 * memoryAcc.c
 *
 *  Created on: Dec 10, 2024
 *      Author: ijk95
 */
#include "memoryAcc.h"
#include "M95.h"
#include "M24.h"
#include "spi.h"

void WriteByte(uint32_t Address, uint8_t Data) {
    if (Address >= M95C04_START && Address <= M95C04_END) {
        // SPI write for M95C04
        WriteByteM95(M95040, Address - M95C04_START, Data);
    } else if (Address >= M95256_START && Address <= M95256_END) {
        // SPI write for M95256
        WriteByteM95(M95256, Address - M95256_START, Data);
    } else if (Address >= M95M04_START && Address <= M95M04_END) {
        // SPI write for M95M04
        WriteByteM95(M95M04, Address - M95M04_START, Data);
    } else if (Address >= M24C02_START && Address <= M24C02_END) {
        // I2C write for M24C02
    	WriteByteM24(M24C02_I2C_ADDR, Address - M24C02_START, Data);
    } else if (Address >= M24256_START && Address <= M24256_END) {
        // I2C write for M24256
    	WriteByteM24(M24256_I2C_ADDR, Address - M24256_START, Data);
    } else if (Address >= M24M01_START && Address <= M24M01_END) {
        // I2C write for M24M01
    	WriteByteM24(M24M01_I2C_ADDR, Address - M24M01_START, Data);
    }
}
uint8_t ReadByte(uint32_t Address) {
	 if (Address >= M95C04_START && Address <= M95C04_END) {
	        // SPI read for M95C04
	        return ReadByteM95(M95040, Address - M95C04_START);
	    } else if (Address >= M95256_START && Address <= M95256_END) {
	        // SPI read for M95256
	        return ReadByteM95(M95256, Address - M95256_START);
	    } else if (Address >= M95M04_START && Address <= M95M04_END) {
	        // SPI read for M95M04
	        return ReadByteM95(M95M04, Address - M95M04_START);
	    } else if (Address >= M24C02_START && Address <= M24C02_END) {
	        // I2C read for M24C02
	        return ReadByteM24(M24C02_I2C_ADDR, Address - M24C02_START);
	    } else if (Address >= M24256_START && Address <= M24256_END) {
	        // I2C read for M24256
	        return ReadByteM24(M24256_I2C_ADDR, Address - M24256_START);
	    } else if (Address >= M24M01_START && Address <= M24M01_END) {
	        // I2C read for M24M01
	        return ReadByteM24(M24M01_I2C_ADDR, Address - M24M01_START);
	    }
	    return 0xFF; // Return 0xFF for invalid addresses
	}
