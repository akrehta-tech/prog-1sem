#include <stdio.h>

void countletter(const char symbs[], int inds[]){
    for (int i = 0; symbs[i] != '\0'; i++) {
        unsigned char index = symbs[i];
        inds[index]++;
    }
    
}

int output(const char symbs[], const int inds[]){
    int uniq = 0;

    for (int i = 0; symbs[i] != '\0'; i++) {
        unsigned char index = symbs[i];

        if (inds[index] == 1){
            printf("%c ", symbs[i]);
            uniq++;
        }
    }
    return uniq;
}

int main(){
    char s[] =  "programming";
    int counts[256] = {0};
    int result = 0;
    countletter(s, counts);
    printf("Уникальные буквы:\n");
    result = output(s, counts);
    printf("\nКоличество: %d", result);
    return 0;
}
