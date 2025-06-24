#include "MuxedPots.hpp"

//being private methods
void MuxedPots::potSelect(uint8_t muxInd, uint8_t potInd){
    if(muxInd < 0 || muxInd > 11){
        printf("Mux index is out of bounds\n");
        return;
    }
    if(potInd < 0 || potInd > 15){
        printf("Channel index is out of bounds\n");
        return;
    }

    //setting the mux index using Bit set/Reset Register to update values simluataneously
    //clear S0-S3 on the GPIOB (PB12-PB15)
    GPIOB->BSRR = (GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15) << 16;

    //set new values for S0-S3
    GPIOB->BSRR = 
                ((potInd & 0x01) ? GPIO_PIN_12 : 0) |
                ((potInd & 0x02) ? GPIO_PIN_13 : 0) |
                ((potInd & 0x03) ? GPIO_PIN_14 : 0) |
                ((potInd & 0x04) ? GPIO_PIN_15 : 0);

    //clear S4-S7 on the GPIOA(PA8-PA11)
    GPIOA->BSRR = (GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11) << 16;
    
    //set new values for S4-S7
    GPIOB->BSRR = 
                ((muxInd & 0x01) ? GPIO_PIN_8 : 0) |
                ((muxInd & 0x02) ? GPIO_PIN_9 : 0) |
                ((muxInd & 0x03) ? GPIO_PIN_10 : 0) |
                ((muxInd & 0x04) ? GPIO_PIN_11 : 0);
}

uint8_t MuxedPots::resistanceToBit(int res){
    if(res < 0 || res > 50000){ //error checking
        cerr <<"Error(resToBit): Resistance out of range\n";
                return 0xFF; // Indicate failure
    }

    return static_cast<uint8_t>((res * 255 + 25000) / 50000); //the 25000 is added so that the truncation actually rounds
}

void MuxedPots::writeBit(uint8_t value) {
    if(value < 0 || value > 255){ //error checking
            cerr << "Error(writeBit): Value out of range\n";
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

    //uint8_t command = 0b00010001;
    uint8_t data[2] = {0b00010001, value}; //concatenating bit strings

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

void MuxedPots::writeResistance(int res){
    if(res < 0 || res > 50000){ //error checking
            cerr << "Error(writeResistance): Resistance out of range\n";
                    return; // Indicate failure
        }

    //uint8_t command = 0b00010001;
    uint8_t data[2] = {0b00010001, resistanceToBit(res)};

    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);

    HAL_SPI_Transmit(hspi, data, 2, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
}

void MuxedPots::shutdownIN(){
    //uint8_t command = 0b00100001; //command says enter shutdown mode
    uint8_t data[2] = {0b00100001, 0b00000000}; //still need to send don't care bits

    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);

    HAL_SPI_Transmit(hspi, data, 2, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
}

//begin public methods
MuxedPots::MuxedPots(SPI_HandleTypeDef spiHandle, GPIO_TypeDef* port, uint16_t pin)
            : hspi(spiHandle), csPort(port), csPin(pin) {}

void MuxedPots::setBit(uint8_t muxInd, uint8_t potInd, uint8_t value){
    potSelect(muxInd, potInd);
    HAL_Delay(1);
    writeBit(value);
}

void MuxedPots::setResistance(uint8_t muxInd, uint8_t potInd, int res){
    potSelect(muxInd, potInd);
    HAL_Delay(1);
    writeResistance(value);
}

void MuxedPots::shutdown(uint8_t muxInd, uint8_t potInd){
    selectPot(muxInd, potInd);
    HAL_Delay(1);
    shutdownIN();
}

void MuxedPots::shutdownAll(){
    for(uint8_t mux = 0; mux < 12; mux++){
        for(uint8_t pot = 0; pot < 16; pot++){
            potSelect(mux, pot); //set selection
            HAL_Delay(1);   //delay to let mux settle
            shutdownIN(); //shtdown current pot
        }
    }
}
