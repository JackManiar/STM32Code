Files included in this folder are to be used for the STM32 ECG anomaly detection under Dr. Pompili's Lab.
All files were written by Jack Maniar with guidance from Khizar Anjum

Main code is stored here: C++ -> HeaderImplementation


ConvertToCpp: Contains python file that converts the python dictionary to 5 C++ matricies for use with setting the potentiometers

main.cpp: Contains main function for setting all potentiometer values

MuxedPots.cpp: Contains source code for the class in MUXEDPOTS_HPP, all functions are commented

MUXEDPOTS_HPP.hpp: Contains function signatures and short descripctions for all functions

weights.hpp: file created by ConvertToCpp that contains all constructed matricies
