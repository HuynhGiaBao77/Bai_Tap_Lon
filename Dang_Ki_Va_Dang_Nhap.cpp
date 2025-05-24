//BAI6: Dang ki va dang nhap
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>  // Dùng cho getch()

#define MAX_TRY 3
#define FILENAME "users.txt"

// Ham nhap mot khau co ky tu
void inputPassword(char *password) {
    char ch;
    int i = 0;
    while (1) {
        ch = getch();
        if (ch == 13) { // Enter
            password[i] = '\0';
            printf("\n");
            break;
        } else if (ch == 8 && i > 0) { // Backspace
            printf("\b \b");
            i--;
        } else if (isprint(ch) && i < 49) {
            password[i++] = ch;
            printf("*");
        }
    }
}

// Kiem tra mat khau
int isValidPassword(const char *pw) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0;
    if (strlen(pw) < 8) return 0;
    for (int i = 0; pw[i]; i++) {
        if (isupper(pw[i])) hasUpper = 1;
        else if (islower(pw[i])) hasLower = 1;
        else if (isdigit(pw[i])) hasDigit = 1;
    }
    return hasUpper && hasLower && hasDigit;
}

// Ðang ky
void registerUser() {
    char username[50], password[50], confirm[50];
    printf("Dang ky tai khoan:\n");

    while (1) {
        printf("Nhap ten dang nhap (>=5 ky tu): ");
        scanf("%s", username);
        if (strlen(username) >= 5) break;
        printf("Ten qua ngan. Thu lai!\n");
    }

    while (1) {
        printf("Nhap mat khau: ");
        inputPassword(password);
        if (!isValidPassword(password)) {
            printf("Mat khau khong hop le. Thu lai!\n");
            continue;
        }
        printf("Nhap lai mat khau: ");
        inputPassword(confirm);
        if (strcmp(password, confirm) != 0) {
            printf("Mat khau khong khop. Thu lai!\n");
        } else break;
    }

    FILE *f = fopen(FILENAME, "w");
    if (f == NULL) {
        printf("Loi ghi file!\n");
        return;
    }
    fprintf(f, "%s %s\n", username, password);
    fclose(f);
    printf("Dang ky thanh cong!\n");
}

// Ðang nhap
int login() {
    char username[50], password[50], file_user[50], file_pass[50];
    int tries = 0;

    FILE *f = fopen(FILENAME, "r");
    if (!f) {
        printf("Chua co tai khoan. Dang ky truoc.\n");
        return 0;
    }
    fscanf(f, "%s %s", file_user, file_pass);
    fclose(f);

    while (tries < MAX_TRY) {
        printf("Dang nhap:\n");
        printf("Ten dang nhap: ");
        scanf("%s", username);
        printf("Mat khau: ");
        inputPassword(password);

        if (strcmp(username, file_user) == 0 && strcmp(password, file_pass) == 0) {
            printf("Dang nhap thanh cong!\n");
            return 1;
        } else {
            printf("Sai ten hoac mat khau. Con %d lan thu.\n", MAX_TRY - tries - 1);
            tries++;
        }
    }

    printf("Dang nhap that bai.\n");
    return 0;
}

int main() {
    int choice;
    printf("1. Dang ky\n2. Dang nhap\nChon: ");
    scanf("%d", &choice);

    if (choice == 1)
        registerUser();
    else if (choice == 2)
        login();
    else
        printf("Lua chon khong hop le!\n");

    return 0;
}

