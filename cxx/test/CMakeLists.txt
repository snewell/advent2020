find_package(GTest CONFIG REQUIRED)

function(create_test name)
    set(options "")
    set(one_value_args "")
    set(multi_value_args LIBRARIES SOURCES)
    cmake_parse_arguments(CREATE_TEST "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})
    add_executable(${name} ${CREATE_TEST_SOURCES})
    set_target_properties(${name} PROPERTIES
        CXX_EXTENSIONS OFF
    )
    target_link_libraries(${name}
        PRIVATE ${CREATE_TEST_LIBRARIES}
        PRIVATE GTest::gtest
        PRIVATE GTest::gtest_main
    )
    add_test(${name} ${name} "--gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/${name}_results.xml")
endfunction()

create_test(accounting_test
    SOURCES
        accounting_test.cpp
    LIBRARIES
        accounting
)

create_test(pass_test
    SOURCES
        pass_test.cpp
    LIBRARIES
        pass
)
