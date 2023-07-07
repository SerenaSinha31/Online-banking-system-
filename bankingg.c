#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "bank_accounts.txt"

struct account {
    char name[50];
    int acc_no; 
    float balance;
};

void create_account() {
    struct account acc;
    FILE *fp;
    fp = fopen(FILENAME, "a");
    printf("\nEnter account holder name: ");
    scanf("%s", &acc.name);
    printf("Enter account number: ");
    scanf("%d", &acc.acc_no);
    printf("Enter opening balance: ");
    scanf("%f", &acc.balance);
    fprintf(fp, "%s %d %.2f\n", acc.name, acc.acc_no, acc.balance);
    printf("\nAccount created successfully!\n");
    fclose(fp);
}

void display_account(int acc_no) {
    struct account acc;
    FILE *fp;
    fp = fopen(FILENAME, "r");
    while (fscanf(fp, "%s %d %f", &acc.name, &acc.acc_no, &acc.balance) != EOF) {
        if (acc.acc_no == acc_no) {
            printf("\nAccount holder name: %s\n", acc.name);
            printf("Account number: %d\n", acc.acc_no);
            printf("Current balance: %.2f\n", acc.balance);
            fclose(fp);
            return;
        }
    }
    printf("\nAccount not found!\n");
    fclose(fp);
}

void deposit(int acc_no) {
    float amount;
    struct account acc;
    FILE *fp;
    fp = fopen(FILENAME, "r+");
    while (fscanf(fp, "%s %d %f", &acc.name, &acc.acc_no, &acc.balance) != EOF) {
        if (acc.acc_no == acc_no) {
            printf("\nEnter amount to deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fprintf(fp, "%s %d %.2f", acc.name, acc.acc_no, acc.balance);
            printf("\nAmount deposited successfully!\n");
            fclose(fp);
            return;
        }
    }
    printf("\nAccount not found!\n");
    fclose(fp);
}

void withdraw(int acc_no) {
    float amount;
    struct account acc;
    FILE *fp;
    fp = fopen(FILENAME, "r+");
    while (fscanf(fp, "%s %d %f", &acc.name, &acc.acc_no, &acc.balance) != EOF) {
        if (acc.acc_no == acc_no) {
            printf("\nEnter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount > acc.balance) {
                printf("\nInsufficient balance!\n");
                fclose(fp);
                return;
            }
            acc.balance -= amount;
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fprintf(fp, "%s %d %.2f", acc.name, acc.acc_no, acc.balance);
            printf("\nAmount withdrawn successfully!\n");
            fclose(fp);
            return;
        }
    }
    printf("\nAccount not found!\n");
    fclose(fp);
}

int main() {
    int choice, acc_no;
    while (1) {
        printf("\n=== ONLINE BANKING SYSTEM ===\n");
        printf("\n1. Create new account");
        printf("\n2. Display account information");
        printf("\n3. Deposit amount");
        printf("\n4. Withdraw amount");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
switch (choice) {
case 1:
create_account();
break;
case 2:
printf("\nEnter account number: ");
scanf("%d", &acc_no);
display_account(acc_no);
break;
case 3:
printf("\nEnter account number: "); 
scanf("%d", &acc_no);
deposit(acc_no);
break;
case 4:
printf("\nEnter account number: ");
scanf("%d", &acc_no);
withdraw(acc_no);
break;
case 5:
printf("\nThank you for using our online banking system!");
exit(0);
default:
printf("\nInvalid choice! Please try again.\n");
}
}
return 0;
}





       

