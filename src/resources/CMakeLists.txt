add_custom_target(resources)

# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET(EP_PREFIX_DIR ${CMAKE_BINARY_DIR}/resources )
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${EP_PREFIX_DIR} )

if(carl_FOUND)
	message("-- Use system version of CArL")
else()
	message("-- Download version of CArL")
	include(carl.cmake)
	find_package(carl)
	if(carl_FOUND)
		message("Found carl.")
	endif()
endif()

if(GTEST_FOUND)
	set(GTEST_LIBRARIES ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} PARENT_SCOPE)
	message("-- Use system version of GTest")
else()
	message("-- Download version of GTest")
	include(gtest.cmake)
endif()

include(glpk.cmake)

#AntLR
message("-- Use included version of AnTLR")

find_package(UUID QUIET)
if(NOT UUID_FOUND)
	message(SEND_ERROR "Package uuid-dev required to build antlr.")
endif()


#set variable pointing to antlr tool
set(ANTLR4CPP_JAR_LOCATION ${PROJECT_SOURCE_DIR}/src/resources/antlr-4.7-complete.jar)
#include external cmake file
include(ExternalAntlr4Cpp.cmake)
#message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4CPP_INCLUDE_DIRS} ")
