#include <stdio.h>
#include <string.h>

void create_account();
void deposit_Money();
void withdraw_Money();
void Check_Balance();

const char* ACCOUNT_FILE = "account.dat";

typedef struct
{
    char name[50];
    int account_no;
    float balance;
} Account;


int main(){

    while (1)
    {
    	system("color b");
        int choice;
        printf("\n\n*** Bank Management System ***");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Check Balance");
        printf("\n5. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        create_account();
            break;
        case 2:
        deposit_Money();
            break;
        case 3:
        withdraw_Money();
            break;
        case 4:
        Check_Balance();
            break;
        case 5:
        printf("\nClosing the Bank, Thanks for your visit.\n");
            return 0;
            break;
        default:
        printf("\nInvalid Choice, Please try again.\n");
            break;
        }
    }
    
}
void create_account(){
    Account acc;
    FILE *file = fopen(ACCOUNT_FILE, "ab+");
    if (file == NULL){
        printf("\nError in opening file.\n");
        return;
    }
    char c;
    do{
        c = getchar();
    }
    while (c != '\n' && c != EOF);
    
    printf("\nEnter Your Name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    int ind = strcspn(acc.name, "\n");
    acc.name[ind] = '\0';
    printf("Enter your Account Numbe: ");
    scanf("%d", &acc.account_no);
    acc.balance = 0;

    fwrite(&acc,sizeof(acc), 1, file);
    fclose(file);
    printf("\nAccount Created Successfully.\n");
    
}


void deposit_Money(){
	system("color a");
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if(file == NULL){
        printf("Unable to open account file!!");
        return;
    }

    int acc_no;
    float money;
    Account acc_to_read;
    printf("Enter your Account Numbe: ");
    scanf("%d", &acc_no);
    printf("Enter amount to deposit: ");
    scanf("%f",&money);

    while(fread(&acc_to_read, sizeof(acc_to_read), 1, file)){
        if (acc_to_read.account_no == acc_no)
        {
            acc_to_read.balance += money;
            fseek(file, -sizeof(acc_to_read), SEEK_CUR);
            fwrite(&acc_to_read, sizeof(acc_to_read), 1, file);
            fclose(file);
            printf("Successfully deposited Rs.%.2f New Balance is Rs.%.2f",money, acc_to_read.balance);
            return;
        }
        
    }
    fclose(file);
    printf("\nMoney could not be deposited as the Account No:%d was not found in found.",acc_no);


}


void withdraw_Money(){
	system("color c");
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if(file == NULL){
        printf("\nUnable to open account file!!");
        return;
    }

    int acc_no;
    float money;
    Account acc_r;
    printf("Enter your Account Numbe: ");
    scanf("%d", &acc_no);
    printf("Enter amount you wish to withdraw: ");
    scanf("%f",&money);

    while(fread(&acc_r, sizeof(acc_r), 1, file != EOF)){
        if (acc_r.account_no == acc_no){
            if (acc_r.balance >= money){
                acc_r.balance -= money;
                fseek(file, -sizeof(acc_r), SEEK_CUR);
                fwrite(&acc_r, sizeof(acc_r), 1, file);
                printf("Successfully withdrawn Rs.%.2f Remaining balance is Rs.%.2f", money, acc_r.balance);
            } else{
                printf("Insufficient balance!");
            }
           fclose(file);
            return;
        }
}
fclose(file);
    printf("\nMoney could not be withdrawn as the Account No:%d was not found in found.",acc_no);

}

void Check_Balance(){
    FILE *file =fopen(ACCOUNT_FILE, "rb");
    if (file == NULL){
        printf("\nError in opening file.\n");
        return;
    }

    int acc_no;
    Account acc_read;
    printf("Enter your Account Numbe: ");
    scanf("%d", &acc_no);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if(acc_read.account_no == acc_no){
            printf("\nYour current balance is Rs.%.2f", acc_read.balance);
            fclose(file);
            return;
        }
    }
    printf("\nAccount No:%d was not found.",acc_no);
    
}
