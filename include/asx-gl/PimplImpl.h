#pragma once

#include <utility>

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
	Pimpl<T>::Pimpl() : m{std::make_unique<T>()}
	{
	}

	template <typename T>
	template <typename... Args>
	Pimpl<T>::Pimpl(Args&&... args) noexcept : m{std::make_unique<T>(std::forward<Args>(args)...)}
	{
	}

	template <typename T>
	Pimpl<T>::~Pimpl()
	{
	}

	template <typename T>
	Pimpl<T>::Pimpl(Pimpl<T>&& x) noexcept : m{std::move(x.m)}
	{
	}

	template <typename T>
	Pimpl<T>& Pimpl<T>::operator=(Pimpl<T>&& x) noexcept
	{
		this->m = std::move(x.m);
		return *this;
	}

	template <typename T>
	T* Pimpl<T>::operator->()
	{
		return m.get();
	}

	template <typename T>
	const T* Pimpl<T>::operator->() const
	{
		return m.get();
	}

	template <typename T>
	T& Pimpl<T>::operator*()
	{
		return *m.get();
	}
}
