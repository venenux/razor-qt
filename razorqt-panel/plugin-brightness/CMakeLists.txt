cmake_minimum_required(VERSION 2.6)

set(PLUGIN "brightness")

set(HEADERS
		brightnessbutton.h
		brightnesspopup.h
    razorbrightness.h
    #razorbrightnessconfiguration.h
)

set(SOURCES
		brightnessbutton.cpp
		brightnesspopup.cpp
    razorbrightness.cpp
    #razorbrightnessconfiguration.cpp
)

set(MOCS
		brightnessbutton.h
		brightnesspopup.h
    razorbrightness.h
    #razorbrightnessconfiguration.h
)

set(UIS
    #razorbrightnessconfiguration.ui
)

#*******************************************
include ("../BuildPlugin.cmake")
BUILD_RAZOR_PLUGIN(${PLUGIN})
