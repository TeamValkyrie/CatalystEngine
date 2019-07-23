cmake_minimum_required(VERSION 3.1)

# Custom macro function to add project filters
macro(add_project_filters path input_list prepend)
  foreach(_source IN ITEMS ${${input_list}})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${prepend}/${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
  endforeach()
endmacro()

set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(CatalystEngine)

if(MSVC)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD /DRELEASE /DCRT_SECURE_NO_WARNINGS")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd /DDEBUG /D_CRT_SECURE_NO_WARNINGS")
add_definitions("${COMPILER_DEFINITIONS} /MP")
endif()

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(TRD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Thirdparty")

# Find Header and source files in source directory
file(GLOB_RECURSE SRC
	LIST_DIRECTORIES false
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.c"
)

file(GLOB_RECURSE INC
	LIST_DIRECTORIES false
    "${SRC_DIR}/*.hpp"
    "${SRC_DIR}/*.h"
)

add_executable(CatalystEngine ${SRC} ${INC})

if(MSVC)
target_compile_options(CatalystEngine PRIVATE /W4 /WX)
endif()

target_include_directories(CatalystEngine PRIVATE "${SRC_DIR}")

####### SUBMODULES #######

## EASTL ##
set(EASTL_ROOT_DIR "${TRD_DIR}/eastl")
include_directories (${EASTL_ROOT_DIR}/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EAAssert/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EABase/include/Common)
include_directories (${EASTL_ROOT_DIR}/test/packages/EAMain/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EAStdC/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EATest/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EAThread/include)
set(EASTL_LIBRARY debug ${EASTL_ROOT_DIR}/build/Debug/EASTL.lib optimized ${EASTL_ROOT_DIR}/build/Release/EASTL.lib)
add_subdirectory("${EASTL_ROOT_DIR}")
add_dependencies(CatalystEngine EASTL)
target_link_libraries(CatalystEngine $(EASTL_LIBRARY))

## GLAD ##
add_subdirectory("${TRD_DIR}/glad")
target_link_libraries(CatalystEngine "glad" "${GLAD_LIBRARIES}")
target_include_directories(CatalystEngine PRIVATE "${TRD_DIR}/glad/include")
add_dependencies(CatalystEngine glad)

## GLFW ##
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${TRD_DIR}/glfw")
target_link_libraries(CatalystEngine "glfw" "${GLFW_LIBRARIES}")
target_include_directories(CatalystEngine PRIVATE "${TRD_DIR}/glfw/include")
add_dependencies(CatalystEngine glfw)

## CEREAL ##
target_include_directories(CatalystEngine PRIVATE "${TRD_DIR}/cereal/include")
## glm ##
target_include_directories(CatalystEngine PRIVATE "${TRD_DIR}/glm/")

add_project_filters(${SRC_DIR} SRC Source)
add_project_filters(${SRC_DIR} INC Include)