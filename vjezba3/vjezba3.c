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

// funkcija za unos iza elementa

int unosIza(char* x,char* z,char* y,int dob, position p){

    position q;
    p=findlastN(p,y);

    if(p!=NULL){
        q=(position)malloc(sizeof(person));
        strcpy(q->ime,x);
        strcpy(q->prezime,z);
        q->god=dob;
        q->next=p->next;
        p->next=q;
    }
    else{
        printf("Prezime ne postoji u listi!");
    }

    return 3;

}

// funckija za unos ispred

int unosIspred(char* x,char* z,char* y,int dob,position p){

    position q;
    while(p->next!=NULL && (strcmp(p->next->prezime,y)!=0))
       p=p->next;
    if(p!=NULL){
        q=(position)malloc(sizeof(person));
        strcpy(q->ime,x);
        strcpy(q->prezime,z);
        q->god=dob;
        q->next=p->next;
        p->next=q; 
    }
    else printf("Prezime ne postoji u listi!");

    return 4;
}

int bubbleSort(position head){

    position p=head->next;
    position q=head;
    position temp=NULL;

    while(p!=NULL && p->next!=NULL){
        if(strcmp(p->prezime,p->next->prezime)>0){

            temp=p->next;
            q->next=temp;
            p->next=temp->next;
            temp->next=p;

            q=head;
            p=head->next;
        }
        else{
            q=p;
            p=p->next;
        }
    }

    return 7;
}

int deleteList(position head){

    position temp;

    while(head->next!=NULL){
        temp=head->next;
        head->next=temp->next;
        free(temp);
    }

    return 8;
}


int main(){

    person Head = {.ime={0},.prezime={0},.god=0,.next=NULL};

    char name[20];
    char lastN[20];
    char delete[20];
    char y[20];
    int godina;
    int br,i;
    char buffer[100];
    FILE* dat;
    position p;

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

    // unos iza clana liste
    
    printf("Unesite ime osobe u listu: ");
    scanf(" %s",name);
    printf("Unesite prezime osobe u listu: ");
    scanf(" %s",lastN);
    printf("Unesite dob osobe: ");
    scanf("%d",&godina);
    printf("Unesite iza kojeg prezimena zelite unijeti novu osobu: ");
    scanf(" %s",y);

    unosIza(name,lastN,y,godina,&Head);

    printList(&Head);

    // unos ispred clana liste

    printf("Unesite ime osobe u listu: ");
    scanf(" %s",name);
    printf("Unesite prezime osobe u listu: ");
    scanf(" %s",lastN);
    printf("Unesite dob osobe: ");
    scanf("%d",&godina);
    printf("Unesite ispred kojeg prezimena zelite unijeti novu osobu: ");
    scanf(" %s",y);

    unosIspred(name,lastN,y,godina,&Head);

    printList(&Head);

    // sorter

    bubbleSort(&Head);

    printf("Lista nakon sortiranja: ");

    printList(&Head);

    // brisanje clana iz liste

    printf("Unesite prezime za brisanje iz liste: ");
    scanf(" %s",delete);

    deleteP(&Head,delete);

    printf("Lista nakon brisanja:\n");
    printList(&Head);

    // ispis u datoteku
    
    dat = fopen("Lista.txt","w");

    if(dat==NULL){
        printf("Doslo je do greske pri otvaranju datoteke!");
        return -3;
    }
    
    fprintf(dat,"%-10s %-10s %-10s\n","IME","PREZIME","GODINA");
    fprintf(dat,"-------------------------------------------------------------------------------------\n");
    for(p=Head.next;p!=NULL;p=p->next){

        fprintf(dat,"%-10s %-10s %-10d\n",p->ime,p->prezime,p->god);

    }

    fclose(dat);

    deleteList(&Head);


    dat = fopen("Lista.txt","r");

    if(dat==NULL){
        printf("Doslo je do greske pri otvaranju datoteke!");
        return -3;
    }

    fgets(buffer, sizeof(buffer),dat);
    fgets(buffer, sizeof(buffer),dat);

    while(fscanf(dat," %19s %19s %d",name,lastN,&godina) == 3){
        insertAfter(name,lastN,godina,&Head);
    }

    fclose(dat);
    
    printf("\nLista procitana iz datoteke: \n");
    printList(&Head);

    deleteList(&Head);


    return 0;
}