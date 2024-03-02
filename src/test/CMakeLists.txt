set(SRC ./test_case.cpp)

add_library(kerbal.test ${SRC})
target_include_directories(kerbal.test PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(kerbal.test.shared SHARED ${SRC})
target_include_directories(kerbal.test.shared PUBLIC ${PROJECT_SOURCE_DIR}/include)
set_target_properties(kerbal.test.shared PROPERTIES OUTPUT_NAME "kerbal.test")
