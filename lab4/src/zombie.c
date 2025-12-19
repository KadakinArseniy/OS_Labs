#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    printf("=== Демонстрация зомби-процессов ===\n");
    
    // Создаём дочерний процесс
    pid = fork();
    
    if (pid == 0) {
        // Дочерний процесс
        printf("Дочерний процесс: PID=%d, PPID=%d\n", getpid(), getppid());
        printf("Дочерний процесс завершается через 2 секунды...\n");
        sleep(2);
        printf("Дочерний процесс завершён! Статус выхода: 42\n");
        exit(42);
        
    } else if (pid > 0) {
        // Родительский процесс
        printf("Родительский процесс: PID=%d, создал дочерний PID=%d\n", getpid(), pid);
        printf("\nТеперь дочерний процесс завершился, но родитель НЕ вызвал wait().\n");
        printf("Дочерний процесс стал ЗОМБИ (в состоянии 'defunct').\n");
        printf("Проверить можно командой: ps aux | grep %d\n", pid);
printf("\nРодитель спит 10 секунд...\n");
        for (int i = 1; i <= 10; i++) {
            printf("%d... ", i);
            fflush(stdout);
            sleep(1);
        }
        
        printf("\n\nТеперь родитель вызывает waitpid()...\n");
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Родитель получил статус завершения дочернего процесса: %d\n", WEXITSTATUS(status));
        }
        
        printf("Зомби-процесс уничтожен!\n");
        
    } else {
        perror("fork failed");
        return 1;
    }
    
    return 0;
}
