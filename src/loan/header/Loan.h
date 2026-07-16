#pragma once
#include <string>
#include <sstream>

class Loan {
public:
    Loan();
    Loan(int memberId, int bookId, const std::string& loanDate, const std::string& dueDate);
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

    std::string toCSV() const;
    static Loan fromCSV(const std::string& line);
    static void syncNextId(int loadedMaxId);

private:
    int id;
    int memberId;
    int bookId;
    std::string loanDate;
    std::string dueDate;
    std::string returnDate;

    static int nextId;
};
