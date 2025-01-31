#include "M24.h"
extern I2C_HandleTypeDef hi2c1;




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

void WriteByteM24(uint8_t M24Type, uint32_t Address, uint8_t WriteData)
{


	//M24Type자체가 디바이스 주소인데, 디바이스 주소 받아서, 맨끝 비트는 0으로 리셋해주어야 함
	uint16_t devAddr=M24Type & 0xFE;
	//각 장치 별로 메모리내의 어드레스 주소가 다를 것이다. 이것을 참조해서 데이터 몇 번 보내는지 파악해야함.
	uint16_t number =0;
	uint8_t pData[3];
	if(M24Type ==0xA8U){
		number = 2;

		pData[0]=Address & 0xFF;
		pData[1] = WriteData;
			}
	else if(M24Type ==0xAAU || M24Type ==0xACU){
		number = 3;

		pData[0] = (Address >> 8) & 0xFF;
		pData[1] = Address & 0xFF;
		pData[2] = WriteData;


	}

	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, devAddr, pData, number, HAL_MAX_DELAY);
	if (status != HAL_OK) {
	    printf("HAL I2C Error: 0x%X\n", HAL_I2C_GetError(&hi2c1));
	}
	while(HAL_I2C_IsDeviceReady(&hi2c1, devAddr,1,HAL_MAX_DELAY)!=HAL_OK){

	};
}


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

uint8_t ReadByteM24(uint8_t M24Type, uint32_t Address)
{
uint8_t ReturnValue = 0;
uint16_t devAddr = M24Type & 0xFE;


uint8_t memAddress[2];
uint16_t number=0;
if(M24Type ==0xA8U){
		number = 1;

		memAddress[0]=Address & 0xFF;
			}
	else if(M24Type ==0xAAU || M24Type ==0xACU){
		number = 2;

		memAddress[0] = (Address >> 8) & 0xFF;
		memAddress[1] = Address & 0xFF;



	}
if (HAL_I2C_Master_Transmit(&hi2c1, devAddr, memAddress, number, HAL_MAX_DELAY) != HAL_OK) {
	printf("I2C Transmit Error\n");
    return 0;
}
devAddr = M24Type | 0x01;
if (HAL_I2C_Master_Receive(&hi2c1, devAddr, &ReturnValue, 1, HAL_MAX_DELAY) != HAL_OK) {

        return 0;
    }


return ReturnValue;
}
