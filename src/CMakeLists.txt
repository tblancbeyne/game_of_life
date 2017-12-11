file(GLOB libPicross "lib/*.cpp")

add_library(libPicross ${libPicross})

file(GLOB picrossExec "executables/*.cpp")

foreach(executable ${picrossExec})
    get_filename_component(execName ${executable} NAME_WE)

    add_executable(${execName} ${executable})

    target_link_libraries(${execName} libPicross ${SFML_LIBRARIES})
endforeach(executable)
