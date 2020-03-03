/**
 * Derived from https://github.com/pingumacpenguin/STM32-O-Scope/blob/master/STM32-O-Scope.ino
 */
/*.
(c) Andrew Hull - 2015
STM32-O-Scope - aka "The Pig Scope" or pigScope released under the GNU GENERAL PUBLIC LICENSE Version 2, June 1991
https://github.com/pingumacpenguin/STM32-O-Scope
Adafruit Libraries released under their specific licenses Copyright (c) 2013 Adafruit Industries.  All rights reserved.
*/
/**
 We use PA0 as input pin
 * DMA1, channel 0
 
 * Vref is using PWM mode for Timer4/Channel 3
 * 
 * Correct init order is 
 *     ADC
 *     DMA
 *     SWSTART
 * 
 */
#include "dso_adc.h"
#include "fancyLock.h"
#include "dma.h"
#include "adc.h"
/**
 */
bool    DSOADC::fastSampleDown(int threshold,int &value, int &timeUs)  
{
    setTimeScale(ADC_SMPR_13_5, ADC_PRE_PCLK2_DIV_6); // about 2 us sampling fq
    adc_dev *dev = PIN_MAP[_pin].adc_device;
    int channel=PIN_MAP[_pin].adc_channel;    
    adc_reg_map *regs = dev->regs;       
    adc_set_exttrig(dev,1);
    adc_set_reg_seqlen(dev, 1);
    regs->SQR3 = channel;    
    regs->CR2 &= ~ADC_CR2_DMA;    
    uint32_t val=regs->DR ; // clear pending value
    
    // go
    int c;
    uint32_t start=micros();
    uint32_t sampleTime;
    bool first=true;
    value=regs->DR ; // clear pending value
    regs->CR2|=ADC_CR2_SWSTART;
    while(1)
    {
        uint32_t sampleStart=millis();
        while(1)
        {
            uint32_t sr=regs->SR;
            if(!(sr & ADC_SR_EOC))
            {
                int now=millis();
                if((now-sampleStart)>10)
                {
                    return false;
                }
            }
            sampleTime=micros();
            break;
        }
        value=regs->DR & ADC_DR_DATA;
        if(value<threshold)
        {
            timeUs=sampleTime-start; 
            return true;
        }
    }    
}