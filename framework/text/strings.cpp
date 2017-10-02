
#include "strings.h"

List<std::string*>* Strings::Split(const std::string& Text, char Delimiter, List<std::string*>* Elements)
{
	std::stringstream ss(Text);
	std::string item;
	while( std::getline(ss, item, Delimiter) )
	{
		Elements->Add(new std::string( item ));
	}
	return Elements;
}

List<std::string*>* Strings::Split(const std::string& Text, char Delimiter)
{
	List<std::string*>* elements = new List<std::string*>();
	Split(Text, Delimiter, elements);
	return elements;
}

std::string Strings::Join(List<std::string*>& Elements, char Delimiter)
{
	std::string result = "";

	for( int i = 0; i < Elements.Count(); i++ )
	{
		if( i != 0 )
		{
			result.append( &Delimiter );
		}
		result.append( *Elements.At( i ) );
	}
	return result;
}

bool Strings::IsNumeric(const std::string& Text)
{
	for( unsigned int i = 0; i < Text.length(); i++ )
	{
		switch( Text[i] )
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '+':
			case '-':
			case '.':
			case ',':
				break;
			default:
				return false;
		}
	}
	return true;
}

int Strings::ToInteger(const std::string& Text)
{
	if( !IsNumeric( Text ) )
	{
		return 0;
	}
	return atoi( Text.c_str() );
}

float Strings::ToFloat(const std::string& Text)
{
	if( !IsNumeric( Text ) )
	{
		return 0;
	}
	return (float)atof( Text.c_str() );
}

std::string Strings::FromNumber(int Value)
{
	char buffer[200];
	sprintf( (char*)&buffer, "%d", Value );
	return std::string(buffer);
}

std::string Strings::Replace(const std::string& Text, const std::string Find, const std::string Replacement)
{
	std::string output;

	unsigned int index = 0;
	while( index < Text.length() )
	{
		std::size_t qidx = Text.find(Find, index);
		if( qidx == std::string::npos )
		{
			output.append( Text.substr( index, Text.length() - index ) );
			index = Text.length();
		} else {
			output.append( Text.substr( index, qidx - index ) );
			output.append( Replacement );
			index = qidx + Find.length();
		}
	}

	return output;
}

bool Strings::StartsWith(std::string Text, std::string Check)
{
	if( Text.substr( 0 , Check.length() ) == Check )
	{
		return true;
	}
	return false;
}

bool Strings::EndsWith(std::string Text, std::string Check)
{
	if( Text.length() < Check.length() )
	{
		return false;
	}
	if( Text.substr( Text.length() - Check.length() , Check.length() ) == Check )
	{
		return true;
	}
	return false;

}


std::string Strings::ToUpper(std::string Text)
{
	// TODO: Fix
	return Text;
}

std::string Strings::ToLower(std::string Text)
{
	// TODO: Fix
	return Text;
}
