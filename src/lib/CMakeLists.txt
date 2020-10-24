# If you create new headers/cpp files, add them to these list!
set(HEADER_FILES
  cpplib.h
  algorithm.h
  analysis.h
  data.h
  json.hpp
)

set(SOURCE_FILES
  cpplib.cpp
  algorithm.cpp
  analysis.cpp
  data.cpp
)

add_library(cpplib ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(cpplib cpprestsdk::cpprest)