file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${GTESTS} ${hdrs} ${srcs})

target_link_libraries(${GTESTS} PUBLIC ${ALG_LIB_NAME} GTest::gtest)