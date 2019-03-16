#include "Tweener.h"
#include "tweeny/tweeny.h"


std::vector<tweeny::tween<int>*> Tweener::m_singleIntTweens;
std::vector<tweeny::tween<float>*> Tweener::m_singleFloatTweens;
std::vector<tweeny::tween<char>*> Tweener::m_singlecharTweens;

std::vector<tweeny::tween<int, int>*> Tweener::m_doubleIntTweens;
std::vector<tweeny::tween<float, float>*> Tweener::m_doubleFloatTweens;
std::vector<tweeny::tween<char, char>*> Tweener::m_doubleCharTweens;

std::vector<tweeny::tween<int, int, int>*> Tweener::m_tripleIntTweens;
std::vector<tweeny::tween<float, float, float>*> Tweener::m_tripleFloatTweens;

Tweener::Tweener()
{
}

void Tweener::UpdateAllTweens(int dt)
{
	UpdateAllSingleTweens(dt);
	UpdateAllDoubleTweens(dt);
	UpdateAllTripleTweens(dt);
}

void Tweener::UpdateAllSingleTweens(int dt)
{
	for (int i = 0; i < m_singleIntTweens.size(); i++)
	{
		m_singleIntTweens[i]->step(dt);
	}

	for (int i = 0; i < m_singleFloatTweens.size(); i++)
	{
		m_singleFloatTweens[i]->step(dt);
	}

	for (int i = 0; i < m_singlecharTweens.size(); i++)
	{
		m_singlecharTweens[i]->step(dt);
	}
}

void Tweener::UpdateAllDoubleTweens(int dt)
{
	for (int i = 0; i < m_doubleIntTweens.size(); i++)
	{
		m_doubleIntTweens[i]->step(dt);
	}

	for (int i = 0; i < m_doubleFloatTweens.size(); i++)
	{
		m_doubleFloatTweens[i]->step(dt);
	}

	for (int i = 0; i < m_doubleCharTweens.size(); i++)
	{
		m_doubleCharTweens[i]->step(dt);
	}
}

void Tweener::UpdateAllTripleTweens(int dt)
{
	for (int i = 0; i < m_tripleIntTweens.size(); i++)
	{
		m_tripleIntTweens[i]->step(dt);
	}

	for (int i = 0; i < m_tripleFloatTweens.size(); i++)
	{
		m_tripleFloatTweens[i]->step(dt);
	}
}


Tweener::~Tweener()
{
}
