
#pragma once

#include <cstdlib>
#include <string>
#include <stdint.h>

class Memory
{

	private:
		uint8_t* dataptr;
		size_t datalen;

	public:
		Memory();
		Memory(size_t InitialSize);
		Memory(Memory* Clone);
		Memory(std::string Filename);
		~Memory();

		void Clear();
		void Resize(size_t Length);
		void AppendData(void* Data, size_t Length);
		void AppendData(Memory* Data);
		size_t GetSize();
		void* GetData();
		void* GetDataOffset(size_t Offset);

		void Save(std::string Filename);
};
