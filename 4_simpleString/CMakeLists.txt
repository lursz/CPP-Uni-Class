cmake_minimum_required(VERSION 3.16)
project(SimpleString_dlaStudentow)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(COMPILER_FLAGS "--std=c++17 -Wall -Wextra -pedantic -Weffc++")
    set(COMPILER_DEBUG_FLAGS "-D_DEBUG")
    set(COMPILER_RELEASE_FLAGS "-O3 -DNDEBUG")
    set(LINKER_FLAGS "--std=c++17")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # for cppcheck

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


file(GLOB SOURCES *.cpp *.cc *.c)
file(GLOB HEADERS *.h *.hpp)
file(GLOB TEST_FILES *Tests.cpp)
set(SOURCES_WITHOUT_TESTS ${SOURCES})
list(REMOVE_ITEM SOURCES_WITHOUT_TESTS ${TEST_FILES})
message("Katalog do zbudowanego projektu: ${PROJECT_BINARY_DIR}")
message(" + Znaleziono nagłówki: ${HEADERS} w katalogach ${INCLUDE_DIRECTORY}")
message(" + Znaleziono źródła: ${SOURCES}")
message("   w tym źródła: ${SOURCES_WITHOUT_TESTS} i testy: ${TEST_FILES}")


############ dodanie binarki z mainem i danymi studenta
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} gtest gtest_main)


############ KOMENDA: make run
add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)


############ KOMENDA: make valgrind_${PROJECT_NAME}
find_program(VALGRIND NAMES valgrind)
if (VALGRIND)
    message("\t* valgrind found: ${VALGRIND}")
    add_custom_target(valgrind_${PROJECT_NAME} DEPENDS ${PROJECT_NAME}
        COMMAND ${VALGRIND} --leak-check=full ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
endif()


############ KOMENDA: make docs_${PROJECT_NAME}
find_program(DOXYGEN NAMES doxygen)
if (DOXYGEN)
    message("\t* doxygen found: ${DOXYGEN}")
    add_custom_target(docs_${PROJECT_NAME}
            COMMAND ${DOXYGEN} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile && make -C ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/latex && cp doxygen/latex/refman.pdf ${CMAKE_CURRENT_BINARY_DIR}/trescWygenerowana.pdf
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()


############ KOMENDA: make zip
get_filename_component(directoryBasename ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_custom_target(zip
        COMMAND zip -r ${CMAKE_BINARY_DIR}/${directoryBasename}.zip ./
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


############ KOMENDA: make format
find_program(CLANG_FORMAT NAMES clang-format)
if (CLANG_FORMAT)
    message("\t* clang-format found: ${CLANG_FORMAT}")
    #idealnym standardem dla C++ jest https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines, niestety nie jest on jeszcze wspierany przez narzędzie clang-format, dlatego używam innego popularnego stylu.
    add_custom_target(format_${PROJECT_NAME}
            COMMAND clang-format -i -style=Google ${HEADERS} ${SOURCES_WITHOUT_TESTS})
endif()


############ KOMENDA: make cppcheck_${PROJECT_NAME}
find_program(CPPCHECK NAMES cppcheck)
if (CPPCHECK)
    message("\t* cppcheck found: ${CPPCHECK}")
    add_custom_target(cppcheck_${PROJECT_NAME} DEPENDS ${PROJECT_NAME}
        COMMAND cppcheck --project=${CMAKE_BINARY_DIR}/compile_commands.json --force --enable=warning,performance,unusedFunction,style,information --template=gcc --inline-suppr --library=gnu.cfg --library=std.cfg --library=cppcheck-lib.cfg --library=motif.cfg --library=qt.cfg --library=windows.cfg --library=gnu.cfg --library=posix.cfg --library=avr.cfg --suppress=missingIncludeSystem -i ${HEADERS} ${SOURCES_WITHOUT_TESTS} -i ${CMAKE_CURRENT_SOURCE_DIR}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
