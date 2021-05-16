#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iso646.h> 
#include <stdbool.h>
#include <conio.h>
#include<windows.h>

//les constante:
#define MAX_PILE 10
#define MAX_FILE 6

//controle la position d'affichage:
COORD xy = {0, 0};
void gotoxy (int x, int y)
{
        xy.X = x; xy.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

//structure pile:
typedef struct pile
{
    int sommet;
    char tab_assiette[MAX_PILE]; //Nom d'asseitte
}pile;

//structure file:
typedef struct file
{
    int queue;
    int tete;
    pile tab_pile[MAX_FILE];
}file;

//creer un pile :
pile *create_pile(void)
{
    pile *p=malloc(sizeof(*p));
    p->sommet=-1;
    return p;
}
void empiler(pile *p , char nom)
{
    if (p->sommet>=MAX_PILE)
        return EXIT_FAILURE;
    p->sommet++;
    p->tab_assiette[p->sommet]=nom;
}
char depiler(pile *p )
{
    if(p->sommet==-1)
        return EXIT_FAILURE;
    char nom=p->tab_assiette[p->sommet];
    p->sommet--;
    return nom;
}

//creer un file :
file *create_file(void)
{
    file *f=malloc(sizeof(*f));
    f->queue=f->tete=0;
    return f;
}
void enfiler(file *f , pile *p)
{
    if((f->queue+1)%MAX_FILE == f->tete )
        return EXIT_FAILURE;
    f->tab_pile[f->queue] = *p;
    f->queue=(f->queue+1)%MAX_FILE;
}
pile *defiler(file *f)
{
    if (f->queue==f->tete)
        return EXIT_FAILURE;
    pile *pile_defiler = &f->tab_pile[f->tete];
    f->tete = (f->tete+1)%MAX_FILE;
    return pile_defiler;
}

//ajouter un pile d'assiettes:
void ajouer_pile_assiettes(file *f)
{
    int nbr_assiette;
    printf("\n\n\t\t\t-->Enter nombre des assiettes dans ce pile(max=10) : ");scanf("%d",&nbr_assiette);getchar();
    pile *p=create_pile();
    for (int i=0;i<nbr_assiette and i<MAX_PILE ; i++)
    {
        empiler(p,'A'+i);
    }
    
    enfiler(f,p);
}

//retirer un assiette dans une pile:
char retire_assiette(file *f)
{
    if (f->queue == f->tete)
        return EXIT_FAILURE;
    file *aux_file=f;
    while(aux_file->tab_pile[aux_file->tete].sommet ==-1)
        defiler(aux_file);
    return depiler(&aux_file->tab_pile[aux_file->tete]);
}

//fonction d'affichage:
void aff_etat_file(file f)
{
    int i=1;
    int k=1;
    system("cls");
    system("color 03");
    while(f.tete != f.queue)
    {
        while(f.tab_pile[f.tete].sommet<=MAX_PILE and f.tab_pile[f.tete].sommet>-1)
        {
            int j=MAX_PILE-f.tab_pile[f.tete].sommet;
            j=j*2;
            gotoxy(k*7,j);
            printf("%c\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2",depiler(&f.tab_pile[f.tete]));
            //getch();
        }
        gotoxy(k*7,25);
        printf("\tPile %d",i);
        k+=5;
           //getch();
        defiler(&f);i++;

    }
    gotoxy(1,30);
    printf("\t________________________________________________________________________________________________________________________________________________________________________");
    printf("\n\t\t\t\t\t\t\t\t\t\t La file ");
    getch();
}

//fonction de gerer la fonction de la nouveau serveure:
file* passage_serveuse(file *f)
{
    if ((f->queue+1)%MAX_FILE == f->tete)
    {
        int nbr_assiette;
        printf("\n\n\t\t\t-->Entrez nombre des assiettes ramene par la serveure :");scanf("%d",&nbr_assiette);
        file *aux_f=create_file();
        int aux_i=0;
        again:
        while(f->tab_pile[f->tete].sommet+1>=MAX_PILE)
        {
            enfiler(aux_f,defiler(f));
        }
        if((aux_f->queue+1)%MAX_FILE != aux_f->tete)
        {
            char nom;
            if (f->tab_pile[f->tete].tab_assiette[f->tab_pile[f->tete].sommet]>=65 && f->tab_pile[f->tete].tab_assiette[f->tab_pile[f->tete].sommet]<=74)
            {
                    nom=f->tab_pile[f->tete].tab_assiette[f->tab_pile[f->tete].sommet];
            }
            else
            {
                nom=64;
            }
            int k=1;

            for(int i=aux_i ; i<nbr_assiette ; i++)
            {
                if (f->tab_pile[f->tete].sommet+1>=MAX_PILE)
                {
                    aux_i=i;
                    goto again;
                }
                empiler(&f->tab_pile[f->tete],nom+k);k++;                
            }
            while(f->queue != f->tete)
            {
                enfiler(aux_f,defiler(f));
            }
        }
        return aux_f;
    }
    else
    {
        ajouer_pile_assiettes(f);
    }
}

int main()
{
    file *FILE=create_file();
    int choix_mode_tritement=0;
    while(1)
    {
    system("CLS");
    system("color 06");
    printf("\n\n\n\n\n\n\n\n\t\t<!----------------------------------------- Representation graphique d\'une file de vaisselle sale -----------------------------------------!>\n\n\n\n\n");
    printf("\t\t...............................................................................................................................................\n");
    printf("\t\t:    1- Ajouter un pile    :    2- retirer un assiette    :    3- afficher la file    :    4- clore le programme    :    5- passage_serveuse  :\n");
    printf("\t\t:..........................:..............................:...........................:.............................:.........................:\n");

    
    
        int choix;
        printf("\n\n\t\t--> Votre choix :");scanf("%d",&choix);
        switch ((choix))
        {
        case 1: ajouer_pile_assiettes(FILE);
            break;
        case 2: retire_assiette(FILE);aff_etat_file(*FILE);
            break;
        case 3: aff_etat_file(*FILE);
            break;
        case 4: free(FILE ) ;exit(1);
            break;
        case 5: FILE=passage_serveuse(FILE);
            break;
        default: printf("\n\n\t\t\t erreur ! :( \n");getch();
            break;
        }
    }
    gotoxy(50,50); 
    return EXIT_SUCCESS;
}




