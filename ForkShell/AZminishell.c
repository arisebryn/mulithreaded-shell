#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

//Make a Buffer to store user input
#define USER_BUFFER 1024

int main(){
    //Store the user command from the terminal
    char command_input[USER_BUFFER];
    //user command argument Length
    char* arg_size[200]; 
    //Keep track of the number of arguments issued by the user
    int user_args ; 
    //Set the file path of the commands
    char* command_path= "/bin/"; 
    //Set file Path length 
    char file_path[50];

    while(1){
        //Prompt user for command
         printf("Enter a command for the shell to execute ");

         //Exit if the command does not fit prespecified length parameters
        if(!fgets(command_input,USER_BUFFER, stdin)){
            break;  
        }

        size_t length = strlen(command_input);

        if(length == 0){
            break;
        }

        if (command_input[length - 1] == '\n'){
            command_input[length - 1] = '\0'; //Account for new line characters by subtracting 1
        }

        //break the user command up using spaces
        char *command;
        command = strtok(command_input," ");
        int user_args=0;
        if(command == NULL){
            continue;
        }
        while(command!=NULL){
            arg_size[user_args]=command;
            command = strtok(NULL," ");
            user_args++;
        }

        arg_size[user_args]=NULL;

        strcpy(file_path, command_path);  //Assign the command path to file_path
        strcat(file_path, arg_size[0]); //attach the command and file path

        if (access(file_path, F_OK)==0){  //check the command is available 

            pid_t child_pid, working_pid;
            int state;

            child_pid = fork();
            if (child_pid == 0) { //check if inside child process
                if (execv(file_path,arg_size) == -1) {
                  perror("Child proccess exited");
                }
                exit(EXIT_FAILURE);
            }
            else if (child_pid > 0) { // parent process
                working_pid = waitpid(child_pid, &state, WUNTRACED);
                while (!WIFEXITED(state) && !WIFSIGNALED(state)){
                    working_pid = waitpid(child_pid, &state, WUNTRACED);
                }
            }
            else {
                perror("Fork could not be created"); //process id can not be created
            }
        }
        else {
            printf("Command could not be found\n"); //Command is not available 
        }

    }
}
