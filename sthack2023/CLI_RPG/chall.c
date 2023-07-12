#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


struct Hero 
{
    char name[16];
    void (*function)(struct Hero *);
    unsigned int fragments;
};


void ignore_me_init_buffering()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}



void intro(struct Hero *a) 
{
    printf("Bonjour et bienvenue à toi ö grand aventurier %s \n \
    Il te faut ouvrir le coffre de Traedor pour récupérer le tant\
     espéré trésor, pour celà, vous devez vous rendre au donjon en \
     possédant au moins 200 fragments !\n Vous démarez l'aventure avec %u fragments\n\n\n",a->name, a->fragments);
    return;
}

unsigned int addFragment(int a)
{
    return a + 1;
}

unsigned int subFragment(int a)
{
    return a - 1;
}

void search(struct Hero *h)
{
    printf("Vous creusez la terre de vos mains ... cela peut prendre un certain temps ...\n");
    for (int i = 0; i <= 3; i++){
        printf(".");
        sleep(900);
        fflush(stdout);
    }
    printf("Oh ! Vous trouvez un fragment !\n");
    h->fragments = addFragment(h->fragments);
    return;
}




void wander (struct Hero *a)
{
    int choice = 0;
    do {
        puts("\nPendant que vous errer dans les rues de la basse ville, un mendiant affamé vous tends la main\n");
        puts("1 - Passer votre chemin en l'ignorant...\n");
        puts("2 - Lui donner un fragment dans un élan de bonté\n");
        puts("Que décidez vous ?");

    } while ((scanf("%d", &choice) != 1) || (choice < 1) || (choice > 2));

    if (choice == 1){
        printf("Vous ignorez le manant, quelques mètres plus loin, vous trébuchez sur un pavé et vous empallez sur une pique sur laquelle est gravé un étrange mot: KARMA");
        exit(EXIT_FAILURE);
    }
    else {
        puts("Vous donnez un de vos fragment au manant qui vous remercie milles fois et part s'offrir de quoi se nourrir");
        a->fragments = subFragment(a->fragments);
    }
    return;
}

void getFlag()
{
    FILE *f;
    char line[50];
    f =  fopen("flag.txt", "r");
    if (f == NULL)
    {
        puts("Une erreur c'est produite");
        exit(EXIT_FAILURE);
    }
    while (fgets(line, 50, f) != NULL) {
        printf("%s", line);
    }
}

int chest(struct Hero *a)
{
    a->fragments = 0;
    char scream[256];
    puts("\nLe coffre scintille devant vous\n");
    puts("\nVous assemblez les fragments pour fabriquer une clef\n");
    puts("\nVous inserez et tournez la clef, le coffre grince et s'ouvre !\n");
    puts("\n Vous découvrez un drapeau !\n");
    getFlag();
    puts(".... Vous semblez déçu, la colère monte en vous, une envie de hurler vous vient !\n");
    puts("Que voulez vous hurler pour extérioriser votre rage ?\n");
    gets(scream);
    puts("Votre cri résonne dans la salle et s'eteint dans un écho lointain ...\n");
    return 1;
}


int menu(struct Hero *h)
{
    //int choice = 0;
    char choice_input[2048];
    int choice;
    do {
        printf("\n\n---- Traedor ----\n\n");
        printf("1 - Chercher des fragments\n");
        printf("2 - Errer dans les rues de Traedor\n");
        printf("3 - Ouvrir le coffre !\n");
        printf("4 - Abandonner lachement l'affaire ... \n");
        //scanf("%d", &choice);
        fgets(choice_input, sizeof choice_input, stdin);
        choice = atoi(choice_input);
        switch (choice)
        {
        case 1:
            search(h);
            break;
        case 2:
            wander(h);
            break;
        case 3:
            if(h->fragments >= 200){
                chest(h);
            }
            else{
                printf("\nVous n'avez que %u fragments ... \n", h->fragments);
            }
            break;
        case 4:
            exit(EXIT_FAILURE);
        default:
            break;
        }
          printf("\n Bien, vous avez à présent %u fragments, la root est longue...",h->fragments);
    } while (choice != 4);
    return choice;
}

int main()
{
    ignore_me_init_buffering();
    struct Hero h;
    memset(h.name,0,16);
    puts("Bonjour à toi héro, quel est ton nom ?");
    h.function = intro;
    h.fragments = 2;
    read(STDIN_FILENO,h.name,16);
    h.function(&h);
    menu(&h);
    return EXIT_SUCCESS;
}

