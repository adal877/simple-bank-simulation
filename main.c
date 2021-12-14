#include "bank.h"

int main(int argc, char **argv) {
int opt = 0;
int pos = 0;
struct BankAccount ba[MAX_CLIENTS];

    while(opt != 4) {
        _clear();
        Menu(pos);
        scanf(" %d", &opt);
        _clear();
        switch(opt) {
            case 1:
                /* Just alloc if the number of clients
                 * if the user didn't (yet) reached
                 * the maximum allowed. */
                if(pos == MAX_CLIENTS) {
                    printf("MAXIMUM OF CLIENTS REGISTERED!!\n");
                } else {
                    ba[pos].BClient = (struct BankClient *)malloc(sizeof(struct BankClient)*MAX_CLIENTS);
                    RegisterBankClient(ba, pos);
                    pos++;
                }
                while(getchar() != '\n');
                while(getchar() != '\n');
                break;
            case 2:
                if(pos == 0) {
                    printf("You need to register at least one client...\n");
                } else {
                    ShowBankClient(ba, pos);
                }
                while(getchar() != '\n');
                while(getchar() != '\n');
                break;
            case 3:
                if(pos == 0) {
                    printf("You need to register at least one client...\n");
                } else {
                    SimulateBankTransitions(ba, pos);
                }
                while(getchar() != '\n');
                while(getchar() != '\n');
                break;
            case 4:
                break;
            default:
                printf("Invalid option!!\n");
                while(getchar() != '\n');
                while(getchar() != '\n');
                break;
        }
    }
    return 0;
}
