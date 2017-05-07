cmake_minimum_required(VERSION 3.7)
project(CATSMAT)
project(libMusicXMLv3)
project(libIMUSANT)
project(IMUSANT_Tests)

set(GTEST_ROOT "C:/Development/googletest-master/googletest-master/cmake-build-debug/googlemock/gtest")
set(GTEST_INCLUDE_DIR "C:/Development/googletest-master/googletest-master/googletest/include/")
include_directories(${GTEST_INCLUDE_DIR})

include_directories("catsmat/libIMUSANT")

add_subdirectory (catsmat/libMusicXMLv3/libmusicxml-3.00-src/cmake)
add_subdirectory (catsmat/libIMUSANT/cmake)
add_subdirectory (catsmat/IMUSANT_Tests/cmake)

set(CMAKE_CXX_STANDARD 11)
