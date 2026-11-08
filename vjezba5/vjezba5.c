#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Stog* Position;
typedef struct Stog{

    int broj;
    Position next;
}stog;


// postavljanje na pocetak liste
int InsertBegin(Position head,Position newS){

    if(head==NULL || newS==NULL){
        printf("Doslo je do greske!");
        return -1;
    }

    newS->next=head->next;
    head->next=newS;

    return 1;
}

// dodavanje vrijednosti novom clanu liste i uvrstavanje u listu
int Push(int x,Position head){

    Position newS=(Position)malloc(sizeof(stog));

    if(newS==NULL){
        printf("Doslo je do greske!");
        return -1;
    }

    newS->broj=x;
    newS->next=NULL;
    InsertBegin(head,newS);

    return 1;
}


// Uzimanje prva 2 clana liste, izvrsavanje operacije, brisanje clanova te dodavanje novog clana u listu
int Pop(char y,Position head){

    int z;
    Position p=head->next;

    if(head->next==NULL || p->next==NULL){
        printf("Doslo je do greske!");
        return -1;
    }

    if(y=='+'){
        z=p->next->broj+head->next->broj;
    }
    else if(y=='-'){
        z=p->next->broj-head->next->broj; 
    }
    else if(y=='*'){
        z=p->next->broj*head->next->broj;
    }
    else if(y=='/'){
        if (head->next->broj == 0) {
        printf("Dijeljenje s nulom!");
        return -1;
    }
        z=p->next->broj/head->next->broj;
    }
    else{
        printf("Operator nije prepoznat! %c",y);
        return -1;
    }
    
    Position first=head->next;
    Position second=first->next;

    head->next=second->next;

    free(first);
    free(second);

    Push(z,head);

    return 1;

}


// brisanje svih clanova sa stoga
int freeStack(Position head){

    Position temp;

    while(head->next!=NULL){
        temp=head->next;
        head->next=temp->next;
        free(temp);
    }

    return 2;
}


// funkcija za citanje datoteke i spremanje informacija
int readFile(char* filename, Position Head) {

    FILE* dat = fopen(filename, "r");

    if (dat == NULL) {
        printf("Greska pri otvaranju datoteke!");
        return -1;
    }

    int br;
    char znak;

    while (fscanf(dat, " %c", &znak) == 1) {

        if ((znak >= '0' && znak <= '9') || znak == '-') {

            ungetc(znak, dat);

            if (fscanf(dat, "%d", &br) == 1) {
                Push(br, Head);
            }
            else {
                printf("Greska pri citanju broja!");
                fclose(dat);
                freeStack(Head);
                return -1;
            }
        }
        else if (znak == '+' || znak == '*' || znak == '/') {

            if (Pop(znak, Head) == -1) {
                fclose(dat);
                freeStack(Head);
                return -1;
            }
        }
        else {
            printf("Nepoznat znak!");
            fclose(dat);
            freeStack(Head);
            return -1;
        }
    }

    fclose(dat);

    if (Head->next == NULL || Head->next->next != NULL) {
        printf("Postfix izraz nije ispravan!");
        freeStack(Head);
        return -1;
    }

    return 1;
}


// funkcija za ispis stoga
int Ispis(Position head){
    
    Position temp=head->next;
    printf("Na stogu imamo: ");
    while(temp!=NULL){
        printf(" %d",temp->broj);
        temp=temp->next;
    }
    return 3;
}


int main(){

    stog head={0,NULL};

    char* a= "postfix.txt";

    readFile(a,&head);
    Ispis(&head);

    freeStack(&head);

    return 0;
}