#include "MUXEDPOTS_HPP.hpp"

const WiperMapEntry MuxedPots::wiperMap[NUM_WIPERS] = {
    {122, 0, 0},  // wiper 122
    {121, 0, 1},  // wiper 121
    {116, 0, 2},  // wiper 116
    {115, 0, 3},  // wiper 115
    {114, 0, 4},  // wiper 114
    {113, 0, 5},  // wiper 113
    {112, 0, 6},  // wiper 112
    {111, 0, 7},  // wiper 111
    {123, 0, 8},  // wiper 123
    {124, 0, 9},  // wiper 124
    {125, 0, 10},  // wiper 125
    {126, 0, 11},  // wiper 126
    {131, 0, 12},  // wiper 131
    {132, 0, 13},  // wiper 132
    {133, 0, 14},  // wiper 133
    {134, 0, 15},  // wiper 134
    {146, 1, 0},  // wiper 146
    {145, 1, 1},  // wiper 145
    {144, 1, 2},  // wiper 144
    {143, 1, 3},  // wiper 143
    {142, 1, 4},  // wiper 142
    {141, 1, 5},  // wiper 141
    {136, 1, 6},  // wiper 136
    {135, 1, 7},  // wiper 135
    {151, 1, 8},  // wiper 151
    {152, 1, 9},  // wiper 152
    {153, 1, 10},  // wiper 153
    {154, 1, 11},  // wiper 154
    {155, 1, 12},  // wiper 155
    {156, 1, 13},  // wiper 156
    {161, 1, 14},  // wiper 161
    {162, 1, 15},  // wiper 162
    {214, 2, 0},  // wiper 214
    {213, 2, 1},  // wiper 213
    {212, 2, 2},  // wiper 212
    {211, 2, 3},  // wiper 211
    {166, 2, 4},  // wiper 166
    {165, 2, 5},  // wiper 165
    {164, 2, 6},  // wiper 164
    {163, 2, 7},  // wiper 163
    {215, 2, 8},  // wiper 215
    {216, 2, 9},  // wiper 216
    {221, 2, 10},  // wiper 221
    {222, 2, 11},  // wiper 222
    {223, 2, 12},  // wiper 223
    {224, 2, 13},  // wiper 224
    {225, 2, 14},  // wiper 225
    {226, 2, 15},  // wiper 226
    {242, 3, 0},  // wiper 242
    {241, 3, 1},  // wiper 241
    {236, 3, 2},  // wiper 236
    {235, 3, 3},  // wiper 235
    {234, 3, 4},  // wiper 234
    {233, 3, 5},  // wiper 233
    {232, 3, 6},  // wiper 232
    {231, 3, 7},  // wiper 231
    {243, 3, 8},  // wiper 243
    {244, 3, 9},  // wiper 244
    {245, 3, 10},  // wiper 245
    {246, 3, 11},  // wiper 246
    {251, 3, 12},  // wiper 251
    {252, 3, 13},  // wiper 252
    {253, 3, 14},  // wiper 253
    {254, 3, 15},  // wiper 254
    {266, 4, 0},  // wiper 266
    {265, 4, 1},  // wiper 265
    {264, 4, 2},  // wiper 264
    {263, 4, 3},  // wiper 263
    {262, 4, 4},  // wiper 262
    {261, 4, 5},  // wiper 261
    {256, 4, 6},  // wiper 256
    {255, 4, 7},  // wiper 255
    {311, 4, 8},  // wiper 311
    {312, 4, 9},  // wiper 312
    {313, 4, 10},  // wiper 313
    {314, 4, 11},  // wiper 314
    {315, 4, 12},  // wiper 315
    {316, 4, 13},  // wiper 316
    {321, 4, 14},  // wiper 321
    {322, 4, 15},  // wiper 322
    {334, 5, 0},  // wiper 334
    {333, 5, 1},  // wiper 333
    {332, 5, 2},  // wiper 332
    {331, 5, 3},  // wiper 331
    {326, 5, 4},  // wiper 326
    {325, 5, 5},  // wiper 325
    {324, 5, 6},  // wiper 324
    {323, 5, 7},  // wiper 323
    {335, 5, 8},  // wiper 335
    {336, 5, 9},  // wiper 336
    {341, 5, 10},  // wiper 341
    {342, 5, 11},  // wiper 342
    {343, 5, 12},  // wiper 343
    {344, 5, 13},  // wiper 344
    {345, 5, 14},  // wiper 345
    {346, 5, 15},  // wiper 346
    {362, 6, 0},  // wiper 362
    {361, 6, 1},  // wiper 361
    {356, 6, 2},  // wiper 356
    {355, 6, 3},  // wiper 355
    {354, 6, 4},  // wiper 354
    {353, 6, 5},  // wiper 353
    {352, 6, 6},  // wiper 352
    {351, 6, 7},  // wiper 351
    {363, 6, 8},  // wiper 363
    {364, 6, 9},  // wiper 364
    {365, 6, 10},  // wiper 365
    {366, 6, 11},  // wiper 366
    {411, 6, 12},  // wiper 411
    {412, 6, 13},  // wiper 412
    {413, 6, 14},  // wiper 413
    {414, 6, 15},  // wiper 414
    {426, 7, 0},  // wiper 426
    {425, 7, 1},  // wiper 425
    {424, 7, 2},  // wiper 424
    {423, 7, 3},  // wiper 423
    {422, 7, 4},  // wiper 422
    {421, 7, 5},  // wiper 421
    {416, 7, 6},  // wiper 416
    {415, 7, 7},  // wiper 415
    {431, 7, 8},  // wiper 431
    {432, 7, 9},  // wiper 432
    {433, 7, 10},  // wiper 433
    {434, 7, 11},  // wiper 434
    {435, 7, 12},  // wiper 435
    {436, 7, 13},  // wiper 436
    {441, 7, 14},  // wiper 441
    {442, 7, 15},  // wiper 442
    {454, 8, 0},  // wiper 454
    {453, 8, 1},  // wiper 453
    {452, 8, 2},  // wiper 452
    {451, 8, 3},  // wiper 451
    {446, 8, 4},  // wiper 446
    {445, 8, 5},  // wiper 445
    {444, 8, 6},  // wiper 444
    {443, 8, 7},  // wiper 443
    {455, 8, 8},  // wiper 455
    {456, 8, 9},  // wiper 456
    {461, 8, 10},  // wiper 461
    {462, 8, 11},  // wiper 462
    {463, 8, 12},  // wiper 463
    {464, 8, 13},  // wiper 464
    {465, 8, 14},  // wiper 465
    {466, 8, 15},  // wiper 466
    {522, 9, 0},  // wiper 522
    {521, 9, 1},  // wiper 521
    {516, 9, 2},  // wiper 516
    {515, 9, 3},  // wiper 515
    {514, 9, 4},  // wiper 514
    {513, 9, 5},  // wiper 513
    {512, 9, 6},  // wiper 512
    {511, 9, 7},  // wiper 511
    {523, 9, 8},  // wiper 523
    {524, 9, 9},  // wiper 524
    {525, 9, 10},  // wiper 525
    {526, 9, 11},  // wiper 526
    {117, 9, 12},  // wiper 117
    {118, 9, 13},  // wiper 118
    {119, 9, 14},  // wiper 119
    {1110, 9, 15},  // wiper 1110
    {1111, 10, 0},  // wiper 1111
    {1112, 10, 1},  // wiper 1112
    {127, 10, 2},  // wiper 127
    {128, 10, 3},  // wiper 128
    {129, 10, 4},  // wiper 129
    {1210, 10, 5},  // wiper 1210
    {1211, 10, 6},  // wiper 1211
    {1212, 10, 7},  // wiper 1212
    {137, 10, 8},  // wiper 137
    {138, 10, 9},  // wiper 138
    {139, 10, 10},  // wiper 139
    {1310, 10, 11},  // wiper 1310
    {1311, 10, 12},  // wiper 1311
    {1312, 10, 13},  // wiper 1312
    {147, 10, 14},  // wiper 147
    {148, 10, 15},  // wiper 148
    {149, 11, 0},  // wiper 149
    {1410, 11, 1},  // wiper 1410
    {1411, 11, 2},  // wiper 1411
    {1412, 11, 3},  // wiper 1412
    {157, 11, 4},  // wiper 157
    {158, 11, 5},  // wiper 158
    {159, 11, 6},  // wiper 159
    {1510, 11, 7},  // wiper 1510
    {1511, 11, 8},  // wiper 1511
    {1512, 11, 9},  // wiper 1512
    {167, 11, 10},  // wiper 167
    {168, 11, 11},  // wiper 168
    {169, 11, 12},  // wiper 169
    {1610, 11, 13},  // wiper 1610
    {1611, 11, 14},  // wiper 1611
    {1612, 11, 15},  // wiper 1612
}; //list of all the entries

