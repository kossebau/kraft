cmake_minimum_required(VERSION 2.8.11)
project(kraft)

cmake_policy(SET CMP0063 NEW)

enable_testing()

# Tell CMake to run moc when necessary:
# set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
# set(CMAKE_INCLUDE_CURRENT_DIR ON)

# include_directories( "${CMAKE_CURRENT_BINARY_DIR}/../src" )

find_package(Qt5Test REQUIRED)

set(test_libs Qt5::Test kraftlib)

add_executable(t_unitman t_unitman.cpp)
target_link_libraries(t_unitman ${test_libs})
add_test(t_unitman t_unitman)

# ============================================================ 

add_executable(t_format t_format.cpp)
add_test(t_format t_format)
target_link_libraries(t_format ${test_libs})

# ============================================================ 

add_executable(t_metaparser t_metaparser.cpp)
add_test(t_metaparser t_metaparser)

target_link_libraries(t_metaparser ${test_libs})

# ============================================================ 

set(doctype_src
)

add_executable(t_doctype t_doctype.cpp ${doctype_src})
add_test(t_doctype t_doctype)

target_link_libraries(t_doctype ${test_libs})


