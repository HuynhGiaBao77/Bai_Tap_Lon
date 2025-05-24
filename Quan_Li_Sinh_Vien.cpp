// Bai 1: Quan ly sinh vien su dung danh sach lien ket don

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cau truc sinh vien
typedef struct SinhVien {
    char ma[15];
    char ten[50];
    float diem;
} SinhVien;

// Node danh sach lien ket
typedef struct Node {
    SinhVien data;
    struct Node* next;
} Node;

// Tao mot node moi
Node* taoNode(SinhVien sv) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        printf("Cap phat bo nho that bai!\n");
        exit(1);
    }
    p->data = sv;
    p->next = NULL;
    return p;
}

// Them node vao cuoi danh sach
void themCuoi(Node** head, SinhVien sv) {
    Node* p = taoNode(sv);
    if (*head == NULL) {
        *head = p;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = p;
    }
}

// Nhap thong tin 1 sinh vien
SinhVien nhap1SV() {
    SinhVien sv;
    getchar(); // xoa ky tu thua truoc do
    printf("Nhap ma SV: ");
    fgets(sv.ma, sizeof(sv.ma), stdin);
    sv.ma[strcspn(sv.ma, "\n")] = '\0';

    printf("Nhap ten SV: ");
    fgets(sv.ten, sizeof(sv.ten), stdin);
    sv.ten[strcspn(sv.ten, "\n")] = '\0';

    printf("Nhap diem: ");
    scanf("%f", &sv.diem);
    return sv;
}

// Nhap danh sach sinh vien
void nhapDanhSach(Node** head, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n-- Nhap SV thu %d --\n", i+1);
        SinhVien sv = nhap1SV();
        themCuoi(head, sv);
    }
}

// Xuat danh sach sinh vien
void xuatDanhSach(Node* head) {
    printf("\n%-10s %-30s %-5s\n", "MaSV", "Ten SV", "Diem");
    while (head != NULL) {
        printf("%-10s %-30s %-5.2f\n", head->data.ma, head->data.ten, head->data.diem);
        head = head->next;
    }
}

// Ghi danh sach ra file
void ghiFile(Node* head, char* filename) {
    FILE* f = fopen(filename, "w");
    while (head != NULL) {
        fprintf(f, "%s,%s,%.2f\n", head->data.ma, head->data.ten, head->data.diem);
        head = head->next;
    }
    fclose(f);
    printf("\nDa ghi vao file %s thanh cong!\n", filename);
}

// Tim SV theo ma
void timSVTheoMa(Node* head, char* maSV) {
    while (head != NULL) {
        if (strcmp(head->data.ma, maSV) == 0) {
            printf("\nTim thay: %s - %s - %.2f\n", head->data.ma, head->data.ten, head->data.diem);
            return;
        }
        head = head->next;
    }
    printf("\nKhong tim thay SV co ma %s!\n", maSV);
}

// Sap xep theo diem giam dan
void sapXepTheoDiem(Node** head) {
    for (Node* p = *head; p != NULL; p = p->next) {
        for (Node* q = p->next; q != NULL; q = q->next) {
            if (p->data.diem < q->data.diem) {
                SinhVien tmp = p->data;
                p->data = q->data;
                q->data = tmp;
            }
        }
    }
    printf("\nDa sap xep xong!\n");
}

// Tach danh sach thanh 2 danh sach: dat va khong dat (diem >= 5)
void tachDanhSach(Node* head, Node** dat, Node** khongdat) {
    while (head != NULL) {
        if (head->data.diem >= 5) themCuoi(dat, head->data);
        else themCuoi(khongdat, head->data);
        head = head->next;
    }
}

// Dem so luong SV
int demSV(Node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// MENU
void menu() {
    printf("\n======== MENU ========\n");
    printf("1. Nhap danh sach sinh vien\n");
    printf("2. Xuat danh sach\n");
    printf("3. Ghi danh sach ra file\n");
    printf("4. Tim SV theo ma\n");
    printf("5. Sap xep theo diem giam dan\n");
    printf("6. Tach danh sach (dat/khong dat)\n");
    printf("0. Thoat\n");
    printf("=======================\n");
}

int main() {
    Node* ds = NULL;
    Node* dat = NULL;
    Node* khongdat = NULL;
    int chon, n;
    char maSV[15];
    do {
        menu();
        printf("Chon chuc nang: "); scanf("%d", &chon);
        switch (chon) {
            case 1:
                printf("Nhap so SV: "); scanf("%d", &n);
                nhapDanhSach(&ds, n);
                break;
            case 2:
                xuatDanhSach(ds);
                break;
            case 3:
                ghiFile(ds, "sinhvien.txt");
                break;
            case 4:
                getchar();
                printf("Nhap ma SV can tim: ");
                fgets(maSV, sizeof(maSV), stdin);
                maSV[strcspn(maSV, "\n")] = '\0';
                timSVTheoMa(ds, maSV);
                break;
            case 5:
                sapXepTheoDiem(&ds);
                break;
            case 6:
                dat = NULL; khongdat = NULL;
                tachDanhSach(ds, &dat, &khongdat);
                printf("\n-- Danh sach DAT --\n");
                xuatDanhSach(dat);
                printf("\n-- Danh sach KHONG DAT --\n");
                xuatDanhSach(khongdat);
                printf("\nTi le dat: %.2f%%\n", (float)demSV(dat) / demSV(ds) * 100);
                break;
        }
    } while (chon != 0);

    return 0;
}

