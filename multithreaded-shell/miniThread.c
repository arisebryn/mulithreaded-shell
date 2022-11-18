#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#define USER_BUFFER 1024 
pid_t pid, wpid; // Process and Wait ID variables
char user_input[USER_BUFFER]; // Buffer for storing user input
char* argv[200]; 
int argc ;
char* path= "/bin/"; // Path variable for bin folder
char file_path[50];
int status; // Status variable for each process
int thread_count = 0; // Counter variable for each thread created

/* The threading function creates the processes after verifying user input */
void *threading(void *arg) {
    while(1) {
        printf("Enter a command for the shell to execute ");  // Ask user to enter command

        // If command exceeds buffer limit, end operation
        if(!fgets(user_input, USER_BUFFER, stdin)) {
            break;  
        }

        size_t length = strlen(user_input); // Store length of user input
        
        // If user's input is 0, end operation
        if(length == 0) {
            break; 
        }

        // If user enters new line as last character, change it to \0
        if (user_input[length - 1] == '\n') {
            user_input[length - 1] = '\0';
        }

        // Using a token, split the command using spaces
        char *string_token;
        string_token = strtok(user_input," ");
        int argc=0;
        if(string_token == NULL) {
            continue;
        }
        while(string_token != NULL) {
            argv[argc] = string_token;
            string_token = strtok(NULL," ");
            argc++;
        }
        argv[argc] = NULL;

        strcpy(file_path, path);  // Assign path to file_path
        strcat(file_path, argv[0]); // Conctanate command and file path

        // Create child process if the command exists in the bin
        if (access(file_path, F_OK) == 0) {
            pid = fork();
            if (pid == 0) { // Child process
                if (execv(file_path, argv) == -1) {
                    perror("Child proccess end");
                }
                exit(EXIT_FAILURE);
            }
            else if (pid > 0) { // Parent process
                // Wait for the status of the child pid
                wpid = waitpid(pid, &status, WUNTRACED);
                while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
                    // Keep waiting if the child process never ended
                    wpid = waitpid(pid, &status, WUNTRACED);
                }
            }
            else {
                perror("Fork Failed");
            }
        }
        else {
            printf("Command is not available in the bin\n"); // The command does not exist in the bin
        }
        thread_count++; // Update when a thread has completed the process
        printf("Thread %d complete\n", thread_count);
    }
}

/* The main method creates a thread to implement the a process upon each command input */
int main() {
    pthread_t tid; // Thread ID
    pthread_attr_t attr; // Default attribute
    
    pthread_attr_init(&attr); // Initialize the attribute argument
    pthread_create(&tid, &attr, *threading, NULL); // Create the first thread
    
    // If the thread has not been ended, create a new thread
	if(pthread_join(tid, NULL) == 0) {
		pthread_create(&tid, &attr, *threading, NULL);
	}
    pthread_join(tid,NULL); // End the thread
}