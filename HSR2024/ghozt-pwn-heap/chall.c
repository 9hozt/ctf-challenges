#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NAME_LEN 16
#define MSG_LEN 24

void ignore_me_init_buffering()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

typedef struct Hero hero;
struct Hero {

    char * stuff_array;
    int stuff_size;
    char name[NAME_LEN];
    char message[MSG_LEN];
    int hp;
    void (* heal )(hero *);
    void (* contact)(hero *, char *);

};

hero *heros[8];
int hero_count;

void delete_hero(int idx)
{
    printf("[-] Removing %s hero.\n", heros[idx]->name);
    free(heros[idx]);
    hero_count--;
}

void heal_hero(hero *h)
{
    h->hp=100;
    printf("Hero %s feels better \n",h->name);
}

void display_hero(hero *h)
{
    printf(" ### Hero stats ###\n\n");
    printf("[+] Hero name: %s\n",h->name);
    printf("[+] Hero Health: %d\n",h->hp);
    printf("[+] Hero stuff:\n%s\n\n",h->stuff_array);
}


void message_hero(hero *h, char *message)
{
    unsigned int message_len = strlen(message);
    if (message_len < 0 || message_len > 24)
    {
        printf("[-] Error with the message\n");
        return;
    }
    memcpy(h->message, message, MSG_LEN);
    printf("[+] Message sent to hero");
}


int get_choice(){

    printf("[+] Enter hero index (0-7): \n");
    int idx;
    scanf("%d",&idx);
    if (idx < 0 || idx > 7){
        printf("[-] Error...\n\n");
        return -1;
    }
    return idx;
}

void create_hero(){

    if ( hero_count >= 8){
        printf("[-] Team is full...\n");
        return;
    }

    hero *h = (hero *)malloc(sizeof(hero));
    int stuff_array_size=0;

    while (stuff_array_size <= 1) {
        printf("Enter the capacity of weapons array: ");
        scanf("%d",&stuff_array_size);
        getchar();
    }

    h->stuff_size = stuff_array_size;
    h->stuff_array= (char *)malloc(stuff_array_size);
    printf("[+] Stuff your hero:  ");
    read(0,h->stuff_array,stuff_array_size);
    printf("Enter Tank ID: ");
    read(0,h->name,16);
    h->hp = 100;
    h->heal = heal_hero;
    h->contact = message_hero;
    memset(h->message,'\0',24);
    heros[hero_count] = h;
    hero_count++;

}

int menu() {

    int choice=0;
    while (choice>6 || choice <1) {
        puts("\n---MENU---");
        puts("1. New Hero");
        puts("2. Fire Hero");
        puts("3. Display Hero stats");
        puts("4. Heal Hero");
        puts("5. Send message to Hero");
        puts("6. Leave");
        printf("\nMake your choice: ");

        scanf("%d",&choice);
        if (choice==6){
            exit(0);
        }
    }

    return choice;

}

int main() {

    ignore_me_init_buffering();
    int herochoice;
    while (1){
        int menu_option = menu();
        switch (menu_option) {

            case 1:
                create_hero();
                break;

            case 2:
                herochoice = get_choice();
                if (herochoice < -1){
                    break;
                } else {

                    delete_hero(herochoice);

                }

                break;

            case 3:

                herochoice = get_choice();
                if (herochoice < -1){
                    break;
                }else {
                    display_hero(heros[herochoice]);

                }
                break;

            case 4:
                herochoice = get_choice();
                if (herochoice < -1){
                    break;
                } else {
                    heros[herochoice]->heal(heros[herochoice]);
                }
                break;
            case 5:
                herochoice = get_choice();
                if (herochoice < -1){
                    break;
                } else {

                    printf("Enter your message: ");
                    char msg[24];
                    scanf("%24s",msg);
                    heros[herochoice]->contact(heros[herochoice], msg);

                }
                break;

        }


    }

}
