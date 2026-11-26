
add_test(NAME cfg_max_voices_8
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}"
    -S ${PROJECT_SOURCE_DIR}
    -B ${CMAKE_BINARY_DIR}/cfg/mv8
    -DOSYNTH_MAX_VOICES=8)

add_test(NAME cfg_q_not_power_of_2
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}"
    -S ${PROJECT_SOURCE_DIR} -B "${CMAKE_BINARY_DIR}/cfg/qnp2"
    -DOSYNTH_COMMAND_QUEUE_SIZE=5)

set_tests_properties(cfg_q_not_power_of_2 PROPERTIES
    WILL_FAIL TRUE
)


add_test(NAME cfg_q_not_0
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}"
    -S ${PROJECT_SOURCE_DIR} -B "${CMAKE_BINARY_DIR}/cfg/qn0"
    -DOSYNTH_COMMAND_QUEUE_SIZE=0)

set_tests_properties(cfg_q_not_0 PROPERTIES
    WILL_FAIL TRUE
)

add_test(NAME cfg_param_not_negative
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}"
    -S ${PROJECT_SOURCE_DIR} -B "${CMAKE_BINARY_DIR}/cfg/pnn"
    -DOSYNTH_MAX_VOICES=-1
)

set_tests_properties(cfg_param_not_negative PROPERTIES
    WILL_FAIL TRUE
)