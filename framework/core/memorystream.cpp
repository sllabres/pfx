
#include "memorystream.h"
#include "maths.h"
#include <stdio.h>
#include <string.h>

MemoryStream::MemoryStream()
{
	chunkcreated = true;
	chunk = new Memory();
	chunkpointer = 0;
	chunkbitpointer = 0;
}

MemoryStream::MemoryStream(Memory* Chunk)
{
	chunkcreated = false;
	chunk = Chunk;
	chunkpointer = 0;
	chunkbitpointer = 0;
}

MemoryStream::~MemoryStream()
{
	if( chunkcreated )
	{
		delete chunk;
	}
}

Memory* MemoryStream::GetChunk()
{
	return chunk;
}

size_t MemoryStream::GetLength()
{
	return chunk->GetSize();
}

void MemoryStream::Seek(size_t Position, MemoryStreamPositions::StreamPositions Base)
{
	switch( Base )
	{
		case MemoryStreamPositions::BEGINNING:
			chunkpointer = Position;
			break;
		case MemoryStreamPositions::CURRENT:
			chunkpointer = chunkpointer + Position;
			break;
		case MemoryStreamPositions::END:
			chunkpointer = chunk->GetSize() + Position;
			break;
	}

	if( chunkpointer < 0 )
	{
		chunkpointer = 0;
	}
	if( chunkpointer > chunk->GetSize() )
	{
		// Make sure the chunk is padded to support the new location
		chunk->GetDataOffset( chunkpointer );
	}
}

bool MemoryStream::CanReadValue(size_t Length)
{
	return ( chunkpointer + Length <= chunk->GetSize() );
}

void MemoryStream::ReadValue(void* Output, size_t Length)
{
	if( CanReadValue( Length ) )
	{
		void* src = chunk->GetDataOffset( chunkpointer );
		memcpy( Output, src, Length );
		chunkpointer += Length;
	}
}

void MemoryStream::WriteValue(void* Input, size_t Length)
{
	// If sat at the end, just append the data
	if( chunkpointer == chunk->GetSize() )
	{
		chunk->AppendData( Input, Length );
	} else {

		if( chunkpointer + Length > chunk->GetSize() )
		{
			// Pad buffer to cover data
			chunk->GetDataOffset( chunkpointer + Length );
		}
		void* rawptr = chunk->GetDataOffset( chunkpointer );
		memcpy( rawptr, Input, Length );
	}
	chunkpointer += Length;
}

Memory* MemoryStream::ReadChunk(size_t Length)
{
	if( !CanReadValue( Length ) )
	{
		return nullptr;
	}

	Memory* newchunk = new Memory();
	newchunk->AppendData( chunk->GetDataOffset( chunkpointer ), Length );
	chunkpointer += Length;
	return newchunk;
}

void MemoryStream::WriteChunk(Memory* Chunk)
{
	WriteValue( Chunk->GetData(), Chunk->GetSize() );
}

void MemoryStream::ReadBitsValue(void* Output, size_t OutputSizeBytes, size_t LengthBits)
{
	unsigned int bytelen = Maths::Ceiling( (chunkbitpointer + LengthBits) / 8.0f );
	unsigned char* bytebuf = (unsigned char*)malloc( bytelen );
	memset( (void*)bytebuf, 0, bytelen );

	unsigned char lowermask = 0;
	unsigned char valuemask = 0;
	int shiftposition = 8 - (chunkbitpointer + (LengthBits % 8));

	if( CanReadValue( bytelen ) )
	{
		void* src = chunk->GetDataOffset( chunkpointer );
		memcpy( bytebuf, src, bytelen );

		// Generate masks
		for( int i = 0; i < shiftposition; i++ )
		{
			lowermask |= 1 << i;
		}

		// Generate masks
		for( size_t i = 0; i < (LengthBits % 8); i++ )
		{
			valuemask |= 1 << i;
		}
		// Just happens to be on an 8bit boundary. Why you'd be reading 8bit boundary values using the bitreader though is a mystery
		if( valuemask == 0 )
		{
			valuemask = ~valuemask;
		}

		// Shifting bits
		for( int i = bytelen - 1; i >= 0; i-- )
		{
			bytebuf[i] = bytebuf[i] >> shiftposition;
			if( i > 0 )
			{
				bytebuf[i] |= (bytebuf[i-1] & lowermask) << chunkbitpointer;
			} else {
				bytebuf[i] &= valuemask;
			}
		}

		// Advance reading pointer
		chunkpointer += (bytelen - 1) + ((chunkbitpointer + LengthBits) / 8);
		chunkbitpointer = (chunkbitpointer + LengthBits) % 8;
	}
	memset( Output, 0, OutputSizeBytes );

	unsigned char* endibuf = (unsigned char*)malloc( bytelen );

	Endian::EndianSwitch( (void*)bytebuf, (void*)endibuf, bytelen, Endian::BIG, Endian::GetNativeEndian() );

	if( Endian::GetNativeEndian() == Endian::BIG )
	{
		Output = (unsigned char*)Output + (OutputSizeBytes - bytelen);
	}
	memcpy( Output, (void*)bytebuf, bytelen );


	free( bytebuf );
}

void MemoryStream::WriteBitsValue(void* Input, size_t Length)
{
}
