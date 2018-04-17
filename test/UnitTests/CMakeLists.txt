file(GLOB SRCS *.cpp)
include_directories(${PROJECT_SOURCE_DIR})
add_executable(UnitTests ${SRCS})
target_link_libraries (UnitTests
  lib
  libgtest
  libgmock
)

