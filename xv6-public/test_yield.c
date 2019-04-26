#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[]){
	int pid;
	pid = fork();

	while(1){
//		pid = fork();

		if(pid < 0){
			printf(1, "E : Fork Failed!\n");
			exit();
		}
		else if(pid == 0){		// child process
			//callyield();
			yield();
			printf(1, "Child\n");
			//callyield();
			yield();
		}
		else{					// parent process
			printf(1, "Parent\n");
//			callyield();
			//wait();
			//callyield();
			yield();
		}
//		callyield();
	}

	exit();
}
