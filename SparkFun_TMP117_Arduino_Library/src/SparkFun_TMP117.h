/******************************************************************************
SparkFunTMP117.h
SparkFunTMP117 Library Header File
Madison Chodikov @ SparkFun Electronics
Original Creation Date: April 29, 2016
https://github.com/sparkfunX/Qwiic_TMP117

This file prototypes the TMP102 class, implemented in SparkFunTMP117.cpp.

Development environment specifics:
	IDE: Arduino 1.8.9
	Hardware Platform: Arduino Uno
	TMP117 Breakout Version: 1.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#ifndef TMP117_h
#define TMP117_h

#include <Wire.h>
#include <Arduino.h>
#include "SparkFun_TMP117.h"

#define TMP117_I2C_ADDR 0x48 // Address found on Page 19 of data sheet (GND)

// Address found on page 23 Table 3 of the data sheet
#define DEVICE_ID_VALUE 0x117

// Resolution of the device, found on page 1 of the data sheet
#define TMP117_RESOLUTION	(double)0.078125 

enum TMP117_ALERT {NOALERT = 0, HIGHALERT, LOWALERT}; // Distinguishes the Alert type

// Configuration register found on page 25 Figure 26 and Table 6
typedef union{
	struct
	{
		uint8_t EMPTY : 1;		 // Empty bit in register
		uint8_t SOFT_RESET : 1;  // Software reset bit
		uint8_t DR_ALERT : 1;    // ALERT pin select bit
		uint8_t POL : 1;		 // ALERT pin polarity bit
		uint8_t T_NA : 1; 		 // Therm/alert mode select
		uint8_t AVG : 2; 		 // Conversion averaging modes
		uint8_t CONV : 3;		 // Conversion cycle bit
		uint8_t MOD : 2; 		 // Set conversion mode
		uint8_t EEPROM_BUSY : 1; // EEPROM busy flag
		uint8_t DATA_READY : 1;  // Data ready flag
		uint8_t LOW_ALERT : 1;   // Low Alert flag
		uint8_t HIGH_ALERT : 1;  // High Alert flag
	} CONFIGURATION_FIELDS;
	uint8_t CONFIGURATION_COMBINED;
} CONFIGURATION_REG;

class TMP117
{
    public:
		// Constructor 
        TMP117(byte address = TMP117_I2C_ADDR);

        bool begin(TwoWire &wirePort = Wire, uint16_t deviceAddress = TMP117_I2C_ADDR);   //Initialize the TMP117 sensor at given address
		bool isConnected(); // Checks connection
		float readTempC();	// Returns the temperature in degrees C
		float readTempF();	// Converts readTempC result to degrees F
		TMP117_ALERT getAlert(); // Returns the type of alert being caused
		bool isHighAlert(); // Sets an alert when the temperature is too high for the device
		bool isLowAlert(); // Sets an alert when the temperature is too low for the device
		void softReset(); // Performs a software reset on the Configuration Register Field bits
		void conversionMode(); // Sets the conversion mode
		void conversionCycleTime(); // Sets the conversion time for the device



		private: 
		TwoWire *_i2cPort = NULL; //The generic connection to user's chosen I2C hardware
		int _address;   // Address of Temperature sensor
		TMP117_ALERT alert_type; 
		
		// Read and write to registers
		uint16_t readRegister(TMP117_Register reg); // Reads register bytes from sensor
		void writeRegisters(TMP117_Register reg, byte *buffer, byte len); // Wires multiple bytes of data to the sensor
		void writeRegister(TMP117_Register reg, byte data); // Wires single byte of data to the sensor

};

#endif