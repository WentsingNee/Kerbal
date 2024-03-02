set(SRC ./sha1.cpp)

add_library(kerbal.hash ${SRC})
add_library(kerbal.hash.shared SHARED ${SRC})
set_target_properties(kerbal.hash.shared PROPERTIES OUTPUT_NAME "kerbal.hash")