const WiperMapEntry* MuxedPots::lookupWiper(uint16_t wiperId) const{
    for(uint8_t i = 0; i < NUM_WIPERS; i++){
        if(wiperMap[i].wiperId == wiperId)
            return &wiperMap[i];
    }
    return nullptr;
}

//begin private methods
void MuxedPots::potSelect(uint8_t muxInd, uint8_t potInd){
    if( muxInd > 11){
        std::cout << "Mux index is out of bounds\n";
        return;
    }
    if(potInd > 15){
        std::cout << "Channel index is out of bounds\n";
        return;
    }

    //setting the mux index using Bit set/Reset Register to update values simluataneously
    //clear S0-S3 on the GPIOB (PB12-PB15)
    GPIOB->BSRR = (GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15) << 16;

    //set new values for S0-S3
    GPIOB->BSRR =
                ((potInd & 0x01) ? GPIO_PIN_12 : 0) |
                ((potInd & 0x02) ? GPIO_PIN_13 : 0) |
                ((potInd & 0x04) ? GPIO_PIN_14 : 0) |
                ((potInd & 0x08) ? GPIO_PIN_15 : 0);

    //clear S4-S7 on the GPIOA(PA8-PA11)
    GPIOA->BSRR = (GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11) << 16;

    //set new values for S4-S7
    GPIOA->BSRR =
                ((muxInd & 0x01) ? GPIO_PIN_8 : 0) |
                ((muxInd & 0x02) ? GPIO_PIN_9 : 0) |
                ((muxInd & 0x04) ? GPIO_PIN_10 : 0) |
                ((muxInd & 0x08) ? GPIO_PIN_11 : 0);
    HAL_Delay(delay);
}

