#include "gemini.h"
#include <string.h>

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len + 1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
  size_t new_len = s->len + size * nmemb;
  s->ptr = realloc(s->ptr, new_len + 1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr + s->len, ptr, size * nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size * nmemb;
}

char *clean_command(char *cmd) {
  if (!cmd)
    return NULL;

  // Remove markdown code blocks
  char *start = cmd;
  if (strncmp(start, "```", 3) == 0) {
    start = strchr(start, '\n');
    if (start)
      start++; // Skip newline
    else
      start = cmd + 3; // Just skip ```
  }

  // Remove trailing ```
  char *end = strstr(start, "```");
  if (end)
    *end = '\0';

  // Trim whitespace
  while (*start && (*start == ' ' || *start == '\n' || *start == '\r'))
    start++;
  size_t len = strlen(start);
  while (len > 0 && (start[len - 1] == ' ' || start[len - 1] == '\n' ||
                     start[len - 1] == '\r')) {
    start[len - 1] = '\0';
    len--;
  }

  return strdup(start);
}

char *ask_gemini(const char *prompt) {
  CURL *curl;
  CURLcode res;
  struct string s;
  init_string(&s);

  char *api_key = getenv("GEMINI_API_KEY");
  if (!api_key) {
    fprintf(stderr, "Error: GEMINI_API_KEY environment variable not set.\n");
    return NULL;
  }

  char url[1024];
  snprintf(url, sizeof(url),
           "https://generativelanguage.googleapis.com/v1beta/models/"
           "gemini-pro:generateContent?key=%s",
           api_key);

  // Create JSON payload
  struct json_object *root = json_object_new_object();
  struct json_object *contents = json_object_new_array();
  struct json_object *part_obj = json_object_new_object();
  struct json_object *parts = json_object_new_array();
  struct json_object *text_obj = json_object_new_object();

  char full_prompt[2048];
  snprintf(full_prompt, sizeof(full_prompt),
           "Translate this natural language command to a bash shell command. "
           "Return ONLY the command, no markdown, no explanation. Command: %s",
           prompt);

  json_object_object_add(text_obj, "text", json_object_new_string(full_prompt));
  json_object_array_add(parts, text_obj);
  json_object_object_add(part_obj, "parts", parts);
  json_object_array_add(contents, part_obj);
  json_object_object_add(root, "contents", contents);

  const char *json_str = json_object_to_json_string(root);

  curl = curl_easy_init();
  if (curl) {
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_str);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
      free(s.ptr);
      s.ptr = NULL;
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
  }

  // Parse response
  char *command = NULL;
  if (s.ptr) {
    struct json_object *parsed_json = json_tokener_parse(s.ptr);
    struct json_object *candidates;
    if (json_object_object_get_ex(parsed_json, "candidates", &candidates)) {
      struct json_object *candidate = json_object_array_get_idx(candidates, 0);
      struct json_object *content;
      if (json_object_object_get_ex(candidate, "content", &content)) {
        struct json_object *parts_res;
        if (json_object_object_get_ex(content, "parts", &parts_res)) {
          struct json_object *part = json_object_array_get_idx(parts_res, 0);
          struct json_object *text;
          if (json_object_object_get_ex(part, "text", &text)) {
            command = strdup(json_object_get_string(text));
          }
        }
      }
    }
    json_object_put(parsed_json); // Free JSON object
    free(s.ptr);
  }
  json_object_put(root); // Free request JSON

  char *cleaned = clean_command(command);
  if (command)
    free(command);
  return cleaned;
}

bool validate_security(const char *command) {
  if (!command)
    return false;
  // Simple blacklist
  const char *blacklist[] = {
      "rm -rf /", "mkfs", ":(){ :|:& };:", "> /dev/sda", "mv /", NULL};

  for (int i = 0; blacklist[i]; i++) {
    if (strstr(command, blacklist[i])) {
      return false;
    }
  }
  return true;
}
