void potSelect(uint8_t muxInd, uint8_t potInd){
    if(mux < 0 || muxInd > 11){
        printf("Mux index is out of bounds\n");
        return;
    }
    if(channel < 0 || potInd > 15){
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
                ((potInd & 0x01) ? GPIO_PIN_8 : 0) |
                ((potInd & 0x02) ? GPIO_PIN_9 : 0) |
                ((potInd & 0x03) ? GPIO_PIN_10 : 0) |
                ((potInd & 0x04) ? GPIO_PIN_11 : 0);
}