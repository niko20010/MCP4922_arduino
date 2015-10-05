
/*************************************************************************
**  Device: MCP4922                                                 	**
**  File:   AH_MCP4922.cpp - Library for get out analog voltage          	**
**                                                                      **
**  Modified by niko20010 2015-08-28                                    **
**  download on github                                                  **
**								    	**
**  Created by A. Hinkel 2012-12-24                                 	**
**  download from "http://www.arduino-projekte.de"  			**
**									**
**  Based on Code from:							**
**  http://www.sinneb.net/2010/06/mcp4921-12bit-dac-voltage-controller/ **
**									**
**  Released into the public domain.  		                    	**
**                                                                  	**
**                                                                  	**
**************************************************************************/



#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#error "Arduino IDE below v1.0 is not supported!"
#endif

#include <SPI.h>
#include "MCP4922.h"
SPISettings MCP4922(8000000, MSBFIRST, SPI_MODE0);
//*************************************************************************
AH_MCP4922::AH_MCP4922(int CS, int LDAC, int SHDN)  //SPI mode
{
 _SLAVESELECT = CS;
 _LDAC = LDAC;
 _SHUTDOWN = SHDN;

 pinMode(_SLAVESELECT,OUTPUT);
 digitalWrite(_SLAVESELECT,HIGH);
 pinMode(_LDAC,OUTPUT);
 digitalWrite(_LDAC,HIGH);
 pinMode(_SHUTDOWN,OUTPUT);
 digitalWrite(_SHUTDOWN,HIGH);
 
 SPI.begin();
 //SPI.setClockDivider(SPI_CLOCK_DIV16);
    outputA(0,0,0);    //Set output voltage
    outputB(0,0,0);    //Set output voltage
    latch();
}



//************************************************************************

void AH_MCP4922::outputA(int value, bool input_buffer, bool gain){
    sendValue_SPI(value, 0, input_buffer, gain, 1);
}

void AH_MCP4922::outputB(int value, bool input_buffer, bool gain){
    sendValue_SPI(value, 1, input_buffer, gain, 1);
}


void AH_MCP4922::latch(){
    digitalWrite(_LDAC,LOW);
    digitalWrite(_LDAC,HIGH);
}




 
//************************************************************************
void AH_MCP4922::sendValue_SPI(int value, bool dac, bool input_buffer, bool gain, bool active_mode) {

    byte msb = 0;
    byte lsb = 0;

    byte header = dac<<7 | input_buffer<<6 |  gain<<5 | active_mode<<4;   //B00110000
    msb = (header & 0xf0) | ((value>>8) & 0x0f);
    lsb = (byte) (value & 0xff);
    SPI.beginTransaction(MCP4922);
    digitalWrite(_SLAVESELECT,LOW);      // initiate data transfer with 4921
    SPI.transfer(msb);			//send 1st byte
    SPI.transfer(lsb);			//send 2nd byte

    //   Serial.print("msb:"); Serial.println(msb);
    //   Serial.print("lsb:"); Serial.println(lsb);

    digitalWrite(_SLAVESELECT,HIGH);   // finish data transfer
    SPI.endTransaction();

} 
 
 