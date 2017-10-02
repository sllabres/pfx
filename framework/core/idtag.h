
#pragma once

template <typename T>
class IDTag
{
	public:
		int id;
		T object;

		IDTag(int ID, T Object) { id = ID; object = Object; };
};
