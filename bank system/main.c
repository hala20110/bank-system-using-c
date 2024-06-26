#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
typedef struct {
char month[20];
int year;
} Date;

int MAX=100;

typedef struct{
char accNo[50];
char name[50];
char address[50];
float balance;
char mobile[50];
int intmonth;
Date dateopened;
}account;
account accounts[100];
void Month (char c[], int x)
{
    switch (x)
    {
    case 1:
        strcpy (c, "January");
        break;
    case 2:
        strcpy (c, "February");
        break;
    case 3:
        strcpy (c, "March");
        break;
    case 4:
        strcpy (c, "April");
        break;
    case 5:
        strcpy (c, "May");
        break;
    case 6:
        strcpy (c, "June");
        break;
    case 7:
        strcpy (c, "July");
        break;
    case 8:
        strcpy (c, "August");
        break;
    case 9:
        strcpy (c, "September");
        break;
    case 10:
        strcpy (c, "October");
        break;
    case 11:
        strcpy (c, "November");
        break;
    case 12:
        strcpy (c, "December");
        break;
    }
}


int LOAD(account accounts[],int MAX)
{
    FILE *file;
    file=fopen("accounts.txt","r");

    if(file==NULL){
        printf("error opening file.\n");
        return 1;
    }
    char c[20];
    int M;
    int read=0;//number of values read successfully
    int records=0;//keep track of numbers of records we read from file
    do{
        read=fscanf(file,"%50[^,],%50[^,],%50[^,],%f,%50[^,],%d-%d\n",&accounts[records].accNo,
                 accounts[records].name,
                 &accounts[records].address,
                 &accounts[records].balance,
                 &accounts[records].mobile,
                 &M,
                 &accounts[records].dateopened.year);

        accounts[records].intmonth = M;
        Month (c, M);
        strcpy (accounts[records].dateopened.month, c);

          if(read==7)
                    records++;
          if(read !=7 && !feof(file))
          {
              printf("\033[1;31m file format incorrect.\033[1;0m\n");
              return 1;
          }
            if(ferror(file))
            {
                printf("\033[1;31m error reading file.\033[1;0m\n");
                return 1;
            }
    }while(!feof(file));
    fclose(file);
    return records;
}
int LOGIN ()
{
    printf ("*************** LOGIN ***************\n");
    start:
    printf ("Enter username: \n");
    char user[30];
    char pass[30];
    scanf ("%s", user);
    printf ("Enter password: \n");
    char c;
    int i = 0;
    while (1)
    {
        c = getch();
        if (c == 13)    //ASCII code of enter key = 13
        {
            pass [i] = '\0';
            break;
        }
        else if (c == 8)   //ASCII code for backspace = 8
        {
            if (i != 0);
            {
                i--;
                printf ("\b \b");
            }
        }
        else if (c == 9 || c == 32);    //ASCII code of tab key = 9 and for the space = 32
        else
        {
            pass [i] = c;
            printf ("*");
            i++;
        }
    }
    printf ("\n\n");

    char k[60];
    k[0] = NULL;
    strcat (k, user);
    strcat (k, " ");
    strcat (k, pass);
    strcat (k, "\n");

    FILE *login;
    login = fopen ("users.txt", "r");
    if (login == NULL)
        {
            printf ("\033[1;31m Error in opening file users.txt!! \033[1;0m");
            exit (1);
        }
    int n = strlen (k) + 1;
    int p = 0;
    char s[60];
    while(fgets(s, n, login))
    {
        if(strstr(s, k)!= NULL)
        {
            printf ("\033[1;32m SUCCESSFUL LOGIN \033[1;0m\n\n");
            p = 1;
            break;
        }
    }
    if (p == 0)
    {
        printf ("\033[1;31m UNSUCCESSFUL LOGIN \033[1;0m\nPlease Try Again...\n\n");
        fclose (login);
        goto start;
    }
    fclose (login);
    return p;
}


void SortByName (account accounts[],int MAX)
{
    printf ("The data of the accounts sorted by name:\n");

    int i, j, c, M;
    M = LOAD(accounts,MAX);
    account sortname[M];
    for (i = 0; i < M; i++)
    {
        sortname[i] = accounts[i];
    }

    account temp;
    for (i = 0; i < M; i++)
    {
        for (j = i + 1; j < M; j++)
        {
            c = strcmp (sortname[i].name, sortname[j].name);
            if (c > 0)
            {
                temp = sortname[i];
                sortname[i] = sortname[j];
                sortname[j] = temp;
            }
        }
    }

    for(int i = 0; i < M; i++)
    {
        printf("Account Number: %s\nName: %s\nAddress: %s\nBalance: %.2f\nMobile Number: %s\nDate Opened: %s %d\n",
               sortname[i].accNo,
               sortname[i].name,
               sortname[i].address,
               sortname[i].balance,
               sortname[i].mobile,
               sortname[i].dateopened.month,sortname[i].dateopened.year);
        printf("\n");
    }
}

