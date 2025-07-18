/*
 * MUXEDPOTS_HPP.hpp
 *
 *  Created on: Jul 8, 2025
 *      Author: jackm
 */

#ifndef INC_MUXEDPOTS_HPP_HPP_
#define INC_MUXEDPOTS_HPP_HPP_

#include "stm32f0xx_hal.h"
//#include "stm32l1xx_hal.h" if using the nucleo board

#include <cstdint>
#include <iostream>

typedef struct{
    uint16_t wiperId;
    uint8_t muxInd;
    uint8_t potInd;
} WiperMapEntry;

//using namespace std
#define NUM_WIPERS 192

class MuxedPots {
    private:
        SPI_HandleTypeDef *hspi;
        GPIO_TypeDef* csPort;
        uint16_t csPin;

        static const WiperMapEntry wiperMap[NUM_WIPERS]; //list of all the wipers with corresponding indicies

        const WiperMapEntry* lookupWiper(uint16_t wiperId) const;


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
        MuxedPots(SPI_HandleTypeDef* spiHandle, GPIO_TypeDef* port, uint16_t pin);

        //set resistance uisng 0-255 bit string

        void setBit(uint8_t muxInd, uint8_t potInd, uint8_t value);
        //overloaded version that accepts wiperId
        void setBit(uint16_t wiperId, uint8_t value);

        //set resistancee suing 0-50000 value
        void setResistance(uint8_t muxInd, uint8_t potInd, int res);
        //overloaded version that accepts wiperId
        void setResistance(uint16_t wiperId, int res);

        //shutdown specific pot (0 ohm resistance)
        void shutdown(uint8_t muxInd, uint8_t potInd);
        //overloaded version that accepts wiperId
        void shutdown(uint16_t wiperId);

        //shutdown all pots (0ohm resistance)
        void shutdownAll();
};



#endif /* INC_MUXEDPOTS_HPP_HPP_ */
