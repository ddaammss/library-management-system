// Book_modification.h
#ifndef BOOK_MODIFICATION_H
#define BOOK_MODIFICATION_H

#include "Book_Class_Design.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdexcept>

// 수정 시도 결과를 구분하기 위한 결과 코드
enum class ModifyResult {
    Success,        // 수정 성공
    NotFound,       // 해당 ID의 도서가 없음
    InvalidStock    // 대출 중인 수량보다 적은 재고로 변경 시도
};

class BookModify {
public:
    // ID로 도서를 찾아 제목/저자/출판사/연도 수정 (재고 제외)
    static ModifyResult modifyInfo(std::vector<Book>& books, int id,
                                     const std::string& title,
                                     const std::string& author,
                                     const std::string& publisher,
                                     int pubYear) {
        Book* target = findById(books, id);
        if (!target) return ModifyResult::NotFound;

        target->setTitle(title);
        target->setAuthor(author);
        target->setPublisher(publisher);
        target->setPubYear(pubYear);
        return ModifyResult::Success;
    }

    // ID로 도서를 찾아 재고만 수정 (대출 중인 수량 미만으로는 불가)
    static ModifyResult modifyStock(std::vector<Book>& books, int id, int newStock) {
        Book* target = findById(books, id);
        if (!target) return ModifyResult::NotFound;

        try {
            target->setStock(newStock); // 대출 수량보다 적으면 여기서 예외 발생
        } catch (const std::invalid_argument&) {
            return ModifyResult::InvalidStock;
        }
        return ModifyResult::Success;
    }

    // 콘솔에서 ID 입력받아 정보 수정 (빈 입력은 기존 값 유지)
    static void modifyFromConsole(std::vector<Book>& books) {
        int id;
        std::cout << "수정할 도서 ID 입력: ";
        std::cin >> id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Book* target = findById(books, id);
        if (!target) {
            std::cout << "[수정 실패] ID " << id << "번 도서를 찾을 수 없습니다.\n";
            return;
        }

        std::string input;

        std::cout << "새 제목 (엔터 시 유지, 현재: " << target->getTitle() << "): ";
        std::getline(std::cin, input);
        if (!input.empty()) target->setTitle(input);

        std::cout << "새 저자 (엔터 시 유지, 현재: " << target->getAuthor() << "): ";
        std::getline(std::cin, input);
        if (!input.empty()) target->setAuthor(input);

        std::cout << "새 출판사 (엔터 시 유지, 현재: " << target->getPublisher() << "): ";
        std::getline(std::cin, input);
        if (!input.empty()) target->setPublisher(input);

        std::cout << "새 출판연도 (0 입력 시 유지, 현재: " << target->getPubYear() << "): ";
        int year;
        std::cin >> year;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (year != 0) target->setPubYear(year);

        std::cout << "새 재고 (-1 입력 시 유지, 현재: " << target->getStock() << "): ";
        int stock;
        std::cin >> stock;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (stock != -1) {
            try {
                target->setStock(stock);
            } catch (const std::invalid_argument& e) {
                std::cout << "[재고 수정 실패] 대출 중인 수량(" << target->getLoanedCount()
                           << "권)보다 적게 설정할 수 없습니다.\n";
            }
        }

        std::cout << "[수정 완료] ID " << id << " 도서 정보가 갱신되었습니다.\n";
    }

private:
    // ID로 도서를 찾아 포인터 반환 (없으면 nullptr)
    static Book* findById(std::vector<Book>& books, int id) {
        auto it = std::find_if(books.begin(), books.end(),
            [id](const Book& b) { return b.getId() == id; });
        return (it != books.end()) ? &(*it) : nullptr;
    }
};

#endif // BOOK_MODIFICATION_H