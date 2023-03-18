#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./stat <int_array>\n");
        return 1;
    }

    int int_array[1000], i = 0;
    char *token = strtok(argv[1], "$");
    while (token != NULL)
    {
        int_array[i++] = atoi(token);
        token = strtok(NULL, "$");
    }

    for (int j = 1; j <= 3; j++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            if (j == 1)
            {

                printf("PID of Child 1: %d\n", getpid());
                printf("PID of Parent: %d\n", getppid());
            }
            else if (j == 2)
            {

                float avg = 0;
                for (int k = 0; k < i; k++)
                {
                    avg += int_array[k];
                }
                avg /= i;
                printf("PID of Child 2: %d\n", getpid());
                printf("Average of all given integer: %f\n", avg);
            }
            else if (j == 3)
            {

                int max_num = int_array[0];
                for (int k = 1; k < i; k++)
                {
                    if (int_array[k] > max_num)
                    {
                        max_num = int_array[k];
                    }
                }
                printf("PID of Child 3: %d\n", getpid());
                printf("Maximum value: %d\n", max_num);
            }

            return 0;
        }
    }

    for (int j = 0; j < 3; j++)
    {
        wait(NULL);
    }

    return 0;
}
