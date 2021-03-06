# Require CMAKE 3.9 or higher
cmake_minimum_required(VERSION 3.9)

# Project name
project(cppstarter CXX)

# Build for C++11 if we can
set(CMAKE_CXX_STANDARD 11)

# Turn on any compiler-specific flags
if (WIN32)
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
else()
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
	if ("$ENV{SANITIZE}" STREQUAL "ON")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
	endif()
	
	if(APPLE)
		set(CMAKE_XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=Debug] "YES")
		set(CMAKE_XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=MinSizeRel] "NO")
		set(CMAKE_XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=RelWithDebInfo] "YES")
		set(CMAKE_XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=Release] "NO")
		# This is a bug in CMake that causes it to prefer the system version over
		# the one in the specified ROOT folder.
		set(OPENSSL_ROOT_DIR ${OPENSSL_ROOT_DIR} /usr/local/opt/openssl)
		set(OPENSSL_CRYPTO_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libcrypto.dylib CACHE FILEPATH "" FORCE)
		set(OPENSSL_SSL_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libssl.dylib CACHE FILEPATH "" FORCE)
		set(OPENSSL_LIBRARIES ${OPENSSL_ROOT_DIR}/lib)
		set(OPENSSL_INCLUDE_DIR ${OPENSSL_ROOT_DIR}/include)

	endif()
endif()

# Any source files in this directory
# set(SOURCE_FILES src/main/save.cpp)


set(LIBRARY_NAME cpplib)
set(LIBRARY_NAME plotlib)

if(APPLE)
find_package(cpprestsdk REQUIRED)
# find_package(openssl REQUIRED)
endif()

if(UNIX)
set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake)
find_package(cpprestsdk REQUIRED)
find_package(Boost REQUIRED system)
endif()

# Where any include files are
include_directories(src/lib)
include_directories(src/plotlib)

# Subdirectories to build
add_subdirectory(src/lib)
add_subdirectory(src/plotlib)
add_subdirectory(src/tests)


# Name of executable
add_executable(start src/main/start.cpp)
add_executable(parse src/main/parse.cpp)
add_executable(save src/main/save.cpp)
add_executable(plot src/main/plot.cpp)


# Link
if(APPLE)
target_link_libraries(start cpplib cpprestsdk::cpprest)
target_link_libraries(parse cpplib cpprestsdk::cpprest)
target_link_libraries(save cpplib cpprestsdk::cpprest)
target_link_libraries(plot plotlib cpprestsdk::cpprest)
endif()

if(UNIX)
target_link_libraries(start cpprestsdk::cpprest ${Boost_SYSTEM_LIBRARY})
target_link_libraries(parse cpplib cpprestsdk::cpprest ${Boost_SYSTEM_LIBRARY})
target_link_libraries(save cpplib cpprestsdk::cpprest ${Boost_SYSTEM_LIBRARY})
target_link_libraries(plot plotlib cpprestsdk::cpprest ${Boost_SYSTEM_LIBRARY})
endif()