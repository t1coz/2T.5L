#include "functionsForFile.h"
void ipSearch(HashTable* cache, const char* filePath, const char* DNS, const char* domain) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL){
        printf("Error: Could not open file %s\n", filePath);
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL){
        char* savePtr = NULL;
        const char* fileDNS = strtok_r(buffer, " \n", &savePtr);
        if (strcmp(fileDNS, DNS) == 0){
            const char* IP = strtok_r(NULL, " \n", &savePtr);
            if(IPChecking(IP) == 0){
                fclose(file);
                ipSearch(cache, filePath, IP, fileDNS);
            }else if(domain != NULL)
                addToHashtable(cache, domain, IP);
            else
                addToHashtable(cache, DNS, IP);
        }
    }
    fclose(file);
}
void printDNS(const char* IPAddress, FILE* file){
    char buffer[256];
    rewind(file);
    while (fgets(buffer, sizeof(buffer), file) != NULL){
        char* savePtr = NULL;
        char* fileDNS = strtok_r(buffer, " \n", &savePtr);
        const char* IP = strtok_r(NULL, " \n", &savePtr);
        if (strcmp(IP, IPAddress) == 0){
            printf("%s\n", fileDNS);
            long pos = ftell(file);
            printDNS(fileDNS, file);
            fseek(file, pos, SEEK_SET);
        }
    }
}
void DNSByIPAddress(const char* IPAddress, const char* filePath){
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filePath);
        return;
    }
    printDNS(IPAddress, file);
    fclose(file);
}
int IPChecking(const char* ip){
    int octet = 0;
    int num_octets = 0;
    char* line = strdup(ip);
    char* savePtr = NULL;
    char* ptr = strtok_r(line, ".\n", &savePtr);
    while (ptr != NULL){
        num_octets++;
        octet = atoi(ptr);
        if (octet < 0 || octet > 255 || (num_octets == 1 && octet == 0)) {
            free(line);
            return 0;
        }
        ptr = strtok_r(NULL, ".\n", &savePtr);
    }
    if (num_octets != 4){
        free(line);
        return 0;
    }
    free(line);
    free(ptr);
    return 1;
}
void addDNSToFile(const char* filePath, const char* DNSName, const char* IPAddress){
    if(IPChecking(IPAddress) == 0) {
        printf("Invalid IP Address\n");
        return;
    }
    FILE* file = fopen(filePath, "r+");
    if (file == NULL) {
        printf("Error: could not open file '%s'\n", filePath);
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char* savePtr = NULL;
        const char* DNSFromFile = strtok_r(buffer, " ", &savePtr);
        if (strcmp(DNSFromFile, DNSName) == 0) {
            printf("Error: DNS '%s' already exists in file.\n", DNSName);
            fclose(file);
            return;
        }
    }
    fseek(file, 0, SEEK_END);
    fprintf(file, "\n%s %s", DNSName, IPAddress);
    fclose(file);
}