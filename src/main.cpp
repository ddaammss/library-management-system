#include <iostream>
#include "book/BookManager.h"
#include "member/MemberManager.h"
#include "loan/LoanManager.h"
#include "search/Search.h"

int main() {
    BookManager bookManager;
    MemberManager memberManager;
    LoanManager loanManager;

    std::cout << "도서관 관리 시스템 시작" << std::endl;

    return 0;
}
