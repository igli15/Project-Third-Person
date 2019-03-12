#pragma once

#include "tweeny/tweeny.h"
#include <vector>
#include <iostream>
#include <algorithm>


/*
	Wraps tweeny functionallity. gives methods to clear tweens and generate them.
	NOTE: heterogenous tweens are not supported in this wrapper.... if you need them make them manually.
	NOTE: updates tweens as well but onstep has to be called for each tween if you want to set the result to a value
	NOTE: up to 3 value tweens are allowed (triple chars are not needed/supported).

	Callback signature is [](int1,int2,int3){ return false;} returning false means it wont be discarded
	also a tween can be pased in the callback parameters if needed.
	onstep has to be called on the update of the component the tweener is used.

	Do not forget to clean/destroy your tweeners via the specfied methods below.
*/
class Tweener
{

public:
	virtual ~Tweener();


	//Generates a single valued tween based on specified type T
	template<typename T>
	static tweeny::tween<T>* GenerateTween(T from, T to,float duration)
	{
		tweeny::tween<T>* tween = new tweeny::tween<T>();
		*tween = tween->from(from).to(to).during(duration);

		if constexpr (std::is_same<T, int>())
		{
			Tweener::m_singleIntTweens.push_back(tween);
		}
		else if constexpr (std::is_same<T, float>())
		{
			Tweener::m_singleFloatTweens.push_back(tween);
		}
		else if constexpr (std::is_same<T, char>())
		{
			Tweener::m_singlecharTweens.push_back(tween);
		}
		else
		{
			std::cout << "Type not supported" << std::endl;
			throw;
		}

		return tween;
	}

	//Generates a double valued tween based on specified type T
	template<typename T>
	static tweeny::tween<T,T>* GenerateTween(T from1, T to1,T from2,T to2, float duration1,float duration2)
	{
		tweeny::tween<T,T>* tween = new tweeny::tween<T,T>();
		*tween = tween->from(from1,from2).to(to1,to2).during(duration1,duration2);

		if constexpr (std::is_same<T, int>())
		{
			Tweener::m_doubleIntTweens.push_back(tween);
		}
		else if constexpr (std::is_same<T, float>())
		{
			Tweener::m_doubleFloatTweens.push_back(tween);
		}
		else if constexpr (std::is_same<T, char>())
		{
			Tweener::m_doubleCharTweens.push_back(tween);
		}
		else
		{
			std::cout << "Type not supported" << std::endl;
			throw;
		}

		return tween;
	}

	//Generates a triple valued tween based on specified type T
	template<typename T>
	static tweeny::tween<T, T,T>* GenerateTween(T from1, T to1, T from2, T to2,T from3,T to3, float duration1, float duration2,float duration3)
	{
		tweeny::tween<T, T,T>* tween = new tweeny::tween<T, T,T>();
		*tween = tween->from(from1, from2,from3).to(to1, to2,to3).during(duration1, duration2,duration3);

		if constexpr (std::is_same<T, int>())
		{
			Tweener::m_tripleIntTweens.push_back(tween);
		}
		else if constexpr (std::is_same<T, float>())
		{
			Tweener::m_tripleFloatTweens.push_back(tween);
		}
		else
		{
			std::cout << "Type not supported" << std::endl;
			throw;
		}

		return tween;
	}

	//Deletes a single valued Tween
	template<typename T>
	static void DeleteTween(tweeny::tween<T>* tween)
	{
		if constexpr (std::is_same<T, int>())
		{
			delete tween;
			m_singleIntTweens.erase(std::find(m_singleIntTweens.begin(), m_singleIntTweens.end(),tween));
		}
		else if constexpr (std::is_same<T, float>())
		{
			delete tween;
			m_singleFloatTweens.erase(std::find(m_singleFloatTweens.begin(), m_singleFloatTweens.end(), tween));
		}
		else if constexpr (std::is_same<T, char>())
		{
			delete tween;
			m_singlecharTweens.erase(std::find(m_singlecharTweens.begin(), m_singlecharTweens.end(), tween));
		}
		else
		{
			std::cout << "Type not supported" << std::endl;
			throw;
		}

	}

	//Deletes a double valued Tween
	template<typename T>
	static void DeleteTween(tweeny::tween<T,T>* tween)
	{
		if constexpr (std::is_same<T, int>())
		{
			delete tween;
			m_doubleIntTweens.erase(std::find(m_doubleIntTweens.begin(), m_doubleIntTweens.end(), tween));
		}
		else if constexpr (std::is_same<T, float>())
		{
			delete tween;
			m_doubleFloatTweens.erase(std::find(m_doubleFloatTweens.begin(), m_doubleFloatTweens.end(), tween));
		}
		else if constexpr (std::is_same<T, char>())
		{
			delete tween;
			m_doubleCharTweens.erase(std::find(m_doubleCharTweens.begin(), m_doubleCharTweens.end(), tween));
		}
		else
		{
			std::cout << "Type not supported" << std::endl;
			throw;
		}

	}


	//Deltes A triple valued tween
	template<typename T>
	static void DeleteTween(tweeny::tween<T, T, T>* tween)
	{

		if constexpr (std::is_same<T, int>())
		{
			delete tween;
			m_tripleIntTweens.erase(std::find(m_tripleIntTweens.begin(), m_tripleIntTweens.end(), tween));
		}
		else if constexpr (std::is_same<T, float>())
		{
			delete tween;
			m_tripleFloatTweens.erase(std::find(m_tripleFloatTweens.begin(), m_tripleFloatTweens.end(), tween));
		}
		else
		{
			std::cout << "Type not supported" << std::endl;
			throw;
		}

	}

	//Updates All tweens, use internally only!
	static void UpdateAllTweens(int dt);

private:

	//Here are located all lists of types of tweeners 

	static std::vector<tweeny::tween<int>*> m_singleIntTweens;
	static std::vector<tweeny::tween<float>*> m_singleFloatTweens;
	static std::vector<tweeny::tween<char>*> m_singlecharTweens;

	static std::vector<tweeny::tween<int, int>*> m_doubleIntTweens;
	static std::vector<tweeny::tween<float, float>*> m_doubleFloatTweens;
	static std::vector<tweeny::tween<char, char>*> m_doubleCharTweens;

	static std::vector<tweeny::tween<int, int,int>*> m_tripleIntTweens;
	static std::vector<tweeny::tween<float, float,float>*> m_tripleFloatTweens;

	static void UpdateAllSingleTweens(int dt);
	static void UpdateAllDoubleTweens(int dt);
	static void UpdateAllTripleTweens(int dt);

	Tweener();

};

