#include <curl/curl.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

size_t each = 0;

static size_t writeTo(void *content, size_t size, size_t nmemb, void *response)
{
	((std::string*)response)->append((char *)content, size * nmemb);
	// std::cout << response << std::endl;
	return (size * nmemb);
}

int main(void)
{
	std::string data;
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(curl, CURLOPT_URL, "https://official-joke-api.appspot.com/random_joke");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeTo);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		res = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
	std::cout << data << std::endl;


	
	
}


