/**
 * @file data.h
 * @author POH JING SENG (jingseng.poh)
 * @brief this file declares the functions used to read, write and update json file data
 * 
 * @copyright Copyright 2020 DigiPen, All rights reserved.
 * 
 */


#pragma once

#include "cJSON.h"

/**
 * @brief Get the Data json object of `config.json`
 * 
 *        Creates config.json if doesnt already exist, sets default values and reads from file
 *        else if file already exists, read from file
 * 
 * @return cJSON* cJSON object. must call destroyData() -> basically free()??
 */
cJSON* getDataObj(void);

/**
 * @brief frees dynamically allocated memory variable `data` is using
 * 
 */
void destroyData(void);


/**
 * @brief updates a number value of config.json
 * 
 * @param key 
 * @param value 
 */
void updateDataNum(const char* key, double value);

/**
 * @brief updates a boolean value of config.json
 * 
 * @param key 
 * @param value 
 */
void updateDataBool(const char* key, int value);


void outputData(void);

/**
 * @brief commits data by writing to file
 * 
 */
void commit(void);
