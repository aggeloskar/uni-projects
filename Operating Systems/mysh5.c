/* Leitourgika Systimata 2017-2018
 * Askisi 2
 * Karagounis Aggelos - 5532
 * karagkouni@ceid.upatras.gr
 */  

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define INPUT_SIZE 128

/* Splits output on the delimiter provided */
void splitter(char *input, const char *delimiter, char **input_array){
	char *temp;
	int i = 0;
	
	temp = strtok(input, " ");
    while(temp != NULL) {
        input_array[i] = temp;
        temp = strtok(NULL, " ");
        i++;
    }
    
    input_array[i] = NULL;
}

/* Trims whitespace bedore and after the input text */
void trimmer(char input[], char clean_input[]){
	char *start = input;
	char *end;
		
	while(isspace(*start)){
		start++;
	}	
	
	if(*start != '\0'){
		end = start + strlen(start) - 1;
		while (end > start && isspace(*end) != 0){
			end--;
		}
	}

	*(end+1) = '\0';
	strncpy(clean_input, input, strlen(start)+1);
}

/* Run program provided without arguements */
void run(char input[]) {
    pid_t pid;
    char clean_input[INPUT_SIZE];
    char *input_array[INPUT_SIZE];
    char *temp;
    char delimiter[INPUT_SIZE/2] = " ";
    char buffer[INPUT_SIZE];
    int i = 0;

    trimmer(input, clean_input);
    splitter(clean_input, delimiter, input_array);

    execvp(input_array[0], input_array);

    perror("Failed"); /* In case of execvp success this isn't reachable */
    exit(1);
}

/* Run proramm with multiple arguments or pipes */
void run_double(char input[]) {
    char *temp;
    char clean_input[INPUT_SIZE];
    char *cmd[2];
    char *cd;
    char *dir;
    int i = 0;
    int p[2];
    int returned_proc;
    pid_t pid1, pid2;

    
    if (!strcmp(input, "exit\n")){	/* Exit the shell */
        printf("Exiting . . .\n");
        exit(0);
    } 
    else if (input[0] == 'c' && input[1] == 'd' && input[2] == ' ') {	/* Chande Directory if input is cd */
        cd = strtok(input, " ");
        dir = strtok(NULL, " ");
        dir[strlen(dir) - 1] = '\0';
        if(chdir(dir)) {
            perror("cd failed");
            exit(1);
        }
    }
    else {
        input[strlen(input) - 1] = '\0';
	    temp = strtok(input, "|");
        while(temp != NULL) { /* Splits input in the delimiter */
            cmd[i] = temp;
            temp = strtok(NULL, "|");
            i++;
            if(i > 2) {
                perror("Maximum 1 pipe");
                exit(1); 
            }
        }

        if(i == 1) { /* If no pipe, run like mysh2 */
            pid1 = fork(); /* Create a child */
            if(pid1 == 0) {
                run(cmd[0]);
            }
            else if(pid1 < 0) {
                perror("Fork error");
                exit(1);
            }
            else { /* Parent waits for child */
                wait(0);
            }
        }
        else { /* Command is piped */
            if(pipe(p) < 0) { 
                perror("Pipe error.");
                exit(1);
            }
            pid1 = fork(); /* Create a child */
            if(pid1 == 0) {
                close(p[0]); 
                dup2(p[1], STDOUT_FILENO); 
                run(cmd[0]);
            }
            else if(pid1 < 0) {
                perror("Fork error");
                exit(1);
            }
            else {
                
                close(p[1]);
                pid2 = fork();

                if(pid2 == 0) {
                    dup2(p[0], STDIN_FILENO);
                    run(cmd[1]);
                }
                else if(pid2 < 0) {
                    perror("Fork error");
                    exit(1);
                }
                else { /* Parents wait for children */
                    waitpid(pid2, NULL, 0);
                    waitpid(pid1, NULL, 0);
                }
            }
        }
    }
}

/* Main function */
int main(int argc, char *argv[]) {
    char input[INPUT_SIZE] = "";
    
    while(1) {
        printf("$");
        if(!fgets(input, sizeof(input), stdin)) {
            perror("Input error");
            exit(1);
        }
        run_double(input);
    }
}
