/**
 
 
 */
#pragma once
#include "Arduino.h"

// mostly internal pin resistance when pulled to VCC or GND
#define WIRE_RESISTANCE_AND_INTERNAL 21
#define ADC_OFFSET  0 

class AutoDisconnect
{
public:
        ~AutoDisconnect();
};

class TestPin
{
  friend class AllPins;
public:
        enum TESTPIN_STATE
        {
          IDLE=0,
          DISCONNECTED=1,
          PULLUP_HI=2,
          PULLUP_LOW=3,
          PULLDOWN_HI=4,
          PULLDOWN_LOW=5,
          PULLUP_MED=6,
          PULLDOWN_MED=7,
          VCC=10,
          GND=11                    
        };
  
        enum PULL_STRENGTH
        {
          PULL_LOW,
          PULL_MED,
          PULL_HI
        };
        
  
                TestPin(int pinNo, int pin, int pinDriveHighRes, int pinDriveMed,int pinDriveLow, int hiRes, int medRes,int lowRes);
        void    setMode(TESTPIN_STATE mode);
        void    init();
        void    pullUp(PULL_STRENGTH strength);
        void    pullDown(PULL_STRENGTH strength);
        void    setToVcc();
        void    setToGround();
        void    disconnect();
        bool    slowSample(int &adcSum, int &nbSamples);
        bool    fastSampleUp(int threshold,int &value, int &timeUs);
        bool    fastSampleDown(int threshold,int &value, int &timeUs)  ;
        TESTPIN_STATE getState() {return _state;}
        void    disconnectAll();
        int     getCurrentRes();

protected:  
        void    configureOutput(int pinNo, int state);
        adc_reg_map    *fastSetup()  ;
        int _pinNumber,_pin,_pinDriveHighRes, _pinDriveLowRes,_pinDriveMedRes;
        int _lowRes,_hiRes,_medRes;
        TESTPIN_STATE _state;
};


