cmake_minimum_required(VERSION 3.14)

set(TESTFILES
    main.cpp
    tests_vector.cpp
)

set(TEST_MAIN unit_tests)

add_executable(${TEST_MAIN} ${TESTFILES})
target_link_libraries(${TEST_MAIN} PRIVATE ${LIBRARY_NAME})
target_include_directories(${TEST_MAIN} PRIVATE ${PROJECT_SOURCE_DIR}/inc)

set_target_properties(${TEST_MAIN} PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO
)

add_test(NAME ${TEST_MAIN} COMMAND ${TEST_MAIN} -V)
