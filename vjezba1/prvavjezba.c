#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxbod 100

typedef struct student{

    char ime[50];
    char prezime[50];
    int bodovi;
}Student;

float RelBod(int); // Funkcija za izracun relativnih bodova
int Ispis(Student*,int); // Funkcija za ispis konacne lista

int main(){

    int i;
    int brojac=0;
    Student* stud;
    FILE* fp;
    char buffer[100];

    fp=fopen("lista.txt","r");

    if(fp==NULL){

        printf("Doslo je do greske pri otvaranju datoteke!");
        return -1;
    }
    
    while(fgets(buffer,100,fp)!=NULL){

        brojac++;
    }

   // printf("%d",brojac); //-->Provjera petlje
    
    rewind(fp);

    stud=(Student*)malloc(sizeof(Student)*brojac);

    for(i=0;i<brojac;i++){

        fscanf(fp," %s %s %d",stud[i].ime, stud[i].prezime, &stud[i].bodovi);
    }
    
    // for(i=0;i<brojac;i++) //-->Provjera upisa
    // printf("%s %s %d   ",stud[i].ime, stud[i].prezime, stud[i].bodovi);
    
    Ispis(stud,brojac);

    return 0;
}

float RelBod(int x){

    if(x>=0 && x<=100){
        return ((float)x/maxbod*100);
    }
    else return -2;

}

int Ispis(Student* stud,int br){

    int i;

    for(i=0;i<br;i++){

        printf("%s %s %d %0.2f\n",stud[i].ime, stud[i].prezime, stud[i].bodovi, RelBod(stud[i].bodovi));
    }


}