#include <iostream>
#include <string>
#include "curl/curl.h"
#include "CookBook.h"
using namespace std;

size_t CookBook::jsonStore(char *data, size_t size, size_t nmemb, std::string *buffer_in) {
    if (buffer_in != NULL)
    {
        // Append the data to the buffer    
        buffer_in->append(data, size * nmemb);

        // How much did we write?   
        recipe = buffer_in;
        printf("%c", &recipe);
        return size * nmemb;
    }

    return 0;

}

int main(int argc, char* argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* easyHandle = curl_easy_init();
    CURLcode res;
    struct curl_slist* headers = NULL; 
    headers = curl_slist_append(headers, "Content-Type: application/json");
    if (easyHandle)
    {
        curl_easy_setopt(easyHandle, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(easyHandle, CURLOPT_URL, "https://api.spoonacular.com/recipes/complexSearch?query=pasta&maxFat=25&number=2");
        curl_easy_setopt(easyHandle, CURLOPT_HTTPGET, 1);
        //curl_easy_setopt(easyHandle, CURLOPT_WRITEFUNCTION, jsonStore);
        res = curl_easy_perform(easyHandle);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "something went wrong\n");
        }
    }
    curl_slist_free_all(headers);
    curl_easy_cleanup(easyHandle);
    return 0;
}