// Bai 3: Quan ly tai khoan ngan hang su dung danh sach lien ket don
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Khai bao cau truc TaiKhoan
typedef struct TaiKhoan {
    char soTK[20];
    char tenChuTK[50];
    float soDu;
} TaiKhoan;

// Node danh sach lien ket
typedef struct Node {
    TaiKhoan tk;
    struct Node* next;
} Node;

// Tao node moi
Node* taoNode(TaiKhoan tk) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (!p) {
        printf("Khong du bo nho!\n");
        exit(1);
    }
    p->tk = tk;
    p->next = NULL;
    return p;
}

// Them cuoi danh sach
void themCuoi(Node** head, TaiKhoan tk) {
    Node* p = taoNode(tk);
    if (*head == NULL) {
        *head = p;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = p;
}

// Nhap 1 tai khoan
TaiKhoan nhap1TK() {
    TaiKhoan tk;
    printf("Nhap so tai khoan: "); fflush(stdin); gets(tk.soTK);
    printf("Nhap ten chu tai khoan: "); fflush(stdin); gets(tk.tenChuTK);
    printf("Nhap so du: "); scanf("%f", &tk.soDu);
    return tk;
}

// Xuat danh sach
void xuatDanhSach(Node* head) {
    printf("\n%-20s %-30s %-10s\n", "So TK", "Ten chu TK", "So du");
    while (head != NULL) {
        printf("%-20s %-30s %-10.2f\n", head->tk.soTK, head->tk.tenChuTK, head->tk.soDu);
        head = head->next;
    }
}

// Tim tai khoan theo so TK
Node* timTheoSoTK(Node* head, char soTK[]) {
    while (head != NULL) {
        if (strcmp(head->tk.soTK, soTK) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

// Giao dich: gui tien
void guiTien(Node* head, char soTK[], float soTien) {
    Node* p = timTheoSoTK(head, soTK);
    if (p) {
        p->tk.soDu += soTien;
        printf("Gui tien thanh cong. So du moi: %.2f\n", p->tk.soDu);
    } else {
        printf("Khong tim thay tai khoan!\n");
    }
}

// Giao dich: rut tien
void rutTien(Node* head, char soTK[], float soTien) {
    Node* p = timTheoSoTK(head, soTK);
    if (p) {
        if (p->tk.soDu >= soTien) {
            p->tk.soDu -= soTien;
            printf("Rut tien thanh cong. So du con lai: %.2f\n", p->tk.soDu);
        } else {
            printf("Khong du tien trong tai khoan!\n");
        }
    } else {
        printf("Khong tim thay tai khoan!\n");
    }
}

// Xoa tai khoan
void xoaTaiKhoan(Node** head, char soTK[]) {
    Node* temp = *head;
    Node* prev = NULL;
    while (temp != NULL && strcmp(temp->tk.soTK, soTK) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    if (prev == NULL) *head = temp->next;
    else prev->next = temp->next;
    free(temp);
    printf("Da xoa tai khoan neu ton tai.\n");
}

// Ghi danh sach ra file
void ghiFile(Node* head, char tenTep[]) {
    FILE* f = fopen(tenTep, "w");
    if (!f) {
        printf("Khong mo duoc file!\n");
        return;
    }
    while (head != NULL) {
        fprintf(f, "%s,%s,%.2f\n", head->tk.soTK, head->tk.tenChuTK, head->tk.soDu);
        head = head->next;
    }
    fclose(f);
    printf("Da ghi danh sach vao file.\n");
}

// MENU
void menu() {
    printf("\n==== MENU QUAN LY TAI KHOAN ====");
    printf("\n1. Nhap danh sach tai khoan");
    printf("\n2. Hien thi danh sach");
    printf("\n3. Gui tien");
    printf("\n4. Rut tien");
    printf("\n5. Tim kiem theo so TK");
    printf("\n6. Xoa tai khoan");
    printf("\n7. Ghi danh sach ra file");
    printf("\n0. Thoat\n");
}

int main() {
    Node* head = NULL;
    int chon;
    char soTK[20];
    float soTien;

    do {
        menu();
        printf("\nChon chuc nang: "); scanf("%d", &chon);
        switch(chon) {
            case 1:
                {
                    int n;
                    printf("Nhap so luong tai khoan: "); scanf("%d", &n);
                    for (int i = 0; i < n; i++) {
                        printf("\nNhap tai khoan thu %d:\n", i+1);
                        TaiKhoan tk = nhap1TK();
                        themCuoi(&head, tk);
                    }
                    break;
                }
            case 2:
                xuatDanhSach(head);
                break;
            case 3:
                printf("Nhap so TK: "); fflush(stdin); gets(soTK);
                printf("Nhap so tien muon gui: "); scanf("%f", &soTien);
                guiTien(head, soTK, soTien);
                break;
            case 4:
                printf("Nhap so TK: "); fflush(stdin); gets(soTK);
                printf("Nhap so tien muon rut: "); scanf("%f", &soTien);
                rutTien(head, soTK, soTien);
                break;
            case 5:
                printf("Nhap so TK can tim: "); fflush(stdin); gets(soTK);
                {
                    Node* p = timTheoSoTK(head, soTK);
                    if (p)
                        printf("Tim thay: %s - %s - %.2f\n", p->tk.soTK, p->tk.tenChuTK, p->tk.soDu);
                    else
                        printf("Khong tim thay tai khoan!\n");
                }
                break;
            case 6:
                printf("Nhap so TK can xoa: "); fflush(stdin); gets(soTK);
                xoaTaiKhoan(&head, soTK);
                break;
            case 7:
                ghiFile(head, "taikhoan.txt");
                break;
            case 0:
                printf("Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (chon != 0);

    return 0;
}

