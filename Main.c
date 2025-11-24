#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 고객 정보 구조체
typedef struct {
    char name[50];
    char phone[20];
    int customerID;
} Customer;

// 의류 정보 구조체
typedef struct {
    char name[50];
    char size[10];
    char color[20];
    int price;
    int stock; // 재고 수량
    int itemID;
} Clothing;

// 데이터 저장을 위한 전역 변수 (배열)
Customer customer_list[100];
Clothing clothing_list[100];
int customer_count = 0;
int clothing_count = 0;

// 함수 원형 선언
void admin_menu();
void member_menu();
void register_customer();
void manage_customer();
void register_clothing();
void manage_inventory();

int main(){
    int choice;

    while(1) {
        printf("\n--- 의류 매장 관리 프로그램 ---\n");
        printf("1. 관리자 메뉴\n");
        printf("2. 회원 메뉴\n");
        printf("3. 프로그램 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                admin_menu();
                break;
            case 2:
                member_menu();
                break;
            case 3:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
    return 0;
}

/**
관리자 메뉴 기능
 */
void admin_menu() {
    printf("\n--- 관리자 메뉴 ---\n");
    printf("1. 의류 등록\n");
    printf("2. 재고 관리\n");
    printf("3. 고객 등록\n");
    printf("4. 고객 관리\n");
    // 추가 기능 구현 가능
}

/**
회원(고객) 메뉴 기능
 */
void member_menu() {
    printf("\n--- 회원 메뉴 ---\n");
    printf("환영합니다! (기능 준비중)\n");
    // 향후 의류 검색, 구매 등의 기능 추가 가능
}

/**
신규 고객 등록 기능
 */
void register_customer() {
    printf("\n--- 신규 고객 등록 ---\n");
    // 여기에 고객 이름, 연락처 등을 입력받는 코드 추가
    // 예: customer_list[customer_count].customerID = customer_count + 1;
    // customer_count++;
    printf("고객 등록 기능이 호출되었습니다.\n");
}

/**
고객 관리 기능
 */
void manage_customer() {
    printf("\n--- 고객 관리 ---\n");
    printf("등록된 고객 목록을 표시합니다.\n");
}

/**
 * @brief 신규 의류 등록 기능
 */
void register_clothing() {
    printf("\n--- 신규 의류 등록 ---\n");
    printf("의류 등록 기능이 호출되었습니다.\n");
}

/**
 * @brief 재고 관리 기능
 */
void manage_inventory() {
    printf("\n--- 재고 관리 ---\n");
    printf("현재 재고 목록을 표시합니다.\n");
}