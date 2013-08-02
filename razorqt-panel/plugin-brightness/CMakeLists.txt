cmake_minimum_required(VERSION 2.6)

set(PLUGIN "brightness")

set(HEADERS
		backlight.h
		xrandrbacklight.h
		backlightfactory.h
		brightnessbutton.h
		brightnesspopup.h
    razorbrightness.h
    #razorbrightnessconfiguration.h
)

set(SOURCES
		backlight.cpp
		xrandrbacklight.cpp
		backlightfactory.cpp
		brightnessbutton.cpp
		brightnesspopup.cpp
    razorbrightness.cpp
    #razorbrightnessconfiguration.cpp
)

set(MOCS
		backlight.h
		xrandrbacklight.h
		backlightfactory.h
		brightnessbutton.h
		brightnesspopup.h
    razorbrightness.h
    #razorbrightnessconfiguration.h
)

set(UIS
    #razorbrightnessconfiguration.ui
)

message("brightness: ${X11_LIB} ${XRANDR_LIB}")
LINK_LIBRARIES(${PLUGIN} ${X11_LIB} "/usr/lib/libXrandr.so.2")

set(LIBRARIES ${LIBRARIES} razor-global-key-shortcuts-client )

#*******************************************
include ("../BuildPlugin.cmake")
BUILD_RAZOR_PLUGIN(${PLUGIN})
