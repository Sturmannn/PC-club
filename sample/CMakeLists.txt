file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${SAMPLE} ${hdrs} ${srcs})

target_link_libraries(${SAMPLE} PUBLIC ${ALG_LIB_NAME})