#include <iostream>
#include <omp.h>
#include <chrono>
#include <limits>
#include <vector>
#include "vector.hpp"
#include <cassert>

class Timer
{
private:
	double m_start;
	double m_end;
	double m_average;
	size_t m_requests;

public:
	Timer() :
		m_start{},
		m_end{},
		m_average{},
		m_requests{}
	{}

	Timer* start()
	{
		++this->m_requests;
		this->m_start = omp_get_wtime();
		return this;
	}

	Timer* end()
	{
		this->m_end = omp_get_wtime();
		this->m_average += this->m_end - this->m_start;
		return this;
	}

	double result()
	{
		return this->m_end - this->m_start;
	}

	double avarage()
	{
		return this->m_average / this->m_requests;
	}
};

int main()
{
	const size_t amount{ 100000 };
	Timer timer;

	//std vector
	timer.start();
	std::vector<size_t> stdvec;

	for (size_t i = 0; i < amount; ++i)
	{
		stdvec.push_back(i);
	}

	timer.end();
	std::cerr << "STDVEC [INSERT]: " << timer.result() << std::endl;

	//fsx vector
	timer.start();
	fsx::vector<size_t> fsxvec;

	for (size_t i = 0; i < amount; ++i)
	{
		fsxvec.push_back(i);
	}

	timer.end();
	std::cerr << "FSXVEC [INSERT]: " << timer.result() << std::endl;

	//remove stuff
	timer.start();
	auto stditer = stdvec.begin();
	int x = 0;
	for (; stditer != stdvec.end(); ++stditer)
	{
		if (x % 2 == 0)
		{
			stditer = stdvec.erase(stditer);
		}
		else
		{
			++stditer;
			++x;
		}
	}
	timer.end();
	std::cerr << "STDVEC [REMOVE]: " << timer.result() << std::endl;

	timer.start();
	auto fsxiter = fsxvec.begin();
	x = 0;
	for (; fsxiter != fsxvec.end(); ++fsxiter)
	{
		if (x % 2 == 0)
		{
			fsxiter = fsxvec.erase(fsxiter);
		}
		else
		{
			++fsxiter;
			++x;
		}
	}
	timer.end();
	std::cerr << "FSXVEC [REMOVE]: " << timer.result() << std::endl;

	//Writing some tests
	std::cerr << std::endl << "Running tests... ";
	for (size_t i = 0; i < stdvec.size(); ++i)
	{
		assert(stdvec[i] == (i + i + 1));
		assert(fsxvec[i] == (i + i + 1));
	}
	std::cerr << "ok" << std::endl;
}