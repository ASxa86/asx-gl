#include <asx-gl/Window.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <asx-gl/PimplImpl.h>

using namespace asx;

struct Window::Impl
{
	Impl(int width, int height, std::string_view t) : title{t}, size{width, height}
	{
	}

	std::string title;
	glm::vec<2, int> size{};
	GLFWwindow* window{nullptr};
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
	}
}

Window::~Window()
{
	if(this->pimpl->glfwInitialized == GLFW_TRUE)
	{
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

void Window::clear(const glm::vec4& color)
{
	glViewport(0, 0, this->size().x, this->size().y);
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Window::open() const noexcept
{
	return glfwWindowShouldClose(this->pimpl->window) == GLFW_FALSE;
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
