enable_testing()

file(GLOB tests "*.cpp")

foreach(test ${tests})

    get_filename_component(testName ${test} NAME_WE)

    add_executable(${testName} ${test})

    target_link_libraries(${testName} libPicross ${SFML_LIBRARIES})

    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)
endforeach(test)
