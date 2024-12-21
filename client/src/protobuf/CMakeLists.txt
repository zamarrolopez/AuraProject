# *****************************************************************************
# Configuración del Proyecto protobuf
# *****************************************************************************
project(protobuf)

# Estándar C++ mínimo requerido
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluir Protobuf y Threads
find_package(Protobuf REQUIRED)
find_package(Threads REQUIRED)

if(NOT PROTOBUF_FOUND)
    message(FATAL_ERROR "No se encontró la biblioteca Protobuf. Asegúrate de que esté instalada.")
endif()

# Mensajes informativos
message(STATUS "Encontrado Protobuf Compiler: ${PROTOBUF_PROTOC_EXECUTABLE}")
message(STATUS "Librería Protobuf: ${Protobuf_LIBRARIES}")

# Configuración de archivos .proto
file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${ProtoFiles})

# Crear la biblioteca
add_library(${PROJECT_NAME} STATIC ${PROTO_SRCS} ${PROTO_HDRS})

# Incluir directorios y vincular dependencias
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROTOBUF_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        protobuf::libprotobuf
        Threads::Threads
)

# Definiciones específicas
target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        _DISABLE_VECTOR_ANNOTATION
        _DISABLE_STRING_ANNOTATION
)
