#include "bank.h"

void Menu(int pos) {
    printf("+------------------------------+\n");
    printf("|-1-| Register new client      |\n");
    printf("|-2-| Show clients registered  |\n");
    printf("|-3-| Simulate bank transition |\n");
    printf("|-4-| Exit                     |\n");
    printf("+------------------------------+\n");
    printf("~%2d out of %2d clients~\n", pos, MAX_CLIENTS);
    printf("=> ");
}
void MenuTransition() {
    printf("+------------------+\n");
    printf("|-1-| Deposit      |\n");
    printf("|-2-| Draw out     |\n");
    printf("|-3-| Show balance |\n");
    printf("|-4-| Exit         |\n");
    printf("+------------------+\n");
    printf("=> ");
}
int verifyUnsigned(long long int num) {
    return ((num < 0)? 1:0);
}
int verifyCPF(struct BankAccount *ba, int pos) {
    int cpf_just_numbers = 0;
    int size = 0;

    while(ba[pos].BClient[pos].ClientCPF[size] != '\0') {
        if(ba[pos].BClient[pos].ClientCPF[size] != '.' &&
                ba[pos].BClient[pos].ClientCPF[size] != '-') {
            /* Here we just have the numbers.
             * We are taking off the dots and dash.*/
            cpf_just_numbers +=
            /* Here we have to decrease 48 from the value
             * to make a conversion from ascii to integer. */
                (ba[pos].BClient[pos].ClientCPF[size] - 48);
        } else {
            cpf_just_numbers += 0;
        }
        size++;
    }
    if(cpf_just_numbers % 11 != 0) {
        return 1;
    } else {
        return 0;
    }
}

int findclient_return = 0;
int FindClient(struct BankAccount *ba, int pos, int BankID) {;
    for(int i = 0; i < pos; i++) {
        if(ba[i].BankID == BankID) {
            findclient_return = i;
            return 0;
        }
    }
    return 1;
}
void RegisterBankClient(struct BankAccount *ba, int pos) {
    ba[pos].BClient[pos].ClientName = (char *)malloc(sizeof(char));
    ba[pos].BClient[pos].ClientCPF = (char *)malloc(sizeof(char));


    /* This variables are to generate
     * the random bank ID for the clien
     * in the [pos] position. */
    int min_rand = 1000;
    int max_rand = 9999;
    ba[pos].BankID = (rand() % (max_rand - min_rand + 1))
        + min_rand;
    /* while the bankID is equal to another existent
     * one, generates another. */
    while(FindClient(ba, pos, ba[pos].BankID) == 0) {
        ba[pos].BankID = (rand() % (max_rand - min_rand + 1))
            + min_rand;
    }
    printf("~ %2d - Client Registration ~\n", pos+1);
    printf("Name: ");
    scanf(" %[^\n]%*c", ba[pos].BClient[pos].ClientName);
    printf("CPF: ");
    scanf(" %[^\n]%*c", ba[pos].BClient[pos].ClientCPF);
    while(verifyCPF(ba, pos) == 1) {
        printf("Wrong CPF format!!\n");
        printf("CPF: ");
        //memset(ba[pos].BClient[pos].ClientCPF, 0, strlen(ba[pos].BClient[pos].ClientCPF));
        ba[pos].BClient[pos].ClientCPF[0] = '\0';
        scanf(" %[^\n]%*c", ba[pos].BClient[pos].ClientCPF);
    }
    printf("Bank Balance: ");
    scanf(" %lf", &ba[pos].balance);
    while((verifyUnsigned(ba[pos].balance)) == 1) {
        printf("Insert a number bigger or equal than 0.\n");
        printf("Bank Balance: ");
        scanf(" %lf", &ba[pos].balance);
    }
    printf("BankID: %d for %s\n", ba[pos].BankID, ba[pos].BClient[pos].ClientName);
}
void ShowBankClient(struct BankAccount *ba, int pos) {
    printf("~ %2d - Clients data ~\n", pos);
    for(int i = 0; i < pos; i++) {
        printf("+--Client %2d-------------------+\n", i+1);
        printf("Name: %s\n", ba[i].BClient[i].ClientName);
        printf("BankID: %d\n", ba[i].BankID);
        printf("Balance: %0.2f\n", ba[i].balance);
        printf("\n");
    }
}
void TransactionsDeposit(struct BankAccount *ba, int pos) {
    double amount_to_deposit = 0;
    printf("How much would you like to deposit?\n");
    printf("%d --- %s\n", ba[findclient_return].BankID, ba[findclient_return].BClient[findclient_return].ClientName);
    printf("Balance: %.2lf\n", ba[findclient_return].balance);
    printf("=> ");
    scanf(" %lf", &amount_to_deposit);
    while((verifyUnsigned(amount_to_deposit)) == 1) {
        printf("Insert a number bigger or equal than 0.\n");
        printf("Bank Balance: ");
        scanf(" %lf", &amount_to_deposit);
    }
    ba[findclient_return].balance += amount_to_deposit;
    _clear();
    printf("Add %.2lf to %d account's.\n", amount_to_deposit, ba[findclient_return].BankID);
    printf("Balance: %.2lf\n", ba[findclient_return].balance);
}
void TransactionsDrawOut(struct BankAccount *ba, int pos) {
    double amount_to_draw_out = 0;
    printf("How much would you like to draw out?\n");
    printf("%d --- %s\n", ba[findclient_return].BankID, ba[findclient_return].BClient[findclient_return].ClientName);
    printf("Balance: %.2lf\n", ba[findclient_return].balance);
    printf("=> ");
    scanf(" %lf", &amount_to_draw_out);
    while(amount_to_draw_out < 0) {
        printf("Insert a number bigger or equal than 0.\n");
        printf("Bank Balance: ");
        scanf(" %lf", &amount_to_draw_out);
    }
    ba[findclient_return].balance -= amount_to_draw_out;
    _clear();
    printf("Draw out %.2lf from %d account's.\n", amount_to_draw_out, ba[findclient_return].BankID);
    printf("Balance: %.2lf\n", ba[findclient_return].balance);
}
void SimulateBankTransitions(struct BankAccount *ba, int pos) {
    int transactions = 0;
    int ClientID = 0;
    printf("Type the client ID to use: ");
    scanf(" %d", &ClientID);
    if((FindClient(ba, pos, ClientID)) == 1) {
        printf("Cannot find a user associated to the %d ID\n", ClientID);
        return;
    }
    while(transactions != 5 ) {
        _clear();
        MenuTransition();
        scanf(" %d", &transactions);
        _clear();
        switch(transactions) {
            case 1:
                TransactionsDeposit(ba, pos);
                while(getchar() != '\n');
                while(getchar() != '\n');
                break;
            case 2:
                TransactionsDrawOut(ba, pos);
                while(getchar() != '\n');
                while(getchar() != '\n');
                break;
            case 3:
                printf("Name: %s\n", ba[findclient_return].BClient[findclient_return].ClientName);
                printf("ID: %d\n", ClientID);
                printf("Balance: %lf\n", ba[findclient_return].balance);
                while(getchar() != '\n');
                while(getchar() != '\n');
                break;
            case 4:
                return;
                break;
            default:
                printf("Invalid option!!\n");
                while(getchar() != '\n');
                while(getchar() != '\n');
                break;
        }
    }
}
