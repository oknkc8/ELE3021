#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int getcmd(char* buf, FILE *fin, int flag_batch){
	if(!flag_batch)
		printf("prompt> ");
	memset(buf, 0, sizeof(buf)*100);

	if(!fgets(buf, 100, fin)) 
		return 0;
	buf[strlen(buf) - 1] = '\0';
	
	return 1;
}

char** parsecmd(char* cmd){
	char **retcmd = (char**)malloc(sizeof(char*)*10);
	int cnt_retcmd = 0;
	char *tmp_cmd = strtok(cmd, " ");
	while(tmp_cmd != NULL){
		retcmd[cnt_retcmd++] = tmp_cmd;
		tmp_cmd = strtok(NULL, " ");
	}
	retcmd[cnt_retcmd++] = NULL;

	return retcmd;
}

void runcmd(char** pcmd){
	execvp(pcmd[0], pcmd);
	fprintf(stderr, "E : exec %s failed!\n", pcmd[0]);
	
	return;
}

int main(int argc, char* argv[]){
	char buf[100];
	char *cmds[10];
	int w, flag_batch = 0;
	FILE *fo = stdin;

	if(argc > 1){
		fo = fopen(argv[1], "r");
		flag_batch = 1;
	}

	while(getcmd(buf, fo, flag_batch)){
		if(!strcmp(buf, "quit")){
			break;
		}

		if(flag_batch)
			fprintf(stdout, "%s\n", buf);

		char *tmp_cmd = strtok(buf, ";");
		int cnt_cmd = 0, flag = 0;
		while(tmp_cmd != NULL){
			cmds[cnt_cmd++] = tmp_cmd;
			if(strstr(tmp_cmd, "quit") != NULL){
				flag = 1;
				break;
			}
			tmp_cmd = strtok(NULL, ";");
		}
		if(flag){
			fprintf(stderr, "E : invalid command(s)!\n");
			continue;
		}

		int i = 0;
		for(i = 0; i < cnt_cmd; i++){
			char **pcmd = parsecmd(cmds[i]);
			if(fork() == 0)
				runcmd(pcmd);
			wait(&w);
		}
	}

	exit(0);
}
