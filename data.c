
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "config.h"

static  cJSON* data;

const char* configFile = "config.json";

/**
 * @brief Get the Data json object of `config.json`
 * 
 *        Creates config.json if doesnt already exist, sets default values and reads from file
 *        else if file already exists, read from file
 * 
 * @return cJSON* cJSON object. must call destroyData() -> basically free()??
 */
cJSON* getDataObj(void) {
  FILE *file = { 0 };
  fopen_s(&file, "config.json", "r");

  if (file == NULL) {
    // create file if it does not already exist
    fopen_s(&file, "config.json", "w");
    if (file == NULL) {
      fprintf(stderr, "error creating config.json file\n");
      exit(11);
    }

    cJSON* root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "sfxVolume", 1);
    cJSON_AddNumberToObject(root, "musicVolume", 1);
    cJSON_AddBoolToObject(root, "memeMode", 0);

    char* jsonStr = cJSON_Print(root);
    fprintf(file, "%s", jsonStr);
    free(jsonStr);
    cJSON_Delete(root);
    fclose(file);

    return getDataObj();  // exit current function and call again as read mode
  }

  fseek(file, 0, SEEK_END);  // set fptr to end of file
  long file_size = ftell(file);  // get size in bytes
  fseek(file, 0, SEEK_SET);  // set fptr back to beginning of file
  char *contents = malloc(file_size + 1);  // dynamically allocate memory for contents. +1 for null terminator
  fread(contents, sizeof(char), file_size, file);
  fclose(file);

  data = cJSON_Parse(contents);
  free(contents);

  // for testing
  // char* jsonStr = cJSON_Print(data);
  // printf("%s\n", jsonStr);
  // free(jsonStr);

  return data;
}

/**
 * @brief frees dynamically allocated memory variable `data` is using
 * 
 */
void destroyData(void) {
  cJSON_Delete(data);  // basically free
}

int _writeJson(const char* filename, const char* jsonStr) {
  FILE* file = { 0 };
  fopen_s(&file, filename, "w");
  if (file == NULL) {
    return 0;
  }

  fprintf(file, jsonStr);
  fclose(file);
  return 1;
}

/**
 * @brief commits data by writing to file
 * 
 */
void commit(void) {
  char* jsonStr = cJSON_Print(data);
  int success = _writeJson(configFile, jsonStr);
  if (!success) {
    fprintf(stderr, "failed to update value of config.json in updateDataBool\n");
    exit(16);
  }
  debug_log("updated json file with values:\n");
  debug_log(jsonStr);
  debug_log("\n");
  free(jsonStr);
}

/**
 * @brief updates a number value of config.json
 * 
 * @param key 
 * @param value 
 */
void updateDataNum(const char* key, double value) {
  // char* jsonStr = cJSON_Print(data);
  // printf("%s\n", jsonStr);
  // free(jsonStr);

  // printf("%s, %lf\n", key, value);


  cJSON* item = cJSON_GetObjectItem(data, key);
  // printf("%d\n", (item != ((void *)0)));
  if (item != NULL) {
    cJSON_SetNumberValue(item, value);
  }
  else {
    fprintf(stderr, "attempted to update value of a field that does not exist. key: %s | value: %lf\n", key, value);
    exit(12);
  }
}

/**
 * @brief updates a boolean value of config.json
 * 
 * @param key 
 * @param value 
 */
void updateDataBool(const char* key, int value) {

  // printf("%s, %d\n", key, value);

  cJSON* item = cJSON_GetObjectItem(data, key);
  if (item != NULL) {
    cJSON_SetBoolValue(item, value);
  }
  else {
    fprintf(stderr, "attempted to update value of a field that does not exist. key: %s | value: %s\n", key, value ? "true" : "false");
    exit(15);
  }
}

void outputData(void) {
  char* jsonStr = cJSON_Print(data);
  debug_log("json file values:\n");
  debug_log(jsonStr);
  debug_log("\n");
  free(jsonStr);
}
