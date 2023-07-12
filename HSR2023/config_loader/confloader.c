#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>


#define MAX_PATH_LEN    64
#define MAX_CONTENT_LEN 4096


	char path[MAX_PATH_LEN];
	char content[MAX_CONTENT_LEN];


void ignore_me_init_buffering() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

void print_banner(){
	puts(" --- Settings console ---\n");
}

void print_menu(){

	puts("\n --- Menu ---\n");
	puts("1 - Check RAM\n");
	puts("2 - Check Integrity\n");
	puts("3 - Push Config\n");
	puts("4 - Load config\n");
    puts("5 - Exit console\n");
    return;
}

int login(){

	int i;
	char input[8];
	char correct_code[8];
	int j = 0;

	memset(correct_code,0, sizeof(correct_code));
	memset(input,0, sizeof(input));

	printf("[+] Generate and send OTP please wait..\n");
	sleep(2);
	printf("[+] Done !\n");
	srand( time( NULL ) );
	for(i = 0; i < 4 ;i++) {
		correct_code[i] = rand() % 26 + 97;
	}
	puts("access code:  ");
	gets(input);

	if (!strcmp(input, correct_code)) {
		printf("[+] Access Granted\n");
		j = 1;
	}
	else{
		puts("[-] Access Denied\n");
		exit(EXIT_FAILURE);
	}
	return j;

}

void check_ram(){
	printf("[+] Checkgin ram...\n");
	sleep(3);
	printf("[+] Done !\n");
	printf("[+] RAM is OK :)\n");
}

void check_integrity(){
	printf("[+] Checkging data integrity ...\n");
	sleep(3);
	printf("[+] All seems fine..\n");
}

int read_config(){

	int f;
	memset(path,'\x00',MAX_PATH_LEN);
	memset(content,'\x00',MAX_CONTENT_LEN);

	printf("[+] File path:\n");
	read(0,path,MAX_PATH_LEN );
	path[strcspn(path, "\n")] = 0;
	f = open(path,O_RDONLY);
	if(f){
		printf("[+] File exists, reading config..\n");
		read(f,content,MAX_CONTENT_LEN -1);
		close(f);
		content[strcspn(content, "\0")] = '\n';
		sleep(2);
		printf("[+] Config stored in memory !\n");
	}
	else{
		printf("[-] Cannot open file..\n");
		return 0;
	}
	return 1;
}

int push_config(){
	printf("[!] Looking for configuration [!]\n");
	sleep(1);
	printf("[+] . . .\n");
	sleep(2);
	printf("[+] Found config file at %s\n",path);
	printf("[+] Sending configuration to remote beacon !\n");
	sleep(3);
	printf("[+] Done !\n");
	return 42
;}


int main(int argc, char *argv[]) {

	int log = 0;
	int k = 0;
	ignore_me_init_buffering();
	print_banner();

	printf("Access restricted - You must log in first\n");
	sleep(1);

	log = login();

	if(log == 0){
		printf("Unauthorized access detected - Exiting\n");
		exit(EXIT_FAILURE);
	}

	while(k != 6){
	    print_menu();
	    printf(">>>");
	    
	    scanf(" %d", &k);
	    fflush(stdin);
	    if(k < 1 || k > 5){
			printf("Unknown action, exiting ... \n");
			exit(EXIT_FAILURE);
	    }
	    switch(k)
	    {
		case 1:
			check_ram();
			break;
		case 2:
			check_integrity();
			break;
		case 3:
			push_config();
			break;
		case 4:
			read_config();
			break;
		case 5:
			exit(EXIT_SUCCESS);
		default: 
			printf("Invalid option..\n");
			break;
	    }

	}
	return 0;

}
