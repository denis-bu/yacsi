cmake_minimum_required (VERSION 3.2)
project (YACSI)

include(CTest)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.60.0 REQUIRED COMPONENTS program_options regex thread) 
include_directories(${Boost_INCLUDE_DIRS} include)

# gtest and gmock
set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")

include(DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test_runner src/yacsi/test/kickoff_test.cpp)
target_link_libraries(test_runner gtest gmock_main ${Boost_LIBRARIES} Threads::Threads yacsi)
add_test(NAME kickoff_test COMMAND test_runner)


#####################################

add_library	(yacsi src/yacsi/kickoff.cpp)
add_executable 	(playground src/yacsi/playground/playground1.cpp)
target_link_libraries(playground ${Boost_LIBRARIES} Threads::Threads yacsi)


