#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
// Определение переменных для хранения информации о частоте процессора
double cpu_freq;

// Получение информации о частоте процессора
FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
char line[256];
while (fgets(line, sizeof(line), cpuinfo)) {
if (sscanf(line, "cpu MHz\t: %lf", &cpu_freq) == 1) {
break;
}
}
fclose(cpuinfo);

// Вывод информации о частоте процессора
printf("CPU frequency: %.9lf GHz\n", cpu_freq / 1000);

// Вывод информации об авторе программы
printf("Author: Your_Name, Group: Your_Group\n");

// Ожидание работы процесса в течение времени, равного частоте процессора
usleep((useconds_t)(1.0 / cpu_freq * 1e6));

// Создание дочернего процесса
pid_t pid = fork();

if (pid == -1) {
perror("fork");
return 1;
} else if (pid == 0) {
// Код процесса-потомка

// Вычисление суммы бесконечного ряда с задержкой
double sum = 0;
int sign = 1;
for (int i = 1; ; i++) {
sum += sign * 1.0 / i;
printf("Sum: %.9lf\n", sum);
sign = -sign;
usleep(100000); // 100 мс задержка
}
} else {
// Код родительского процесса

// Ожидание завершения работы дочернего процесса
waitpid(pid, NULL, 0);

// Вывод информации об идентификаторах процессов
printf("Parent process ID: %d\n", getpid());
printf("Child process ID: %d\n", pid);
}

return 0;
}