void SortByDate (account accounts[],int MAX)
{
    start:
    printf ("Choose how do you want to sort the date\n");
    printf ("[1] Newest to oldest\n[2] Oldest to newest\n");
    printf ("Write the number of choice: ");
    int choice;
    scanf ("%d", &choice);
    printf ("\n");
    if (!(choice == 1 || choice == 2))
    {
        printf ("Please choose number 1 or 2 only\nTry again...\n");
        goto start;
    }
    int i, j, c, M;
    M = LOAD(accounts,MAX);
    account sortdate[M];
    for (i = 0; i < M; i++)
    {
        sortdate[i] = accounts[i];
    }
    account temp;

    if (choice == 1)
    {
        for (i = 0; i < M; i++)
        {
            for (j = i + 1; j < M; j++)
            {
                if (sortdate[i].dateopened.year < sortdate[j].dateopened.year)
                {
                    temp = sortdate[i];
                    sortdate[i] = sortdate[j];
                    sortdate[j] = temp;
                }
                else if (sortdate[i].dateopened.year == sortdate[j].dateopened.year)
                {
                    if (sortdate[i].intmonth < sortdate[j].intmonth)
                    {
                        temp = sortdate[i];
                        sortdate[i] = sortdate[j];
                        sortdate[j] = temp;
                    }
                }
            }
        }
        printf ("Data sorted from newest to oldest\n\n");
    }
    else if (choice == 2)
    {
        for (i = 0; i < M; i++)
        {
            for (j = i + 1; j < M; j++)
            {
                if (sortdate[i].dateopened.year > sortdate[j].dateopened.year)
                {
                    temp = sortdate[i];
                    sortdate[i] = sortdate[j];
                    sortdate[j] = temp;
                }
                else if (sortdate[i].dateopened.year == sortdate[j].dateopened.year)
                {
                    if (sortdate[i].intmonth > sortdate[j].intmonth)
                    {
                        temp = sortdate[i];
                        sortdate[i] = sortdate[j];
                        sortdate[j] = temp;
                    }
                }
            }
        }
        printf ("Data sorted from oldest to newest\n\n");
    }
    for(int i = 0; i < M; i++)
    {
        printf("Account Number: %s\nName: %s\nAddress: %s\nBalance: %.2f\nMobile Number: %s\nDate Opened: %s %d\n",
               sortdate[i].accNo,
               sortdate[i].name,
               sortdate[i].address,
               sortdate[i].balance,
               sortdate[i].mobile,
               sortdate[i].dateopened.month,sortdate[i].dateopened.year);
        printf("\n");
    }
}

void SortByBalance (account accounts[],int MAX)
{
    start:
    printf ("Choose how do you want to sort the balance\n");
    printf ("[1] Lowest to highest\n[2] Highest to lowest\n");
    printf ("Write the number of choice: ");
    int choice;
    scanf ("%d", &choice);
    printf ("\n");
    if (!(choice == 1 || choice == 2))
    {
        printf ("Please choose number 1 or 2 only\nTry again...\n");
        goto start;
    }
    int i, j, c, M;
    M = LOAD(accounts,MAX);
    account sortbalance[M];
    for (i = 0; i < M; i++)
    {
        sortbalance[i] = accounts[i];
    }
    account temp;

    if (choice == 1)
    {
        for (i = 0; i < M; i++)
        {
            for (j = i + 1; j < M; j++)
            {
                if (sortbalance[i].balance > sortbalance[j].balance)
                {
                    temp = sortbalance[i];
                    sortbalance[i] = sortbalance[j];
                    sortbalance[j] = temp;
                }
            }
        }
        printf ("Data sorted from lowest balance to highest balance\n\n");
    }
    else if (choice == 2)
    {
        for (i = 0; i < M; i++)
        {
            for (j = i + 1; j < M; j++)
            {
                if (sortbalance[i].balance < sortbalance[j].balance)
                {
                    temp = sortbalance[i];
                    sortbalance[i] = sortbalance[j];
                    sortbalance[j] = temp;
                }
            }
        }
        printf ("Data sorted from highest balance to lowest balance\n\n");
    }

    for(int i = 0; i < M; i++)
    {
        printf("Account Number: %s\nName: %s\nAddress: %s\nBalance: %.2f\nMobile Number: %s\nDate Opened: %s %d\n",
               sortbalance[i].accNo,
               sortbalance[i].name,
               sortbalance[i].address,
               sortbalance[i].balance,
               sortbalance[i].mobile,
               sortbalance[i].dateopened.month,sortbalance[i].dateopened.year);
        printf("\n");
    }
}
int month_rev(char c[])
{
    int x;
    if (strcmp("January", c) == 0)
        x = 01;
    else if (strcmp("February", c) == 0)
        x = 02;
    else if (strcmp("March", c) == 0)
        x = 03;
    else if (strcmp("April", c) == 0)
        x = 04;
    else if (strcmp("May", c) == 0)
        x = 05;
    else if (strcmp("June", c) == 0)
        x = 06;
    else if (strcmp("July", c) == 0)
        x = 07;
    else if (strcmp("August", c) == 0)
        x = 8;
    else if (strcmp("September", c) == 0)
        x = 9;
    else if (strcmp("October", c) == 0)
        x = 10;
    else if (strcmp("November", c) == 0)
        x = 11;
    else
        x = 12;
    return x;
}

