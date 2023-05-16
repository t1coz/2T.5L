#ifndef INC_5LAB_MENUCOMMANDS_H
#define INC_5LAB_MENUCOMMANDS_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cache.h"
#include "functionsForFile.h"
void menuInterface(HashTable* cache);
void functionsSelection(HashTable* cache, int choice);
int methodOfInput(int size);
void getStr(char **string);
#endif
