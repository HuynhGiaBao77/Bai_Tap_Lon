// Bai 2: Quan ly doan vien su dung danh sach lien ket don
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Khai bao cau truc DoanVien
typedef struct DoanVien {
    char ma[10];
    char hoTen[50];
    char chiDoan[30];
    int namSinh;
    float diemRL;
} DoanVien;

// Node danh sach lien ket
typedef struct Node {
    DoanVien dv;
    struct Node* next;
} Node;

// Tao node moi
Node* taoNode(DoanVien dv) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        printf("Khong du bo nho!\n");
        exit(1);
    }
    p->dv = dv;
    p->next = NULL;
    return p;
}

// Them cuoi danh sach
void themCuoi(Node** head, DoanVien dv) {
    Node* p = taoNode(dv);
    if (*head == NULL) {
        *head = p;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = p;
}

// Nhap thong tin doan vien
DoanVien nhap1DoanVien() {
    DoanVien dv;
    printf("Nhap ma doan vien: "); fflush(stdin); gets(dv.ma);
    printf("Nhap ho ten: "); fflush(stdin); gets(dv.hoTen);
    printf("Nhap chi doan: "); fflush(stdin); gets(dv.chiDoan);
    printf("Nhap nam sinh: "); scanf("%d", &dv.namSinh);
    printf("Nhap diem ren luyen: "); scanf("%f", &dv.diemRL);
    return dv;
}

// Xuat danh sach
void xuatDanhSach(Node* head) {
    printf("\n%-10s %-25s %-20s %-10s %-10s\n", "Ma", "Ho ten", "Chi doan", "Nam sinh", "Diem RL");
    while (head != NULL) {
        printf("%-10s %-25s %-20s %-10d %-10.2f\n",
            head->dv.ma, head->dv.hoTen, head->dv.chiDoan,
            head->dv.namSinh, head->dv.diemRL);
        head = head->next;
    }
}

// Tim kiem doan vien theo ma
Node* timTheoMa(Node* head, char ma[]) {
    while (head != NULL) {
        if (strcmp(head->dv.ma, ma) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

// Tinh diem RL trung binh cua mot chi doan
float diemRLTrungBinh(Node* head, char chiDoan[]) {
    int dem = 0;
    float tong = 0;
    while (head != NULL) {
        if (strcmp(head->dv.chiDoan, chiDoan) == 0) {
            tong += head->dv.diemRL;
            dem++;
        }
        head = head->next;
    }
    if (dem == 0) return 0;
    return tong / dem;
}

// Xoa doan vien theo ma
void xoaTheoMa(Node** head, char ma[]) {
    Node* temp = *head;
    Node* prev = NULL;
    while (temp != NULL && strcmp(temp->dv.ma, ma) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return; // khong tim thay

    if (prev == NULL) *head = temp->next;
    else prev->next = temp->next;

    free(temp);
}

// Ghi danh sach ra tep
void ghiFile(Node* head, char tenTep[]) {
    FILE* f = fopen(tenTep, "w");
    if (!f) {
        printf("Khong mo duoc file!\n");
        return;
    }
    while (head != NULL) {
        fprintf(f, "%s,%s,%s,%d,%.2f\n", head->dv.ma, head->dv.hoTen,
            head->dv.chiDoan, head->dv.namSinh, head->dv.diemRL);
        head = head->next;
    }
    fclose(f);
}

// MENU chinh
void menu() {
    printf("\n==== MENU QUAN LY DOAN VIEN ====");
    printf("\n1. Nhap danh sach doan vien");
    printf("\n2. Xuat danh sach");
    printf("\n3. Tim kiem theo ma");
    printf("\n4. Tinh diem RL trung binh theo chi doan");
    printf("\n5. Xoa doan vien theo ma");
    printf("\n6. Ghi danh sach ra file");
    printf("\n0. Thoat\n");
}

int main() {
    Node* head = NULL;
    int chon;
    char ma[10], chiDoan[30];

    do {
        menu();
        printf("\nChon chuc nang: "); scanf("%d", &chon);
        switch(chon) {
            case 1:
                {
                    int n;
                    printf("Nhap so luong doan vien: "); scanf("%d", &n);
                    for (int i = 0; i < n; i++) {
                        printf("\nNhap doan vien thu %d:\n", i+1);
                        DoanVien dv = nhap1DoanVien();
                        themCuoi(&head, dv);
                    }
                    break;
                }
            case 2:
                xuatDanhSach(head);
                break;
            case 3:
                printf("Nhap ma can tim: "); fflush(stdin); gets(ma);
                {
                    Node* kq = timTheoMa(head, ma);
                    if (kq)
                        printf("Tim thay: %s - %s\n", kq->dv.ma, kq->dv.hoTen);
                    else
                        printf("Khong tim thay!\n");
                }
                break;
            case 4:
                printf("Nhap ten chi doan: "); fflush(stdin); gets(chiDoan);
                printf("Diem RL trung binh: %.2f\n", diemRLTrungBinh(head, chiDoan));
                break;
            case 5:
                printf("Nhap ma can xoa: "); fflush(stdin); gets(ma);
                xoaTheoMa(&head, ma);
                printf("Da xoa neu ton tai.\n");
                break;
            case 6:
                ghiFile(head, "doanvien.txt");
                printf("Da ghi file thanh cong.\n");
                break;
            case 0:
                printf("Tam biet!\n");
                break;
            default:
                printf("Khong hop le!\n");
        }
    } while (chon != 0);
    return 0;
}

