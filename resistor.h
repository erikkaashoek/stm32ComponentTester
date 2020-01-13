#pragma once
#include "testPins.h"
#include "Component.h"
/**
 */
class Resistor : public Component
{
public:                 
                    Resistor( TestPin &A, TestPin &B,TestPin &C) :  Component(A,B,C)
                    {
                      resistance=0;
                    }
            virtual bool compute()            ;
            virtual bool draw(Ucglib *u,int yOffset);
                    int  getValue() {return resistance;}
            
protected:
            float resistance;
            bool probe( TestPin &A,TestPin::TESTPIN_STATE stateA, TestPin &B,TestPin::TESTPIN_STATE stateB,float &adc, int &resistance);
};