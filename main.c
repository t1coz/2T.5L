#include "menuCommands.h"
#include "cache.h"
int main(){
    HashTable* cache = hashtableCreation();
    int choice;
    char* userDNS = NULL;
    char* userIP = NULL;
    printf("\nTheme: \033[0;36mDNS and IP searching (cache).\033[0m\n");
    while(1){
        printf("\n\033[0;32mChoose what to do:\033[0m"
               "\n1. Searching with DNS first;"
               "\n2. Searching with IP first;"
               "\n3. Add DNS+IP address to the table;"
               "\n4. Print existing cache;"
               "\n5. Clear cache."
               "\n\033[0;31m(Type 99 to exit the program)\033[0m\n"
               "\n\033[0;32mDecision: \033[0m");
        choice = methodOfInput(5);
        if (choice == 99){
            printf("\n\033[0;31mFinishing the program.\n\033[0m");
            hashtableDeletion(cache);
            return 0;
        }
        printf("\n");
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
            case 4:{
                HashEntry *current = NULL;
                for (int i = 0; i < cache->size; i++) {
                    current = cache->table[i];
                    while (current != NULL){
                        printf("%s | %s\n", current->key, current->value);
                        current = current->next;
                    }
                }
            }
                break;
            case 5:
                hashtableDeletion(cache);
                cache = hashtableCreation();
                printf("Cache is clear.\n");
                break;
            default:
                break;
        }
    }
}
