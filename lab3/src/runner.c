#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    
    if (pid == 0) {
        // Дочерний процесс
        printf("Child process (PID: %d) will run sequential_min_max\n", getpid());
        
        // Заменяем образ процесса на sequential_min_max с аргументами
        char *args[] = {"./sequential_min_max", "42", "10", NULL};
        execvp(args[0], args);
        
        // Если execvp вернулся, значит ошибка
        perror("execvp failed");
        exit(1);
    } else {
        // Родительский процесс
        printf("Parent process (PID: %d) created child PID: %d\n", getpid(), pid);
        
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child terminated abnormally\n");
        }
    }
    
    return 0;
}
