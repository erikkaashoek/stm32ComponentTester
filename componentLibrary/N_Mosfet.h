#pragma once
#include "testPins.h"
#include "Component.h"
#include "Mosfet.h"
/**
 */
class NMosFet : public  Mosfet
{
public:                 
                    // Order is Gate, Drain Source
                    NMosFet( TestPin &A, TestPin &B,TestPin &C) :  Mosfet(A,B,C)
                    {
                   
                    }
            virtual bool compute()            ;
            virtual bool draw(int yOffset);
                    
            
protected:
         
            
            bool  computeDiode();
            bool  computeRdsOn();
            bool  computeVgOn();
            bool  computeCg();
public:
            
};
