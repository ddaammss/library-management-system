#include "header/LoanManager.h"
#include <iostream>
#include <ctime>
#include <cstring>

LoanManager::LoanManager() {}

// ----------------------------------------------------------------------------------------- 대출
bool LoanManager::loanBook(int memberId, int bookId, Book& book) {
    if (!book.loanOneCopy()) {
        std::cout << "대출 불가: 재고 없음 (도서 ID " << bookId << ")\n";
        return false;
    }
    std::string today = todayStr();
    std::string due   = dueDateStr();
    loans.emplace_back(memberId, bookId, today, due);
    std::cout << "대출 완료: 회원 " << memberId  << " → 도서 " << book.getTitle() << " 반납 예정: " << due << "\n";
    return true;
}
// ----------------------------------------------------------------------------------------- 반납
// bool LoanManager::returnBook(int loanId, Book& book) {
//     Loan* loan = findById(loanId);
//     if (!loan) {
//         std::cout << "반납 불가: 대출 기록 없음 (대출 ID " << loanId << ")\n";
//         return false;
//     }
//     if (loan->isReturned()) {
//         std::cout << "반납 불가: 이미 반납된 기록입니다\n";
//         return false;
//     }
//     int overdue = loan->getOverdueDays();
//     book.returnOneCopy();
//     loan->setReturnDate(todayStr());
//     if (overdue > 0) {
//         std::cout << "반납 완료 — 연체 " << overdue << "일 / 벌금 " << overdue * 100 << "원\n";
//     } else {
//         std::cout << "반납 완료\n";
//     }
//     return true;
// }

// Loan* LoanManager::findById(int loanId) {
//     for (auto& loan : loans) {
//         if (loan.getId() == loanId) return &loan;
//     }
//     return nullptr;
// }

// ----------------------------------------------------------------------------------------- 통계
// void LoanManager::printStats() const {
//     int total    = static_cast<int>(loans.size());
//     int active   = 0, returned = 0, overdue = 0;
//     for (const auto& loan : loans) {
//         if (loan.isReturned()) {
//             ++returned;
//         } else {
//             ++active;
//             if (loan.getOverdueDays() > 0) ++overdue;
//         }
//     }
//     std::cout << "=== 대출 통계 ===\n"
//               << "전체 대출: " << total    << "건\n"
//               << "대출 중:   " << active   << "건\n"
//               << "반납 완료: " << returned << "건\n"
//               << "연체 중:   " << overdue  << "건\n";
// }

std::string LoanManager::todayStr() {
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", t);
    return std::string(buf);
}

std::string LoanManager::dueDateStr(int loanDays) {
    time_t now = time(nullptr);
    now += static_cast<time_t>(loanDays) * 86400;
    struct tm* t = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", t);
    return std::string(buf);
}

void LoanManager::printAll() const {
    if (loans.empty()) { std::cout << "대출 기록 없음\n"; return; }
    for (const auto& loan : loans) loan.print();
}
