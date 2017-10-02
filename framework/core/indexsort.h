
#pragma once
#include <cstdlib>
//#include "memory.h"

class IndexSort
{

	private:
		int itemcount;
		int* idlist;
		int* valuelist;

		void SortRecurse(int StartIndex, int Items);

	public:
		IndexSort(int ItemCount);
		~IndexSort();

		void SetItem(int Position, int Index, int SortingValue);

		void Sort();

		int GetIndexAtPosition(int Position);

};
