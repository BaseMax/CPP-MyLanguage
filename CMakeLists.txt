cmake_minimum_required(VERSION 3.1)

###
###
### Chosse the project name, This section
###
###
project(mylanguage-cpp)

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

set(${PROJECT_NAME}_HEADERS
  ${HFiles}
)

set(${PROJECT_NAME}_SOURCES
  ${CppFiles}
)

###
###
### Create project executable.
###
###
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS})


###
###
### Install section
###
###
set(DIST_TEST_PATH ${DIST_PATH}/test)

file(GLOB TEST_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test/*)
file(COPY ${TEST_FILES_PATH} DESTINATION ${DIST_TEST_PATH})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
