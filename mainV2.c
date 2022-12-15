#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE_MAX 1000

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}


/* Joueur */
int nomJoueur();
char joueur[255];


/*	life	*/
int life = 8;


/* taille du mot secret*/
int tailleMot();
int taille = 0;


/*	Mot Secret	*/
char motSecret[255];


/*	initialiser Tab Tiree	*/
int initTabTir();
int afficheTabTir();
char tabTir[255];


/*	aquisition d'un caractère	*/
char caractere();
char c;
 

/*	test caractère*/
int testLettre();
int indiceTaille = 0;


/*	dessin du dessinPendu	*/
int dessinPendu();
int corde = 0;


int letteNonTrouvee();


int comparaison();
int comp;


int win();
int perdu();

/*	Lire Fichier	*/
char tabMot[5000000][100];

int lireFichier();
int ligne=0, lettreMot=0;

int initRand();
int choixligne;

int fonctionMotSecret();

/******************************************************************************/

int main(int argc, char const *argv[])
{
	nomJoueur();
	srand(time(NULL));

	lireFichier();
    initRand();
    fonctionMotSecret();

	tailleMot();
	initTabTir();


  

	while(life != 0 && taille != comp) // on crée un boucle while 
	{

		afficheTabTir();
		caractere();
		testLettre();
		letteNonTrouvee();
		dessinPendu();
		comparaison();
		
	}
	perdu();
	win();
	return 0;
}

/******************************************************************************/

int nomJoueur()			
{
	printf("Non du joueur? ");
	scanf("%254s",joueur);
	printf("\nBienvenue %s\n",joueur);

	printf("Tu as 8 vie.\nQue la partie commence.\n\n");
	
}
/*	demande le nom du joueur,
 * 	puis je crée une chaine pour stocker le nom,
 *	"scanf" permet de creer un char défini ici 255.
 */

/*******************************************************************************/

int initTabTir()
{
	for (int i = 0; i < strlen(motSecret); ++i)
	{
		tabTir[i] = '_';
		
	}
	tabTir[strlen(motSecret)] = '\0';
}
/* initialisation du tableau 
 * affiche '_' pour chaque lettre
 */

/*******************************************************************************/

int tailleMot()
{
	for(int i = 0; i < strlen(motSecret); i++)
	{
		taille++;
	}
	
}
/* On parcourt le mot avec strlen 
 * pour chaque lettre on augmente la taille du mot secret
*/

/*******************************************************************************/
char caractere()
{
	printf("\nEntrer une lettre: ");
	viderBuffer();
	c = getchar();
}
/* getchar met le jeu en pause 
 * demande un caractère au joueur
 */

/******************************************************************************/

int testLettre()
{
	int lettreTrouve = 0;

	for (int i = 0; i < strlen(motSecret); ++i)
	{
		if(c == motSecret[i])
		{
			tabTir[i] = c;
			lettreTrouve = 1;
			
		}
				
	}
	return lettreTrouve;
}
/* On teste la lettre 
 * création du tableau on va tester la lettre obtenue dans la fonction caractère()
 * on teste la lettre pour chaque lettre du mot secret
 * on utilise lettreTrouve pour informer si on a trouvé une lettre dans le mot secret
 */

/********************************************************************************/

int afficheTabTir()
{
	printf("Le mot secret est: %s\n", tabTir);
}
/* phrase pour afficher le mot secret avec des tirées
 *
 */
/********************************************************************************/

int letteNonTrouvee()
{
	if (testLettre() == 0)
	{
		life--;
		corde++;
		printf("Dommage, la lettre: %c n'est pas dans le mot.\n", c );
		printf("Il vous reste %d vie.\n",life );

	}
}
/* grâce a lettreTrouve qui est égal à 0 ou 1
 * si on n'a trouvé aucune lettre dans le mot secret
 * alors on enlève une vie au joueur et on affiche du texte
 */

/********************************************************************************/


int comparaison()
{
	comp=0;	
	for (int i = 0; i < strlen(motSecret); ++i)
	{
		
		if (motSecret[i] == tabTir[i])
		{
			comp++;
		}	
		
	}
	
}
/* on compare le tableau de motSecret et la tabTir
 *
 */
/*******************************************************************************/

