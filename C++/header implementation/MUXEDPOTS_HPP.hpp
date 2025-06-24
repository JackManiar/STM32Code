#ifndef MUXEDPOTS_HPP
#define MUZEDPOTS_HPP

#include <cstdint>
#include <iostream>
#include "stm32f1xx_hal.h"

class MuxedPots {
    private:
        SPI_HandleTypeDef *hspi;
        GPIO_TypeDef* csPort;
        uint16_t csPin;

        void potSelect(uint8_t muxInd, uint8_t potInd);
        
        //function that takes in desired potentiometer value and returns the 0-255 value that corresponds for use with the MP41510 function
        static uint8_t resistanceToBit(int res);

        //function that takes in value and sets the potentiometer to that value
        //function example: pot1.writeBit(50)
        void writeBit(uint8_t value);

        //same as above function but takes in resistance value instead of 0-255
        void writeResistance(int res);

        //function that puts the pots in shutdown mode when not being used
        //in shutdown mode, the wiper gets shorted to ground and terminal A gets open circuited, this saves power for when they are not being used
        //to wake up, just call the write functions
        void shutdownIN();

    public:
        //default constructor
        MuxedPots(SPI_HandleTypeDef spiHandle, GPIO_TypeDef* port, uint16_t pin);
        
        //set resistance uisng 0-255 bit string
        void setBit(uint8_t muxInd, uint8_t potInd, uint8_t value);

        //set resistancee suing 0-50000 value
        void setResistance(uint8_t muxInd, uint8_t potInd, int res);
        
        //shutdown specific pot (0 ohm resistance)
        void shutdown(uint8_t muxInd, uint8_t potInd);

        //shutdown all pots (0ohm resistance)
        void shutdownAll();
}