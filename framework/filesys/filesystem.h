
#pragma once


#include "../core/list.h"
#include "../text/strings.h"
#include "tinydir.h"

class FileSystemEntry
{

	public:
		std::string filename;
		bool isdirectory;
		size_t filesize;

		FileSystemEntry(std::string Filename, bool IsDirectory, size_t FileSize)
		{
			filename = Filename;
			isdirectory = IsDirectory;
			filesize = FileSize;
		};
};


class FileSystem
{

	public:
		static List<FileSystemEntry*>* GetFilenames(std::string Path);
		static FileSystemEntry* GetFileData(std::string Path);

};
