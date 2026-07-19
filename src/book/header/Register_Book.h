// Register_Book.h
#ifndef REGISTER_BOOK_H
#define REGISTER_BOOK_H

#include "Book_Class_Design.h"
#include <vector>
#include <string>
#include <iostream>
#include <limits>

class BookRegister {
public:
    // ---- 사전검증: Book 객체를 만들기 전에 ISBN 중복 여부만 확인 ----
    // Book 생성자를 호출하지 않으므로 nextId를 소비하지 않음
    static bool isIsbnTaken(const std::vector<Book>& books, const std::string& isbn) {
        for (const auto& b : books) {
            if (b.getIsbn() == isbn) return true;
        }
        return false;
    }

    // ---- 이미 만들어진 Book을 목록에 등록 ----
    // 주의: 이 함수를 호출하기 "전에" isIsbnTaken()으로 먼저 검증했어야 함
    //       (여기서도 방어적으로 한 번 더 체크는 하지만, ID 낭비 자체는
    //        여기 도달하기 전에 이미 막았어야 하는 게 핵심)
    static bool registerBook(std::vector<Book>& books, const Book& newBook) {
        if (isIsbnTaken(books, newBook.getIsbn())) {
            std::cerr << "[등록 실패] 이미 존재하는 ISBN입니다: "
                      << newBook.getIsbn() << "\n";
            return false;
        }
        books.push_back(newBook);
        std::cout << "[등록 성공] ID " << newBook.getId()
                   << " - " << newBook.getTitle() << "\n";
        return true;
    }

    // ---- 콘솔에서 직접 입력받아 등록 ----
    // ISBN을 먼저 입력받아 중복 여부를 확인한 뒤에만 Book을 생성함
    static void registerBookFromConsole(std::vector<Book>& books) {
        std::string isbn, title, author, publisher;
        int pubYear, stock;

        // 1. ISBN 먼저 입력받고, 중복이면 Book을 만들지 않고 재입력 요청
        while (true) {
            std::cout << "ISBN 입력: ";
            std::getline(std::cin, isbn);

            if (isIsbnTaken(books, isbn)) {
                std::cout << "[등록 실패] 이미 존재하는 ISBN입니다. 다시 입력해주세요.\n";
                continue;
            }
            break;
        }

        // 2. 중복이 아님이 확정된 뒤에만 나머지 정보 입력받음
        std::cout << "제목 입력: ";
        std::getline(std::cin, title);

        std::cout << "저자 입력: ";
        std::getline(std::cin, author);

        std::cout << "출판사 입력: ";
        std::getline(std::cin, publisher);

        pubYear = readValidatedInt("출판연도 입력: ", 0, 2100);
        stock = readValidatedInt("재고 수량 입력: ", 0, 100000);

        // 3. 이 시점에는 중복이 아님이 보장됨 → 안전하게 Book 생성
        Book newBook(isbn, title, author, publisher, pubYear, stock);
        books.push_back(newBook);
        std::cout << "[등록 성공] ID " << newBook.getId()
                   << " - " << newBook.getTitle() << "\n";
    }

private:
    static int readValidatedInt(const std::string& prompt, int minVal, int maxVal) {
        int value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;

            if (std::cin.fail() || value < minVal || value > maxVal) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "잘못된 입력입니다. " << minVal << " ~ " << maxVal
                          << " 사이 숫자를 입력해주세요.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
};

#endif // REGISTER_BOOK_H