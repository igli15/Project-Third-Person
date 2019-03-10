#pragma once

#include "tweeny/tweeny.h"
#include <vector>
#include <iostream>
#include <algorithm>

class Tweener
{

private:
	static std::vector<tweeny::tween<int>*> m_intTweeners;
	Tweener();

public:
	virtual ~Tweener();

	template<typename T>
	static tweeny::tween<T>* GenerateTween(T from, T to,float duration)
	{
		tweeny::tween<T>* tween = new tweeny::tween<T>();
		*tween = tween->from(from).to(to).during(duration);

		
		if constexpr (std::is_same<T, int>())
		{
			Tweener::m_intTweeners.push_back(tween);
		}

		return tween;
	}

	template<typename T>
	static void DeleteTween(tweeny::tween<T>* tween)
	{
		if constexpr (std::is_same<T, int>())
		{
			m_intTweeners.erase(std::find(m_intTweeners.begin(), m_intTweeners.end(),tween));
		}

	}

};

