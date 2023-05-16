#include "menuCommands.h"
void functionsSelection(HashTable* cache, int choice){
    char* userDNS = NULL;
    char* userIP = NULL;
    switch (choice){
        case 1:
            printf("Enter the DNS: ");
            getStr(&userDNS);
            surfaceSearching(cache, userDNS);
            break;
        case 2:
            printf("Enter the IP: ");
            getStr(&userIP);
            DNSByIPAddress(userIP, "listOfDNSAndIP.txt");
            break;
        case 3:
            printf("Enter the DNS: ");
            getStr(&userDNS);
            printf("Enter the IP: ");
            getStr(&userIP);
            addDNSToFile("listOfDNSAndIP.txt", userDNS, userIP);
            break;
        case 4:
            printf("");
            HashEntry * current = NULL;
            for(int i = 0; i < cache->size; i++) {
                current = cache->table[i];
                while (current != NULL) {
                    printf("%s | %s\n", current->key, current->value);
                    current = current->next;
                }
            }
            break;
        case 5:
            hashtableDeletion(cache);
            //cache = hashtableCreation();
            break;
        default:
            break;
    }
}
void menuInterface(HashTable* cache){
    printf("\nTheme: \033[0;36mSearching in cache.\033[0m\n");
    while(1){
        printf("\n\033[0;32mChoose what to do:\033[0m"
               "\n1. Searching with DNS first;"
               "\n2. Searching with IP first;"
               "\n3. Add DNS+IP address to the table;"
               "\n4. Write cache;"
               "\n5. Clear cache."
               "\n\033[0;31m(Type 99 to exit the program)\033[0m\n"
               "\n\033[0;32mDecision: \033[0m");
        int choice;
        choice = methodOfInput(5);
        if (choice == 99){
            printf("\n\033[0;31mFinishing the program.\n\033[0m");
            return;
        }
        printf("\n");
        functionsSelection(cache, choice);
    }
}
int methodOfInput(int size){
    int num;
    while (scanf("%d", &num) != 1 || (!(num >=1 && num <=size)&& num != 99) || getchar() != '\n') {
        printf("Try better:\n");
        rewind(stdin);
    }
    return num;
}
void getStr(char **string){
    int size = 0;
    int realSize = 16;
    *string = (char *)malloc(realSize * sizeof(char));
    rewind(stdin);
    char check;
    while (1) {
        check = (char)getchar();
        if (check == '\n') {
            if (size + 1 < realSize) {
                *string = (char *) realloc(*string, (size + 1) * sizeof(char));
            }
            (*string)[size] = '\0';
            return;
        }
        (*string)[size] = check;
        size++;
        if (size + 1 == realSize) {
            realSize *= 2;
            *string = (char *) realloc(*string, realSize * sizeof(char));
        }
    }
}