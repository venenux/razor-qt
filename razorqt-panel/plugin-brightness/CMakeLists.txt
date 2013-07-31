cmake_minimum_required(VERSION 2.6)

set(PLUGIN "brightness")

set(HEADERS
    razorbrightness.h
    #razorbrightnessconfiguration.h
)

set(SOURCES
    razorbrightness.cpp
    #razorbrightnessconfiguration.cpp
)

set(MOCS
    razorbrightness.h
    #razorbrightnessconfiguration.h
)

set(UIS
    #razorbrightnessconfiguration.ui
)

#*******************************************
include ("../BuildPlugin.cmake")
BUILD_RAZOR_PLUGIN(${PLUGIN})
