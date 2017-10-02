
#pragma once

#include <cstdlib>
#include "memory.h"

template <typename T>
class List
{

	private:
		Memory itemarray;
		int itemcount;
		int arraycount;

	public:
		List() { Clear(); };

		void Clear()
		{
			arraycount = itemarray.GetSize() / sizeof( T );
			itemcount = 0;
		};

		int Count() { return itemcount; };

		void Add(T Item)
		{
			// Make sure we have enough buffer
			if( itemcount >= arraycount )
			{
				itemarray.Resize( (itemcount + 1) * sizeof( T ) );
			}

			T* ia = (T*)itemarray.GetData();
			ia[itemcount] = Item;

			arraycount = itemarray.GetSize() / sizeof( T );
			itemcount++;
		};

		void InsertAt(T Item, int Index)
		{
			if( Index >= itemcount )
			{
				Add( Item );
			} else {
				itemarray.Resize( (itemcount + 1) * sizeof( T ) );

				T* ia = (T*)itemarray.GetData();

				for( int i = itemcount - 1; i >= Index; i-- )
				{
					ia[i + 1] = ia[i];
				}
				ia[Index] = Item;

				arraycount = itemarray.GetSize() / sizeof( T );
				itemcount++;
			}
		};

		T At(int Index)
		{
			T* ia = (T*)itemarray.GetData();
			return ia[Index];
		};

		T operator[](int Index)
		{
			return At(Index);
		};

		void Delete(T Item)
		{
			T* ia = (T*)itemarray.GetData();
			for( int i = 0; i < itemcount; i++ )
			{
				if( Item == ia[i] )
				{
					DeleteAt( i );
					return;
				}
			}
		};

		void DeleteAt(int Index)
		{
			if( Index < itemcount - 1 )
			{
				T* ia = (T*)itemarray.GetData();

				for( int i = Index; i < itemcount - 1; i++ )
				{
					ia[i] = ia[i + 1];
				}

			}
			itemcount--;
		};

		int Find(T Item)
		{
			T* ia = (T*)itemarray.GetData();
			for( int i = 0; i < itemcount; i++ )
			{
				if( Item == ia[i] )
				{
					return i;
				}
			}
			return -1;
		};

};

