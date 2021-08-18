#pragma once

#include <memory>

namespace asx
{
	///
	///	\class Pimpl
	///
	///	\brief Private Implementation. Useful for hiding implementation details and modifying code without changing the API.
	///
	///	Modified from http://herbsutter.com/gotw/_101/
	///
	template <typename T>
	class Pimpl
	{
	public:
		Pimpl();
		template <typename... Args>
		Pimpl(Args&&...) noexcept;
		~Pimpl();
		Pimpl(Pimpl&&) noexcept;
		Pimpl& operator=(Pimpl&&) noexcept;
		T* operator->();
		const T* operator->() const;
		T& operator*();

	private:
		std::unique_ptr<T> m;
	};
}
