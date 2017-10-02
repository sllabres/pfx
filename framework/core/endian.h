
#pragma once

#include "maths.h"
#include "memory.h"
#include <string.h>

class Endian
{

	public:
		enum Endians
		{
			LITTLE,
			BIG
		};

		static Endians GetNativeEndian()
		{
			unsigned int tmp = 0xFF;
			unsigned char* c = (unsigned char*)&tmp;
			if( c[0] == 0xFF )
			{
				return Endians::LITTLE;
			} else {
				return Endians::BIG;
			}
		};


		template <typename T>
		static T LittleEndianBytesTo(void* Data, int DataLength)
		{
			T output = 0;
			int copybytes = Maths::Min( sizeof( T ), DataLength );

			unsigned char* dptr = (unsigned char*)Data;
			unsigned char* optr = (unsigned char*)&output;
			if( GetNativeEndian() == Endians::LITTLE )
			{
				memcpy( (void*)&output, Data, copybytes );
			} else {
				optr += sizeof( T ) - 1;
				for( int i = 0; i < copybytes; i++ )
				{
					optr[0] = dptr[i];
					optr--;
				}
			}
			return output;
		};

		template <typename T>
		static T BigEndianBytesTo(void* Data, int DataLength)
		{
			T output = 0;
			int copybytes = Maths::Min( sizeof( T ), DataLength );

			unsigned char* dptr = (unsigned char*)Data;
			unsigned char* optr = (unsigned char*)&output;
			if( GetNativeEndian() == Endians::BIG )
			{
				dptr += (DataLength - copybytes);
				memcpy( (void*)&output, (void*)dptr, copybytes );
			} else {
				for( int i = 0; i < copybytes; i++ )
				{
					optr[0] = dptr[DataLength - i - 1];
					optr++;
				}

			}
			return output;
		};

		template <typename T>
		static Memory* ToLittleEndianBytes(T Value)
		{
			Memory* m = new Memory();
			if( GetNativeEndian() == Endians::LITTLE )
			{
				m->AppendData( &Value, sizeof( T ) );
			} else {
				unsigned char* v = (unsigned char*)&Value;
				for( int i = sizeof( T ) - 1; i >= 0; i++ )
				{
					unsigned char* vo = v + i;
					m->AppendData( (void*)vo, 1 );
				}
			}
			return m;
		};

		template <typename T>
		static Memory* ToBigEndianBytes(T Value)
		{
			Memory* m = new Memory();
			if( GetNativeEndian() == Endians::BIG )
			{
				m->AppendData( &Value, sizeof( T ) );
			} else {
				unsigned char* v = (unsigned char*)&Value;
				for( int i = sizeof( T ) - 1; i >= 0; i++ )
				{
					unsigned char* vo = v + i;
					m->AppendData( (void*)vo, 1 );
				}
			}
			return m;
		};

		template <typename T>
		static T LittleEndianToNative(T Value)
		{
			T v = 0;
			EndianSwitch( (void*)&Value, (void*)&v, sizeof( T ), Endians::LITTLE, GetNativeEndian() );
			return v;
		}

		template <typename T>
		static T BigEndianToNative(T Value)
		{
			T v = 0;
			EndianSwitch( (void*)&Value, (void*)&v, sizeof( T ), Endians::BIG, GetNativeEndian() );
			return v;
		}

		template <typename T>
		static T NativeToLittleEndian(T Value)
		{
			T v = 0;
			EndianSwitch( (void*)&Value, (void*)&v, sizeof( T ), GetNativeEndian(), Endians::LITTLE );
			return v;
		}

		template <typename T>
		static T NativeToBigEndian(T Value)
		{
			T v = 0;
			EndianSwitch( (void*)&Value, (void*)&v, sizeof( T ), GetNativeEndian(), Endians::BIG );
			return v;
		}


		static void EndianSwitch(void* Source, void* Target, int Length, Endians SourceEndian, Endians TargetEndian)
		{
			if( SourceEndian == TargetEndian )
			{
				memcpy( Target, Source, Length );
			} else {
				unsigned char* s = (unsigned char*)Source;
				unsigned char* t = (unsigned char*)Target;
				for( int i = 0; i < Length; i++ )
				{
					t[Length - i - 1] = s[i];
				}
			}
		};

};
