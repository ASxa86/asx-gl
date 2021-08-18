#pragma once

#include <asx-gl/Pimpl.h>
#include <asx-gl/export.hxx>
#include <glm/glm.hpp>
#include <string_view>

namespace asx
{
	class Event;

	class ASX_GL_EXPORT Window final
	{
	public:
		Window(int width = 1280, int height = 720, std::string_view title = {});
		~Window();

		Window(Window&& x) noexcept;
		Window& operator=(Window&& x) noexcept;

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		///
		///
		///
		void clear(const glm::vec4& color = {0.0f, 0.0f, 0.0f, 1.0f});

		///
		///	\brief Return the open state of this window.
		/// \return bool True while the window remains open.
		///
		bool open() const noexcept;

		///
		///	\brief Perform swap buffers.
		/// 
		void display() const noexcept;

		///
		///	\brief Polls for an event from the window's event queue if any exist.
		/// \return bool Returns true while events remain within the queue.
		///
		bool pollEvent(asx::Event& x);

		///
		///	\brief Return the current dimensions of this window.
		///
		glm::vec<2, int> size() const noexcept;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}
