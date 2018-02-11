#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//Constantes
#define LONGUEUR_TABLE 40
#define LARGUEUR_TABLE 20
#define VITESSEDASE 400     //vitesse de déplacement, de base, du serpent
#define TAILLEMAX 20       //taille maximale du serpent
#define GAUCHE 1
#define DROITE 2
#define BAS 3
#define HAUT 4


//Types structurés

typedef struct snake{
                        int x;
                        int y;
                        int sens;
                        char carac;
                        }snake;

typedef struct objet{
                        int x;
                        int y;
                        char carac;
                        }objet;

//Type énuméré

enum bool{true,false};

//Prototypes
void init_table(char table[LARGUEUR_TABLE][LONGUEUR_TABLE]);
void affiche_table(char table[LARGUEUR_TABLE][LONGUEUR_TABLE],int score);
void init_snake(snake serpent[TAILLEMAX],char table[LARGUEUR_TABLE][LONGUEUR_TABLE],int taille);
void place_objet(objet *pomme,char table[LARGUEUR_TABLE][LONGUEUR_TABLE],snake serpent[TAILLEMAX],int taille);
void deplacement(snake serpent[TAILLEMAX],char table[LARGUEUR_TABLE][LONGUEUR_TABLE],int taille,int vitesse);
enum bool mange(snake serpent[TAILLEMAX],objet pomme,int *taille,int *vitesse);
enum bool morsure(snake serpent[TAILLEMAX],int taille);
void acceuil();

//Programme Principale
int main()
{
    char table[LARGUEUR_TABLE][LONGUEUR_TABLE];     //tableau du plateau de jeu
    snake serpent[TAILLEMAX];                       //tableau qui contient les information de chaque partie du serpent
    objet pomme;
    int taille=4;                                   //taille du serpent
    int vitesse=VITESSEDASE;                        //vitesse de déplacement du serpent
    int score=0;



    srand (time(NULL));
    acceuil();
    init_table(table);
    init_snake(serpent,table,taille);
    place_objet(&pomme,table,serpent,taille);
    affiche_table(table,score);

    do{
        //si on presse une touche directionnele
        if (GetAsyncKeyState(VK_LEFT)){
                if (serpent[0].sens!=DROITE)
                serpent[0].sens=GAUCHE;
            }
            else if (GetAsyncKeyState(VK_RIGHT)){
                if (serpent[0].sens!=GAUCHE)
                serpent[0].sens=DROITE;
            }
            else if (GetAsyncKeyState(VK_UP)){
                if (serpent[0].sens!=BAS)
                serpent[0].sens=HAUT;
            }
            else if(GetAsyncKeyState(VK_DOWN)){
                if (serpent[0].sens!=HAUT)
                serpent[0].sens=BAS;
            }

                if (mange(serpent,pomme,&taille,&vitesse)==true){     //si une pomme est manger on en replace une
                    place_objet(&pomme,table,serpent,taille);
                    score=score+1;
                }
                deplacement(serpent,table,taille,vitesse);      //on déplace le serpent

                //on réaffiche le plateau
                affiche_table(table,score);


        //Tant que la tête ne touche pas les côtés ou le corps
        }while( (serpent[0].x!=LARGUEUR_TABLE-1)&&(serpent[0].y!=LONGUEUR_TABLE-1)&&(serpent[0].x!=0)&&(serpent[0].y!=0)&& (morsure(serpent,taille)==false) );


        printf("Partie Terminer !!!\n");
        printf("Votre score est de: %d points\n",score);
        system("pause");

    return 0;
}

//Fonction qui vérifie si le serpent se mord la queue
enum bool morsure(snake serpent[TAILLEMAX],int taille){

    int i=0,test=false;

    for (i=1;i<taille;i++){

        //si les coordonnées de la tête coorespondes a une partie du corps
        if ( (serpent[0].x==serpent[i].x)&&(serpent[0].y==serpent[i].y) ){
            test=true;
        }
    }
    return test;
}

//Fonction qui vérifie si le serpent mange une pomme et qui l'agrandit si c'est le cas
enum bool mange(snake serpent[TAILLEMAX],objet pomme,int *taille,int *vitesse){

    if( (serpent[0].x==pomme.x)&&(serpent[0].y==pomme.y) ){
            if (*taille!=TAILLEMAX){
                *taille=*taille+1;
                serpent[*taille].carac=' ';
                serpent[*taille-1].carac='X';
            }else{          //si on atteint la taille maximale du serpent on augmente la vitesse
                if (*vitesse>50){
                        *vitesse=*vitesse-35;
                }



            }


        return true;
    }else{
        return false;
    }
}

