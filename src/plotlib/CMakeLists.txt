set(HEADER_FILES
  matplotlibcpp.h
)
set(SOURCE_FILES
  example.cpp
)
add_library(plotlib ${HEADER_FILES} ${SOURCE_FILES})


# add required libraries for matplotlib_cpp
# check if Python.h is in usr/include/python2.7
find_package(Python2 COMPONENTS Development)

target_include_directories(plotlib PRIVATE ${Python2_INCLUDE_DIRS})
target_link_libraries(plotlib Python2::Python)
