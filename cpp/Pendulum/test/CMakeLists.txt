set(BINARY ${CMAKE_PROJECT_NAME}_tst)

set(TEST_SOURCES main.cpp test_vmath.cpp test_runge_kutta_system.cpp)

# file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)