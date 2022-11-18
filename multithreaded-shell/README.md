# multithreaded-shell
mulitthreaded-shell is a program built in the C programming language that implements an simple, interactive shell using multithreading.

## Installation

Needed dependencies for running the program successfully. This step assumes that you know how to access and use a host VPN.

```
Putty Winscp FortiClient
```

Download and save the following file to a folder on your local disk.

```
miniThread.c
```

Upload this file from local disk to your remote network host using Winscp and FortiClient.

## Usage
Open a terminal in putty.

If needed, navigate to the directory containing your file using:

```
cd <directory name>
```

Run the following commands to compile and run your program.

```c
gcc -pthread miniThread.c -o miniThread
```

```
./miniThread
```

Follow the prompt output by the program in the terminal. Run commands using the multithreaded shell.


![image](https://user-images.githubusercontent.com/62272564/202629215-1e2dbc68-0c8f-4c67-babf-f7d60c9146a5.png)
