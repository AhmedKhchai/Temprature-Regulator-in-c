
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
int tempGenarator(int lower, int upper,
                            int count)
{
    int i;
    for (i = 0; i < count; i++) {
        int num = (rand() %
        (upper - lower + 1)) + lower;
        return num;
    }
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
        sig.sa_flags = 0;
        sigaction(SIGALRM,&sig,NULL);
        printf("Signal \n");
        alarm(3);
	}
	return 0;
}

int ecouteAlarm(sig, temp_target){
    int lower = 15, upper = 25, count = 1;
    unsigned char result = '0';
    srand(time(0));
    int temp_current = tempGenarator(lower, upper, count);
    if (temp_current == temp_target){
        printf("TEMP_OK \n");
        printf("RESULT: 0 \n");
        toBinary(result);
    }else if (temp_current > temp_target){
        printf("REFROIDIR \n");
        result = '128';
        printf("RESULT: 128 \n");
        toBinary(result);
    }else{
        printf("CHAUFFER \n");
        result = '64';
        printf("RESULT: 64 \n");
        toBinary(result);
    }
	printf("ALARM \n");
    printf("Temp Target %d: \n", temp_target);
    printf("Temp: %d \n", temp_current);
	sigaction(SIGALRM,&sig,NULL);

}
