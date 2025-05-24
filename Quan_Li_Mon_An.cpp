// BAI7: Quan Li Mon An
#include <stdio.h>
#include <string.h>

#define MAX_MON_AN 100
#define MAX_BAN 5
#define MAX_DAT_MON 50


// Cau truc mon an
typedef struct {
    char ten[50];
    int gia;
} MonAn;

// Cau truc dat mon
typedef struct {
    char ten[50];
    int soLuong;
} DatMon;

// Cau truc don hang cua ban
typedef struct {
    DatMon datMon[MAX_DAT_MON];
    int soLuongDat;
} DonHang;

MonAn thucDon[MAX_MON_AN];
int soLuongMon = 0;

DonHang dsBan[MAX_BAN]; // 5 ban tu 0 den 4

// Tim vi tri mon an trong thuc don
int timMonAn(char ten[]) {
    for (int i = 0; i < soLuongMon; i++) {
        if (strcmp(thucDon[i].ten, ten) == 0) {
            return i;
        }
    }
    return -1;
}

void themMonAn() {
    if (soLuongMon >= MAX_MON_AN) {
        printf("Thuc don da day!\n");
        return;
    }
    MonAn m;
    printf("Nhap ten mon an: ");
    fflush(stdin);
    gets(m.ten);
    printf("Nhap gia mon an: ");
    scanf("%d", &m.gia);
    thucDon[soLuongMon++] = m;
    printf("Da them mon an vao thuc don!\n");
}

void xemThucDon() {
    printf("\n--- THUC DON ---\n");
    printf("%-30s | Gia\n", "Ten mon");
    printf("------------------------------------------\n");
    for (int i = 0; i < soLuongMon; i++) {
        printf("%-30s | %d\n", thucDon[i].ten, thucDon[i].gia);
    }
    printf("----------------------------\n\n");
}

void datMonChoBan() {
    int soBan;
    printf("Nhap so ban (1-5): ");
    scanf("%d", &soBan);
    if (soBan < 1 || soBan > 5) {
        printf("So ban khong hop le!\n");
        return;
    }
    soBan--; // chuyen ve chi so mang
    int tiepTuc;
    do {
        if (dsBan[soBan].soLuongDat >= MAX_DAT_MON) {
            printf("Ban da dat qua nhieu mon!\n");
            break;
        }
        char tenMon[50];
        int soLuong;
        printf("Nhap ten mon an muon dat: ");
        fflush(stdin);
        gets(tenMon);
        int viTri = timMonAn(tenMon);
        if (viTri == -1) {
            printf("Mon an khong ton tai trong thuc don!\n");
        } else {
            printf("Nhap so luong: ");
            scanf("%d", &soLuong);
            // Luu vao don hang cua ban
            DatMon dm;
            strcpy(dm.ten, tenMon);
            dm.soLuong = soLuong;
            dsBan[soBan].datMon[dsBan[soBan].soLuongDat++] = dm;
            printf("Da dat mon thanh cong!\n");
        }
        printf("Ban co muon dat them? (1: Co, 0: Khong): ");
        scanf("%d", &tiepTuc);
    } while (tiepTuc == 1);
}

void xemDonHangBan() {
    int soBan;
    printf("Nhap so ban (1-5): ");
    scanf("%d", &soBan);
    if (soBan < 1 || soBan > 5) {
        printf("So ban khong hop le!\n");
        return;
    }
    soBan--; // chi so mang
    printf("\n--- DON HANG CUA BAN %d ---\n", soBan + 1);
    printf("%-30s | So luong | Don gia | Thanh tien\n", "Ten mon");
    printf("------------------------------------------------------------\n");
    int tongTien = 0;
    for (int i = 0; i < dsBan[soBan].soLuongDat; i++) {
        DatMon dm = dsBan[soBan].datMon[i];
        int viTri = timMonAn(dm.ten);
        if (viTri != -1) {
            int donGia = thucDon[viTri].gia;
            int thanhTien = donGia * dm.soLuong;
            printf("%-30s | %-9d | %-8d | %d\n", dm.ten, dm.soLuong, donGia, thanhTien);
            tongTien += thanhTien;
        }
    }
    printf("------------------------------------------------------------\n");
    printf("Tong tien: %d VND\n\n", tongTien);
}

int main() {
    int luaChon;
    do {
        printf("\n===== MENU QUAN LY QUAN AN =====\n");
        printf("1. Them mon an vao thuc don\n");
        printf("2. Xem thuc don\n");
        printf("3. Dat mon an cho ban\n");
        printf("4. Xem don hang cua ban\n");
        printf("5. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                themMonAn();
                break;
            case 2:
                xemThucDon();
                break;
            case 3:
                datMonChoBan();
                break;
            case 4:
                xemDonHangBan();
                break;
            case 5:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 5);

    return 0;
}

