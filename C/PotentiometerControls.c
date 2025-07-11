//startup function that sets all the pots to the shutdwon state until the first command goes through to begin writing to them
void MO41050_BootShutdown(){
    for(uint8_t mux = 0; mux < 12; mux++){
        for(uint8_t pot = 0; pot < 16; pot++){
            potSelect(mux, pot); //set selection
            HAL_Delay(1);   //delay to let mux settle
            MP41050_Shutdown(&hspi1, GPIOA, GPIO_PIN_0); //shtdown current pot
        }
    }
}

//function that takes in the handle type, port type, pin number, potentiometer select, and value and sets the potentiometer to that value
//function example:
//MP41050_Write(&hspi1, GPIOB, GPIO_PIN_6, 128)
void MP41050_Write_Bit(SPI_HandleTypeDef *hspi,GPIO_TypeDef* csPort, uint16_t csPin, uint8_t value) {
	if(value < 0 || value > 255){ //error checking
			printf("Error(Write_Bit): Value out of range\n");
					return; // Indicate failure
		}
	//format: [XXC1C0 XXXP0] [DDDD DDDD]
	//XX = don't care bits
	//C1C0(command bits): 00, 11 = no command executed, 01 = write data, 10 = put pots in shutdown mode
	//P0(pot select bits): 0 = nothing, 1 = pot 0
	//D...D = new register data,

	//setting the resistance, calculating D_n, implement this with a function later
	//R_WA = (R_AB)(256-D_n)/256 + R_w, R_WB = (R_AB)(D_n)/256 + R_w
	//R_WA = (50k)(256-D_n)/256 + wiper resistance, R_WB = (50k)(D_n)/256 + wiper resistance

	//shutdown mode: disconnects the "A" terminal from the resistor stack and simultaneously connects the wiper to the "B" terminal. During shutdown mode, the content of the wiper register can be changed and the pot return from shutdown to the new value. The wiper is reset to the mid-scale position upon power-up. The reset pin implements a hardware reset and also returns the wiper to mid-scale.
	//The shutdown command allows the user to put the application circuit into power-saving mode. In this mode, the a terminal A is open-circuited and the B and W terminals are shorted together. The command select bits C1C0 are set to 10. The pot selection bits P1P0 allow each pot to be shut down independently. If either P1P0 are high, the respective pot will enter shutdown mode. The data bits following the command byte still need to be transmitted for the shutdown command, but they are don't care bits.

	uint8_t command = 0b00010001;
	uint8_t data[2] = {command, value}; //concatenating bit strings

	//executing any command is accomplished by setting CS low
	//then clocking-in a command byte followed by a data byte into
	//the 16-bit shift reg, the command is executed when CS is raised

	//resets cs low to begin data transfer
	HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);

	//sends the 16 bit command
	HAL_SPI_Transmit(hspi, data, 2, HAL_MAX_DELAY);

	//sets cs high to end the data transfer
	HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
}

//same as above function but takes in resistance value instead of 0-255
void MP41050_Write_Resistance(SPI_HandleTypeDef *hspi,GPIO_TypeDef* csPort, uint16_t csPin, int res) {
	if(res < 0 || res > 50000){ //error checking
			printf("Error(Write_Resistance): Resistance out of range\n");
					return; // Indicate failure
		}

	uint8_t command = 0b00010001;
	uint8_t data[2] = {command, resistanceToBit(res)};

	HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(hspi, data, 2, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
}

//function that takes in desired potentiometer value and returns the 0-255 value that corresponds for use with the MP41510 function
uint8_t resistanceToBit(int res){
	if(res < 0 || res > 50000){ //error checking
		printf("Error(resToBit): Resistance out of range\n");
				return 0xFF; // Indicate failure
	}

	return (uint8_t)((res * 255 + 25000) / 50000); //the 25000 is added so that the truncation actually rounds

}

//function that puts the pots in shutdown mode when not being used
//in shutdown mode, the wiper gets shorted to ground and terminal A gets open circuited, this saves power for when they are not being used
//to wake up, just call the write functions
void MP41050_Shutdown(SPI_HandleTypeDef *hspi, GPIO_TypeDef* csPort, uint16_t csPin){
	uint8_t command = 0b00100001; //command says enter shutdown mode
	uint8_t data[2] = {command, 0b00000000}; //still need to send don't care bits

	HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(hspi, data, 2, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
}