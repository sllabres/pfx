
#pragma once

#include <curl/curl.h>
#include "../events/eventcontroller.h"
#include "../core/list.h"
#include "../core/memory.h"

class DownloadInformation
{
	public:
		std::string url;
		unsigned long totalsize;
		unsigned long currentsize;

		DownloadInformation()
		{
		};

		DownloadInformation( std::string* SourceURL )
		{
			url = SourceURL->c_str();
			totalsize = 0;
			currentsize = 0;
		};

		DownloadInformation(const DownloadInformation& obj)
		{
			url = obj.url.c_str();
			totalsize = obj.totalsize;
			currentsize = obj.currentsize;
		};

};

class DownloadController
{

	private:
		List<DownloadInformation*> downloading;
		List<std::string*> downloadqueue;

		void* DownloadPage(DownloadInformation* ThreadData);

	public:
		static bool abortdownloads;
		int maxdownloads;

		DownloadController();

		void RequestURL(std::string URL);
		void EventOccured(Event* What);
		void Update();

		int CurrentDownloads();
		int QueuedDownloads();

};
