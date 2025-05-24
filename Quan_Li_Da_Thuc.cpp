//Bai4: QUAN LI DA THUC
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node {
    int hs;     // He so
    int mu;     // Luy thua
    Node *Next;
};

// Tao node moi
Node* TaoNode(int hs, int mu) {
    Node *p = (Node*)malloc(sizeof(Node));
    if (p != NULL) {
        p->hs = hs;
        p->mu = mu;
        p->Next = NULL;
    }
    return p;
}

// Them node vào cuoi danh sách
void ThemCuoi(Node* &H, int hs, int mu) {
    Node *p = TaoNode(hs, mu);
    if (H == NULL) {
        H = p;
    } else {
        Node *q = H;
        while (q->Next != NULL) q = q->Next;
        q->Next = p;
    }
}

// Nhap da thuc
void NhapDaThuc(Node* &H) {
    int n, hs, mu;
    H = NULL;
    printf("Nhap so luong hang tu: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Nhap he so va so mu thu %d (vd: 3 2 cho 3x^2): ", i+1);
        scanf("%d%d", &hs, &mu);
        ThemCuoi(H, hs, mu);
    }
}

// Xuat da thuc
void XuatDaThuc(Node* H) {
    if (H == NULL) {
        printf("0");
        return;
    }
    while (H != NULL) {
        if (H->hs > 0 && H != NULL) printf("+");
        if (H->mu == 0) printf("%d", H->hs);
        else if (H->mu == 1) printf("%dx", H->hs);
        else printf("%dx^%d", H->hs, H->mu);
        H = H->Next;
    }
    printf("\n");
}

// Tính giá tri tai x
double TinhGiaTri(Node* H, int x) {
    double tong = 0;
    while (H != NULL) {
        tong += H->hs * pow(x, H->mu);
        H = H->Next;
    }
    return tong;
}

// Tính dao hàm tai x
double DaoHam(Node* H, int x) {
    double tong = 0;
    while (H != NULL) {
        if (H->mu != 0)
            tong += H->hs * H->mu * pow(x, H->mu - 1);
        H = H->Next;
    }
    return tong;
}

// Cong hai da thuc
Node* Cong(Node* A, Node* B) {
    Node *KQ = NULL;
    // Sao chép A vào KQ
    while (A != NULL) {
        ThemCuoi(KQ, A->hs, A->mu);
        A = A->Next;
    }
    // Cong B vào KQ
    while (B != NULL) {
        Node *p = KQ;
        int found = 0;
        while (p != NULL) {
            if (p->mu == B->mu) {
                p->hs += B->hs;
                found = 1;
                break;
            }
            p = p->Next;
        }
        if (!found) ThemCuoi(KQ, B->hs, B->mu);
        B = B->Next;
    }
    return KQ;
}

// Menu
int Menu() {
    int chon;
    printf("\n----- MENU -----\n");
    printf("1. Nhap da thuc A\n");
    printf("2. Nhap da thuc B\n");
    printf("3. Xuat A va B\n");
    printf("4. Tinh gia tri A tai x\n");
    printf("5. Tinh dao ham A tai x\n");
    printf("6. Cong A + B\n");
    printf("7. Thoat\n");
    printf("Chon: ");
    scanf("%d", &chon);
    return chon;
}

// Main
int main() {
    Node *A = NULL, *B = NULL, *KQ = NULL;
    int chon, x;
    do {
        chon = Menu();
        switch (chon) {
            case 1:
                NhapDaThuc(A);
                break;
            case 2:
                NhapDaThuc(B);
                break;
            case 3:
                printf("Da thuc A: ");
                XuatDaThuc(A);
                printf("Da thuc B: ");
                XuatDaThuc(B);
                break;
            case 4:
                printf("Nhap x = ");
                scanf("%d", &x);
                printf("Gia tri A(x) = %.2lf\n", TinhGiaTri(A, x));
                break;
            case 5:
                printf("Nhap x = ");
                scanf("%d", &x);
                printf("Dao ham A'(x) = %.2lf\n", DaoHam(A, x));
                break;
            case 6:
			    KQ = Cong(A, B);
			    printf("Tong A + B = ");
			    XuatDaThuc(KQ);
			    printf("\nNhap x de tinh gia tri cua A + B tai x: ");
			    scanf("%d", &x);
			    printf("Gia tri (A + B)(%d) = %.2lf\n", x, TinhGiaTri(KQ, x));
			    break;
            case 7:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (chon != 7);
    return 0;
}

