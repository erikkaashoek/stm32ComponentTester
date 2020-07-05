#pragma once
#include "testPins.h"
#include "Component.h"
/**
 */
class Capacitor : public Component
{
public:    

            typedef struct CapScale
            {
                int                 fq;
                TestPin::PULL_STRENGTH strength;
                bool                doubled;
            };
            typedef enum CapEval
            {
                EVAL_OK=0,
                EVAL_BIGGER_CAP=1,
                EVAL_SMALLER_CAP=2,
                EVAL_ERROR=99
            };
            struct CapCurve
            {
                int nbSamples;
                int iMin;
                int iMax;
                int vMin;
                int vMax;
                float resistance;
                float period;
            };
public:                 
                    Capacitor( TestPin &A, TestPin &B,TestPin &C) :  Component(A,B,C,"Capacitor")
                    {
                      capacitance=0;
                      computed=false;
                    }
            virtual bool compute()  ;
            static  bool quickEval(TestPin &a, TestPin &b,TestPin &dummy); // return true if this is a capacitor
            virtual bool draw(int yOffset);
                    int  getValue() {return capacitance;}
                    int  likely() {return 50;} // medium likely
            
protected:
            bool  quickEval(); // return true if this is a capacitor
            float capacitance;
            bool  doOne(float target,int dex, float &cap);
            CapEval eval(const CapScale &sc,CapCurve &curve, int &deltaTime,bool largeWindow=false);
            bool  computeMediumCap(bool overSample=true);
            bool  computeHighCap(bool overSample=true);
            bool  computeLowCap(bool overSample=true);
            bool  computeVeryLowCap();
            bool computeCapRange(int n, const Capacitor::CapScale *scale, int overSampling);
            bool doOneQuick(TestPin::PULL_STRENGTH strength, bool doubled, float percent,int &timeUs, int &resistance,int &value);
            bool getRange(int dex, int &range);
            bool getEsr(float &esr);
            bool minMax(bool high,int &minmax);
            bool computeWrapper();
public:
            bool calibrationValue(float &c);
            bool computed;
static      float computeCapacitance(int nbSample, uint16_t *samples, int resistance, float period);
static      float computeCapacitance(CapCurve &curve);
};