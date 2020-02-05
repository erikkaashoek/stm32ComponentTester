#pragma once
#include "testPins.h"
#include "Component.h"
/**
 */
class Capacitor : public Component
{
public:                 
                    Capacitor( TestPin &A, TestPin &B,TestPin &C) :  Component(A,B,C)
                    {
                      capacitance=0;
                    }
            virtual bool compute()            ;
            virtual bool draw(int yOffset);
                    int  getValue() {return capacitance;}
            
protected:
            float capacitance;
            bool  zero(int threshold); 
            bool  doOne(int dex, float &cap);
            float computeCapacitance(int time, int iresistance, int actualValue);
            bool  computeHiCap(int dex,int overSampling,float &c);
            
            bool quickEval(float &cap);
            bool doOneQuick(TestPin::PULL_STRENGTH strength, bool doubled, float percent,int &timeUs, int &resistance,int &value);
            bool getRange(int dex, int &range);
};