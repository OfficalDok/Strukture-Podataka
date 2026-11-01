#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Polinom* Position;
typedef struct _Polinom{

    int koe;
    int eks;
    Position next;

}Polinom;

// funkcija za unos na pocetak liste

int insertBegin(Position head, Position newPoli){   

    if(head==NULL || newPoli==NULL){
        printf("Došlo je do greske pri unosu!");
        return -1;
    }

    newPoli->next=head->next;
    head->next=newPoli;

    return 0;
}

// funkcija za sortirani unos

int insertSort(Position head,Position newPoli){

    Position q=head;
    Position temp;

    // slucaj za praznu listu
    if(q->next==NULL || newPoli->eks < q->next->eks){
        return insertBegin(head,newPoli);
    }
    // Dolazimo do elementa sa vecim ili jednakim eksponentom
        while(q->next!=NULL && q->next->eks < newPoli->eks){
            q=q->next;
        }

    // Ako je eksponent jednak zbrajamo koeficijente
    if(q->next != NULL && q->next->eks == newPoli->eks){
        q->next->koe += newPoli->koe;
        free(newPoli);

    // Ako je zbroj koeficijenata 0 onda brisemo element iz liste
        if(q->next->koe == 0){
            temp=q->next;
            q->next=temp->next;
            free(temp);
        }

        return 1;
    }

    // Unetanje novog elementa u listu ako nije ispunjen gornji if

        newPoli->next=q->next; 
        q->next=newPoli;

    return 1;
}

// funkcija za citanje datoteke

int readPoli(FILE* dat, Position head){

    int koe;
    int eks;

    while(fscanf(dat," %d %d", &koe, &eks) == 2){

        Position newPoli=malloc(sizeof(*newPoli));

        if(newPoli==NULL)
           return -1;


        newPoli->koe=koe;
        newPoli->eks=eks;

        insertSort(head,newPoli);
    }

    return 2;
}

// funkcija za zbrajanje polinoma

int suma(Position P1, Position P2, Position S){

    Position temp;
    Position newPoli;

    P1=P1->next;
    P2=P2->next;

    while(P1!=NULL && P2!=NULL){

        newPoli=malloc(sizeof(*newPoli));
        if(newPoli==NULL)
          return -1;

        if(P1->eks == P2->eks){
            
            newPoli->koe=P1->koe+P2->koe;
            newPoli->eks=P1->eks;

            P1=P1->next;
            P2=P2->next;
        }
        else if(P1->eks > P2->eks){
            
            newPoli->koe=P1->koe;
            newPoli->eks=P1->eks;

            P1=P1->next;
        }
        else{
            newPoli->koe=P2->koe;
            newPoli->eks=P2->eks;

            P2=P2->next;
        }

        newPoli->next=NULL;
        insertSort(S,newPoli);

    }
        while (P1 != NULL) {

        newPoli = malloc(sizeof(*newPoli));

        if (newPoli == NULL)
            return -1;

        newPoli->koe = P1->koe;
        newPoli->eks = P1->eks;
        newPoli->next = NULL;

        insertSort(S, newPoli);

        P1 = P1->next;
    }

        while (P2 != NULL) {

        newPoli = malloc(sizeof(*newPoli));

        if (newPoli == NULL)
            return -1;

        newPoli->koe = P2->koe;
        newPoli->eks = P2->eks;
        newPoli->next = NULL;

        insertSort(S, newPoli);

        P2 = P2->next;
    }

    return 2;
  
}

// funkcija za ispis

void printPoli(Position head){

    Position q=head->next;

    while(q!=NULL){
        if(q->koe!=0){
        printf("%+dx^%d ",q->koe,q->eks);
        }
        q=q->next;
    }
    printf("\n");
}

// funkcija za mnozenje

int umnozak(Position P1,Position P2,Position U){

    Position p;
    Position q;
    Position newPoli;

    P1=P1->next;
    P2=P2->next;

    for(p=P1;p!=NULL;p=p->next){
        for(q=P2;q!=NULL;q=q->next){

            newPoli=malloc(sizeof(*newPoli));

            if(newPoli==NULL){
                printf("Doslo je do geaske!");
                return -1;
            }

            newPoli->koe=p->koe*q->koe;
            newPoli->eks=p->eks+q->eks;
            newPoli->next=NULL;

            insertSort(U,newPoli);
        }
    }
    return 3;
}


int main(){

    Polinom headFirst;
    Polinom headSecond;
    Polinom headRes;

    headFirst.next=NULL;
    headSecond.next=NULL;
    headRes.next=NULL;

    FILE* dat1 = fopen("polinom1.txt","r");
    FILE* dat2 = fopen("polinom2.txt","r");

    if(dat1==NULL || dat2==NULL){
        printf("Doslo je do greske pri otvaranju datoteke!");
        return -1;
    }

    readPoli(dat1,&headFirst);
    readPoli(dat2,&headSecond);

    printPoli(&headFirst);
    printf("\n");
    printPoli(&headSecond);
    printf("\n");

    suma(&headFirst,&headSecond,&headRes);

    printPoli(&headRes);
    printf("\n");

    Polinom headUmnozak;
    headUmnozak.next=NULL;

    umnozak(&headFirst,&headSecond,&headUmnozak);

    printPoli(&headUmnozak);
    printf("\n");





    return 0;
}