int SAVE(account accounts[],int num_acc)
{
    char s[4];
    printf("Do you want to save this process? (Yes or No): ");
    scanf("%s", s);

    if (strcmp(s,"Yes") != 0 && strcmp(s,"yes") != 0 && strcmp(s,"YES") != 0)
    {
        return 0;
    }

    FILE *file;
    file = fopen("accounts.txt", "w");
    if (file == NULL)
    {
        printf("\033[1;31mError opening file!\033[1;0m\n");
        return -1;
    }


    for (int i = 0; i < num_acc ; i++)
    {
        int x = month_rev(accounts[i].dateopened.month);

        fprintf(file, "%s,%s,%s,%.2f,%s,%d-%d\n", accounts[i].accNo, accounts[i].name, accounts[i].address,
                accounts[i].balance, accounts[i].mobile, x, accounts[i].dateopened.year);
    }

    fclose(file);
    return 1;
}
void add_acc(account accounts[],int MAX)
{
SYSTEMTIME time;
GetSystemTime(&time);
int year=time.wYear;
int month=time.wMonth;
char x[50];
int K,i,q;

char a[50], b[50], c[50], d[50];
char temp[50];
int flag=1,map=1,s=0;
q=LOAD(accounts,MAX);
K=q;
K += 1;
FILE *file = fopen("accounts.txt", "a+");
if (file == NULL) {
printf("Error opening file for writing.\n");
return;
}
while(s==0){
printf("Enter a new account number: ");
scanf("%s",x);
 if (x[strlen(x) - 1] == '\n') {
x[strlen(x) - 1] = '\0';}
if(strlen(x)==10){
for (i = 0; i < K - 1; i++) {
if (strcmp(accounts[i].accNo, x) == 0) {
printf("Account number already used.\n");
printf("Please enter a different account number.\n");
s=0;
break;
}}
 if (i == K - 1)
{
strcpy(accounts[K - 1].accNo, x);
FILE *f = fopen(strcat(x,".txt"), "a+");
fclose(f);
s = 1;
}}
else
{
printf("Account number should be 10 numbers\n");
s = 0;
}}
int bag=1;
while (bag == 1)
{printf("\nEnter your name: ");
getchar();
gets(a);
if(strlen(a)==0){
bag=1;
printf("Name cannot be empty Please enter a valid name.\n");
}
else
{
int validName = 1;
for (int j = 0; j < strlen(a); j++)
{if (!isalpha(a[j]) && !isspace(a[j]))
{
validName = 0;
break;}}
if (validName){
strcpy(accounts[K - 1].name, a);
accounts[K - 1].name[strcspn(accounts[K - 1].name, "\n")] = '\0';
bag = 0;}
else
{
bag = 1;
printf("\nInvalid name. Please enter a name without numbers.\n");
}}}
printf("\nEnter your added balance: ");
scanf("%f", &accounts[K- 1].balance);
getchar();

while (flag==1){
printf("\nEnter your email address: ");
//getchar();
gets(b);
if(strchr(b,'@')!=NULL   && strchr(b,'.')!=NULL ){
strcpy(accounts[K- 1].address, b);
accounts[K - 1].address[strcspn(accounts[K- 1].address, "\n")] = '\0';
flag=0;}
else {
flag=1;
printf("\n\033[1;31m INVALID EMAIL ADDRESS \033[1;0m\n");
}}
while(map==1){
printf("\nEnter your phone number: ");
gets(c);
accounts[K- 1].mobile[strcspn(accounts[K - 1].mobile, "\n")] = '\0';
if(strlen(c)==11&&c[0]=='0'){
strcpy(accounts[K- 1].mobile, c);
map=0;}
else

{
printf("\n\033[1;31m Invalid phone number \033[1;0m\n");
map=1;
}}

fprintf(file, "%s,%s,%s,%.2f,%s,%d-%d\n",
  accounts[K- 1].accNo,
  accounts[K - 1].name,
  accounts[K - 1].address,
  accounts[K - 1].balance,
  accounts[K - 1].mobile,
  month,
  year);

fclose(file);
printf("\n\033[1;32m Account is created successfully \033[1;0m\n");
int descision;
    printf("DO YOU WANT TO ADD ANOTHER ACCOUNT ?\n");
    printf("1.\033[1;32m YES \033[1;0m\n2.\033[1;31m NO\033[1;0m\n");
    scanf("%d",&descision);
    switch(descision)
    {
   case 1:
    add_acc( accounts,MAX);
    break;
   case 2:
    MENU2();
    break;
    }
}
void delete_acc(account accounts[], int MAX) {
    int k = LOAD(accounts, MAX);
    int i, flag = 0;
    char c[50];

    printf("Please enter account number to delete it: ");
    getchar();
    fgets(c,sizeof(c),stdin);
    c[strcspn(c,"\n")] = '\0';

    for (i = 0; i<k; i++) {
        if (strcmp(c, accounts[i].accNo) == 0) {
            flag = 1;
            if (accounts[i].balance == 0) {
                printf("Account is deleted\n");
                for (int j = i; j < k - 1; j++) {
                    strcpy(accounts[j].accNo, accounts[j + 1].accNo);
                    strcpy(accounts[j].name, accounts[j + 1].name);
                    strcpy(accounts[j].address, accounts[j + 1].address);
                    strcpy(accounts[j].mobile, accounts[j + 1].mobile);
                    accounts[j].balance = accounts[j + 1].balance;
                    accounts[j].dateopened.year = accounts[j + 1].dateopened.year;
                    strcpy(accounts[j].dateopened.month, accounts[j + 1].dateopened.month);
                }
                k--;
                SAVE(accounts, k);
            } else {
                printf("\033[1;31m Account deletion is rejected. Balance is not zero.\033[1;0m \n");
            }
            break;
        }
    }

    if (flag == 0) {
        printf("\033[1;31m Account is not found \033[1;0m\n");
    }

int descision;
    printf("DO YOU WANT TO DELETE ANOTHER ACCOUNT ?\n");
    printf("1.\033[1;32m YES \033[1;0m\n2.\033[1;31m NO\033[1;0m\n");
    scanf("%d",&descision);
    switch(descision)
    {
   case 1:
    delete_acc( accounts,MAX);
    break;
   case 2:
    MENU2();
    break;
    }
}
void modify(account accounts[],int MAX)
{
int index2;
int K=LOAD(accounts,MAX);
int INDEX;
char x[50],str[50],y[50],z[50],s[4],p[4],w[4];
int i,b=0;
int flag=1,d=1,m=1,key=0;
FILE *file = fopen("accounts.txt", "r+");
if (file == NULL) {
printf("Error opening file for writing.\n");
return;}
printf("please enter your account number : ");
scanf("%s",x);
x[strcspn(x, "\n")] = '\0';
fflush(stdin);
for(i=0;i<K;i++)
{
if(strcmp(accounts[i].accNo,x)==0)
{
b=1;index2=i;
printf("You are only allowed to modify your name,phone number,email\n");
printf("Do you want to modify your name? (Yes or No): ");
    scanf("%s", s);
if (strcmp(s,"Yes") == 0 ||strcmp(s,"yes") ==0 ||strcmp(s,"YES") == 0)
{getchar();
while (m == 1)
{printf("\nEnter your modified name  :  ");
gets(str);
str[strcspn(str, "\n")] = '\0';
if(strlen(str)==0){
m=1;
printf("Name cannot be empty Please enter a valid name.\n");
}
else
{
int validName = 1;
for (int j = 0; j < strlen(str); j++)
{if (!isalpha(str[j]) && !isspace(str[j]))
{
validName = 0;
break;}}
if (validName){
strcpy(accounts[i].name, str);
accounts[i].name[strcspn(accounts[i].name, "\n")] = '\0';
m = 0;
key++;}
else
{
m= 1;
printf("\nInvalid name. Please enter a name without numbers.\n");
}}}}
fflush(stdin);

printf("Do you want to modify your phone number? (Yes or No): ");
scanf("%s", p);
if (strcmp(p,"Yes") == 0 ||strcmp(p,"yes") ==0 ||strcmp(p,"YES") == 0)
{getchar();
while(flag==1){
printf("\nEnter your modified phone number  :  ");
gets(y);
y[strcspn(y, "\n")] = '\0';
if(strlen(y)==11&&y[0]=='0'){
strcpy(accounts[i].mobile,y);
flag=0;key++;
}
else
{
printf("Invalid phone number\n");
flag=1;
}}}
fflush(stdin);

printf("Do you want to modify your email address? (Yes or No): ");
scanf("%s", w);
if (strcmp(w,"Yes") == 0 ||strcmp(w,"yes") ==0 ||strcmp(w,"YES") == 0)
{
while(d==1){
printf("\n enter your modified email  :  ");
gets(z);
z[strcspn(z, "\n")] = '\0';
if(strchr(z,'@')){
strcpy(accounts[i].address,z);
d=0;key++;}
else{
    printf("Invalid email address\n");
    d=1;
}}}}}
fflush(stdin);



    if (key!=0)
   {INDEX=SAVE(accounts,K);
    if(INDEX==0)
      {
    printf("\nYour process wasn't saved\n ");
       }
  else
    printf("your modified process was saved\n");

fclose(file);
}
if(b==0)
{printf("\ninvalid account number\n");
modify(accounts,MAX);
}
int descision;
    printf("DO YOU WANT TO MAKE ANOTHER MODIFICATION?\n");
    printf("1.\033[1;32m YES \033[1;0m\n2.\033[1;31m NO\033[1;0m\n");
    scanf("%d",&descision);
    switch(descision)
    {
   case 1:
    modify(accounts,MAX);
    break;
   case 2:
    MENU2();
    break;
    }
}
void QUERY()
{
    char n[20];
    printf("Enter the account number you want to search\n");
    scanf("%s", n);

    int acc = LOAD(accounts,MAX);
    int index = 0;
    for (int i = 0; i < acc; i++)
    {
        if (strcmp(n,accounts[i].accNo)==0)
        {
            printf("Account Number: %s\n", accounts[i].accNo);
            printf("Name: %s\n", accounts[i].name);
            printf("E-mail: %s\n", accounts[i].address);
            printf("Balance: %0.2f\n", accounts[i].balance);
            printf("Mobile: %s\n", accounts[i].mobile);
            printf("Date: %s %d\n\n", accounts[i].dateopened.month, accounts[i].dateopened.year);
            index++;
        }

    }

    if (index == 0)
    {
        printf("\033[1;31mSorry, the account number you entered isn't in our system\033[1;0m\n");
    }
    int descision;
    printf("DO YOU WANT TO SEARCH ANOTHER ACCOUNT ?\n");
    printf("1.\033[1;32mYES\033[1;0m\n2.\033[1;31mNO\033[1;0m\n");
    scanf("%d",&descision);
    switch(descision)
    {
   case 1:
    QUERY();
    break;
   case 2:
    MENU2();
    break;
    }
}

