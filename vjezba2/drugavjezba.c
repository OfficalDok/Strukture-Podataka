#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definiranje strukture

typedef struct _Person* position;
typedef struct _Person{

     char ime[20];
     char prezime[20];
     int god;

     position next;

}person;


// funkcija za dodavanje na pocetak liste

int insertBegin(char* name, char* lastN, int dob, position head){   

    position newPerson = (position)malloc(sizeof(person));

    if(newPerson==NULL){
        printf("Došlo je do greske pri unosu!");
        return -1;
    }

    newPerson->god=dob;
    strcpy(newPerson->ime,name);
    strcpy(newPerson->prezime,lastN);

    newPerson->next=head->next;
    head->next=newPerson;

    return 0;
}

//funkcija za dodavanje na kraj liste

int insertAfter(char* name, char* lastN, int dob, position head){   

    position newPerson = (position)malloc(sizeof(person));

    if(newPerson==NULL){
        printf("Došlo je do greske pri unosu!");
        return -1;
    }

    newPerson->god=dob;
    strcpy(newPerson->ime,name);
    strcpy(newPerson->prezime,lastN);

    while(head->next!=NULL){
        head=head->next;
    }

    newPerson->next=head->next;
    head->next=newPerson;

    return 0;
}

// funkcija za pronalazak prezimena unutar liste

position findlastN(position p,char* lastN){

    for(p=p->next;p!=NULL;p=p->next){
        if(strcmp(p->prezime,lastN)==0){
            return p;
        }
    }

    return NULL;
}

// funkcija za brisanje odredjenog prezimena

int deleteP(position p,char* lastN){

    position current=p->next;
    position prev=p;

    current=findlastN(p,lastN);

    while(prev->next!=current)
        prev=prev->next;

    prev->next=prev->next->next;

    free(current);
    
    return 2;
}

// funkcija za ispis liste

int printList(position p){   
    
    while(p->next!=NULL){

        printf("\n");
        p=p->next;
        printf("%s %s %d\n",p->ime,p->prezime,p->god);
        
    }

    return 0;
}



int main(){

    person Head = {.ime={0},.prezime={0},.god=0,.next=NULL};

    char name[20];
    char lastN[20];
    char delete[20];
    int godina;
    int br,i;

    printf("Unesite broj osoba: ");
    scanf("%d",&br);

    for(i=0;i<br;i++){

        printf("Unesite ime: ");
        scanf(" %s",name);
        printf("Unesite prezime: ");
        scanf(" %s",lastN);
        printf("Unesite godinu rodjenja: ");
        scanf("%d",&godina);

        //insertBegin(name,lastN,godina,&Head);
        insertAfter(name,lastN,godina,&Head);

    }

    printList(&Head);

    printf("Unesite prezime za brisanje iz liste: ");
    scanf(" %s",delete);

    deleteP(&Head,delete);

    printf("Lista nakon brisanja:\n");
    printList(&Head);

    return 0;
}