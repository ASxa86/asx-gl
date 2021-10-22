project(asx-gl)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/asx-gl/ElementBufferObject.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Pimpl.h
	${PROJECT_INCLUDE_DIR}/asx-gl/PimplImpl.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Primitive.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Renderer.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Shader.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Vertex.h
	${PROJECT_INCLUDE_DIR}/asx-gl/VertexArrayObject.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Window.h
)

target_sources(${PROJECT_NAME} PRIVATE
	ElementBufferObject.cpp
	GLCheck.cpp
	GLCheck.h
	Renderer.cpp
	Shader.cpp
	Vertex.cpp
	VertexArrayObject.cpp
	Window.cpp
)

find_package(libpng REQUIRED COMPONENTS system)
find_package(JPEG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${JPEG_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
	glfw
	glad::glad
	png
	${JPEG_LIBRARIES}
	glm::glm
)

project_install_target()
project_compile_options()
project_gen_export()
