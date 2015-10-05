
/*************************************************************************
**  Device: MCP4922                                                 	**
**  File:   AH_MCP4922.h - Library for get out analog voltage          	**
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

#ifndef MCP4922_h
#define MCP4922_h


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#error "Arduino IDE below v1.0 is not supported!"
#endif


class AH_MCP4922
{
  public:
    AH_MCP4922(int CS,int LDAC, int SHDN);
    void outputA(int value, bool input_buffer, bool gain);
    void outputB(int value, bool input_buffer, bool gain);
    void latch();
    int _LDAC;
    int _SHUTDOWN;
    int _SLAVESELECT;

    void sendValue_SPI(int value, bool dac, bool input_buffer, bool gain, bool active_mode);
};

#endif