#include <iostream>
#include <curl/curl.h>
#include <string.h>
#include <math.h>
#include "../lib/cJSON.h"
#include "exercise.h"

#define BASE_URL "https://jsonplaceholder.typicode.com/"

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
    curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &(response->rtt));
    curl_easy_cleanup(curl);

    return response;
}

const char* get_resource_url(const char *resource_path, int id)
{
    string url(BASE_URL);
    url.append(resource_path);
    url.append(to_string(id));

    return strdup(url.c_str());

}

post_type* get_post_details(int post_id)
{
    if ((post_id < 1) || (post_id > 100)) {
        cerr << "Out-of-bounds post id" << endl;
        return NULL;
    }
    
    string url(BASE_URL);
    url.append("posts/");
    url.append(to_string(post_id));

    response_type *response = get_request(url.c_str());

    cJSON *json = cJSON_Parse(response->body.c_str());
    cJSON *user_id = cJSON_GetObjectItemCaseSensitive(json, "userId");
    cJSON *title = cJSON_GetObjectItemCaseSensitive(json, "title");

    post_type *post = new post_type;
    post->user_id = user_id->valueint;
    post->title = strdup(title->valuestring);

    cJSON_Delete(json);

    return post;
}

int get_request_timing(int user_id)
{
    if ((user_id < 1) || (user_id > 10)) {
        cerr << "Out-of-bounds user id" << endl;
        return 0;
    }

    double total_request_rtt = 0.0;

    string posts_url(BASE_URL);
    posts_url.append("posts?userId=");
    posts_url.append(to_string(user_id));

    response_type *posts_response = get_request(posts_url.c_str());
    total_request_rtt += posts_response->rtt;

    cJSON *posts_json = cJSON_Parse(posts_response->body.c_str());
    int posts_count = cJSON_GetArraySize(posts_json);

    for (int index = 0; index < posts_count; index++) {
        cJSON *post_json = cJSON_GetArrayItem(posts_json, index);
        cJSON *post_id_json = cJSON_GetObjectItemCaseSensitive(post_json, "id");
        int post_id = post_id_json->valueint;

        string comments_url(BASE_URL);
        comments_url.append("comments?postId=");
        comments_url.append(to_string(post_id));

        response_type *comments_response = get_request(comments_url.c_str());
        total_request_rtt += comments_response->rtt;
    }

    cJSON_Delete(posts_json);

    return ceil(total_request_rtt * 1000);
}
