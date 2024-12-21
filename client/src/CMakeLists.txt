# Versión mínima de CMake
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(otclient)

# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluir directorio de módulos personalizados
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Buscar dependencias necesarias
find_package(Protobuf REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenAL REQUIRED)
find_package(ZLIB REQUIRED)

# Definir directorios de inclusión
include_directories(
    ${Protobuf_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${OPENAL_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Generar archivos .cpp y .h a partir de archivos .proto
set(PROTO_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/client/src/protobuf/appearances.proto
)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

# Busca todos los archivos fuente dentro de src/
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Depuración: Imprimir archivos encontrados
if(SOURCES)
    message(STATUS "Se encontraron los siguientes archivos fuente:")
    foreach(FILE ${SOURCES})
        message(STATUS "  ${FILE}")
    endforeach()
else()
    message(FATAL_ERROR "No se encontraron archivos fuente en el directorio src.")
endif()


# Crear el ejecutable principal
add_executable(otclient ${SOURCES} ${PROTO_SRCS} ${PROTO_HDRS})

# Vincular bibliotecas necesarias
target_link_libraries(otclient
    ${Protobuf_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${OPENAL_LIBRARIES}
    ${ZLIB_LIBRARIES}
)

# Definir macros para compilación específica si es necesario
add_definitions(-DPROTOCOL_SUPPORT -DCLIENT_FEATURES)

# Instrucciones adicionales de configuración para plataformas específicas
if(WIN32)
    message(STATUS "Configurando para Windows...")
    add_definitions(-DWINDOWS_BUILD)
elseif(UNIX)
    message(STATUS "Configurando para Unix...")
endif()
