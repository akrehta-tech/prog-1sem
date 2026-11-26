#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **reserve(int n) {
        int **m = malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++) m[i] = malloc(n * sizeof(int));
        return m;
}

void release(int **m, int n) {
        for (int i = 0; i < n; i++) free(m[i]);
        free(m);
}

void copy(int **orig, int **parody, int n) {
        for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                        parody[i][j] = orig[i][j];
}

void filling(int **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = rand() % 10;
}

void rot_formula(int **orig, int **parody, int n) {
        for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                        parody[j][n - 1 - i] = orig[i][j];
}

void rot_tr_otr(int **m, int n) {
        for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++) {
                        int t = m[i][j]; m[i][j] = m[j][i]; m[j][i] = t;
                }
        for (int i = 0; i < n; i++)
                for (int j = 0; j < n / 2; j++) {
                        int t = m[i][j]; m[i][j] = m[i][n - 1 - j]; m[i][n - 1 - j] = t;
                }
}

void print_mat(int **m, int n) {
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) printf("%3d", m[i][j]);
                printf("\n");
        }
}

int main(void) {
        int n, ang;
        printf("размер и угол: ");
        if (scanf("%d %d", &n, &ang) != 2 || n <= 0 || (ang != 90 && ang != 180 && ang != 270)) {
                printf("Ошибка ввода\n");
                return 1;
        }

        
        int **orig = reserve(n);
        int **temp = reserve(n);
        int **res = reserve(n);

        srand((unsigned int)time(NULL));
        filling(orig, n);

        printf("Исходная:\n");
        print_mat(orig, n);
        printf("\n");

        int steps = ang / 90;

        copy(orig, res, n);
        for (int s = 0; s < steps; s++) {
                rot_formula(res, temp, n);
                copy(temp, res, n);
        }
        printf("Поворот по формуле:\n");
        print_mat(res, n);
        printf("\n");

        copy(orig, temp, n);
        for (int s = 0; s < steps; s++) rot_tr_otr(temp, n);
        printf("Поворот путем трансп+отражения:\n");
        print_mat(temp, n);

        int coinc = 1;
        for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                        if (res[i][j] != temp[i][j]) coinc = 0;}

        printf(coinc ? "Совпадение\n" : "Не совпадение\n");
        release(orig, n);
        release(temp, n);
        release(res, n);
        return 0;
}
