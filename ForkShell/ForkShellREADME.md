
Minishell in C 

In this project, we were taked with creating a simple shell program that uses the fork() API to process commands entered by the user in child processes created by fork(). The parent function is used to continuously ask the user for new commands. 


## Authors

Zachary Essoh

Arielle Gilmore
## API Reference

#### Get all items

```http
  fork()
```

```http
  execv()
```

#### fork()
Parameters:

child_pid == 0 - indicates if the program is inside the child process of the fork.

child_pid > 0 - indicates if the program is inside of the parent process of the fork.

Function:

breaks a single process into 2 separate processes and creates a child process with its own process ID (PID)

###  execv()
Parameters:

file_path - specifies the location of the commands within the operating system.

arg_size - specifies the the length of the command the user is allowed to enter.

Function:

replaces the current process image with a new process image specified by a given path. In our case the path we needed to use was /bin/. So the child process image gets replaced with the user entered command that is in the bin folder, then the command is executed by the child process. 


## Deployment

To run this program first cd into the directory of the file. 
```bash
  cd file directory location
```
In my case the file is located on the desktop
```bash
  cd Desktop
```
Once in the proper directory type 
```bash
  gcc AZminishell.c -o AZminishell
```
to compile the program.

To execute the program type
```bash
  ./AZminishell
```

To exit the program press
```bash
  ctrl c 
```
## Demo

## A sample deployment of the program is given below
![image](https://user-images.githubusercontent.com/78782929/202630461-540178cb-05c3-4667-8676-612bebfd0570.png)


## Screenshots

##In this example, the ping command is executed
![image](https://user-images.githubusercontent.com/78782929/202630573-aa734cb8-cb24-4005-95e6-746c50ae7eae.png)

##In this example, a new directory is created using the mkdir command
![image](https://user-images.githubusercontent.com/78782929/202630674-19a6e23e-1b8a-4046-9d79-2c98a352ebd5.png)

##In this eample the location of the newly created directory is shown
![image](https://user-images.githubusercontent.com/78782929/202630741-b61d6094-cdbf-49f3-86b7-d5385b34947b.png)
