/*
 *  data.h for stock project 
 *  USC EE 599: Computing Principles for Electrical Engineers - Fall 2020
 *  ----------------------------------------------------------
 */
#pragma once

#include <vector>
#include <string>
#include <map>
#include <ctime>

struct DataPoint
{

    double openPrice;
    double closePrice;
    double minPrice;
    double maxPrice;
    int volume;
    std::time_t timestamp;
};

struct Signal
{

    int s;
    // s = 0 - BUY Signal
    // s = 1 - SELL Signal
    std::time_t timestamp;
};

class Signals
{
public:
    std::vector<Signal> d;
    std::string method;
    std::time_t start_time;
    std::map<std::string, std::string> metadata;
};

class Data
{
    /* 
     * Stock data series
     */
public:
    Data(){};
    ~Data(){};
    // getter function
    std::vector<DataPoint> getData();
    // setter function
    void setData(std::vector<DataPoint> &);

    // merge data with same metadata, with correct timestamps
    Data merge(Data &);
    // start time of stock data
    std::time_t start_time;
    // metadata
    std::map<std::string, std::string> metadata;

private:
    std::vector<DataPoint> d;
};
