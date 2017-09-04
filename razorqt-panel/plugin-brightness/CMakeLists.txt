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

include_directories(${X11_X11_INCLUDE_PATH} ${X11_Xrandr_INCLUDE_PATH})
LINK_LIBRARIES(${PLUGIN} ${X11_X11_LIB} ${X11_Xrandr_LIB})

set(LIBRARIES ${LIBRARIES} razor-global-key-shortcuts-client )

#*******************************************
include ("../BuildPlugin.cmake")
BUILD_RAZOR_PLUGIN(${PLUGIN})
