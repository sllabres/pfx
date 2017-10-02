
#include "downloadcontroller.h"
#include <thread>
#include "../pfx.h"

size_t dl_write_data(void* ptr, size_t size, size_t nmemb, void *user);
int dl_download_progress(void* user, double dltotal, double dlnow, double ultotal, double ulnow);


bool DownloadController::abortdownloads = false;

DownloadController::DownloadController()
{
	maxdownloads = 1;
}

void DownloadController::RequestURL(std::string URL)
{
	downloadqueue.Add( new std::string( URL.c_str() ) );
}

void DownloadController::EventOccured(Event* What)
{
	if( What->type == EventTypes::EVENT_DOWNLOAD_COMPLETE )
	{
    for( int i = 0; i < downloading.Count(); i++ )
    {
			DownloadInformation* di = downloading[i];
			if( di->url.compare( *What->data.download.url ) == 0 )
			{
				downloading.DeleteAt( i );
				delete di;
				return;
			}
    }
	}
}

void DownloadController::Update()
{
	if( DownloadController::abortdownloads )
	{
		downloadqueue.Clear();
	} else {

		while( downloading.Count() < maxdownloads && downloadqueue.Count() > 0 )
		{
			DownloadInformation* di = new DownloadInformation( downloadqueue.At( 0 ) );
			downloadqueue.DeleteAt( 0 );
			downloading.Add( di );

			Event* fxe = new Event();
			fxe->type = EventTypes::EVENT_DOWNLOAD_STARTING;
			fxe->data.download.url = new std::string( di->url.c_str() );
			FX->events.PushEvent( fxe );

			std::thread* downloader = new std::thread( &DownloadController::DownloadPage, this, di );

		}

	}

}

int DownloadController::CurrentDownloads()
{
	return downloading.Count();
}

int DownloadController::QueuedDownloads()
{
	return downloadqueue.Count();
}


void* DownloadController::DownloadPage(DownloadInformation* ThreadData)
{
	CURL* curl_handle;
	Memory* buffer = new Memory();
	std::string workingurl( ThreadData->url.c_str() );

	curl_handle = curl_easy_init();
	curl_easy_setopt( curl_handle, CURLOPT_URL, ThreadData->url.c_str() );
	curl_easy_setopt( curl_handle, CURLOPT_FOLLOWLOCATION, 1L );
	curl_easy_setopt( curl_handle, CURLOPT_NOPROGRESS, 0L );
	curl_easy_setopt( curl_handle, CURLOPT_WRITEFUNCTION, dl_write_data );
	curl_easy_setopt( curl_handle, CURLOPT_WRITEDATA, (void*)buffer );
	curl_easy_setopt( curl_handle, CURLOPT_PROGRESSFUNCTION, dl_download_progress );
	curl_easy_setopt( curl_handle, CURLOPT_PROGRESSDATA, ThreadData );
	curl_easy_setopt( curl_handle, CURLOPT_TIMEOUT, (long)60 );
	curl_easy_setopt( curl_handle, CURLOPT_NOSIGNAL, 1L );
/*
	if( FRAMEWORK->Settings->GetQuickBooleanValue( "Downloads.ProxyRequired", false ) )
	{
		curl_easy_setopt( curl_handle, CURLOPT_PROXY, FRAMEWORK->Settings->GetQuickStringValue( "Downloads.ProxyServer", "" )->c_str() );
		curl_easy_setopt( curl_handle, CURLOPT_PROXYPORT, FRAMEWORK->Settings->GetQuickInteger64Value( "Downloads.ProxyPort", 8080 ) );
	}
*/
	if( curl_easy_perform( curl_handle ) != 0 )
	{
		buffer->Clear();
	}
	curl_easy_cleanup( curl_handle );

	if( !DownloadController::abortdownloads )
	{
		Event* fxe = new Event();
		fxe->type = EventTypes::EVENT_DOWNLOAD_COMPLETE;
		fxe->data.download.url = new std::string( ThreadData->url.c_str() );
		fxe->data.download.data = buffer;
		FX->events.PushEvent( fxe );
	}

	return 0;
}

size_t dl_write_data(void *ptr, size_t size, size_t nmemb, void *user)
{
	Memory* mem = (Memory*)user;
	mem->AppendData( ptr, size * nmemb );
	return size * nmemb;
}

int dl_download_progress(void *user, double dltotal, double dlnow, double ultotal, double ulnow)
{
	DownloadInformation* di = (DownloadInformation*)user;
	di->totalsize = (unsigned long)dltotal;
	di->currentsize = (unsigned long)dlnow;

	Event* fxe = new Event();
	fxe->type = EventTypes::EVENT_DOWNLOAD_PROGRESS;
	fxe->data.download.url = new std::string( di->url.c_str() );
	fxe->data.download.totalbytes = di->totalsize;
	fxe->data.download.downloadedbytes = di->currentsize;
	FX->events.PushEvent( fxe );
	return 0;
}