void ADVANCED_SEARCH()
{
    char n[20];
    printf("Enter the name you want to search\n");
    scanf("%s", n);

    int acc = LOAD(accounts,MAX);

    int index = 0;
    for (int i = 0; i < acc; i++) {
        char *found = strstr(accounts[i].name, n);

        if (found != NULL) {
            printf("Account Number: %s\n", accounts[i].accNo);
            printf("Name: %s\n", accounts[i].name);
            printf("E-mail: %s\n", accounts[i].address);
            printf("Balance: %0.2f\n", accounts[i].balance);
            printf("Mobile: %s\n", accounts[i].mobile);
            printf("Date: %s %d\n\n", accounts[i].dateopened.month, accounts[i].dateopened.year);
            index++;
        }
    }

    if (index == 0) {
        printf("\033[1;31mSorry, the name you entered isn't in our system\033[1;0m\n");
    }
    int descision;
    printf("DO YOU WANT TO SEARCH ANOTHER ACCOUNT ?\n");
    printf("1.\033[1;32mYES\033[1;0m\n2.\033[1;31mNO\033[1;0m\n");
    scanf("%d",&descision);
    switch(descision)
    {
   case 1:
    ADVANCED_SEARCH();
    break;
   case 2:
    MENU2();
    break;
    }
}
void WITHDRAW()
{

    char n[20];
    start:
    printf("Enter the account number you want to withdraw\n");
    scanf("%s", n);

    int acc = LOAD(accounts, MAX);
    int index = -1;

    for (int i = 0; i < acc; i++)
    {
        if (strcmp(n, accounts[i].accNo) == 0)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("The account number you entered isn't in our system\nPlease try again...\n");
        goto start;
    }

    float withdrawno;
    int MAX1 = 10000;

    withdraw:
    printf("Enter the amount to withdraw: $\n");
    scanf("%f", &withdrawno);

    if (withdrawno <= 0)
    {
        printf("\033[1;31mInvalid amount. Please enter a positive value.\033[1;0m\n");
        goto withdraw;
    }
    else if (withdrawno > MAX1)
    {
        printf("The maximum withdraw amount is %d $\n", MAX1);
        goto withdraw;
    }
    else if (withdrawno > accounts[index].balance)
    {
        printf("Cannot withdraw %.2f $. Insufficient balance: %.2f $\n", withdrawno, accounts[index].balance);
        goto withdraw;
    }
    accounts[index].balance -= withdrawno;
    int saveResult = SAVE(accounts,acc);

    if (saveResult == 0)
    {
        printf("Your processes weren't saved to the system.\n");
    }
    else
    {
        printf("\033[1;32mSuccessfully saved the deposit process.\033[1;0m\n");
        printf("Transaction successful. $%.2f withdrawn from account %s.\n", withdrawno, accounts[index].accNo);
        printf("Updated balance for account %s: $%.2f\n", accounts[index].accNo, accounts[index].balance);

        FILE *f;
        char c[50];
        sprintf(c, "%s.txt", accounts[index].accNo);
        f = fopen(c, "a+");

        if (f == NULL)
        {
            printf("\033[1;31mError opening file.\033[1;0m\n");
            return;
        }

        fprintf(f, "Transaction successful. $%.2f withdrawn from account %s.\n", withdrawno, accounts[index].accNo);
        fprintf(f, "Updated balance for account %s: $%.2f\n", accounts[index].accNo, accounts[index].balance);
        fprintf(f, "\n\n");
        fclose(f);
    }
    int descision;
    printf("DO YOU WANT TO MAKE ANOTHER WITHDRAWAL ?\n");
    printf("1.\033[1;32mYES\033[1;0m\n2.\033[1;31mNO\033[1;0m\n");
    scanf("%d",&descision);
    switch(descision)
    {
   case 1:
    WITHDRAW();
    break;
   case 2:
    MENU2();
    break;
    }
}

