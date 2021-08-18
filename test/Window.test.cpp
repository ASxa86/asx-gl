#include <asx-gl/Window.h>
#include <gtest/gtest.h>

using namespace asx;

namespace asx
{
	class Event
	{
	};
}

TEST(Window, Constructor)
{
	Window window;

	EXPECT_TRUE(window.open());

	auto count = 0;
	while(window.open() == true && count < 1000000000)
	{
		count++;

		asx::Event e;
		while(window.pollEvent(e) == true)
		{
		}

		window.clear();
		// window.draw();
		window.display();
	}
}
