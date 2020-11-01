#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 4095
#define NLIGNES 4095

int AC;
int MQ;
int MEMOIRE[4095];
int PC=0;
int MAR[12];
int IR[8];
int IBR[20];
int MBR[40];




void Ibr(){
   for (int i=0;i<20; i++){
    IBR[i]=MBR[i+20]; //IBR un tableau de 20 octet pour stocker l'insruction de droite durant l'éxécution de l'instructin de gauche => ainsi IBR au 20 dernier octet de l'insruction
  }
}


int Pc(){
PC++;
return PC;
}


void setMemoire(int adresse,int val){
    MEMOIRE[adresse]=val;
}

int getMemoire(int adresse){
  return MEMOIRE[adresse];
}

int Mbr(int j){
  for (int i = 0;i<40;i++){
    MBR[i]=MEMOIRE[j];
    j++;
  }  // MBR un tableau de 40 octet pour stocker l'instruction => Memoire va dans le MBR
  return j;
}



void Ir(){
  for (int i=0 ;i<8;i++){
    IR[i]=MBR[i];
  } // Ir un tableau de 8 octet pour stocker l'operande de l'instruction en cours d'execution
}

void Mar(){
  for (int i = 0 ; i<12;i++){
    MAR[i]=MBR[i+8]; // Mar un tableau de 12 octet pour stocker la valeur de l'adresse pc est incrementer
    PC++ ;
  }
}

void etatRegistre(){
  printf("-----Etat Registre-----\n" );
  printf("\n PC : %d ",PC );
  printf("\nMAR :" );
  for(int i =0 ; i<12;i++){
    printf("%d",MAR[i] );
  }
  printf("\nMBR :" );
  for(int i = 0;i < 40;i++)
    {
        printf("%d",MBR[i]);
    }
  printf("\nIR : " );
  for(int i = 0;i < 8;i++)
    {
        printf("%d",IR[i]);
    }
    printf("\nIBR : ");
    for(int i = 0;i < 20;i++)
    {
        printf("%d",IBR[i]);
    }
    printf("AC : %d \n", AC);
}


// fonction pour decoder l'adresse en memoire en sont instruction qui possede des errreurs
/*
void decode(int adresse){
int tab[7];
for(int i = 0 ; i<8; i++){
  tab[i]=MEMOIRE[adresse]; // on compare les 8 octet de l'operande pour savoir quelle instruction réaliser
}

  switch (opcode)
  {
    case 'LOADMQ' :
    AC=MQ ; // execution de LOADMQ, on transfère le contenu de MQ dans l'AC

    case 'LOADMQX' :
    MQ=getMemoire(adresse); // execution du LOADMQ,M(X) on transfère le contenu de la memoire dans le MQ

    case 'STOREMX' :
    setMemoire(adresse,AC);  // execution de STOREMX enregistre le contenu de l'AC dans la memoire
  }

    case 'LOADMX' :
    AC = getMemoire(adresse); // execution de LOADMX transfere le contenu de M(X) dans l'AC


    case 'JUMP' :
    PC=adresse; // permet de mettre le PC = a la l'adresse memoire

    case 'JUMPPLUS' :
    if (AC > 0){
      PC=adresse;
    }

    case 'ADDMX' :
    int adresseval= AC;
    int valeur =getMemoire(adresse); // ajouter la valeur de  l'adresse absolue dans l'AC

    int add = adresseval + valeur ;
    PC = add ;


    int add = adresseval+valeur;
    PC = add ;

    case 'SUBMX' :
    int adresseval = AC ;
    int valeur = getMemoire(adresse); // soustrait le contenu de la memoire de l'AC
    int subb = adresseval - valeur ;
    AC = subb ;


  int subb  = adresseval-valeur ;
  AC = subb ;

  case 'MULMX' :
  int val = getMemoire(adresse);  //multiplie l'emplacement par MQ et met le resultat dans l'AC

  int mul = val * MQ ;
  AC = mul ;

  case 'LSH' :
  adresseval = AC ;
  adresseval = adresseval * 2 ; // multplie AC par 2
  AC = adresseval ;

  case 'RSH' :
  adresseval = AC ;
  adresseval = adresseval / 2 ;
  AC = adresseval ;

}

*/


void execute(int selection, int location);


int main(int argc, char const *argv[]) {

   FILE* fichier = NULL;
   char chaine[TAILLE_MAX] = "";
   fichier = fopen("decode.txt", "r");
   if(fichier == NULL){
     printf("impossible d'ouvrir le fichier \n" );
     exit(EXIT_FAILURE);
   }

  printf("------------Affichage du contenu ligne par ligne du fichier------\n" );
   if(fichier!=NULL){
     char tableau[NLIGNES][1000];
     char ligne[4095];
     int i ;

     while(fgets(ligne, TAILLE_MAX, fichier) != NULL && i < NLIGNES){
       printf("%s", ligne);
      strcpy(tableau[i],ligne);     // on copie dans tableau ligne par ligne le fichier decode
        i++;
     }

     printf("\n" );
     printf("------------Chargement du fichier dans la mémoire---------------\n" );

    // printf("%s\n",tableau[0] );
     void *ptr;
     for(int i = 0 ; i<3; i++){
       ptr=&tableau[i];
       int val = (int)ptr;
       printf("%d\n",val);
       MEMOIRE[i]=val;
     }
     for(int k=0 ; k<1000 ; k++){
       printf("%d\n",MEMOIRE[k]); // methode n'a pas focntionner pour afficher les valeur dans la Memoire
     }
     for(int k=0 ; k<1000 ; k++){

       int j=Mbr(j);
       j=MEMOIRE[PC];
       //IR = j ;
       // 3 premiers instructions doivent permettre de mettre la valeur du PC à 1 de mettre la valeur du PC dans le MAR puis mettre la valeur du MBR dans l'IR
       etatRegistre();
       //decode(IR); // on decode ce qui est dans l'IR
       etatRegistre();
  // on realise la boucle 1000 fois on affiche l'etat de la mmeoire avant et apres avoir realiser les insructions
     }

     fclose(fichier);
   }

  return 0;
}
