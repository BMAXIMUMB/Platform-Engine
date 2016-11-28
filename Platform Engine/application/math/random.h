// math.h

#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "../../platform_engine.h"

#include <random>

namespace PlatformEngine
{
	/**
	*	Генератор случайных чисел
	*
	*	В качетстве генератора используется mt19937
	*	Для задания зерна используется недетерминированный генератор random_device
	*/

	class CRandomDevice
	{
	private:

		// ГПСЧ
		std::mt19937 gen;

	public:
		PLATFORMENGINE_API CRandomDevice();
		PLATFORMENGINE_API ~CRandomDevice();

		/**
		* Возвращает целое число в заданном диапазоне [min, max]
		*/
		template <typename T = int>
		PLATFORMENGINE_API T GetIntValue(T min, T max);

		/**
		* Возвращает вещественное число в заданном диапазоне [min, max)
		*/
		template <typename T = double>
		PLATFORMENGINE_API T GetRealValue(T min, T max);

		/**
		*	Формирует дискретное распределение целых чисел на интервале [0, n);
		*/
		template <typename T = int>
		PLATFORMENGINE_API T DiscreteDistribution(std::initializer_list<double> list);
	};
	
	// Для использования вне dll
	template PLATFORMENGINE_API int CRandomDevice::GetIntValue<int>(int, int);
	template PLATFORMENGINE_API short CRandomDevice::GetIntValue<short>(short, short);
	template PLATFORMENGINE_API long CRandomDevice::GetIntValue<long>(long, long);
	template PLATFORMENGINE_API long long CRandomDevice::GetIntValue<long long>(long long, long long);

	template PLATFORMENGINE_API int CRandomDevice::DiscreteDistribution<int>(std::initializer_list<double>);
	template PLATFORMENGINE_API short CRandomDevice::DiscreteDistribution<short>(std::initializer_list<double>);
	template PLATFORMENGINE_API long CRandomDevice::DiscreteDistribution<long>(std::initializer_list<double>);
	template PLATFORMENGINE_API long long CRandomDevice::DiscreteDistribution<long long>(std::initializer_list<double>);

	template PLATFORMENGINE_API float CRandomDevice::GetRealValue<float>(float, float);
	template PLATFORMENGINE_API double CRandomDevice::GetRealValue<double>(double, double);
	template PLATFORMENGINE_API long double CRandomDevice::GetRealValue<long double>(long double, long double);
}
#endif /*_RANDOM_H_*/
