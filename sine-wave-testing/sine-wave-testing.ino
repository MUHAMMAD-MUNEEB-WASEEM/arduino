// Written by Celtic Engineering Solutions LLC 2021

// SF5.ino is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.

// SF5.ino is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with SF5.ino.  If not, see http://www.gnu.org/licenses/.

// Title: SF5.ino
// Author: The Celtic Engineer
// Description: This is example code of a polled interface for the
// SF-5 Digital to Analog Converter board
// Revision History: (Created Monday June 28 13:08 2021)

#include<Wire.h>
#include<avr/pgmspace.h>

// Definitions
#define addr 0b1100011  // Default device address (pin is pulled up to VDD). YOU WILL HAVE TO CHANGE THIS IF YOU CHANGE THE JUMPER.

// REGISTERS
#define Conver_reg      0X00 // Conversion Register (read only)
#define Config_reg      0x01 // Configuration Register
#define Low_lim_reg     0X02 // Low Threshold Register
#define High_lim_reg    0X03 // High Threshold Register

// COMMAND TYPE
#define FM      0x00      // Fast Mode
#define LD      0x02      // Load DAC
#define DaEP    0x03      // Load DAC and EEPROM

//Variables
unsigned char incomingByte = 0;           // Byte from user
unsigned char DataH = 0;                  // High DAC byte
unsigned char DataL = 0;                  // Low DAC byte
unsigned char Cmd = 0x00;                 // Command Byte default is normal
unsigned char PDM = 0;                    // Power Down Mode
unsigned char Array[6] = {0, 0, 0, 0, 0}; // Input value
unsigned char i = 0;                      // Counter
unsigned char val = 0;                    // 8 bit character scratchpad
unsigned int temp = 0;                    // 16 bit integer scratchpad
unsigned char wait = 0;                   // Trap
unsigned char x = 0;                      // delays for sine wave
const PROGMEM unsigned int mysine[] = {
  // Save this to FLASH. It is not really necessary because it is a small amount
  // of data, but an interesting exercise in case you want to use larger data blocks.
  2048,
  2447,
  2831,
  3185,
  3495,
  3750,
  3939,
  4056,
  4095,
  4056,
  3939,
  3750,
  3495,
  3185,
  2831,
  2447,
  2048,
  1648,
  1264,
  910,
  600,
  345,
  156,
  39,
  0,
  39,
  156,
  345,
  600,
  910,
  1264,
  1648
};

void setup() {
  // This is your initialization code
  Wire.begin(); // Start I2C Bus as Master
  Serial.begin(9600);
  banner();     // This is part of your user interface
}

