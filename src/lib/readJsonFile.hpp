#pragma once

#include <cpprest/json.h>

/**
 * @brief Parse a JSON file into a JSON object.
 *
 * @param jsonFileName The path to the JSON file to parse.
 */
web::json::value readJsonFile(std::string const & jsonFileName)
{
    web::json::value output;  // JSON read from input file

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
        output = web::json::value::parse(strStream);
    }
    catch (web::json::json_exception excep)
    {
        throw web::json::json_exception("Error Parsing JSON file " + jsonFileName);
    }

    return output;
}