/* cc -o ctcurl ctcurl.c -lcurl */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>

struct memory_struct {
  char    *memory;
  size_t  size;
};

static size_t ctcurl_ss(char *in) {
  size_t i;
  for (i = 0; i < strlen(in) - 13; i++) {
    if((isalpha(in[i]) &&
      (in[i] == 'C' || in[i] == 'c')) &&
      in[i+1] == 'o' && in[i+2] == 'n' &&
      (in[i+8] == 'T' || in[i+8] == 't') &&
      in[i+9] == 'y' && in[i+10] == 'p')
      return i + 12;
  }
  return 10;
}

static size_t wm_callback(void *contents, size_t size, size_t nmemb, void *userp) {
 
  size_t realsize = size * nmemb;
  struct memory_struct *mem = (struct memory_struct *)userp;
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <url>\n", argv[0]);
  }
  
  CURLcode ret;
  CURL *hnd;

  struct memory_struct chunk;
  
  chunk.memory = malloc(1);
  chunk.size = 0;

  hnd = curl_easy_init();
  
  curl_easy_setopt(hnd, CURLOPT_URL, argv[1]);
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, wm_callback);
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void *)&chunk);
  curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(hnd, CURLOPT_NOBODY, 1L);
  curl_easy_setopt(hnd, CURLOPT_HEADER, 1L);
  curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.50.1");
  curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 5L);
  curl_easy_setopt(hnd, CURLOPT_FILETIME, 1L);
  curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

  ret = curl_easy_perform(hnd);

  if(ret != CURLE_OK) {
    fprintf(stderr, "Failed to fetch content-type, %s\n", curl_easy_strerror(ret));
  } else {
    int start = 0, mid = 0, end = 0;
    // Use sentinels to grep out '/', then go back and forth to find endpoints, finally printing the range to stdout.
    size_t i;
    for (i = ctcurl_ss(chunk.memory); i < chunk.size; i++) {
      if (chunk.memory[i] == '/') {
        mid = i;
        break;
      }
    }

    for (i = mid + 1; i < chunk.size; i++) {
      if (!isalpha(chunk.memory[i]) && chunk.memory[i] != '-') {
        end = i;
        break;
      }
    }
  
    for (i = mid - 1; i > 0; i--) {
      if (!isalpha(chunk.memory[i]) && chunk.memory[i] != '-') {
        start = ++i; 
        break;
      }
    }
    
    printf("%.*s\n", end - start, &chunk.memory[start]);
  }

  curl_easy_cleanup(hnd);
  hnd = NULL;

  return (int)ret;
}
