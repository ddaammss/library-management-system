// Full_Book_List_Output.h
#ifndef FULL_BOOK_LIST_OUTPUT_H
#define FULL_BOOK_LIST_OUTPUT_H

#include "Book_Class_Design.h"
#include <vector>
#include <iostream>
#include <iomanip>

class BookListOutput {
public:
    // 전체 도서 목록을 테이블 형식으로 출력
    static void printAll(const std::vector<Book>& books) {
        if (books.empty()) {
            std::cout << "등록된 도서가 없습니다.\n";
            return;
        }

        printHeader();
        for (const auto& b : books) {
            printRow(b);
        }
        printSeparator();
        std::cout << "총 " << books.size() << "권 등록됨\n";
    }

private:
    // 표 상단 헤더 (열 제목 + 구분선)
    static void printHeader() {
        printSeparator();
        std::cout << std::left
                   << std::setw(5)  << "ID"
                   << std::setw(15) << "ISBN"
                   << std::setw(25) << "제목"
                   << std::setw(15) << "저자"
                   << std::setw(15) << "출판사"
                   << std::setw(8)  << "연도"
                   << std::setw(8)  << "재고"
                   << std::setw(8)  << "대출중"
                   << "\n";
        printSeparator();
    }

    // 도서 한 권을 한 줄로 출력
    static void printRow(const Book& b) {
        std::cout << std::left
                   << std::setw(5)  << b.getId()
                   << std::setw(15) << b.getIsbn()
                   << std::setw(25) << b.getTitle()
                   << std::setw(15) << b.getAuthor()
                   << std::setw(15) << b.getPublisher()
                   << std::setw(8)  << b.getPubYear()
                   << std::setw(8)  << b.getStock()
                   << std::setw(8)  << b.getLoanedCount()
                   << "\n";
    }

    // 구분선 출력 (열 너비 총합에 맞춰 '-' 반복)
    static void printSeparator() {
        std::cout << std::string(99, '-') << "\n";
    }
};

#endif // FULL_BOOK_LIST_OUTPUT_H