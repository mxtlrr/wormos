#include "shell/sh.h"

char* commands[] = {
	"help",
	"fetch"
};

char* description[] = {
	"Shows commands that are available",
	"Gets information about the system"
};


void _sh_help(){
	printf("\nAvailable commands:\n");
	for(int i = 0; i != (sizeof(commands)/sizeof(commands[0])); i++){
		printf("\t%s: %o%s%o\n", commands[i], 0xa, description[i], 0xf);
	}
}


void handle_commands(char* buf){
	if(strcmp(buf, commands[0]) == 0) _sh_help();
}
