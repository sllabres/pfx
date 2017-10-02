
#pragma once

#include "memory.h"
#include "endian.h"

namespace MemoryStreamPositions
{
	enum StreamPositions
	{
		BEGINNING,
		CURRENT,
		END
	};
}

class MemoryStream
{

	private:
		bool chunkcreated;
		Memory* chunk;
		size_t chunkpointer;
		size_t chunkbitpointer;

		bool CanReadValue(size_t Length);
		void ReadValue(void* Output, size_t Length);
		void WriteValue(void* Input, size_t Length);
		void ReadBitsValue(void* Output, size_t OutputSizeBytes, size_t LengthBits);
		void WriteBitsValue(void* Input, size_t Length);

	public:
		MemoryStream();
		MemoryStream(Memory* Chunk);
		~MemoryStream();

		size_t GetLength();
		void Seek(size_t Position, MemoryStreamPositions::StreamPositions Base);

		Memory* GetChunk();

		template <typename T>
		bool CanRead() { return CanReadValue( sizeof( T ) ); };

		template <typename T>
		T Read()
		{
			return Read<T>( Endian::LITTLE );
		};

		template <typename T>
		T Read(Endian::Endians UseEndian)
		{
			T value;
			T endianed;
			ReadValue( (void*)&value, sizeof( T ) );
			Endian::EndianSwitch( (void*)&value, (void*)&endianed, sizeof( T ), UseEndian, Endian::GetNativeEndian() );
			return endianed;
		};


		template <typename T>
		void Write(T Value)
		{
			Write<T>( Value, Endian::LITTLE );
		};

		template <typename T>
		void Write(T Value, Endian::Endians UseEndian)
		{
			T value = 0;
			Endian::EndianSwitch( (void*)&Value, (void*)&value, sizeof( T ), Endian::GetNativeEndian(), UseEndian );
			WriteValue( (void*)&value, sizeof( T ) );
		};

		Memory* ReadChunk(size_t Length);
		void WriteChunk(Memory* Chunk);

		template <typename T>
		T ReadBits(int BitCount)
		{
			T value = 0;
			ReadBitsValue( (void*)&value, sizeof( T ), BitCount );
			//return Endian::LittleEndianBytesTo<T>( (void*)&value, sizeof( T ) );
			return value;
		};


};