void DEPOSIT()
{
    char n[20];
    start:
    printf("Enter the account number you want to deposit\n");
    scanf("%s", n);

    int acc = LOAD(accounts, MAX);
    int index = -1;

    for (int i = 0; i < acc; i++)
    {
        if (strcmp(n, accounts[i].accNo) == 0)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("\033[1;31mThe account number you entered isn't in our system\033[1;0m\nPlease try again...\n");
        goto start;
    }

    float depositno;
    int MAX1 = 10000;
    deposit:
    printf("Enter the amount to deposit: $\n");
    scanf("%f", &depositno);

    if (depositno <= 0)
    {
        printf("\033[1;31mInvalid amount. Please enter a positive value.\033[1;0m\n");
        goto deposit;
    }
    else if (depositno > MAX1)
    {
        printf("The maximum deposit amount is %d $\n", MAX1);
        goto deposit;
    }


    accounts[index].balance += depositno;
    int saveResult = SAVE(accounts,acc);

    if (saveResult == 0)
    {
        printf("Your processes weren't saved to the system.\n");
    }
    else
    {
        printf("\033[1;32mSuccessfully saved the deposit process.\033[1;0m\n");
        printf("Transaction successful. $%.2f deposit to account %s.\n", depositno, accounts[index].accNo);
        printf("Updated balance for account %s: $%.2f\n", accounts[index].accNo, accounts[index].balance);

        FILE *f;
        char c[50];
        sprintf(c, "%s.txt", accounts[index].accNo);
        f = fopen(c, "a+");

        if (f == NULL)
        {
            printf("\033[1;31mError opening file.\033[1;0m\n");
            return;
        }

        fprintf(f, "Transaction successful. $%.2f deposit to account %s.\n", depositno, accounts[index].accNo);
        fprintf(f, "Updated balance for account %s: $%.2f\n", accounts[index].accNo, accounts[index].balance);
        fprintf(f, "\n\n");

        fclose(f);
    }
    int descision;
    printf("DO YOU WANT TO MAKE ANOTHER DEPOSIT ?\n");
    printf("1.\033[1;32mYES\033[1;0m\n2.\033[1;31mNO\033[1;0m\n");
    scanf("%d",&descision);
    switch(descision)
    {
   case 1:
    DEPOSIT();
    break;
   case 2:
    MENU2();
    break;
    }
}

