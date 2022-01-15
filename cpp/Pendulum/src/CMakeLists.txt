set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES main.cpp vmath.h runge_kutta_system.h)

add_executable(${BINARY}_run ${SOURCES})
# add_executable(${BINARY}_run main.cpp vmath.h)

# file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

# set(SOURCES ${SOURCES})

# add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})