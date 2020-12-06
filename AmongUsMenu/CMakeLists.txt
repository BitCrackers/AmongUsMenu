cmake_minimum_required (VERSION 3.8)

file(
    GLOB_RECURSE FileList 
    LIST_DIRECTORIES false
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c*"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h*"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.png"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.aps"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.rc"
)
set(DEBUG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/NatvisFile.natvis") 

IF(MSVC)
	add_library(AmongUsMenu MODULE ${FileList} ${DEBUG_FILE})
ELSE()
	add_library(AmongUsMenu MODULE ${FileList})
ENDIF()

foreach(FileName IN ITEMS ${FileList})
    get_filename_component(File_Path "${FileName}" PATH)
    file(RELATIVE_PATH File_Path_Rel "${CMAKE_CURRENT_SOURCE_DIR}" "${File_Path}")
    string(REPLACE "/" "\\" Group_Name "${File_Path_Rel}")
	target_include_directories(AmongUsMenu PRIVATE "${Group_Name}")
    source_group("${Group_Name}" FILES "${FileName}")
endforeach()

target_link_libraries(AmongUsMenu "${CMAKE_CURRENT_SOURCE_DIR}/includes/detours/detours.lib")

IF(XINPUT)
	target_compile_definitions(AmongUsMenu PRIVATE _XINPUT=1)
	set_target_properties(AmongUsMenu PROPERTIES OUTPUT_NAME "xinput1_3")
ENDIF(XINPUT)

target_compile_definitions(AmongUsMenu PRIVATE _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS=1)
target_compile_definitions(AmongUsMenu PRIVATE _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING=1 )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /UMBCS /D_UNICODE /DUNICODE /MP /sdl") 

set_property(TARGET AmongUsMenu PROPERTY CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_target_properties( AmongUsMenu
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)