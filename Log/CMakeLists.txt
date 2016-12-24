add_subdirectory(Source)

file(GLOB_RECURSE Log_Module_Src_Public
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/Public/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/Public/*.cpp"
)

file(GLOB_RECURSE Log_Module_Src_Private
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/Private/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/Private/*.cpp"
)

add_library(Log SHARED ${Log_Module_Src_Public} ${Log_Module_Src_Private})

target_link_libraries(Log Core)

source_group("Public" FILES ${Log_Module_Src_Public})
source_group("Private" FILES ${Log_Module_Src_Private})

target_include_directories(Log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source/Public)
target_include_directories(Log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Source/Public)

add_definitions(-DUNICODE -D_UNICODE)