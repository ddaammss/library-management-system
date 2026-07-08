#pragma once
#include <string>

class Loan {
public:
    Loan();
    Loan(int id, int memberId, int bookId, const std::string& loanDate, const std::string& dueDate);

    int getId() const;
    int getMemberId() const;
    int getBookId() const;
    std::string getLoanDate() const;
    std::string getDueDate() const;
    std::string getReturnDate() const;

    bool isReturned() const;
    int getOverdueDays() const;

    void setReturnDate(const std::string& returnDate);

    void print() const;

private:
    int id;
    int memberId;
    int bookId;
    std::string loanDate;
    std::string dueDate;
    std::string returnDate;
};
