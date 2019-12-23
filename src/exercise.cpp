#include <iostream>
#include <curl/curl.h>
#include "exercise.h"

using namespace std;

static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *response_body)
{
    size_t length = size * nmemb;

    try {
        ((string*)response_body)->append(ptr, length);
    } catch (bad_alloc &e) {
        cerr << "Failed to write to response body" << endl; 
        return 0;
    }

    return length;
}

response_type* get_request(const char *url)
{
    CURL *curl = curl_easy_init();

    if (!curl) {
        cerr << "Unable to initialize the cURL client" << endl;
        return NULL;
    }

    response_type *response = new response_type;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(response->body));
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return response;
}
