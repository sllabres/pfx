
#include "memory.h"
#include <stdio.h>
#include <string.h>

#define READ_PACKET_SIZE 65536 // 64KB chunks

Memory::Memory()
{
	dataptr = 0;
	datalen = 0;
}

Memory::Memory(size_t InitialSize)
{
	if( InitialSize <= 0 )
	{
		dataptr = 0;
		datalen = 0;
	} else {
		dataptr = (uint8_t*)malloc( InitialSize );
		datalen = InitialSize;
	}
}

Memory::Memory(Memory* Clone)
{
	if( Clone->GetSize() == 0 )
	{
		dataptr = 0;
		datalen = 0;
	} else {
		dataptr = (uint8_t*)malloc( Clone->GetSize() );
		datalen = Clone->GetSize();
		memcpy( dataptr, Clone->GetData(), datalen );
	}
}

Memory::Memory(std::string Filename)
{
	dataptr = 0;
	datalen = 0;

	FILE* filehnd = fopen( Filename.c_str(), "rb" );
	if( filehnd != nullptr )
	{
		void* data_buffer = malloc( READ_PACKET_SIZE * sizeof( uint8_t ) );
		unsigned char* cb = (unsigned char*)data_buffer;
		size_t data_read;

		do
		{
			data_read = fread( data_buffer, sizeof( uint8_t ), READ_PACKET_SIZE, filehnd );
			AppendData( data_buffer, READ_PACKET_SIZE * sizeof( uint8_t ) );
		} while ( data_read == READ_PACKET_SIZE );

		fclose( filehnd );
		free( data_buffer );
	}

}

Memory::~Memory()
{
	Clear();
}

size_t Memory::GetSize()
{
	return datalen;
}

void Memory::Resize(size_t Length)
{
	void* ptr;

	if( dataptr == 0 )
	{
		ptr = malloc( Length );
	} else {
		ptr = realloc( dataptr, Length );

	}

	if( ptr == 0 )
	{
		return;
	}
	dataptr = (uint8_t*)ptr;
	datalen = Length;
}

void Memory::AppendData(void* Data, size_t Length)
{
	void* ptr;

	if( dataptr == 0 )
	{
		ptr = malloc( Length );
	} else {
		ptr = realloc( dataptr, datalen + Length );
	}

	if( ptr == 0 )
	{
		return;
	}
	dataptr = (uint8_t*)ptr;
	memcpy( &(dataptr[datalen]), Data, Length );
	datalen += Length;
}

void Memory::AppendData(Memory* Data)
{
	AppendData( Data->GetData(), Data->GetSize() );
}

void* Memory::GetData()
{
	return dataptr;
}

void Memory::Clear()
{
	if( dataptr != 0 )
	{
		free( dataptr );
	}
	dataptr = 0;
	datalen = 0;
}

void* Memory::GetDataOffset(size_t Offset)
{
	// Auto extend chunk to reach new offset
	if( Offset > datalen )
	{
		size_t addn = Offset - datalen;
		void* newbuffer = malloc( addn );
		memset( newbuffer, 0, addn );
		AppendData( newbuffer, addn );
		free( newbuffer );
	}

	return &(dataptr[Offset]);
}

void Memory::Save(std::string Filename)
{
	FILE* filehnd = fopen( Filename.c_str(), "wb" );
	if( filehnd != nullptr )
	{
		fwrite( (void*)dataptr, sizeof( uint8_t ), datalen, filehnd );
		fclose( filehnd );
	}
}
