
#pragma once

#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "../core/list.h"

class Strings
{

	public:

		static List<std::string*>* Split(const std::string& Text, char Delimiter, List<std::string*>* Elements);
		static List<std::string*>* Split(const std::string& Text, char Delimiter);

		static std::string Join(List<std::string*>& Elements, char Delimiter);

		static bool IsNumeric(const std::string& Text);
		static int ToInteger(const std::string& Text);
		static float ToFloat(const std::string& Text);

		static std::string FromNumber(int Value);

		static std::string Replace(const std::string& Text, const std::string Find, const std::string Replacement);

		static bool StartsWith(std::string Text, std::string Check);
		static bool EndsWith(std::string Text, std::string Check);

		static std::string ToUpper(std::string Text);
		static std::string ToLower(std::string Text);

};
