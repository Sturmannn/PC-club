file(GLOB hdrs "headers/*.h*")
file(GLOB srcs "sources/*.cpp")

add_library(${ALG_LIB_NAME} STATIC ${hdrs} ${srcs})

# target_include_directories(${ALG_LIB_NAME} INTERFACE headers)
target_include_directories(${ALG_LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)