void TRANSFER()
{
    char n[20];
    send:
    printf("Enter the account number you want to transfer money from \n");
    scanf("%s", n);

    int acc = LOAD(accounts,MAX);
    int index1 = -1;

    for (int i = 0; i < acc; i++)
    {
        if (strcmp(n, accounts[i].accNo) == 0)
        {
            index1 = i;
            break;
        }
    }

    if (index1 == -1)
    {
        printf("\033[1;31mSorry, the account number that will send money you entered isn't in our system\033[1;0m\n");
        goto send;
    }
    char s[20];
    recieve:
    printf("Enter the account number you want to transfer money to \n");
    scanf("%s", n);
    int index2 = -1;

    for (int k = 0; k < acc; k++)
    {
        if (strcmp(n, accounts[k].accNo) == 0)
        {
            index2 = k;
            break;
        }
    }

    if (index2 == -1)
    {
        printf("Sorry, the account number that will receive money you entered isn't in our system\n");
        goto recieve;
    }
        if (strcmp(accounts[index1].accNo,accounts[index2].accNo)==0)
    {
        printf("\033[1;31mSorry you can't transfer money from account to itself\033[1;0m\n");
        goto send;
    }
    float amount_transfer;
    money:
    printf("Enter amount to transfer:  ");
    scanf("%f",&amount_transfer);

    if (amount_transfer <= 0)
    {
        printf("\033[1;31mInvalid amount. Please enter a positive value.\033[1;0m\n");
        goto money;
    }

    if (amount_transfer > accounts[index1].balance)
    {
        printf("\033[1;31mInsufficient funds in sender's account.\033[1;0m\nTry again\n");
        goto money;
    }
    accounts[index1].balance=accounts[index1].balance-amount_transfer;
    accounts[index2].balance=accounts[index2].balance+amount_transfer;
    int saveResult = SAVE(accounts,acc);

    if (saveResult == 0)
    {
        printf("Your processes weren't saved to the system.\n");
    }
    else
    {
        printf("\033[1;32mSuccessfully saved the deposit process.\033[1;0m\n");

        printf("\033[1;32mTransfer successful.\033[1;0m\n");
        printf("$%0.2f transferred from account %s to account %s.\n", amount_transfer, accounts[index1].accNo, accounts[index2].accNo);
        printf("Updated balance for account %s: $%0.2f\n", accounts[index1].accNo, accounts[index1].balance);
        printf("Updated balance for account %s: $%0.2f\n",accounts[index2].accNo, accounts[index2].balance);

        FILE *f;
        char c[50];
        sprintf(c, "%s.txt", accounts[index1].accNo);
        f = fopen(c, "a+");

        if (f == NULL)
        {
            printf("\033[1;31mError opening file.\033[1;0m\n");
            return;
        }

        fprintf(f, "Transaction successful. $%.2f transfered from account %s.\n", amount_transfer, accounts[index1].accNo);
        fprintf(f, "Updated balance for account %s: $%.2f\n", accounts[index1].accNo, accounts[index1].balance);
        fprintf(f, "\n\n");

        fclose(f);

        FILE *f1;
        char y[50];
        sprintf(y, "%s.txt", accounts[index2].accNo);
        f1 = fopen(y, "a+");

        if (f1 == NULL)
        {
            printf("\033[1;31mError opening file.\033[1;0m\n");
            return;
        }

        fprintf(f, "Transaction successful. $%.2f transfered to account %s.\n", amount_transfer, accounts[index2].accNo);
        fprintf(f, "Updated balance for account %s: $%.2f\n", accounts[index2].accNo, accounts[index2].balance);
        fprintf(f, "\n\n");

        fclose(f1);
    }
    int descision;
    printf("DO YOU WANT TO MAKE ANOTHER TRANSACTION?\n");
    printf("1.\033[1;32mYES\033[1;0m\n2.\033[1;31mNO\033[1;0m\n");
    scanf("%d",&descision);
    switch(descision)
    {
   case 1:
    TRANSFER();
    break;
   case 2:
    MENU2();
    break;
    }
}
void REPORT ()
{
    char a[20];
    startt:
    printf("Enter the account number\n");
    scanf("%s", a);
    int acc = LOAD(accounts, MAX);
    int i, p = 0;
    for (i = 0; i < acc; i++)
    {
        if (strcmp (a, accounts[i].accNo) == 0)
            p = 1;
    }
    if (p == 0)
    {
        printf ("Account isn't in our system\nPlease try again\n");
        goto startt;
    }
    FILE *file;
    char t[20];
    strcpy (t, a);
    strcat(t,".txt");
    file = fopen(t, "r");
    if (file == NULL){
        printf("Error opening file");}

    printf ("**********Report of account number %s**********\n\n", a);
    fseek(file, 0, SEEK_SET);
    long check = ftell (file);
    fseek(file, 0, SEEK_END);
    int count = 0;
    char c;
    long position = ftell (file);

    do {
        fseek(file, --position, SEEK_SET);
        c = fgetc(file);
        if (c == 'T') {
            count++;
        }

    } while (count < 5 && c!=EOF && position != check);

    if (count > 0){
        putchar ('T');}

    while (c != EOF) {
        c = fgetc(file);
        if (c == EOF) {
            break;
        }
        putchar(c);
    }
        fclose(file);
    int descision;
    printf("DO YOU WANT ANOTHER REPORT?\n");
    printf("1.\033[1;32mYES\033[1;0m\n2.\033[1;31mNO\033[1;0m\n");
    scanf("%d",&descision);
    switch(descision)
    {
   case 1:
    REPORT();
    break;
   case 2:
    MENU2();
    break;
    }

}
void PRINT (account accounts[],int MAX)
{
    printf ("*************** PRINT ***************\n");
    start:
    printf ("Choose how do you want to print the data of the accounts\n");
    printf ("[1] Sorted by name\n[2] Sorted by date\n[3] Sorted by balance\n");
    printf ("Write the number of choice: ");
    int choice;
    scanf ("%d", &choice);
    printf ("\n");
    if (choice > 3 || choice < 1)
        {
            printf ("\033[1;31mPlease choose a number from 1 to 3 only\033[1;0m\nTry again...\n");
            goto start;
        }

    switch (choice)
    {
        case 1:
            SortByName(accounts,MAX);
            break;
        case 2:
            SortByDate(accounts,MAX);
            break;
        case 3:
            SortByBalance(accounts,MAX);
            break;
    }
    int descision;
    printf("DO YOU WANT TO PRINT AGAIN ?\n");
    printf("1.\033[1;32mYES\033[1;0m\n2.\033[1;31mNO\033[1;0m\n");
    scanf("%d",&descision);
    switch(descision)
    {
   case 1:
    PRINT(accounts,MAX);
    break;
   case 2:
    MENU2();
    break;
    }
}

