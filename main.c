
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#define TEMP_OK 0
#define CHAUFFER 64
#define REFROIDIR 1 << 7

struct sigaction sig;
int temp_target;
int tempGenarator(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}
void toBinary(unsigned char result)
{
    int binary[8];
    for (int n = 0; n < 8; n++)
        binary[7 - n] = (result >> n) & 1;
    for (int n = 0; n < 8; n++)
        printf("%d", binary[n]);
    printf("\n");
}
unsigned char setPower(unsigned char result, int diff)
{
    if (abs(diff) == 1)
    {
        result |= 1 << 1;
    }
    else if (abs(diff) == 2)
    {
        result |= 1 << 0;
    }
    else if (abs(diff) > 2)
    {
        result |= 1 << 0;
        result |= 1 << 1;
    }
    return result;
}
int ecouteAlarm(sig)
{
    int lower = 15, upper = 25;
    unsigned char result = TEMP_OK;
    srand(time(0));
    int temp_current = tempGenarator(lower, upper);
    int diff = temp_target - temp_current;
    if (temp_current == temp_target)
    {
        printf("TEMP_OK \n");
        result = setPower(result, diff);
        printf("RESULT: %u ,DIFF: %d\n", result, abs(diff));
        toBinary(result);
    }
    else if (temp_current > temp_target)
    {
        printf("REFROIDIR \n");
        result = REFROIDIR;
        result = setPower(result, diff);
        printf("RESULT: %u ,DIFF: %d\n", result, abs(diff));
        toBinary(result);
    }
    else
    {
        printf("CHAUFFER \n");
        result = CHAUFFER;
        result = setPower(result, diff);
        printf("RESULT: %u ,DIFF: %d\n", result, abs(diff));
        toBinary(result);
    }
    printf("ALARM \n");
    printf("Temp Target %d: \n", temp_target);
    printf("Temp: %d \n", temp_current);
    alarm(2);
}

int main(int argc, char **argv)
{
    printf("Quelle est votre temperature preferee ?: \n");
    scanf("%d", &temp_target);
    sig.sa_handler = &ecouteAlarm;
    sig.sa_flags = 0;
    sigaction(SIGALRM, &sig, NULL);
    alarm(2);
    while (1)
    {
    }
    return 0;
}
