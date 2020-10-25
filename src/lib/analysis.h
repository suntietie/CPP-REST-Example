/*
 *  analysis.h for stock project 
 *  USC EE 599: Computing Principles for Electrical Engineers - Fall 2020
 *  ----------------------------------------------------------
 */
#pragma once

#include "data.h"
#include "algorithm.h"
#include <set>
#include <unordered_map>


class Analysis{
    public:

        double simpleBackTesting(Signals& sig, Data& d);
        // evaluate how often your simple backtesting is profitable
        // e.g. a BUY signal is shown at any timestamp, and stock price 
        // get higher after your BUY signal
        // return accuracy of signal (# of correct signals) / (# of signals)

        
        double complexBackTesting(std::vector<Signals>& sigs, Data& d);
        // evaluate how often your complex backtesting is profitable

        // e.g. a BUY signal is shown by mulptiple signals very nearly 
        // (you define near), and stock price goes higher after your BUY signal
        // SELL if  RSI == SELL AND MACD == SELL AND Data Signal == SELL

        // return accuracy of signal (# of correct signals) / (# of signals)

        std::vector<std::set<std::string>> TopAccuracy(std::vector<Signals>& sigs, Data& d, int N);
        // Make a full combination of all simple backtesting methods.
        
        // evaluate the top n highest accuracy for different methods of complex backtesting
        // use heap data structure to get the top n! 
        // e.g. return { {RSI, MACD}, {Simp_Mov_Average, RSI}, ... }


   
        double tradeBackTesting();
        // open question:
        // simulate your stock trading with user-defined fund input, using your 
        // own indicator algorithms (simple or complex)
        // define input parameters by yourself


        double maxProfit(Data& d, int numOfShare);
        // In this step, say you have a daily time series(vector<DataPoint>) of S&P 500, 
        // with the length of 3 - 6 months. Try to design an algorithm that can make you 
        // get the highest profit.

        // see more instruction on Project description

};  


class StockGraph{
    // define your stock graph using 
    public:
        void generateGraph(std::vector<Data &> ds, double threshold);
        // generate your stock graph based on project description and the paper
        
        std::unordered_map<std::string, double> generateCorrelatedPortfolio();
        // output: APPLE (stock name) -> 0.1 (portion)

        std::unordered_map<std::string, double> generateUncorrelatedPortfolio();

    private:    
        std::unordered_map<std::string, int> stock_index_mapper;
        // a map used in undirected_graph
        // e.g. APPLE (stock name) -> 0 (index)
        std::vector<std::vector<int>> undirected_graph;

};


