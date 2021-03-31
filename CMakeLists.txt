cmake_minimum_required(VERSION 3.1)

###
###
### Chosse the project name, This section
###
###
set(PROJECT_EXE_NAME mylanguage-cpp)
set(PROJECT_STATIC_LIB_NAME ${PROJECT_EXE_NAME}-lib-static)
set(PROJECT_SHARED_LIB_NAME ${PROJECT_EXE_NAME}-lib-shared)

project(${PROJECT_STATIC_LIB_NAME})
project(${PROJECT_SHARED_LIB_NAME})
project(${PROJECT_EXE_NAME})

###
###
### Default settings for project:
###   - Current directory included
###   - Project standard sets to C++17 and force it.
###   - Minumum Qt standard sets to 5.12.0
###
###
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

###
###
### Installation Variables.
###
###
set(DIST_PATH ${PROJECT_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIST_PATH}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DIST_PATH}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${DIST_PATH}/lib)

###
###
### Turn on some extra compiler warning.
###
###
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pedantic-errors -Werror")

###
###
### Third-party
### - Nlohmann::Json
###
###
include_directories(third-party/json)

###
###
### Finding the needed files to build the project
###
###
file(GLOB         HFiles            include/Language/*.h include/Language/*.hpp)
file(GLOB         CppFiles          source/*.cpp)

include_directories(include)

set(${PROJECT_EXE_NAME}_HEADERS
  ${HFiles}
)

set(${PROJECT_EXE_NAME}_SOURCES
  ${CppFiles}
)

set(${PROJECT_EXE_NAME}_LIB_SOURCES
  ${${PROJECT_EXE_NAME}_SOURCES}
)
list(REMOVE_ITEM ${${PROJECT_EXE_NAME}_LIB_SOURCES} ./source/main.cpp)


###
###
### Create project executable.
###
###
add_executable(${PROJECT_EXE_NAME} ${${PROJECT_EXE_NAME}_SOURCES} ${${PROJECT_EXE_NAME}_HEADERS})
add_library(${PROJECT_STATIC_LIB_NAME} STATIC ${${PROJECT_EXE_NAME}_LIB_SOURCES} ${${PROJECT_EXE_NAME}_HEADERS})
add_library(${PROJECT_SHARED_LIB_NAME} SHARED ${${PROJECT_EXE_NAME}_LIB_SOURCES} ${${PROJECT_EXE_NAME}_HEADERS})


###
###
### Install section
###
###
set(DIST_TEST_PATH ${DIST_PATH}/test)
set(DIST_HEADER_PATH ${DIST_PATH}/lib/include)

file(GLOB TEST_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test/*)
file(COPY ${TEST_FILES_PATH} DESTINATION ${DIST_TEST_PATH})
file(COPY ${${PROJECT_EXE_NAME}_HEADERS} DESTINATION ${DIST_HEADER_PATH})

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
