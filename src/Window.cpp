#include <asx-gl/Window.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <asx-gl/PimplImpl.h>
#include <asx-gl/Renderer.h>
#include "GLCheck.h"

using namespace asx;

struct Window::Impl
{
	Impl(int width, int height, std::string_view t) : title{t}, size{width, height}
	{
	}

	std::string title;
	glm::vec<2, int> size{};
	GLFWwindow* window{nullptr};
	std::unique_ptr<Renderer> renderer;
	int glfwInitialized{GLFW_FALSE};
	int gladInitialized{GL_FALSE};
};

Window::Window(int width, int height, std::string_view title) : pimpl{width, height, title}
{
	this->pimpl->glfwInitialized = glfwInit();

	if(this->pimpl->glfwInitialized == GLFW_TRUE)
	{
		this->pimpl->window = glfwCreateWindow(width, height, "ASX-GL", nullptr, nullptr);
		glfwMakeContextCurrent(this->pimpl->window);

		this->pimpl->gladInitialized = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

		if(this->pimpl->gladInitialized == GL_TRUE)
		{
			this->pimpl->renderer = std::make_unique<Renderer>();
		}
	}
}

Window::~Window()
{
	if(this->pimpl->glfwInitialized == GLFW_TRUE)
	{
		this->pimpl->renderer.reset();

		glfwDestroyWindow(this->pimpl->window);
		glfwTerminate();
	}
}

Window::Window(Window&& x) noexcept : pimpl{std::move(x.pimpl)}
{
}

Window& Window::operator=(Window&& x) noexcept
{
	this->pimpl = std::move(x.pimpl);
	return *this;
}

bool Window::open() const noexcept
{
	return glfwWindowShouldClose(this->pimpl->window) == GLFW_FALSE;
}

void Window::clear(const glm::vec4& color)
{
	glCheck(glViewport(0, 0, this->size().x, this->size().y));
	glCheck(glClearColor(color.r, color.g, color.b, color.a));
	glCheck(glClear(GL_COLOR_BUFFER_BIT));
	glEnable(GL_BLEND);
}

void Window::draw(const Drawable& x, RenderStates states)
{
	this->pimpl->renderer->draw(x, states);
}

void Window::draw(const VertexArrayObject& x, RenderStates states) const
{
	this->pimpl->renderer->draw(x, states);
}

void Window::draw(const ElementBufferObject& x, RenderStates states) const
{
	this->pimpl->renderer->draw(x, states);
}

void Window::display() const noexcept
{
	glfwSwapBuffers(this->pimpl->window);
}

bool Window::pollEvent(asx::Event& x)
{
	glfwPollEvents();
	return false;
}

glm::vec<2, int> Window::size() const noexcept
{
	return this->pimpl->size;
}
