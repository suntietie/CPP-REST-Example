/*
 *  json.h for stock project 
 *  USC EE 599: Computing Principles for Electrical Engineers - Fall 2020
 *  ----------------------------------------------------------
 */
#pragma once

#include "data.h"
#include <cpprest/json.h>
#include <cpprest/filestream.h>

using namespace web;

json::value readJsonFile(std::string const & jsonFileName)
{
    json::value output;  // JSON read from input file

    try
    {
        // Open the file stream
        std::ifstream f(jsonFileName);
        // String stream for holding the JSON file
        std::stringstream strStream;

        // Stream file stream into string stream
        strStream << f.rdbuf();
        f.close();  // Close the filestream

        // Parse the string stream into a JSON object
        output = json::value::parse(strStream);
    }
    catch (json::json_exception excep)
    {
        throw json::json_exception("Error Parsing JSON file ");
    }

    return output;
}

Data& parseJSON(json::value jsonObject){
    // parse your JSON Object into Data

}