void QUIT()
{
    int nf;
    printf("ARE YOU SURE YOU WANT TO EXIT?\n");
    printf("1.YES\n");
    printf("2.NO\n");
    scanf("%d",&nf);
    if(nf==1)
    {
        exit(0);
    }
    else
    {
        MENU();
    }
}

void MENU2(){
    LOAD(accounts, MAX);
int choice;
printf("1.ADD\n\n");
printf("2.DELETE\n\n");
printf("3.MODIFY\n\n");
printf("4.SEARCH\n\n");
printf("5.ADVANCED SEARCH\n\n");
printf("6.WITHDRAW\n\n");
printf("7.DEPOSIT\n\n");
printf("8.TRANSFER\n\n");
printf("9.REPORT\n\n");
printf("10.PRINT\n\n");
printf("11.\033[1;31m QUIT \033[1;0m\n\n");
printf("*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_PLEASE ENTER YOUR CHOICE_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n");
printf("!!!!!! number should be from 1 to 11 !!!!!!!\n");
scanf("%d",&choice);
if(choice<12){
switch(choice)
{
    case 1:
       add_acc(accounts,MAX);
       break;
    case 2:
       delete_acc(accounts,MAX);
       break;
    case 3:
       modify(accounts,MAX);
       break;
    case 4:
       QUERY();
       break;
    case 5:
       ADVANCED_SEARCH();
       break;
    case 6:
       WITHDRAW();
       break;
    case 7:
       DEPOSIT();
       break;
    case 8:
       TRANSFER();
       break;
    case 9:
       REPORT();
       break;
    case 10:
       PRINT(accounts,MAX);
       break;
    case 11:
       QUIT();
       break;
}}
else{
    printf("\033[1;31m PLEASE ENTER A NUMBER FROM 1 TILL 11 ONLY\n \033[1;0m");
    MENU2();
}
    }
