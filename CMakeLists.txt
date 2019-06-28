cmake_minimum_required(VERSION 3.6.3)
project(CATSMAT)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

if (APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET=10.10)
    set(MACOSX_RPATH ON)
    set(CMAKE_C++_FLAGS -mmacosx-version-min=10.10)
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
add_subdirectory (catsmat/catsmat/count/cmake)
add_subdirectory (catsmat/catsmat/Segmentation/cmake)
add_subdirectory (catsmat/catsmat/general/cmake)

set(CMAKE_CXX_STANDARD 11)
