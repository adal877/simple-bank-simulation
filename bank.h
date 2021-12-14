#ifndef _BANK_H_
#define _BANK_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Defines and compilers declaration/calls */
#ifdef __linux__
#define _clear() system("clear");
#else
#define _clear() system("cls");
#endif

#define MAX_CLIENTS 2

struct BankClient {
    char *ClientName;
    /* It's in char * format just to
     * make it easy to parse the input. */
    char *ClientCPF;
};

struct BankAccount {
    int BankID;
    struct BankClient *BClient;
    double balance;
};

/* Functions declaration */
void Menu(int);
void MenuTransition();
int verifyUnsigned(long long int);
int verifyCPF(struct BankAccount *, int);
void RegisterBankClient(struct BankAccount *, int);
void ShowBankClient(struct BankAccount *, int);
void SimulateBankTransitions(struct BankAccount *, int);
int FindClient(struct BankAccount *, int, int);
void TransactionsDeposit(struct BankAccount *, int);
void TransactionsDrawOut(struct BankAccount *, int);

#endif
