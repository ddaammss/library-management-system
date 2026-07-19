#include "header/Loan.h"
#include <iostream>
#include <ctime>
#include <cstdio>
#include <sstream>

int Loan::nextId = 1;

Loan::Loan() : id(nextId++), memberId(0), bookId(0) {}

Loan::Loan(int memberId, int bookId, const std::string& loanDate, const std::string& dueDate)
    : id(nextId++), memberId(memberId), bookId(bookId), loanDate(loanDate), dueDate(dueDate), returnDate("") {}

Loan::Loan(int id, int memberId, int bookId, const std::string& loanDate, const std::string& dueDate)
    : id(id), memberId(memberId), bookId(bookId), loanDate(loanDate), dueDate(dueDate), returnDate("") {}

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
    if (isReturned()) return 0;

    int year, month, day;
    if (std::sscanf(dueDate.c_str(), "%d-%d-%d", &year, &month, &day) != 3) return 0;

    struct tm tm_due = {};
    tm_due.tm_year  = year - 1900;
    tm_due.tm_mon   = month - 1;
    tm_due.tm_mday  = day;
    tm_due.tm_isdst = -1;
    time_t due_time = mktime(&tm_due);

    time_t now = time(nullptr);
    double diff = difftime(now, due_time);
    int days = static_cast<int>(diff / 86400);
    return days > 0 ? days : 0;
}

void Loan::setReturnDate(const std::string& rd) {
    returnDate = rd;
}

void Loan::print() const {
    std::cout << "[대출 #" << id << "] "  << " 회원:" << memberId << " 도서:" << bookId << " 대출일:" << loanDate << " 반납예정:" << dueDate;
    if (isReturned()) {
        std::cout << "반납일:" << returnDate;
    } else {
        int overdue = getOverdueDays();
        if (overdue > 0)
            std::cout << " [연체 " << overdue << "일]";
        else
            std::cout << " [대출 중]";
    }
    std::cout << "\n";
}

std::string Loan::toCSV() const {
    std::ostringstream oss;
    oss << id << '|' << memberId << '|' << bookId << '|'
        << loanDate << '|' << dueDate << '|' << returnDate;
    return oss.str();
}

Loan Loan::fromCSV(const std::string& line) {
    std::stringstream ss(line);
    std::string idStr, memberIdStr, bookIdStr, ld, dd, rd;
    std::getline(ss, idStr, '|');
    std::getline(ss, memberIdStr, '|');
    std::getline(ss, bookIdStr, '|');
    std::getline(ss, ld, '|');
    std::getline(ss, dd, '|');
    std::getline(ss, rd, '|');

    Loan loan(std::stoi(idStr), std::stoi(memberIdStr), std::stoi(bookIdStr), ld, dd);
    loan.setReturnDate(rd);
    return loan;
}

void Loan::syncNextId(int loadedMaxId) {
    if (loadedMaxId + 1 > nextId)
        nextId = loadedMaxId + 1;
}
