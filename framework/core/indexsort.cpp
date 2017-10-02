
#include "indexsort.h"

IndexSort::IndexSort(int ItemCount)
{
	itemcount = ItemCount;
	idlist = (int*)malloc( ItemCount * sizeof( int ) );
	valuelist = (int*)malloc( ItemCount * sizeof( int ) );
}

IndexSort::~IndexSort()
{
	free( idlist );
	free( valuelist );
}

void IndexSort::SetItem(int Position, int Index, int SortingValue)
{
	idlist[Position] = Index;
	valuelist[Position] = SortingValue;
}

void IndexSort::Sort()
{
	SortRecurse( 0, itemcount );
}

void IndexSort::SortRecurse(int StartIndex, int Items)
{
	if( Items < 2 )
	{
		return;
	}

	int pivot = valuelist[StartIndex + (Items / 2)];

	int i = StartIndex;
	int j = StartIndex + Items - 1;
	while( i < j )
	{
		while( valuelist[i] < pivot )
		{
			i++;
		}
		while( valuelist[j] > pivot )
		{
			j--;
		}
		if( i < j )
		{
			int tmp = valuelist[i];
			valuelist[i] = valuelist[j];
			valuelist[j] = tmp;
			tmp = idlist[i];
			idlist[i] = idlist[j];
			idlist[j] = tmp;
			i++;
			j--;
		}
	}

	SortRecurse( StartIndex, i - StartIndex );
	SortRecurse( StartIndex + (i - StartIndex), Items - (i - StartIndex) );
}

int IndexSort::GetIndexAtPosition(int Position)
{
	return idlist[Position];
}
