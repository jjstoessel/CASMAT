cmake_minimum_required(VERSION 3.6.3)
project(CATSMAT)

if (APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET=10.5)
    set(MACOSX_RPATH ON)
    set(CMAKE_C++_FLAGS -mmacosx-version-min=10.5)
endif (APPLE)


add_subdirectory (catsmat/googletest-master/googletest)
add_subdirectory (catsmat/libMusicXMLv3/libmusicxml-3.00-src/cmake)
add_subdirectory (catsmat/libIMUSANT/cmake)
add_subdirectory (catsmat/libIMUSANT_Tests/cmake)
add_subdirectory (catsmat/catsmat/cmake)
add_subdirectory (catsmat/CATSMAT_Tests/cmake)
add_subdirectory (catsmat/Commando/cmake)
add_subdirectory (catsmat/catsmat/repeats/cmake)
add_subdirectory (catsmat/catsmat/canonic_techniques/cmake)

set(CMAKE_CXX_STANDARD 11)
