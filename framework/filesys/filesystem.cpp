
#include "filesystem.h"
#include "../pfx.h"

List<FileSystemEntry*>* FileSystem::GetFilenames(std::string Path)
{
	List<FileSystemEntry*>* items = new List<FileSystemEntry*>();
	FileSystemEntry* item;

	tinydir_dir d;
	if( tinydir_open( &d, Path.c_str() ) >= 0 )
	{

		while( d.has_next )
		{
			tinydir_file f;
			tinydir_readfile( &d, &f );

			item = new FileSystemEntry( *(new std::string( f.name )), f.is_dir, 0 );
			items->Add( item );

			tinydir_next( &d );
		}

	} else {
		FX->events.PushEvent( Event::ErrorEvent( "FileSystem::GetFilenames", "Invalid path '" + Path + "'", false ) );
	}

	return items;
}

FileSystemEntry* FileSystem::GetFileData(std::string Path)
{
	FileSystemEntry* info = nullptr;
	return info;
}
