cmake_minimum_required(VERSION 3.14)
cmake_policy(VERSION 3.14)
project("advent-2020"
    LANGUAGES
        CXX
)

enable_testing()

set(input_dir "${CMAKE_CURRENT_SOURCE_DIR}/../input")

function(create_puzzle name)
    set(options "")
    set(one_value_args VALIDATE)
    set(multi_value_args LIBRARIES SOURCES)
    cmake_parse_arguments(CREATE_PUZZLE "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})
    add_executable(${name}
        ${name}.cpp
        ${CREATE_PUZZLE_SOURCES}
    )
    if(CREATE_PUZZLE_LIBRARIES)
        target_link_libraries(${name}
            PRIVATE ${CREATE_PUZZLE_LIBRARIES}
        )
    endif()
    target_compile_features(${name} PRIVATE
        cxx_std_17
    )
    set_target_properties(${name} PROPERTIES
        CXX_EXTENSIONS OFF
    )
    add_custom_target(${name}-test
        DEPENDS ${name}
        COMMAND $<TARGET_FILE:${name}> <"${input_dir}/${name}"
    )
    if(CREATE_PUZZLE_VALIDATE)
        set(validate_test "${name}-validate")
        add_test(${validate_test}
            ${name} "${input_dir}/${name}"
        )
        set_tests_properties(${name}-validate PROPERTIES
            PASS_REGULAR_EXPRESSION "${CREATE_PUZZLE_VALIDATE}"
        )
    endif()
endfunction()

function(create_library name)
    add_library(${name} SHARED ${ARGN})
    target_include_directories(${name}
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
    set_target_properties(${name} PROPERTIES
        CXX_EXTENSIONS OFF
    )
    target_compile_features(${name} PUBLIC
        cxx_std_17
    )
endfunction()

create_library(accounting
    accounting.cpp
)
create_library(baggage
    baggage.cpp
)
create_library(computer
    computer.cpp
)
create_library(pass
    pass.cpp
)
create_library(seatmap
    seatmap.cpp
)

add_subdirectory(test)

create_puzzle(1a
    LIBRARIES
        accounting
    VALIDATE 1005459
)
create_puzzle(1b
    LIBRARIES
        accounting
    VALIDATE 92643264
)
create_puzzle(2a
    VALIDATE 483
)
create_puzzle(2b
    VALIDATE 482
)
create_puzzle(3a
    VALIDATE 171
)
create_puzzle(3b
    VALIDATE 1206576000
)
create_puzzle(4a
    VALIDATE 228
)
create_puzzle(4b
    VALIDATE 175
)
create_puzzle(5a
    LIBRARIES
        pass
    VALIDATE 885
)
create_puzzle(5b
    LIBRARIES
        pass
    VALIDATE 623
)
create_puzzle(6a
    VALIDATE 6775
)
create_puzzle(6b
    VALIDATE 3356
)
create_puzzle(7a
    LIBRARIES
        baggage
    VALIDATE 252
)
create_puzzle(7b
    LIBRARIES
        baggage
    VALIDATE 35487
)
create_puzzle(8a
    LIBRARIES
        computer
    VALIDATE 1487
)
create_puzzle(8b
    LIBRARIES
        computer
    VALIDATE 1607
)
create_puzzle(9a
    VALIDATE 14144619
)
create_puzzle(9b
    VALIDATE 1766397
)

create_puzzle(10a
    VALIDATE 2346
)
create_puzzle(10b
    VALIDATE 6044831973376
)
create_puzzle(11a
    LIBRARIES
        seatmap
    VALIDATE 2247
)
create_puzzle(11b
    LIBRARIES
        seatmap
    VALIDATE 2011
)
create_puzzle(12a
    VALIDATE 879
)