//Procédure de déplacement du serpent
void deplacement(snake serpent[TAILLEMAX],char table[LARGUEUR_TABLE][LONGUEUR_TABLE],int taille,int vitesse){

    int i=0;

        Sleep(vitesse);
        //chaque partie du serpent prend les coordonnées de la partie précédante
        for (i=taille;i>=1;i--){
            serpent[i].x=serpent[i-1].x;
            serpent[i].y=serpent[i-1].y;

        }

        //En fonction du sens, la tête du serpent se déplace de 1
        if (serpent[0].sens==BAS){
                    serpent[0].x=serpent[0].x+1;
        }else if (serpent[0].sens==HAUT){
                    serpent[0].x=serpent[0].x-1;
        }else if (serpent[0].sens==DROITE){
                    serpent[0].y=serpent[0].y+1;
        }else if (serpent[0].sens==GAUCHE){
                    serpent[0].y=serpent[0].y-1;
        }

        //On replace le serpent sur le plateau
        for (i=0;i<=taille;i++){
                table[serpent[i].x][serpent[i].y]=serpent[i].carac;
        }

        //on efface l'écran
        system("cls");

}

//Procédure qui initialise le plateau de jeu
void init_table(char table[LARGUEUR_TABLE][LONGUEUR_TABLE]){

    int x=0,y=0;

    //Pour les 2 côtés
    for(x=0;x<LARGUEUR_TABLE;x++){
        table[x][0]='|';
        table[x][LONGUEUR_TABLE-1]='|';
        }

    //Pour le haut et le bas
    for(y=0;y<LONGUEUR_TABLE;y++){
        table[0][y]='-';
        table[LARGUEUR_TABLE-1][y]='-';
        }

    //Pour l'intérieur
    for(x=1;x<LARGUEUR_TABLE-1;x++){
        for(y=1;y<LONGUEUR_TABLE-1;y++){
        table[x][y]=' ';
        }
    }
}

//Procédure qui initialise le serpent
void init_snake(snake serpent[TAILLEMAX],char table[LARGUEUR_TABLE][LONGUEUR_TABLE],int taille){

    int i=0;

        //initialisation de la tête et placement sur le plateau
        serpent[i].x=10;
        serpent[i].y=10;
        serpent[i].carac='Y';
        serpent[i].sens=BAS;
        table[serpent[i].x][serpent[i].y]=serpent[i].carac;

        //initialisation du corps et placement sur le plateau
        for (i=1;i<=taille;i++){
            serpent[i].x=serpent[i-1].x-1;
            serpent[i].y=serpent[i-1].y;
            serpent[i].carac='X';
            serpent[taille].carac=' ';
            table[serpent[i].x][serpent[i].y]=serpent[i].carac;
        }

}

//Procédure de placement d'une pomme
void place_objet(objet *pomme,char table[LARGUEUR_TABLE][LONGUEUR_TABLE],snake serpent[TAILLEMAX],int taille){

    int i=0;

    //initialisation des coordonnées de la pomme
    for (i=0;i<=taille;i++){
        do{
            pomme->x=rand()%(LARGUEUR_TABLE-2)+1;;
            pomme->y=rand()%(LONGUEUR_TABLE-2)+1;;
            pomme->carac='o';
        }while ((pomme->x==serpent[i].x)&&(pomme->y==serpent[i].y));    //différent des coordonnées du serpent
    }

        //placement sur le plateau
        table[pomme->x][pomme->y]=pomme->carac;
}

//Procédure d'affichage du tableau
void affiche_table(char table[LARGUEUR_TABLE][LONGUEUR_TABLE],int score){

    int i,j;

    printf("Jeu du serpent\n");
    for(i=0; i<LARGUEUR_TABLE; i++)
	{
		for(j=0; j<LONGUEUR_TABLE; j++)
		{
			printf("%c", table[i][j]);
		}
		printf("\n");
	}
	printf("Pts: %d\n",score);
}

void acceuil(){
    printf("Bienvenue dans le jeu du Serpent.\n\n");
    printf("Utilisez les touche directionneles pour vous deplacez.\n");
    printf("Et manger les pommes pour marquer des points.\n\n");
    printf("Bonne Chance !\n\n");
    system("pause");
    system("cls");
}




