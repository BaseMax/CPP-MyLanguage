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
### Utility Functions:
###   - Thanks to: https://stackoverflow.com/a/15283110/9248466
###
###
function(contcat IN_FILE OUT_FILE)
  file(READ ${IN_FILE} CONTENTS)
  file(APPEND ${OUT_FILE} "\n${CONTENTS}")
endfunction()

###
###
### Build Options
###
###
option(lang_STATIC_LIB_BUILD "Build Static Version" ON)
option(lang_SHARED_LIB_BUILD "Build Shared Version" ON)
option(lang_BINARY_BUILD "Build Executable Version" ON)
option(lang_HEADER_ONLY_BUILD "Header Only Version" ON)

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
### - Catch2: TDD
###
###
include_directories(third-party/json)
include_directories(third-party/catch2)

###
###
### Finding the needed files to build the project
###
###
file(GLOB  HFiles            include/Language/*.h include/Language/*.hpp)
file(GLOB  PRE_BUILD_HEADERS third-party/catch2/*.hpp third-party/json/*.hpp)
file(GLOB  CppFiles          source/*.cpp)

include_directories(include)

set(${PROJECT_EXE_NAME}_HEADERS
  ${HFiles}
)

set(${PROJECT_EXE_NAME}_SOURCES
  ${CppFiles}
  ${PRE_BUILD_HEADERS}
)

set(${PROJECT_EXE_NAME}_LIB_SOURCES
  ${${PROJECT_EXE_NAME}_SOURCES}
  ${PRE_BUILD_HEADERS}
)
list(REMOVE_ITEM ${PROJECT_EXE_NAME}_LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp)

set(${ROJECT_HEADER_ONLY}_FILES
  ${PRE_BUILD_HEADERS}
  ${HFiles}
  ${${PROJECT_EXE_NAME}_LIB_SOURCES}
)
list(REMOVE_ITEM ${ROJECT_HEADER_ONLY}_FILES ${CMAKE_CURRENT_SOURCE_DIR}/third-party/catch2/catch.hpp)

###
###
### Create project executable.
###
###
if(lang_STATIC_LIB_BUILD)
 add_library(${PROJECT_STATIC_LIB_NAME} STATIC ${${PROJECT_EXE_NAME}_LIB_SOURCES} ${${PROJECT_EXE_NAME}_HEADERS})
endif()

if(lang_SHARED_LIB_BUILD)
 add_library(${PROJECT_SHARED_LIB_NAME} SHARED ${${PROJECT_EXE_NAME}_LIB_SOURCES} ${${PROJECT_EXE_NAME}_HEADERS})
endif()

if(lang_BINARY_BUILD)
 add_executable(${PROJECT_EXE_NAME} ${${PROJECT_EXE_NAME}_SOURCES} ${${PROJECT_EXE_NAME}_HEADERS})
endif()

if(lang_HEADER_ONLY_BUILD)
 set(HEADER_ONLY_FILE_PATH ${DIST_PATH}/lib/${PROJECT_EXE_NAME}-headeronly.hpp)
 file(WRITE ${HEADER_ONLY_FILE_PATH} "")

 foreach(FILE ${${ROJECT_HEADER_ONLY}_FILES})
   contcat(${FILE} ${HEADER_ONLY_FILE_PATH})
 endforeach()
endif()

###
###
### Adding prebuild headers
###
###
target_precompile_headers(${PROJECT_EXE_NAME} PRIVATE ${PRE_BUILD_HEADERS})
target_precompile_headers(${PROJECT_STATIC_LIB_NAME} PRIVATE ${PRE_BUILD_HEADERS})
target_precompile_headers(${PROJECT_SHARED_LIB_NAME} PRIVATE ${PRE_BUILD_HEADERS})


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
