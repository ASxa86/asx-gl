project(asx-gl)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/asx-gl/Drawable.h
	${PROJECT_INCLUDE_DIR}/asx-gl/ElementBufferObject.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Image.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Pimpl.h
	${PROJECT_INCLUDE_DIR}/asx-gl/PimplImpl.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Primitive.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Renderer.h
	${PROJECT_INCLUDE_DIR}/asx-gl/RenderStates.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Shader.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Sprite.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Texture.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Transformable.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Vertex.h
	${PROJECT_INCLUDE_DIR}/asx-gl/VertexArrayObject.h
	${PROJECT_INCLUDE_DIR}/asx-gl/Window.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Drawable.cpp
	ElementBufferObject.cpp
	GLCheck.cpp
	GLCheck.h
	Image.cpp
	Renderer.cpp
	Shader.cpp
	Sprite.cpp
	Texture.cpp
	Transformable.cpp
	Vertex.cpp
	VertexArrayObject.cpp
	Window.cpp
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

find_path(STB_INCLUDE_DIRS "stb.h")
target_include_directories(${PROJECT_NAME} PRIVATE ${STB_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC
	glfw
	glad::glad
	glm::glm
)

project_install_target()
project_compile_options()
project_gen_export()
