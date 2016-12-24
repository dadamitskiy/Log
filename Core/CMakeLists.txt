add_subdirectory(Source)

file(GLOB_RECURSE Core_Module_Src_Public
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/Public/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/Public/*.cpp"
)

file(GLOB_RECURSE Core_Module_Src_Private
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/Private/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/Private/*.cpp"
)

add_library(Core SHARED ${Core_Module_Src_Public} ${Core_Module_Src_Private})

source_group("Public" FILES ${Core_Module_Src_Public})
source_group("Private" FILES ${Core_Module_Src_Private})

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source/Public)

add_definitions(-DUNICODE -D_UNICODE)