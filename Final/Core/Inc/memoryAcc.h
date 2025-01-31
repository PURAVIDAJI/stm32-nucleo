/*
 * memoryAcc.h
 *
 *  Created on: Dec 10, 2024
 *      Author: ijk95
 */

#ifndef INC_MEMORYACC_H_
#define INC_MEMORYACC_H_


#include <stdint.h>
// Memory map definitions
#define M95C04_START 0x00000000
#define M95C04_END   0x00000FFF

#define M95256_START 0x00001000
#define M95256_END   0x00040FFF

#define M95M04_START 0x00041000
#define M95M04_END   0x00440FFF

#define M24C02_START 0x00441000
#define M24C02_END   0x004417FF

#define M24256_START 0x00441800
#define M24256_END   0x004817FF

#define M24M01_START 0x00481800
#define M24M01_END   0x005817FF




// Function prototypes
void WriteByte(uint32_t Address, uint8_t Data);
uint8_t ReadByte(uint32_t Address);



#endif /* INC_MEMORYACC_H_ */
