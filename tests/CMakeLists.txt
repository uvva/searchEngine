include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(search_engine_test testInvertedIndex.cpp ${MY_INCLUDE_DIR}/invertedIndex.h ${MY_SRC_DIR}/invertedIndex.cpp testSearchServer.cpp ${MY_INCLUDE_DIR}/searchServer.h ${MY_SRC_DIR}/searchServer.cpp)

include_directories(${MY_INCLUDE_DIR})

include_directories(${MY_SRC_DIR})

target_link_libraries(search_engine_test PRIVATE gtest_main) #search_engine_test

include(GoogleTest)
gtest_discover_tests(search_engine_test)