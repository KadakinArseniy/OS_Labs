#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

volatile sig_atomic_t timeout = 0;

void handler(int sig) {
    printf("ALARM! Timeout reached\n");
    timeout = 1;
}

int main() {
    signal(SIGALRM, handler);
    
    // Устанавливаем таймаут 1 секунда
    alarm(1);
    
    printf("Starting long operation...\n");
    
    // Имитируем долгую работу
    for (int i = 0; i < 10; i++) {
        if (timeout) {
            printf("Breaking due to timeout\n");
            break;
        }
        printf("Working... %d\n", i);
        sleep(1); // 1 секунда задержки
    }
    
    // Отключаем alarm
    alarm(0);
    
    printf("Done\n");
    return 0;
}
