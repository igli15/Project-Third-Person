#include "PlayerPrefs.h"
#include <iostream>

std::map<std::string,std::string> PlayerPrefs::m_stringMap;
std::map<std::string, int> PlayerPrefs::m_intMap;
std::map<std::string, float> PlayerPrefs::m_floatMap;
std::map<std::string, bool> PlayerPrefs::m_boolMap;


PlayerPrefs::PlayerPrefs()
{
}


PlayerPrefs::~PlayerPrefs()
{
}

void PlayerPrefs::SetString(const std::string & tag, const std::string & string)
{
	m_stringMap[tag] = string;
}

void PlayerPrefs::SetInt(const std::string& tag, int i)
{
	m_intMap[tag] = i;
}

void PlayerPrefs::SetFloat(const std::string& tag, float f)
{
	m_floatMap[tag] = f;
}

void PlayerPrefs::Setbool(const std::string& tag, bool b)
{
	m_boolMap[tag] = b;
}

std::string PlayerPrefs::GetString(const std::string & tag)
{
	if (m_stringMap.find(tag) == m_stringMap.end())
	{
		std::cout << "There is not string with that Tag" << std::endl;
		throw;
	}

	return m_stringMap[tag];
}

int PlayerPrefs::GetInt(const std::string & tag)
{
	if (m_intMap.find(tag) == m_intMap.end())
	{
		std::cout << "There is not int with that Tag" << std::endl;
		throw;
	}

	return m_intMap[tag];
}

float PlayerPrefs::GetFloat(const std::string & tag)
{
	if (m_floatMap.find(tag) == m_floatMap.end())
	{
		std::cout << "There is not float with that Tag" << std::endl;
		throw;
	}

	return m_floatMap[tag];
}

bool PlayerPrefs::GetBool(const std::string & tag)
{
	if (m_boolMap.find(tag) == m_boolMap.end())
	{
		std::cout << "There is not boolean with that Tag" << std::endl;
		throw;
	}

	return m_boolMap[tag];
}

void PlayerPrefs::ClearAll()
{
	PlayerPrefs::ClearAllStrings();
	PlayerPrefs::ClearAllInts();
	PlayerPrefs::ClearAllFloats();
	PlayerPrefs::ClearAllBooleans();
}

void PlayerPrefs::Clear(const std::string & tag)
{
	if (m_stringMap.find(tag) != m_stringMap.end())
	{
		m_stringMap.erase(m_stringMap.find(tag));
	}
	else if(m_intMap.find(tag) != m_intMap.end())
	{
		m_intMap.erase(m_intMap.find(tag));
	}
	else if (m_floatMap.find(tag) != m_floatMap.end())
	{
		m_floatMap.erase(m_floatMap.find(tag));
	}
	else if (m_boolMap.find(tag) != m_boolMap.end())
	{
		m_boolMap.erase(m_boolMap.find(tag));
	}
	else
	{
		std::cout << "there is nothing to clear with that tag" << std::endl;
		throw;
	}
}

void PlayerPrefs::ClearAllStrings()
{
	m_stringMap.clear();
}

void PlayerPrefs::ClearAllInts()
{
	m_intMap.clear();
}

void PlayerPrefs::ClearAllBooleans()
{
	m_boolMap.clear();
}

void PlayerPrefs::ClearAllFloats()
{
	m_floatMap.clear();
}
