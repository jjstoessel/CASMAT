cmake_minimum_required(VERSION 3.6.3)
project(CATSMAT)
#project(libMusicXMLv3)
#project(libIMUSANT)
#project(IMUSANT_Tests)


if (APPLE)
#    set(CMAKE_OSX_ARCHITECTURES "x86_64 i386")
    set(CMAKE_OSX_DEPLOYMENT_TARGET=10.4)
    set(MACOSX_RPATH ON)
    #	if (${CMAKE_SYSTEM_VERSION} VERSION_LESS 9.0.0)
    #		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.4u.sdk)
    #	elseif (${CMAKE_SYSTEM_VERSION} VERSION_LESS 10.8.0)
    #		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
    #	elseif (${XCODE_VERSION} VERSION_LESS 8.0.0)
    #		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.6.sdk)
    #	else ()
    #		set (CMAKE_OSX_SYSROOT "macosx10.7")
    #	endif ()
    set(CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
endif (APPLE)





include_directories("catsmat/libIMUSANT")

add_subdirectory (catsmat/libMusicXMLv3/libmusicxml-3.00-src/cmake)
add_subdirectory (catsmat/libIMUSANT/cmake)
add_subdirectory (catsmat/IMUSANT_Tests/cmake)

set(CMAKE_CXX_STANDARD 11)
