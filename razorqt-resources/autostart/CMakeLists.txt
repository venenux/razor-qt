cmake_minimum_required( VERSION 2.6 )

file(GLOB DESKTOP_FILES_IN *.desktop.in)

# Translations **********************************
include(RazorTranslate)
razor_translate_desktop(DESKTOP_FILES
    SOURCES
        ${DESKTOP_FILES_IN}
)
add_custom_target(autostart_desktop_files ALL DEPENDS ${DESKTOP_FILES})
#************************************************

install(FILES ${DESKTOP_FILES} DESTINATION ${RAZOR_ETC_XDG_DIRECTORY}/autostart)
