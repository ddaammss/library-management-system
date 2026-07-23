// Delete_Books.h
#ifndef DELETE_BOOKS_H
#define DELETE_BOOKS_H

#include "Book_Class_Design.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

// 삭제 시도 결과를 구분하기 위한 결과 코드
enum class DeleteResult {
    Success,        // 삭제 성공
    NotFound,       // 해당 ID의 도서가 없음
    LoanedCopies    // 대출 중인 도서라 삭제 불가
};

class BookDelete {
public:
    // ID로 도서를 찾아 삭제 시도
    static DeleteResult deleteById(std::vector<Book>& books, int id) {
        // std::find_if: 조건을 만족하는 첫 원소를 찾아 iterator를 리턴
        auto it = std::find_if(books.begin(), books.end(),
            [id](const Book& b) { return b.getId() == id; });

        if (it == books.end()) {
            return DeleteResult::NotFound; // 못 찾음
        }

        if (!it->isDeletable()) {
            return DeleteResult::LoanedCopies; // 대출 중이라 삭제 불가
        }

        books.erase(it); // 실제 삭제
        return DeleteResult::Success;
    }

    // 콘솔에서 ID 입력받아 삭제 + 결과 메시지 출력까지 수행
    static void deleteByIdFromConsole(std::vector<Book>& books) {
        int id;
        std::cout << "삭제할 도서 ID 입력: ";
        std::cin >> id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        DeleteResult result = deleteById(books, id);

        switch (result) {
            case DeleteResult::Success:
                std::cout << "[삭제 성공] ID " << id << " 도서가 삭제되었습니다.\n";
                break;
            case DeleteResult::NotFound:
                std::cout << "[삭제 실패] ID " << id << "번 도서를 찾을 수 없습니다.\n";
                break;
            case DeleteResult::LoanedCopies:
                std::cout << "[삭제 실패] 대출 중인 도서는 삭제할 수 없습니다.\n";
                break;
        }
    }
};

#endif // DELETE_BOOKS_H