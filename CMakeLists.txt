cmake_minimum_required (VERSION 2.8.11)
project (YACSI)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.60.0 REQUIRED COMPONENTS program_options regex thread) 

add_library	(yacsi src/yacsi/kickoff.cpp)
add_executable 	(playground src/yacsi/playground/playground1.cpp)
add_executable 	(test_runner src/yacsi/test/kickoff_test.cpp)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} include) 
    target_link_libraries(playground ${Boost_LIBRARIES} Threads::Threads yacsi)
    target_link_libraries(test_runner ${Boost_LIBRARIES} Threads::Threads yacsi)
endif()

