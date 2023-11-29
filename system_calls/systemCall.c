#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Implementation of fork() system call
pid_t my_fork() {
    pid_t child_pid = fork();
    return child_pid;
}

// Implementation of wait() system call
int my_wait(int *status) {
    pid_t child_pid = wait(status);
    return child_pid;
}

// Implementation of exec() system call
int my_exec(const char *path, char *const argv[]) {
    int ret = execvp(path, argv);
    return ret;
}

// Implementation of exit() system call
void my_exit(int status) {
    exit(status);
}

int main() {
    int status;
    pid_t child_pid;

    // Fork a child process
    child_pid = my_fork();

    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {
        // This is the child process

        // Replace the child process with a new program using exec()
        char *const args[] = {"ls", "-l", NULL};
        my_exec("/bin/ls", args);

        // If exec fails, it will continue here
        perror("Exec failed");
        my_exit(1);
    } else {
        // This is the parent process

        // Wait for the child process to complete
        my_wait(&status);

        printf("Child process completed.\n");
    }

    return 0;
}
