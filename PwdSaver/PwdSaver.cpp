#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

typedef struct PassWord
{
    int id;
    char user_name[20];
    char pass_word[20];
    char web_site[20];
    struct PassWord *next;
} PWD;

int GetMaxNumber(PWD* h) {
    PWD* p = h->next;

    if (p==NULL)
    {
        return 0;
    }
    while (p->next != NULL)
    {
        p = p->next;
    }
    return p->id;
}

 void AddPwd(PWD* h, PWD node) {
     PWD *p = h;     
     if (p!=NULL)
     {
         while (p->next != NULL)
         {
             p = p->next;
         }
     }     
     PWD * newNode = (PWD*)malloc(sizeof(PWD));
     
     newNode->id = GetMaxNumber(h)+1;
     memcpy(newNode->user_name, node.user_name, strlen(node.user_name));    
     newNode->user_name[strlen(node.user_name)] = 0;

     memcpy(newNode->pass_word, node.pass_word, strlen(node.pass_word));
     newNode->pass_word[strlen(node.pass_word)] = 0;

     memcpy(newNode->web_site, node.web_site, strlen(node.web_site));
     newNode->web_site[strlen(node.web_site)] = 0;

     newNode->next = NULL;
     
     p->next = newNode;
 };

 void SavePwdListToFile(PWD* h) {
     FILE *fp;
     if ((fp=fopen("stu.txt", "wb")) == NULL) {
         printf("Can not open the file!");
     }
     PWD *p = h->next;
     while (p!=NULL)
     {
         fwrite(p, sizeof(PWD), 1, fp);
         p = p->next;
     }
     fclose(fp);
     printf("save success\n");
 };

 PWD* InitPwdFromFile() {
     FILE *fp;
     int IsOpen = 1;
     if ((fp = fopen("stu.txt", "rb+")) == NULL)
     {
         IsOpen = 0;
     }

     PWD* h = (PWD*)malloc(sizeof(PWD));
     h->id = 0;
     h->next = NULL;
     PWD*p2 = h;
    
     if (IsOpen)
     {
         do
         {
             PWD* p1 = (PWD*)malloc(sizeof(PWD));
             fread(p1, sizeof(PWD), 1, fp);
             p2->next = p1;
             p2 = p1;
         } while (p2->next != NULL);
         fclose(fp);
     } 
     printf("Init complete!\n\n");       
     return h;
 };
 
 void PrintPwdList(PWD* h) {
     PWD* p = h->next;
     int num = 1;
     if (p==NULL)
     {
         printf("\n\n No record\n\n");
         return;
     }
     char id[10] = "ID";
     char un[10] = "UserName";
     char pw[10] = "Pass word";
     char ws[10] = "Web Site";
     printf("\nPass Word List");
     printf("\n--------------------------------------------------------------------------------\n");
     printf("┊ %-10s┊ %-20s┊ %-20s┊ %-20s┊\n", id, ws, un, pw);
     printf("--------------------------------------------------------------------------------\n");

     while (p!=NULL)
     {
         printf("┊ %-10d  %-20s  %-20s  %-20s┊\n", p->id,p->web_site, p->user_name, p->pass_word);
         printf("--------------------------------------------------------------------------------\n");
         p = p->next;
         num++;
     }
 }

 void DeletePwd(PWD* h, int pwdId) {
     PWD*p = h->next;
     PWD* prevp = NULL;
     PWD* deletep = NULL;
     if (p==NULL)
     {
         return;
     }

     int IsFind = 0;
     while (p!=NULL&& !IsFind)
     {
         if (p->id == pwdId)
         {
             IsFind = 1;
             deletep = p;
             break;
         }
         prevp = p;
         p = p->next;
     }
     if (prevp==NULL)
     {
         h->next = deletep->next;
     }
     else {
         prevp->next = deletep->next;
     }
     if (deletep!=NULL) free(deletep);   
 }

 void DestroyList(PWD* h) {
     if (h==NULL)
     {
         return;
     }
     PWD * p = h->next;
     PWD *q = NULL;
     while (p!=NULL)
     {
         q = p;
         p = p->next;
         free(q);
     }
     printf("destroy success");
 }

int main()
{ 
    printf("-----Password Keeper System---------\n");
    printf("-----------------------------------\n");
    printf("☆ add ： create pass word         ☆\n");
    printf("☆ list：show all pass word list   ☆\n");
    printf("☆ save：save pass word  to file   ☆\n");
    printf("☆ delete ：delete password by Id  ☆\n");
    printf("☆ exit ：exit system              ☆\n");
    printf("-----------------------------------\n");
    char cmd[10];

    PWD* pwdList = InitPwdFromFile();

    gets_s(cmd);

    while (1)
    {        
        if (strcmp(cmd,"list")==0)
        {           
            PrintPwdList(pwdList);
        }
        else if (strcmp(cmd, "add")==0)
        {
            printf("please input number you want to create \n");
            int num=0;
            scanf_s("%d", &num);
            for (int i = 0; i < num; i++)
            {
                PWD pwd;
                printf("\n [%d],website username password separate each with a space.\n\n",i+1); 
                pwd.next = NULL;

                scanf("%s%s%s",pwd.web_site,pwd.user_name,pwd.pass_word);
                AddPwd(pwdList, pwd);
            }
        }
        else if (strcmp(cmd, "save")==0)
        {
            SavePwdListToFile(pwdList);
        }
        else if (strcmp(cmd, "delete") == 0)
        {
            printf("please input id\n\n");
            int id = 0;
            scanf("%d", &id);            
            DeletePwd(pwdList, id);
        }
        else if (strcmp(cmd, "exit") == 0)
        {
            SavePwdListToFile(pwdList);
            DestroyList(pwdList);
            exit(0);
        }
        gets_s(cmd);
    }

    printf("Exit PwdSaver \n");
    return 0;
}

