#pragma once
#include <vector>
#include <string>
#include "Loan.h"
#include "../../book/header/Book_Class_Design.h"

class LoanManager {
public:
    LoanManager();

    bool loanBook(int memberId, int bookId, Book& book);
    bool returnBook(int loanId, Book& book);

    void printAll() const;
    // void printStats() const;

private:
    std::vector<Loan> loans;

    Loan* findById(int loanId);
    static std::string todayStr();
    static std::string dueDateStr(int loanDays = 14);
};
