// File_Input_Output.h
#ifndef FILE_INPUT_OUTPUT_H
#define FILE_INPUT_OUTPUT_H

#include "Book_Class_Design.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

class BookFileIO {
public:
    // 도서 목록을 파일에 저장 (한 줄 = 도서 한 권)
    // 성공하면 true, 파일을 못 열면 false
    static bool save(const std::vector<Book>& books, const std::string& filepath) {
        std::ofstream out(filepath);
        if (!out.is_open()) {
            std::cerr << "[저장 실패] 파일을 열 수 없습니다: " << filepath << "\n";
            return false;
        }

        for (const auto& b : books) {
            out << b.toCSV() << "\n";
        }

        out.close();
        std::cout << "[저장 완료] " << books.size() << "권을 " << filepath << "에 저장했습니다.\n";
        return true;
    }

    // 파일에서 도서 목록을 불러옴
    // 파일이 없으면 빈 목록으로 시작 (에러 아님)
    // 성공하면 true (파일이 없는 것도 성공으로 취급)
    static bool load(std::vector<Book>& books, const std::string& filepath) {
        std::ifstream in(filepath);
        if (!in.is_open()) {
            std::cout << "[불러오기] 기존 데이터 파일이 없어 새로 시작합니다.\n";
            return true; // 첫 실행 시 파일이 없는 건 정상 상황
        }

        books.clear();
        int maxId = 0;
        std::string line;
        int lineNumber = 0;

        while (std::getline(in, line)) {
            ++lineNumber;
            if (line.empty()) continue; // 빈 줄은 건너뜀

            try {
                Book b = Book::fromCSV(line);
                if (b.getId() > maxId) maxId = b.getId();
                books.push_back(b);
            } catch (const std::exception& e) {
                // 한 줄이 손상돼도 전체를 중단하지 않고 그 줄만 건너뜀
                std::cerr << "[불러오기 경고] " << lineNumber
                           << "번째 줄이 손상되어 건너뜁니다: " << line << "\n";
            }
        }

        in.close();
        Book::syncNextId(maxId); // 다음 등록 ID가 기존 ID와 겹치지 않도록 동기화

        std::cout << "[불러오기 완료] " << books.size() << "권을 불러왔습니다.\n";
        return true;
    }
};

#endif // FILE_INPUT_OUTPUT_H