void loop() {
  // This is the main loop of the program

  if (Serial.available() > 0)           // Wait for a command from user to do something.
  {
    // Read the incoming byte from User:
    incomingByte = Serial.read();

    //====================
    if (incomingByte == '1')            // Read DAC Registers
    {
      incomingByte = 0;                 // Clear incomming byte

      Wire.requestFrom(addr, 5, 1);
      i = 0;
      while (Wire.available())          // Keep doing this as long as there is data avialable
      {
        i++;                            // Incrament the counter
        Array[i] = Wire.read();         // Get a byte
      }
      Serial.print("\n This is the Command Byte: "); Serial.print(Array[1], HEX);
      Serial.print("\n DAC Reg MSB Byte: "); Serial.print(Array[2], HEX);
      Serial.print("\n DAC REG LSB Byte: "); Serial.print(Array[3], HEX);
      Serial.print("\n EEPROM Power down + MSB Byte: "); Serial.print(Array[4], HEX);
      Serial.print("\n EEPROM LSB Byte: "); Serial.println(Array[5], HEX);
      banner();
    }

    //====================
    if (incomingByte == '2')            // Power Down Select
    {
      incomingByte = 0;                 // Clear incomming byte

      // Sub-Menu Power Down Mode Select
      Serial.print("\nSelect the power down mode\n");
      Serial.print("1 - Normal Mode (0)\n");
      Serial.print("2 - 1K Resistor to GND (1)\n");
      Serial.print("3 - 100K Resistor to GND (2)\n");
      Serial.print("4 - 500K Resistor to GND (3)\n");
      wait = 1;   // Set up trap
      PDM = 0;    // Clear out old power down mode
      while (wait) {    // Hang out until user responds
        if (Serial.available() > 0)      // Wait for a command from user to do something.
        {
          // Read the incoming byte from User:
          incomingByte = Serial.read();
          if ((incomingByte > 47) && (incomingByte < 53)) {// Make sure it is a number
            wait = 0;
          }
        }
      }
      switch (incomingByte) {// Set variable based on user selection
        case 49:
          PDM = 0x00;
          break;
        case 50:
          PDM = 0x01;
          break;
        case 51:
          PDM = 0x02;
          break;
        case 52:
          PDM = 0x03;
          break;
      }
      incomingByte = 0;
      Serial.print("\nPDM mode: ");
      Serial.print(PDM);
      Serial.print("\n");
      banner();
    }

    //====================
    if (incomingByte == '3')            // Command Mode Select
    {
      incomingByte = 0;                 // Clear incomming byte

      // Sub-Menu Command Mode Select
      Serial.print("\nSelect the Command Mode\n");
      Serial.print("1 - Fast (0)\n");
      Serial.print("2 - Write to DAC (2)\n");
      Serial.print("3 - Write to DAC and EEPROM (3)\n");

      wait = 1;                       // Set up trap
      Cmd = 0;                        // Clear out old power down mode
      while (wait) {                  // Hang out until user responds
        if (Serial.available() > 0)   // Wait for a command from user to do something.
        {
          // Read the incoming byte from User:
          incomingByte = Serial.read();
          if ((incomingByte > 48) && (incomingByte < 52)) {// Only accept 1 , 2 or 3
            wait = 0;
          }
        }
      }
      switch (incomingByte) {// Set variable base on user selection
        case 49:
          Cmd = 0x00;
          break;
        case 50:
          Cmd = 0x02;
          break;
        case 51:
          Cmd = 0x03;
          break;
      }
      Serial.print("\nCMD mode: ");
      Serial.print(Cmd);
      Serial.print("\n");
      banner();
    }

    //====================
    if (incomingByte == '4')        // Get value to write
    {
      incomingByte = 0;             // Clear incomming byte

      // Get value to write
      Serial.print("\nEnter a value between 0 and 4095\n");
      Serial.print("You must use leading zeros\n");
      Serial.print("Value: ");

      wait = 1;
      i = 0;
      while (wait) {
        if (Serial.available() > 0)      // Wait for a command from user to do something.
        {
          // Read the incoming byte from User:
          incomingByte = Serial.read();
          if ((incomingByte) != 10) {
            i++;
            Array[i] = (incomingByte - 48);
            if (i >= 4) {
              wait = 0;
            }
          }
        }
      }

      // Assemble value
      temp = 0;
      temp = 1000 * Array[1] + 100 * Array[2] + 10 * Array[3] + Array[4];
      if (temp > 4095) {
        Serial.print("\nError: Value too large -> ");
        Serial.print(temp);
      }
      else {  // Format data for a Normal write
        DataL = ((temp << 4) & 0x00F0);   // Only want the bottom 4 bits, but left justified
        DataH = ((temp >> 4) & 0x00FF);   // Top 8 bits of integer moved to a character
      }
      Serial.print("\n");
      Serial.print(temp);
      Serial.print("\n");
      banner();
    }

    //====================
    if (incomingByte == '5')            // Execute a write
    {
      incomingByte = 0;                 // Clear incomming byte

      if (Cmd & 0x06)   // Reg or Reg and EEPROM
      {
        // Normal data 3 bytes
        val = (((Cmd << 5) & 0xE0)  | ((PDM < 1) & 0x06)); // C2 C1 C0 X X PD1 PD0 X
        Wire.beginTransmission(addr);
        Wire.write(val);                // Command and power down
        Wire.write(DataH);              // MSB Data out
        Wire.write(DataL);              // LSB Data out
        Wire.endTransmission();

        Serial.print("\n MSB: "); Serial.print(DataH, HEX);
        Serial.print("\n LSB: "); Serial.println(DataL, HEX);
      }

      else              // Fast Mode
      {
        // Compressed data to 2 bytes
        val = (((PDM << 4) & 0x30) | (( DataH >> 4) & 0x0F));  // 0 0 PD1 PD0 D11 D10 D9 D8
        Wire.beginTransmission(addr);
        Wire.write(val);
        val = (((DataH << 4) & 0xF0) | ((DataL >> 4) & 0x0F)); // Low 8 bits of data
        Wire.write(val);
        Wire.endTransmission();
        Serial.print("\nFast MSB: "); Serial.print(DataH, HEX);
        Serial.print("\n LSB: "); Serial.println(DataL, HEX);
      }
      banner();
    }

    //====================
    if (incomingByte == '6')        // Sine wave example
    {
      /*  This outputs a sine wave based on the Table of 32 steps saved to FLASH
       *   It is best to look at on an o-scope.
       *   The output is a bit ragged, but you can improve the look by adding an RC
       *   fileter.  Place a resistor (10K - 1.5M) and a Cap (0.1uF) depending
       *   on your frequency. A 0-Delay will output a sine wave of 92Hz, while 
       *   a 255-Delay will output a sine wave of 0.122Hz (8.2 second period).
       */
      incomingByte = 0;             // Clear incomming byte
      Serial.print("\nOutputs a sine wave\n");

      Serial.print("Enter the 'e' key to exit\n");
      Serial.print("+ to increase period and - to decrease period\n");
      Serial.print("Delay time will be printed to Serial Monitor \n");
      Serial.print("Outputing wave now\n");

      wait = 1; // Set trap
      i = 0;

      while (wait)
      {
        if (Serial.available() > 0)
        {
          // Read the incoming byte from User: Should we leave or should we stay?
          incomingByte = Serial.read();
          if ((incomingByte == 'e') | (incomingByte == 'E')) {
            wait = 0;
          }
          if (incomingByte == 43) { // increment
            x++;
            Serial.println(x);
          }
          else if (incomingByte == 45) {  // decrement
            x--;
            Serial.println(x);
          }
          incomingByte = 0;             // Clear incomming byte
        }
        // Crude way of waiting. Assumes you don't want to do anything else
        delay(x);

        // Get next voltage to send out
        temp = pgm_read_word_near(mysine + i);
        //temp = (mysine[i]);
        DataL = ((temp << 4) & 0x00F0);   // Only want the bottom 4 bits, but left justified
        DataH = ((temp >> 4) & 0x00FF);   // Top 8 bits of integer moved to a character

        val = (((PDM << 4) & 0x30) | (( DataH >> 4) & 0x0F));  // 0 0 PD1 PD0 D11 D10 D9 D8
        Wire.beginTransmission(addr);
        Wire.write(val);
        val = (((DataH << 4) & 0xF0) | ((DataL >> 4) & 0x0F)); // Low 8 bits of data
        Wire.write(val);
        Wire.endTransmission();

        // Update counter
        i++;                    // incrament couter
        i = i & 0x1F;           // count to 31 then go back to zero
      }
      banner();
    }

    //====================
    if ((incomingByte == 'H') | (incomingByte == 'h')) // Print Banner
    {
      incomingByte = 0;             // Clear incomming byte

      Serial.print("\n");
      banner();                     // This is your User Interface - Menu
    }
  }
}

void banner() {
  // This is your User Interface - Menu
  Serial.print ("\nDigital to Analog Converter SF-5: Main Menu\n\n");
  Serial.print ("1. Read DAC Registers\n");
  Serial.print ("2. Power Down Select\n");
  Serial.print ("3. Command Mode Select\n");
  Serial.print ("4. Get value to write\n");
  Serial.print ("5. Execute a write\n");
  Serial.print ("6. Sine wave output\n");
  Serial.print ("H. Help Menu\n");
}
