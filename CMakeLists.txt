cmake_minimum_required (VERSION 2.8.11)
project (YACSI)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.60.0 REQUIRED COMPONENTS program_options regex thread) 

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.gtest googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test_runner src/yacsi/test/kickoff_test.cpp)
target_link_libraries(test_runner gtest_main ${Boost_LIBRARIES} Threads::Threads yacsi)
add_test(NAME kickoff_test COMMAND test_runner)


#####################################

add_library	(yacsi src/yacsi/kickoff.cpp)
add_executable 	(playground src/yacsi/playground/playground1.cpp)
#add_executable 	(test_runner src/yacsi/test/kickoff_test.cpp)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} include) 
    target_link_libraries(playground ${Boost_LIBRARIES} Threads::Threads yacsi)
    #    target_link_libraries(test_runner ${Boost_LIBRARIES} Threads::Threads yacsi)
endif()

