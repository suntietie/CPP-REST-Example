/*
 *  algorithm.h for stock project 
 *  USC EE 599: Computing Principles for Electrical Engineers - Fall 2020
 *  ----------------------------------------------------------
 */
#pragma once

#include "data.h"


class Algorithm{
    public:
        Algorithm(){};
        // abstract class
        // generate buy or sell signals for a stock time series data 
        virtual Signals apply(Data& , int indicator) = 0;
};

class Simp_Mov_Average: Algorithm{
    // derived class, please implement the "apply" function
};

class Exp_Mov_Average: Algorithm{

};

class RSI: Algorithm{

};

class MACD: Algorithm{

};

