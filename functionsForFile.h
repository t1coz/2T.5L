#ifndef INC_5LAB_FUNCTIONSFORFILE_H
#define INC_5LAB_FUNCTIONSFORFILE_H
#include "cache.h"
void ipSearch(HashTable* cache, const char* filePath, const char* DNS, const char* domain);
void printDNS(const char* IPAddress, FILE* file);
void DNSByIPAddress(const char* IPAddress, const char* filePath);
int IPChecking(const char* ip);
void addDNSToFile(const char* filePath, const char* DNSName, const char* IPAddress);
#endif
