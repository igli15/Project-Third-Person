#pragma once

#include <map>

class PlayerPrefs
{
public:
	PlayerPrefs();
	virtual ~PlayerPrefs();

	static void SetString(const std::string& tag, const std::string& string);
	static void SetInt(const std::string& tag, int i);
	static void SetFloat(const std::string& tag, float f);
	static void Setbool(const std::string& tag, bool b);

	static std::string GetString(const std::string& tag);
	static int GetInt(const std::string& tag);
	static float GetFloat(const std::string& tag);
	static bool GetBool(const std::string& tag);

	//Use with caution... cleares everything
	static void ClearAll();

	//Clears any saved type with the specified tag
	static void Clear(const std::string& tag);

private:
	static std::map<std::string, std::string> m_stringMap;
	static std::map<std::string, int> m_intMap;
	static std::map<std::string, float> m_floatMap;
	static std::map<std::string, bool> m_boolMap;

	//internal cleanups

	static void ClearAllStrings();
	static void ClearAllInts();
	static void ClearAllBooleans();
	static void ClearAllFloats();
};

