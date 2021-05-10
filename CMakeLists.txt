cmake_minimum_required(VERSION 3.15.0)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

project(CZAR)
file(GLOB_RECURSE INCS "include/*.h")
file(GLOB_RECURSE SRC src/*)

add_executable(CZAR ${SRC} ${INCS})
source_group("Includes" FILES ${INCS} ${SRC})

set_property(TARGET CZAR PROPERTY CXX_STANDARD 17)
target_include_directories(CZAR PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(
	TARGETS

	CZAR

	RUNTIME DESTINATION
	${CMAKE_INSTALL_PREFIX}/bin
)