project(${project_name})

find_library(libvlc NAMES libvlcpp libvlc libvlccore vlcpp vlc 
            PATHS /usr/lib /usr/lib64/ /usr/lib64/vlc)

add_library(battry_notification bn.cpp)

target_link_libraries(battry_notification PUBLIC ${libvlc})