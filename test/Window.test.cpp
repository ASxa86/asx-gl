#include <asx-gl/Window.h>
#include <gtest/gtest.h>
#include <chrono>
#include <iostream>
#include <numeric>

#include <asx-gl/VertexBufferObject.h>

using namespace asx;

constexpr std::string_view ShaderVertex = R"(
	#version 330 core
	layout (location = 0) in vec3 aPos;

	void main()
	{
		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
)";

constexpr std::string_view ShaderFragment = R"(
	#version 330 core
	out vec4 FragColor;

	void main()
	{
		FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	}
)";

namespace asx
{
	class Event
	{
	};
}

TEST(Window, Constructor)
{
	Window window;

	Shader shader;
	shader.loadFromMemory(ShaderVertex, ShaderFragment);

	VertexBufferObject vbo{Primitive::Triangles};
	std::vector<Vertex> vertices;
	vertices.push_back({{-0.5f, -0.5f, 0.0f}});
	vertices.push_back({{0.5f, -0.5f, 0.0f}});
	vertices.push_back({{0.0f, 0.5f, 0.0f}});
	vbo.apply(vertices);

	EXPECT_TRUE(window.open());

	auto count = 0;
	std::vector<std::chrono::duration<double>> frames;
	frames.reserve(10'000'000);

	while(window.open() == true && count < 1000000000)
	{
		auto start = std::chrono::steady_clock::now();
		count++;

		asx::Event e;
		while(window.pollEvent(e) == true)
		{
		}

		window.clear({0.2f, 0.3f, 0.3f, 1.0f});
		window.draw(vbo, shader);
		window.display();

		std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
		frames.push_back(elapsed);
	}

	const auto sum = std::accumulate(std::begin(frames), std::end(frames), decltype(frames)::value_type::zero());
	const auto avg = sum / frames.size();
	std::cout << "Elapsed: " << avg.count() << " FPS: " << 1.0 / avg.count() << "\n";
}