int win()
{
	if (comp == taille)
	{
		printf("Le mot secret est: %s\n", tabTir);
		printf("Félicitation\n");
	}
}
/* Affiche félicitations
 *
*/

/*******************************************************************************/

int lireFichier()
{
    FILE* fichier = NULL;
    char chaine[TAILLE_MAX] = "";

    fichier = fopen("words.txt", "r");

	if (fichier != NULL)
    {
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
			
            while(chaine[lettreMot] != '\0' && chaine[lettreMot] != '\n')
            {
                tabMot[ligne][lettreMot] = chaine[lettreMot];
                lettreMot++;
                
            }
            tabMot[ligne][lettreMot] = '\0';
            ligne++;
            lettreMot=0;
        }
        fclose(fichier);
        
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }

}

int initRand()
{
    choixligne = (rand() % ligne);
}

int fonctionMotSecret()
{
    int j = 0;
    char c = tabMot[choixligne][j];

        while(c != '\0')
        {
            
            motSecret[j] = c;
            j++;
            c = tabMot[choixligne][j];
        }
        motSecret[j] = '\0';  
}

/*******************************************************************************/

int perdu()
{
	if (life == 0)
	{
		printf("\nVous avez perdu.\n");
		printf(" _____ \n");
		printf("|     |\n");
		printf("| x x |\n");
		printf("|     |\n");
		printf("| --- |\n");
		printf("|_____|\n");
	}
}
/* si le nombre de vie arrive a 0 
 * alors on affiche du text
 */

/********************************************************************************/

int dessinPendu()
{
	if (corde == 1)
	{
		printf("               \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
	}

	if (corde == 2)
	{
		printf("  _______      \n");
        printf(" |       |     \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
	}

	if (corde == 3)
	{
		printf("  _______      \n");
        printf(" |       |     \n");
        printf(" |       _     \n");
        printf(" |      / \\   \n");
        printf(" |      \\_/   \n");
        printf(" |      _|_    \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
        printf(" |             \n");
	}

	if (corde == 4)
	{
		printf("  _______      \n");
        printf(" |       |     \n");
        printf(" |       _     \n");
        printf(" |      / \\   \n");
        printf(" |      \\_/   \n");
        printf(" |      _|_    \n");
        printf(" |      | |    \n");
        printf(" |      |_|    \n");
        printf(" |       ^     \n");
        printf(" |             \n");
        printf(" |             \n");
	}

	if (corde == 5)
	{
		printf("  _______      \n");
        printf(" |       |     \n");
        printf(" |       _     \n");
        printf(" |      / \\   \n");
        printf(" |      \\_/   \n");
        printf(" |      _|_    \n");
        printf(" |     /| |    \n");
        printf(" |    / |_|    \n");
        printf(" |       ^     \n");
        printf(" |             \n");
        printf(" |             \n");
	}

	if (corde == 6)
	{
		printf("  _______      \n");
        printf(" |       |     \n");
        printf(" |       _     \n");
        printf(" |      / \\   \n");
        printf(" |      \\_/   \n");
        printf(" |      _|_    \n");
        printf(" |     /| |\\  \n");
        printf(" |    / |_| \\ \n");
        printf(" |       ^     \n");
        printf(" |             \n");
        printf(" |             \n");
	}

	if (corde == 7)
	{
		printf("  _______      \n");
        printf(" |       |     \n");
        printf(" |       _     \n");
        printf(" |      / \\   \n");
        printf(" |      \\_/   \n");
        printf(" |      _|_    \n");
        printf(" |     /| |\\  \n");
        printf(" |    / |_| \\ \n");
        printf(" |       ^     \n");
        printf(" |      /      \n");
        printf(" |     /       \n");
	}

	if (corde == 8)
	{
		printf("  _______      \n");
        printf(" |       |     \n");
        printf(" |       _     \n");
        printf(" |      / \\   \n");
        printf(" |      \\_/   \n");
        printf(" |      _|_    \n");
        printf(" |     /| |\\  \n");
        printf(" |    / |_| \\ \n");
        printf(" |       ^     \n");
        printf(" |      / \\   \n");
        printf(" |     /   \\  \n");
	}
}
/* on dessine les différentes phases du pendu
 *
 */
/*******************************************************************************/
