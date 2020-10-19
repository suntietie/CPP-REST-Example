#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>
 
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
 

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
        throw json::json_exception("Error Parsing JSON file " + jsonFileName);
    }

    return output;
}


int main() {

	std::string file = "results.json";

	// Create a FileStream to write JSON
	auto fileStream = std::make_shared<ostream>();
	
	// Open stream to output file.
	pplx::task<void> requestTask = fstream::open_ostream(U(file))
	.then([=](ostream outFile){
	
		*fileStream = outFile;

		// Make a GET request.
		auto endpoint = http_client(U("https://www.alphavantage.co/"))
				.request(methods::GET,
				uri_builder().append_path(U("query"))
				.append_query(U("function"), "TIME_SERIES_INTRADAY")
				.append_query(U("symbol"), "IBM")
				.append_query(U("interval"), "5min")
				.append_query(U("apikey"), "demo").to_string());

		return endpoint;
	})

	// Get the response.
	.then([=](http_response response) {
		// Check the status code.
		if (response.status_code() != 200) {
			throw std::runtime_error("Returned " + std::to_string(response.status_code()));
		}
 
		// Write the response body to file stream.
		response.body().read_to_end(fileStream->streambuf()).wait();
		
		return fileStream->close();
	});

	
	// Wait for the concurrent tasks to finish.
	try {
		requestTask.wait();
	} catch (const std::exception &e) {
		printf("Error exception:%s\n", e.what());
	}


	// Read JSON file
    auto jsonObject = readJsonFile(file);
    auto metaValue = jsonObject[U("Meta Data")].as_object();
 
	// Parse details.
    std::cout << "------ Extract my JSON -------" <<std::endl;
    std::cout << metaValue[U("1. Information")].as_string()
        << '\n' << metaValue[U("2. Symbol")].as_string()
        << '\n' << metaValue[U("3. Last Refreshed")].as_string()
        << '\n' << metaValue[U("4. Interval")].as_string()
        << '\n' << metaValue[U("5. Output Size")].as_string()
        << '\n' << metaValue[U("6. Time Zone")].as_string()
        << std::endl;
	return 0;
}