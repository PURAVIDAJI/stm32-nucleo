#include "M95.h"
#include "spi.h"

void EnableChipSelectM95(uint8_t M95Type)
{
	switch (M95Type){
	case 0:
		HAL_GPIO_WritePin(U5_CS_GPIO_Port, U5_CS_Pin,GPIO_PIN_RESET); //CS-> low
		break;
	case 1:
		HAL_GPIO_WritePin(U6_CS_GPIO_Port, U6_CS_Pin, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(U7_CS_GPIO_Port, U7_CS_Pin, GPIO_PIN_RESET);
		break;
	}
} //default -high

void DisableChipSelectM95(uint8_t M95Type)
{
	switch (M95Type){
	case 0:
		HAL_GPIO_WritePin(U5_CS_GPIO_Port, U5_CS_Pin,GPIO_PIN_SET); //CS-> high
		break;
	case 1:
		HAL_GPIO_WritePin(U6_CS_GPIO_Port, U6_CS_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(U7_CS_GPIO_Port, U7_CS_Pin, GPIO_PIN_SET);
		break;
	}




}
void DisableWriteProtectM95(void)
{

	HAL_GPIO_WritePin(M95_WPn_GPIO_Port, M95_WPn_Pin, GPIO_PIN_SET);


}
//defualt high - WP disabled,
//WP -high ->bp1,bp0 change o

void DisableHoldM95(void)
{

	HAL_GPIO_WritePin(M95_Hn_GPIO_Port, M95_Hn_Pin, GPIO_PIN_SET);



}
//defualt high - Hold disabled,
//Hd -high ->communication o
//Hd -low -> communication stop




void WriteEnableM95(uint8_t M95Type)
{
	uint8_t Command =SPI_WREN;

	//Enable Chip select
	EnableChipSelectM95(M95Type);
	//Send Command
	SPISendByte(Command);
	//Disable chip select.
	DisableChipSelectM95(M95Type);


}
void WriteStatusRegisterM95(uint8_t M95Type, uint8_t WriteData)
{
	uint8_t Command =SPI_WRSR;

		//enable write
	WriteEnableM95(M95Type);

		//Enable Chip select
	EnableChipSelectM95(M95Type);
		//Send Command and write
	SPISendByte(Command);
	 SPISendByte(WriteData);

		//Disable chip select.
	DisableChipSelectM95(M95Type);
//	while (ReadStatusRegisterM95(M95Type) & 0x01) {
//	        // WIP bit-1 => await
//		    }

}


uint8_t ReadStatusRegisterM95(uint8_t M95Type)
{
	uint8_t Command =SPI_RDSR;
	uint8_t ReturnValue =0;
	//Enable Chip select
	EnableChipSelectM95(M95Type);

	//Send Command and receive the data
	SPISendByte(Command);

	ReturnValue =SPIReceiveByte();

	//Disable chip select.
	DisableChipSelectM95(M95Type);

return ReturnValue;
}
void WriteByteM95(uint8_t M95Type, uint32_t Address, uint8_t WriteData)
{
	 uint8_t Command = SPI_WRITE;

	 WriteEnableM95(M95Type);

	 EnableChipSelectM95(M95Type);

	 SPISendByte(Command);


	 if(M95Type==0){
		 SPISendByte(Address & 0xFF);
	 }
	 else if(M95Type==1){
		 SPISendByte((Address >> 8) & 0xFF);
		 SPISendByte(Address & 0xFF);
	 }else if(M95Type==2){
		 SPISendByte((Address >> 16) & 0xFF);
		 SPISendByte((Address >> 8) & 0xFF);
		 SPISendByte(Address & 0xFF);
	 }


	 SPISendByte(WriteData);

	 DisableChipSelectM95(M95Type);



}
uint8_t ReadByteM95(uint8_t M95Type, uint32_t Address)
{
	uint8_t Command = SPI_READ;
	uint8_t ReturnValue = 0;


	 EnableChipSelectM95(M95Type);

	 SPISendByte(Command);


	 if(M95Type==0){
		 SPISendByte(Address & 0xFF);
	 }
	 else if(M95Type==1){
		 SPISendByte((Address >> 8) & 0xFF);
		 SPISendByte(Address & 0xFF);
	 }else if(M95Type==2){
		 SPISendByte((Address >> 16) & 0xFF);
		 SPISendByte((Address >> 8) & 0xFF);
		 SPISendByte(Address & 0xFF);
	 }

	 ReturnValue = SPIReceiveByte();
	 DisableChipSelectM95(M95Type);



return ReturnValue;
}
