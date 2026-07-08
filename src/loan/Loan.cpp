#include "Loan.h"
#include <iostream>
#include <ctime>

Loan::Loan() : id(0), memberId(0), bookId(0) {}

Loan::Loan(int id, int memberId, int bookId, const std::string& loanDate, const std::string& dueDate) : id(id), memberId(memberId), bookId(bookId),loanDate(loanDate), dueDate(dueDate), returnDate("") {}

int Loan::getId() const { return id; }
int Loan::getMemberId() const { return memberId; }
int Loan::getBookId() const { return bookId; }
std::string Loan::getLoanDate() const { return loanDate; }
std::string Loan::getDueDate() const { return dueDate; }
std::string Loan::getReturnDate() const { return returnDate; }

bool Loan::isReturned() const {
    return !returnDate.empty();
}

int Loan::getOverdueDays() const {
    // TODO: 오늘 날짜와 dueDate 비교해서 연체 일수 반환
    // 반납됐으면 0 반환
    return 0;
}

void Loan::setReturnDate(const std::string& returnDate) {
    this->returnDate = returnDate;
}

void Loan::print() const {
    // TODO: 대출 정보 출력
}
