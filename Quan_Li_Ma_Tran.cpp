//Bai5: Quan li ma tran
#include <stdio.h>
#include <stdlib.h>

// a. Cap phat bo nho dong
void CapPhat1(int n, int **&a) {
    a = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        a[i] = (int *)malloc(n * sizeof(int));
    }
}

// Hoac co the dung ham tra ve
int **CapPhat2(int n) {
    int **a = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        a[i] = (int *)malloc(n * sizeof(int));
    }
    return a;
}

// b. Giai phóng bo nho
void XoaBN(int n, int **a) {
    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
}

// c. Nhap ma tran
void Nhap(int &n, int **&a) {
    printf("Nhap cap ma tran vuong n: ");
    scanf("%d", &n);
    CapPhat1(n, a);
    printf("Nhap cac phan tu ma tran:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

// d. Xuat ma tran
void Xuat(int n, int **a) {
    printf("Ma tran:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5d", a[i][j]);
        }
        printf("\n");
    }
}

// e. Kiem tra doi xung qua duong cheo phu
int DoiXungPhu(int n, int **a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != a[n - 1 - j][n - 1 - i]) {
                return 0;
            }
        }
    }
    return 1;
}

// f. Liet ke cac hang co tong max
void LietKe(int n, int **a) {
    int max = 0;
    int *tong = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tong[i] = 0;
        for (int j = 0; j < n; j++) {
            tong[i] += a[i][j];
        }
        if (i == 0 || tong[i] > max)
            max = tong[i];
    }

    printf("Cac hang co tong lon nhat = %d:\n", max);
    for (int i = 0; i < n; i++) {
        if (tong[i] == max) {
            for (int j = 0; j < n; j++) {
                printf("%5d", a[i][j]);
            }
            printf("\n");
        }
    }
    free(tong);
}

// g. Menu
int Menu() {
    int chon;
    printf("\n----- MENU -----\n");
    printf("1. Nhap ma tran\n");
    printf("2. Xuat ma tran\n");
    printf("3. Kiem tra doi xung qua duong cheo phu\n");
    printf("4. Liet ke cac hang co tong lon nhat\n");
    printf("5. Thoat\n");
    printf("Chon chuc nang [1-5]: ");
    scanf("%d", &chon);
    return chon;
}

// Ham main
int main() {
    int **a = NULL;
    int n = 0;
    int chon;
    do {
        chon = Menu();
        switch (chon) {
            case 1:
                if (a != NULL)
                    XoaBN(n, a);
                Nhap(n, a);
                break;
            case 2:
                if (a != NULL)
                    Xuat(n, a);
                else
                    printf("Chua co du lieu ma tran!\n");
                break;
            case 3:
                if (a != NULL) {
                    if (DoiXungPhu(n, a))
                        printf("Ma tran doi xung qua duong cheo phu.\n");
                    else
                        printf("Ma tran KHONG doi xung qua duong cheo phu.\n");
                } else {
                    printf("Chua co du lieu ma tran!\n");
                }
                break;
            case 4:
                if (a != NULL)
                    LietKe(n, a);
                else
                    printf("Chua co du lieu ma tran!\n");
                break;
            case 5:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai!\n");
        }
    } while (chon != 5);

    if (a != NULL)
        XoaBN(n, a);

    return 0;
}

