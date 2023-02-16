#ifndef FSX_ITERATOR_HPP
#define FSX_ITERATOR_HPP

#include <iostream>

namespace fsx
{
	template <typename T>
	class vector;

	template <typename T>
	class iterator
	{
	private:
		friend fsx::vector<T>;
		size_t m_position;
		size_t m_start;
		size_t m_end;
		const fsx::vector<T>* m_vector;

	public:
		iterator() = default;

		iterator(const fsx::vector<T>* vectorPtr, size_t position = 0, size_t start = 0, size_t end = 0) :
			m_position(position),
			m_start(start),
			m_end(end),
			m_vector(vectorPtr)
		{}

		inline size_t index() const noexcept
		{
			return this->m_position - this->m_start;
		}

		bool operator!=(const fsx::iterator<T>& other) const noexcept
		{
			return (this->m_position - this->m_start) != (other.m_position - other.m_start);
		}

		fsx::iterator<T> operator+(size_t index) const noexcept
		{
			return fsx::iterator<T>(this->m_vector, this->m_position + index, this->m_start, this->m_end);
		}

		fsx::iterator<T> operator-(size_t index) const noexcept
		{
			return fsx::iterator<T>(this->m_vector, this->m_position - index, this->m_start, this->m_end);
		}

		T* operator->() const noexcept
		{
			return &this->m_vector->operator[](this->m_position - this->m_start - this->m_end);
		}

		T& operator*() const noexcept
		{
			return this->m_vector->operator[](this->m_position - this->m_start - this->m_end);
		}

		const fsx::iterator<T>& operator++() noexcept
		{
			++this->m_position;
			return *this;
		}

		~iterator() = default;
	};
}

#endif