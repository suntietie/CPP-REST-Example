#pragma once

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


int main() {
	// Make a GET request.
	auto requestJson = http_client(U("https://www.alphavantage.co/"))
		.request(methods::GET,
				uri_builder().append_path(U("query"))
				.append_query(U("function"), "TIME_SERIES_INTRADAY")
				.append_query(U("symbol"), "IBM")
				.append_query(U("interval"), "5min")
				.append_query(U("apikey"), "demo").to_string())
 
	// Get the response.
	.then([](http_response response) {
		// Check the status code.
		if (response.status_code() != 200) {
			throw std::runtime_error("Returned " + std::to_string(response.status_code()));
		}
 
		// Convert the response body to JSON object.
		return response.extract_json();
	})
 
	// Get the data field.
	.then([](json::value jsonObject) {
		return jsonObject[U("Meta Data")];
	})
 
	// Parse the JSON details.
	.then([](json::value jsonObject) {
		std::cout << "------ Extract my JSON -------" <<std::endl;
		std::cout << jsonObject[U("1. Information")].as_string()
			<< '\n' << jsonObject[U("2. Symbol")].as_string()
			<< '\n' << jsonObject[U("3. Last Refreshed")].as_string()
			<< '\n' << jsonObject[U("4. Interval")].as_string()
			<< '\n' << jsonObject[U("5. Output Size")].as_string()
			<< '\n' << jsonObject[U("6. Time Zone")].as_string()
			<< std::endl;
	});
 
	// Wait for the concurrent tasks to finish.
	try {
		requestJson.wait();
	} catch (const std::exception &e) {
		printf("Error exception:%s\n", e.what());
	}
 
	return 0;
}