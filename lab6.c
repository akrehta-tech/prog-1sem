#include <stdio.h>

double det2x2(double m[2][2]) {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

double det3x3(double m[3][3]) {
    return m[0][0] * m[1][1] * m[2][2] + 
           m[0][1] * m[1][2] * m[2][0] + 
           m[0][2] * m[1][0] * m[2][1] - 
           m[0][2] * m[1][1] * m[2][0] - 
           m[0][0] * m[1][2] * m[2][1] - 
           m[0][1] * m[1][0] * m[2][2];
}

void makeAssistantMatrix(int size, double srcA[][size], double srcB[], double dest[][size], int colIdx) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j == colIdx) {
                dest[i][j] = srcB[i]; 
            } else {
                dest[i][j] = srcA[i][j]; 
            }
        }
    }
}

void solve2x2() {
    double A[2][2], B[2], Tmp[2][2];
    double D, Dx[2];

    printf("\n--- Ввод данных для СЛАУ 2x2 ---\n");
    for (int i = 0; i < 2; i++) {
        printf("Уравнение %d (a%d1 a%d2 b%d): ", i+1, i+1, i+1, i+1);
        scanf("%lf %lf %lf", &A[i][0], &A[i][1], &B[i]);
    }

    D = det2x2(A);

    for (int i = 0; i < 2; i++) {
        makeAssistantMatrix(2, A, B, Tmp, i);
        Dx[i] = det2x2(Tmp);
    }

    printf("D = %.4f, Dx1 = %.4f, Dx2 = %.4f\n", D, Dx[0], Dx[1]);

    if (D != 0) {
        printf("Решение: x1 = %.4f, x2 = %.4f\n", Dx[0] / D, Dx[1] / D);
    } else {
        if (Dx[0] == 0 && Dx[1] == 0) {
            printf("Система имеет бесконечно много решений.\n");
        } else {
            printf("Система не имеет решений.\n");
        }
    }
}

void solve3x3() {
    double A[3][3], B[3], Tmp[3][3];
    double D, Dx[3];

    printf("\n--- Ввод данных для СЛАУ 3x3 ---\n");
    for (int i = 0; i < 3; i++) {
        printf("Уравнение %d (a%d1 a%d2 a%d3 b%d): ", i+1, i+1, i+1, i+1, i+1);
        scanf("%lf %lf %lf %lf", &A[i][0], &A[i][1], &A[i][2], &B[i]);
    }

    D = det3x3(A);

    for (int i = 0; i < 3; i++) {
        makeAssistantMatrix(3, A, B, Tmp, i);
        Dx[i] = det3x3(Tmp);
    }

    printf("D = %.4f, Dx1 = %.4f, Dx2 = %.4f, Dx3 = %.4f\n", D, Dx[0], Dx[1], Dx[2]);

    if (D != 0) {
        printf("Решение: x1 = %.4f, x2 = %.4f, x3 = %.4f\n", Dx[0] / D, Dx[1] / D, Dx[2] / D);
    } else {
        if (Dx[0] == 0 && Dx[1] == 0 && Dx[2] == 0) {
            printf("Система имеет бесконечно много решений.\n");
        } else {
            printf("Система не имеет решений.\n");
        }
    }
}

int main() {
    int choice;
    printf("Выберите размерность СЛАУ:\n1. Система 2x2\n2. Система 3x3\nВаш выбор: ");
    if (scanf("%d", &choice) != 1) return 1;

    if (choice == 1) {
        solve2x2();
    } else if (choice == 2) {
        solve3x3();
    } else {
        printf("Неверный выбор.\n");
    }

    return 0;
}