uint8_t MuxedPots::resistanceToBit(int res){
    if(res < 0 || res > 50000){ //error checking
        std::cerr <<"Error(resToBit): Resistance out of range\n";
                return 0xFF; // Indicate failure
    }

    return static_cast<uint8_t>((res * 255 + 25000) / 50000); //the 25000 is added so that the truncation actually rounds
}

void MuxedPots::writeBit(uint8_t value) {
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
    HAL_Delay(delay);

    //sends the 16 bit command
    HAL_SPI_Transmit(hspi, data, 2, HAL_MAX_DELAY);
    HAL_Delay(delay);

    //sets cs high to end the data transfer
    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
    HAL_Delay(delay);
}

void MuxedPots::writeResistance(int res){
    if(res < 0 || res > 50000){ //error checking
            std::cerr << "Error(writeResistance): Resistance out of range\n";
                    return; // Indicate failure
        }

    //uint8_t command = 0b00010001;
    uint8_t data[2] = {0b00010001, resistanceToBit(res)};

    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);

    HAL_SPI_Transmit(hspi, data, 2, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
    HAL_Delay(delay);
}

void MuxedPots::shutdownIN(){
    //uint8_t command = 0b00100001; //command says enter shutdown mode
    uint8_t data[2] = {0b00100001, 0b00000000}; //still need to send don't care bits

    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET);
    HAL_Delay(delay);

    HAL_SPI_Transmit(hspi, data, 2, HAL_MAX_DELAY);
    HAL_Delay(delay);

    HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET);
    HAL_Delay(delay);
}

//begin public methods
MuxedPots::MuxedPots(SPI_HandleTypeDef* spiHandle, GPIO_TypeDef* port, uint16_t pin)
            : hspi(spiHandle), csPort(port), csPin(pin) {}

void MuxedPots::setBit(uint8_t muxInd, uint8_t potInd, uint8_t value){
    potSelect(muxInd, potInd);
    HAL_Delay(delay);
    writeBit(value);
}

void MuxedPots::setBit(uint16_t wiperId, uint8_t value){
    const WiperMapEntry* temp = lookupWiper(wiperId);
    if(!temp){
        std::cerr << "Invalid wiper ID: " << wiperId << std::endl;
        return;
    }
    setBit(temp->muxInd, temp->potInd, value);
}

void MuxedPots::setResistance(uint8_t muxInd, uint8_t potInd, int res){
    potSelect(muxInd, potInd);
    HAL_Delay(delay);
    writeResistance(res);
}

void MuxedPots::setResistance(uint16_t wiperId, int res){
    const WiperMapEntry* temp = lookupWiper(wiperId);
    if(!temp){
        std::cerr << "Invalid wiper ID: " << wiperId << std::endl;
        return;
    }
    setResistance(temp->muxInd, temp->potInd, res);
}

void MuxedPots::shutdown(uint8_t muxInd, uint8_t potInd){
    potSelect(muxInd, potInd);
    HAL_Delay(delay);
    shutdownIN();
}

void MuxedPots::shutdown(uint16_t wiperId){
    const WiperMapEntry* temp = lookupWiper(wiperId);
    if(!temp){
        std::cerr << "Invalid wiper ID: " << wiperId << std::endl;
        return;
    }
    shutdown(temp->muxInd, temp->potInd);
}

void MuxedPots::shutdownAll(){
    for(uint8_t mux = 0; mux < 12; mux++){
        for(uint8_t pot = 0; pot < 16; pot++){
            potSelect(mux, pot); //set selection
            HAL_Delay(delay);   //delay to let mux settle
            shutdownIN(); //shtdown current pot
            HAL_Delay(delay);
        }
    }
}