#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 고객 정보 구조체
typedef struct {
    char name[50];
    char phone[20];
    int customerID;
    int mileage;
} Customer;

// 의류 정보 구조체
typedef struct {
    char name[50];
    char size[10];
    char color[20];
    int price;
    int stock; // 재고 수량
    char itemID[20];
} Clothing;

// 데이터 저장을 위한 전역 변수 (배열)
Customer customer_list[100];
Clothing clothing_list[100];
int customer_count = 0;
int clothing_count = 0;

// 함수 원형 선언
int admin_login();
void admin_menu();
void member_menu();
void register_customer();
void manage_customer();
void register_clothing();
void manage_inventory();
void purchase_clothing();

int main(){
    int choice;

    while(1) {
        printf("\n--- 의류 매장 관리 프로그램 ---\n");
        printf("1. 관리자 메뉴\n");
        printf("2. 회원 메뉴\n");
        printf("3. 프로그램 종료\n");
        printf("메뉴 선택: ");
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin)) {
            sscanf(buffer, "%d", &choice);
        }

        switch(choice) {
            case 1:
                if (admin_login()) {
                    admin_menu();
                }
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

/*
관리자 로그인 기능
*/
int admin_login() {
    char username[50];
    char password[50];
    const char admin_user[] = "admin";
    const char admin_pass[] = "1234";

    printf("\n--- 관리자 로그인 ---\n");
    printf("아이디: ");
    scanf("%s", username);
    printf("비밀번호: ");
    scanf("%s", password);

    if (strcmp(username, admin_user) == 0 && strcmp(password, admin_pass) == 0) {
        printf("로그인 성공!\n");
        return 1; // 로그인 성공
    } else {
        printf("아이디 또는 비밀번호가 일치하지 않습니다.\n");
        return 0; // 로그인 실패
    }
}

/*
관리자 메뉴 기능
*/
void admin_menu() {
    int choice;
    while(1) {
        printf("\n--- 관리자 메뉴 ---\n");
        printf("1. 의류 등록\n");
        printf("2. 재고 관리\n");
        printf("3. 고객 등록\n");
        printf("4. 고객 관리\n");
        printf("5. 메인 메뉴로 돌아가기\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // 입력 버퍼에 남아있는 개행 문자 제거

        switch(choice) {
            case 1: register_clothing(); break;
            case 2: manage_inventory(); break;
            case 3: register_customer(); break;
            case 4: manage_customer(); break;
            case 5: return; // 메인 메뉴로 복귀
            default: printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
}

/*
회원(고객) 메뉴 기능
*/
void member_menu() {
    int choice;
    char buffer[100];
    while(1) {
        printf("\n--- 회원 메뉴 ---\n");
        printf("1. 의류 구매\n");
        printf("2. 메인 메뉴로 돌아가기\n");
        printf("메뉴 선택: ");
        if (fgets(buffer, sizeof(buffer), stdin)) {
            sscanf(buffer, "%d", &choice);
        }

        switch(choice) {
            case 1: purchase_clothing(); break;
            case 2: return;
            default: printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
}

/*
신규 고객 등록 기능
*/
void register_customer() {
    if (customer_count >= 100) {
        printf("더 이상 고객을 등록할 수 없습니다. (최대 100명)\n");
        return;
    }

    printf("\n--- 신규 고객 등록 ---\n");
    Customer new_customer;
    char buffer[100];

    printf("고객 이름: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(new_customer.name, buffer, sizeof(new_customer.name) - 1);
    }

    printf("연락처: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(new_customer.phone, buffer, sizeof(new_customer.phone) - 1);
    }

    printf("고객 ID (숫자): ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        sscanf(buffer, "%d", &new_customer.customerID);
    }

    new_customer.mileage = 0; // 마일리지 기본값 0으로 설정

    customer_list[customer_count] = new_customer;
    customer_count++;

    printf("신규 고객 등록이 완료되었습니다!\n");
}

/*
고객 관리 기능
*/
void manage_customer() {
    printf("\n--- 고객 관리 ---\n");

    if (customer_count == 0) {
        printf("등록된 고객이 없습니다.\n");
        return;
    }

    printf("-------------------- 현재 고객 목록 --------------------\n");
    printf("고객ID\t이름\t\t연락처\t\t마일리지\n");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < customer_count; i++) {
        printf("%d\t%s\t\t%s\t%d\n", customer_list[i].customerID, customer_list[i].name, customer_list[i].phone, customer_list[i].mileage);
    }
    printf("----------------------------------------------------------\n\n");

    int choice;
    char buffer[100];
    printf("1. 고객 정보 수정\n");
    printf("2. 고객 정보 삭제\n");
    printf("3. 이전 메뉴로\n");
    printf("메뉴 선택: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        sscanf(buffer, "%d", &choice);
    }

    switch (choice) {
        case 1: { // 고객 정보 수정
            int target_id;
            printf("수정할 고객의 ID를 입력하세요: ");
            if (fgets(buffer, sizeof(buffer), stdin)) sscanf(buffer, "%d", &target_id);

            int found_index = -1;
            for (int i = 0; i < customer_count; i++) {
                if (customer_list[i].customerID == target_id) {
                    found_index = i;
                    break;
                }
            }

            if (found_index != -1) {
                printf("새로운 고객 이름: ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    buffer[strcspn(buffer, "\n")] = 0;
                    strncpy(customer_list[found_index].name, buffer, sizeof(customer_list[found_index].name) - 1);
                }
                printf("새로운 연락처: ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    buffer[strcspn(buffer, "\n")] = 0;
                    strncpy(customer_list[found_index].phone, buffer, sizeof(customer_list[found_index].phone) - 1);
                }
                printf("고객 정보가 성공적으로 업데이트되었습니다.\n");
            } else {
                printf("해당 ID의 고객을 찾을 수 없습니다.\n");
            }
            break;
        }
        case 2: { // 고객 정보 삭제
            int target_id;
            printf("삭제할 고객의 ID를 입력하세요: ");
            if (fgets(buffer, sizeof(buffer), stdin)) sscanf(buffer, "%d", &target_id);

            int found_index = -1;
            for (int i = 0; i < customer_count; i++) {
                if (customer_list[i].customerID == target_id) {
                    found_index = i;
                    break;
                }
            }

            if (found_index != -1) {
                for (int i = found_index; i < customer_count - 1; i++) {
                    customer_list[i] = customer_list[i + 1];
                }
                customer_count--;
                printf("고객 정보가 성공적으로 삭제되었습니다.\n");
            } else {
                printf("해당 ID의 고객을 찾을 수 없습니다.\n");
            }
            break;
        }
        case 3:
            return;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
    }
}

/*
의류 구매 및 마일리지 적립 기능
*/
void purchase_clothing() {
    char buffer[100];
    int customer_id;
    int customer_idx = -1;

    printf("\n--- 의류 구매 ---\n");

    if (customer_count == 0 || clothing_count == 0) {
        printf("등록된 고객 또는 의류가 없어 구매를 진행할 수 없습니다.\n");
        return;
    }

    // 1. 고객 확인
    printf("고객 ID를 입력하세요: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        sscanf(buffer, "%d", &customer_id);
    }

    for (int i = 0; i < customer_count; i++) {
        if (customer_list[i].customerID == customer_id) {
            customer_idx = i;
            break;
        }
    }

    if (customer_idx == -1) {
        printf("해당 ID의 고객을 찾을 수 없습니다.\n");
        return;
    }

    printf("환영합니다, %s 님! (보유 마일리지: %d점)\n", customer_list[customer_idx].name, customer_list[customer_idx].mileage);

    // 2. 의류 목록 표시
    printf("-------------------- 구매 가능 의류 목록 --------------------\n");
    printf("품번\t이름\t\t사이즈\t색상\t가격\t재고\n");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < clothing_count; i++) {
        printf("%s\t%s\t\t%s\t%s\t%d\t%d\n",
               clothing_list[i].itemID, clothing_list[i].name, clothing_list[i].size,
               clothing_list[i].color, clothing_list[i].price, clothing_list[i].stock);
    }
    printf("----------------------------------------------------------\n\n");

    // 3. 의류 선택 및 구매
    char target_item_id[20];
    int clothing_idx = -1;
    int quantity;

    printf("구매할 의류의 품번(itemID)을 입력하세요: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(target_item_id, buffer, sizeof(target_item_id) - 1);
    }

    for (int i = 0; i < clothing_count; i++) {
        if (strcmp(clothing_list[i].itemID, target_item_id) == 0) {
            clothing_idx = i;
            break;
        }
    }

    if (clothing_idx == -1) {
        printf("해당 품번의 의류를 찾을 수 없습니다.\n");
        return;
    }

    printf("구매할 수량을 입력하세요: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        sscanf(buffer, "%d", &quantity);
    }

    if (quantity <= 0) {
        printf("구매 수량은 1 이상이어야 합니다.\n");
        return;
    }

    // 4. 재고 확인 및 처리
    if (clothing_list[clothing_idx].stock < quantity) {
        printf("재고가 부족합니다. (현재 재고: %d)\n", clothing_list[clothing_idx].stock);
        return;
    }

    // 4. 재고 확인 및 결제 처리
    int total_price = clothing_list[clothing_idx].price * quantity;
    int final_price = total_price;
    int used_mileage = 0;

    // 5. 마일리지 사용
    if (customer_list[customer_idx].mileage > 0) {
        char use_mileage_choice;
        printf("\n총 결제 예정 금액: %d원\n", total_price);
        printf("현재 보유 마일리지: %d점\n", customer_list[customer_idx].mileage);
        printf("마일리지를 사용하시겠습니까? (y/n): ");
        if (fgets(buffer, sizeof(buffer), stdin)) {
            sscanf(buffer, " %c", &use_mileage_choice);
        }

        if (use_mileage_choice == 'y' || use_mileage_choice == 'Y') {
            printf("사용할 마일리지를 입력하세요: ");
            if (fgets(buffer, sizeof(buffer), stdin)) {
                sscanf(buffer, "%d", &used_mileage);
            }

            if (used_mileage < 0) {
                printf("사용할 마일리지는 0 이상이어야 합니다. 마일리지 사용이 취소됩니다.\n");
                used_mileage = 0;
            } else if (used_mileage > customer_list[customer_idx].mileage) {
                printf("보유 마일리지를 초과하여 사용할 수 없습니다. 마일리지 사용이 취소됩니다.\n");
                used_mileage = 0;
            } else if (used_mileage > total_price) {
                printf("결제 금액을 초과하여 마일리지를 사용할 수 없습니다. 마일리지 사용이 취소됩니다.\n");
                used_mileage = 0;
            }

            if (used_mileage > 0) {
                customer_list[customer_idx].mileage -= used_mileage;
                final_price = total_price - used_mileage;
            }
        }
    }

    clothing_list[clothing_idx].stock -= quantity; // 재고 차감
    int earned_mileage = final_price * 0.05; // 실제 결제액의 5%를 마일리지로 적립
    customer_list[customer_idx].mileage += earned_mileage;

    printf("\n구매가 완료되었습니다!\n");
    printf("총 상품 금액: %d원\n", total_price);
    printf("사용한 마일리지: %d점\n", used_mileage);
    printf("최종 결제 금액: %d원\n", final_price);
    printf("적립된 마일리지: %d점 (남은 총 마일리지: %d점)\n", earned_mileage, customer_list[customer_idx].mileage);
}

/*
신규 의류 등록 기능
*/
void register_clothing() {
    if (clothing_count >= 100) {
        printf("더 이상 의류를 등록할 수 없습니다. (최대 100개)\n");
        return;
    }

    printf("\n--- 신규 의류 등록 ---\n");
    Clothing new_item;
    char buffer[100]; // 입력을 안전하게 받기 위한 버퍼

    printf("의류 이름: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = 0; // 개행 문자 제거
        strncpy(new_item.name, buffer, sizeof(new_item.name) - 1);
    }

    printf("사이즈: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = 0; // 개행 문자 제거
        strncpy(new_item.size, buffer, sizeof(new_item.size) - 1);
    }

    printf("색상: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = 0; // 개행 문자 제거
        strncpy(new_item.color, buffer, sizeof(new_item.color) - 1);
    }

    printf("가격: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        sscanf(buffer, "%d", &new_item.price);
    }

    printf("재고 수량: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        sscanf(buffer, "%d", &new_item.stock);
    }
    
    printf("품번(itemID): ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = 0; // 개행 문자 제거
        strncpy(new_item.itemID, buffer, sizeof(new_item.itemID) - 1);
    }

    clothing_list[clothing_count] = new_item;
    clothing_count++;

    printf("의류 등록이 완료되었습니다!\n");
}


/*
재고 관리 기능
*/
void manage_inventory() {
    printf("\n--- 재고 관리 ---\n");

    if (clothing_count == 0) {
        printf("등록된 의류가 없습니다.\n");
        return;
    }

    // 현재 등록된 모든 의류 목록 출력
    printf("-------------------- 현재 의류 목록 --------------------\n");
    printf("품번\t이름\t\t사이즈\t색상\t가격\t재고\n");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < clothing_count; i++) {
        printf("%s\t%s\t%s\t%s\t%d\t%d\n",
               clothing_list[i].itemID, clothing_list[i].name, clothing_list[i].size,
               clothing_list[i].color, clothing_list[i].price, clothing_list[i].stock);
    }
    printf("----------------------------------------------------------\n\n");

    int choice;
    printf("1. 재고 수량 수정\n");
    printf("2. 의류 삭제\n");
    printf("3. 이전 메뉴로\n");
    printf("메뉴 선택: ");
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        sscanf(buffer, "%d", &choice);
    }

    switch(choice) {
        case 1: { // 재고 수량 수정
            char target_id[20];
            printf("재고를 수정할 의류의 품번(itemID)을 입력하세요: ");
            if (fgets(buffer, sizeof(buffer), stdin)) {
                buffer[strcspn(buffer, "\n")] = 0;
                strncpy(target_id, buffer, sizeof(target_id) - 1);
            }

            int found_index = -1;
            for (int i = 0; i < clothing_count; i++) {
                if (strcmp(clothing_list[i].itemID, target_id) == 0) {
                    found_index = i;
                    break;
                }
            }

            if (found_index != -1) {
                int new_stock;
                printf("새로운 재고 수량을 입력하세요: ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    sscanf(buffer, "%d", &new_stock);
                }
                clothing_list[found_index].stock = new_stock;
                printf("재고 정보가 성공적으로 업데이트되었습니다.\n");
            } else {
                printf("해당 품번의 의류를 찾을 수 없습니다.\n");
            }
            break;
        }
        case 2: { // 의류 삭제
            char target_id[20];
            printf("삭제할 의류의 품번(itemID)을 입력하세요: ");
            if (fgets(buffer, sizeof(buffer), stdin)) {
                buffer[strcspn(buffer, "\n")] = 0;
                strncpy(target_id, buffer, sizeof(target_id) - 1);
            }

            int found_index = -1;
            for (int i = 0; i < clothing_count; i++) {
                if (strcmp(clothing_list[i].itemID, target_id) == 0) {
                    found_index = i;
                    break;
                }
            }

            if (found_index != -1) {
                // 찾은 위치부터 배열의 끝까지 모든 요소를 한 칸씩 앞으로 이동
                for (int i = found_index; i < clothing_count - 1; i++) {
                    clothing_list[i] = clothing_list[i + 1];
                }
                clothing_count--; // 전체 의류 수 감소
                printf("의류가 성공적으로 삭제되었습니다.\n");
            } else {
                printf("해당 품번의 의류를 찾을 수 없습니다.\n");
            }
            break;
        }
        case 3:
            return; // 이전 메뉴로 돌아가기
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
    }
}