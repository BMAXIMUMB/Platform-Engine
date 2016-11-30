// random.cpp

#include "random.h"

namespace PlatformEngine
{
	CRandomDevice::CRandomDevice()
	{
		std::random_device rd;
		gen.seed(rd());
	}

	CRandomDevice::~CRandomDevice()
	{
		
	}

	template <typename T>
	T CRandomDevice::GetIntValue(T min, T max)
	{
		std::uniform_int_distribution<T> uid(min, max);
		return uid(gen);
	}
	
	template <typename T>
	T CRandomDevice::GetRealValue(T min, T max)
	{
		std::uniform_real_distribution<T> urd(min, max);
		return urd(gen);
	}

	template <typename T>
	T CRandomDevice::DiscreteDistribution(std::initializer_list<double> list)
	{
		std::discrete_distribution<T> dd(list);
		return dd(gen);
	}

	template <typename T>
	void CRandomDevice::Generate(std::vector<T> &vec, int amount, T min, T max)
	{
		std::uniform_int_distribution<T> ud(min, max);
		std::generate(vec.begin(), 
			vec.begin() + amount, 
			[&ud, this]()
		{
			return ud(gen); 
		});
	}
}