
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
# define TEMP_OK 0
# define CHAUFFER 64
# define REFROIDIR 128

int tempGenarator(int lower, int upper)
{
    int num;
    return  num = (rand() % (upper - lower + 1)) + lower;
}
void toBinary(unsigned char result){
  int binary[8];
  for(int n = 0; n < 8; n++)
    binary[7-n] = (result >> n) & 1;
  /* print result */
  for(int n = 0; n < 8; n++)
    printf("%d", binary[n]);
  printf("\n");
}

int ecouteAlarm(int, int);

int main(int argc , char **argv){
    int temp_target;
    printf("Quelle est votre temperature preferee ?: \n");
    scanf("%d", &temp_target);
    while(1){
        struct sigaction sig;
        sig.sa_handler = ecouteAlarm(&sig, temp_target);
        sig.sa_flags = 5;
        sigaction(SIGALRM,&sig,NULL);
        printf("Signal \n");
        alarm(1);
	}
	return 0;
}

int ecouteAlarm(sig, temp_target){
    int lower = 15, upper = 25;
    unsigned char result = TEMP_OK;
    srand(time(0));
    int temp_current = tempGenarator(lower, upper);
    int diff = temp_target - temp_current;
    if (temp_current == temp_target){
        printf("TEMP_OK \n");
        int diff = temp_target - temp_current;
        if (abs(diff) == 1){
            result |= 1 << 1;
        }else if( abs(diff) == 2){
            result |= 1 << 0;
        }else{
            result |= 1 << 0;
            result |= 1 << 1;
        }
        // printf("RESULT: 0 \n");
        printf("RESULT: %u ,DIFF: %d\n", result, abs(diff));
        toBinary(result);
    }else if (temp_current > temp_target){
        printf("REFROIDIR \n");
        result = REFROIDIR;
        if (abs(diff) == 1){
            result |= 1 << 1;
        }else if( abs(diff) == 2){
            result |= 1 << 0;
        }else{
            result |= 1 << 0;
            result |= 1 << 1;
        }
        // printf("RESULT: 128 \n");
        printf("RESULT: %u ,DIFF: %d\n", result, abs(diff));
        toBinary(result);
    }else{
        printf("CHAUFFER \n");
        result = CHAUFFER;
        if (abs(diff) == 1){
            result |= 1 << 1;
        }else if( abs(diff) == 2){
            result |= 1 << 0;
        }else{
            result |= 1 << 0;
            result |= 1 << 1;
        }
        // printf("RESULT: 64 \n");
        printf("RESULT: %u ,DIFF: %d\n", result, abs(diff));
        toBinary(result);
    }
	printf("ALARM \n");
    printf("Temp Target %d: \n", temp_target);
    printf("Temp: %d \n", temp_current);
	sigaction(SIGALRM,&sig,NULL);

}
