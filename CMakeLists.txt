# Require CMAKE 3.1 or higher
cmake_minimum_required(VERSION 3.17.3)

# Project name
project(cppstarter)

# Build for C++20 if we can
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
set(SOURCE_FILES src/main/main.cpp)


set(LIBRARY_NAME cpplib)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)

# Where any include files are
include_directories(src/lib)

# Subdirectories to build
add_subdirectory(src/lib)
add_subdirectory(src/tests)


# Name of executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link
target_link_libraries(${PROJECT_NAME} cpplib cpprestsdk::cpprest)