void MENU()
{
 int option;
 printf("\n\n\n\n\n");
 printf("\t\t\t\t\t\033[1;36m ....    ..   .    . .   .   .....  .    .   .....  ........   ......   .     .  \033[1;0m\n ");
 printf("\t\t\t\t\t\033[1;36m|    :  .  .  :.   : : .    :       :    :  :           :     .        :  . .  : \033[1;0m\n ");
 printf("\t\t\t\t\t\033[1;36m|....: ...... :.   : :.     :.....    .     :.....      :    . ......  :   .   : \033[1;0m\n");
 printf("\t\t\t\t\t\033[1;36m|    : :    : : .  : : .         :    :          :      :     .        :       : \033[1;0m\n");
 printf("\t\t\t\t\t\033[1;36m ....  :    : :   .  :   .  .....:    :     .....:      :      ......  :       : \033[1;0m\n\n\n");
 printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
 printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\033[1;36mWELCOME TO MAIN MENU\033[1;0m>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
 printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n\n\n");

 printf("1.LOGIN\n");
 printf("2.QUIT\n\n");
 printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PLEASE CHOOSE AN OPTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
 scanf("%d",&option);

if(option==1)
{
    if(LOGIN())
{
MENU2();
}
else
{
    MENU();
}
}
 else
{
    QUIT();
}
}
int main()
{
 MENU();
}
