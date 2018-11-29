# Add as a subdirectory SimpleRenderEngineProject using add_subdirectory
IF (NOT DEFINED all_libs)
    message( FATAL_ERROR "This CMakeLists.txt must be included using the command add_subdirectory(name)" )
ENDIF (NOT DEFINED all_libs)
# Ensure SimpleRenderEngineProject is up-to-date
IF (WIN32)
    IF (NOT DEFINED DLLFileList)
        message( FATAL_ERROR "The SimpleRenderEngineProject has been updated. Clone the project (https://github.com/mortennobel/SimpleRenderEngineProject) again the project again and start over." )
    ENDIF(NOT DEFINED DLLFileList)
ENDIF(WIN32)

# Add hpp and cpp files
file(GLOB_RECURSE WormSource
        "src/*.hpp"
        "src/*.h"
        "src/*.cpp"
        )

# Compile cpp files (from Snake variable)
add_executable(Worm ${WormSource})
target_link_libraries(Worm ${all_libs})


# including Boost library
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# include boost libs (and dependencies)
include_directories(libs/boost/geometry/include)
include_directories(libs/boost//mpl/include)
include_directories(libs/boost/config/include)
include_directories(libs/boost/preprocessor/include)
include_directories(libs/boost/range/include)
include_directories(libs/boost/type_traits/include)
include_directories(libs/boost/iterator/include)
include_directories(libs/boost/static_assert/include)
include_directories(libs/boost/core/include)
include_directories(libs/boost/numeric_conversion/include)
include_directories(libs/boost/throw_exception/include)
include_directories(libs/boost/utility/include)
include_directories(libs/boost/math/include)
include_directories(libs/boost/predef/include)
include_directories(libs/boost/lexical_cast/include)
include_directories(libs/boost/detail/include)
include_directories(libs/boost/concept_check/include)
include_directories(libs/boost/integer/include)
include_directories(libs/boost/array/include)
include_directories(libs/boost/container/include)
include_directories(libs/boost/move/include)
include_directories(libs/boost/variant/include)
include_directories(libs/boost/tuple/include)
include_directories(libs/boost/rational/include)
include_directories(libs/boost/algorithm/include)
include_directories(libs/boost/tokenizer/include)
include_directories(libs/boost/function/include)
include_directories(libs/boost/type_index/include)
include_directories(libs/boost/container_hash/include)
include_directories(libs/boost/bind/include)
include_directories(libs/boost/function_types/include)
include_directories(libs/boost/intrusive/include)
include_directories(libs/boost/smart_ptr/include)
include_directories(libs/boost/qvm/include)
include_directories(libs/boost/exception/include)

# include logging library
include_directories(libs/spdlog/include)

add_subdirectory(libs/poly2tri)
include_directories(libs/poly2tri)
target_link_libraries(Worm poly2tri)

# copy files to dest
IF (WIN32)
    file(COPY atlas_textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY atlas_textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
ELSE(WIN32)
    file(COPY atlas_textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
ENDIF(WIN32)

IF (WIN32)
    # Copy dll files to ${CMAKE_CURRENT_BINARY_DIR}/Debug
    file(COPY ${DLLFileList} DESTINATION Debug)
    file(COPY ${DLLFileList} DESTINATION Release)
    file(COPY ${DLLFileList} DESTINATION .)

    # Set working directory to ${CMAKE_CURRENT_BINARY_DIR}/Debug
    set_target_properties(Worm PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug)
ENDIF(WIN32)


option(WITH_DEBUG_PHYSICS "Enables the visualization of the Physics Colliders" OFF)

if(WITH_DEBUG_PHYSICS)
    message("physics visualization ENABLED")
    add_definitions(-DDEBUG_PHYSICS)
else()
    message("physics visualization DISABLED")
endif()
