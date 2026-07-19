// Book_Class_Design.h
#ifndef BOOK_CLASS_DESIGN_H
#define BOOK_CLASS_DESIGN_H

#include <string>
#include <sstream>
#include <stdexcept>

class Book {
private:
    int id;                 // 자동 부여되는 고유 ID
    std::string isbn;
    std::string title;
    std::string author;
    std::string publisher;
    int pubYear;
    int stock;               // 전체 보유 수량
    int loanedCount;         // 현재 대출 중인 수량 (stock 중 일부)

    static int nextId;        // 다음에 부여할 ID (자동 증가)

public:
    // ---- 생성자 ----
    // 신규 등록용: ID 자동 부여
    Book(const std::string& isbn_,
         const std::string& title_,
         const std::string& author_,
         const std::string& publisher_,
         int pubYear_,
         int stock_)
        : id(nextId++), isbn(isbn_), title(title_), author(author_),
          publisher(publisher_), pubYear(pubYear_), stock(stock_), loanedCount(0)
    {}

    // 파일에서 불러올 때용: ID를 명시적으로 지정
    Book(int id_,
         const std::string& isbn_,
         const std::string& title_,
         const std::string& author_,
         const std::string& publisher_,
         int pubYear_,
         int stock_, // 재고
         int loanedCount_) // 대출 수량
        : id(id_), isbn(isbn_), title(title_), author(author_),
          publisher(publisher_), pubYear(pubYear_), stock(stock_), loanedCount(loanedCount_)
    {}

    // ---- Getter (불변 조회 / 값을 가져오는 함수) ----
    int getId() const { return id; }
    const std::string& getIsbn() const { return isbn; }
    const std::string& getTitle() const { return title; }
    const std::string& getAuthor() const { return author; }
    const std::string& getPublisher() const { return publisher; }
    int getPubYear() const { return pubYear; }
    int getStock() const { return stock; }
    int getLoanedCount() const { return loanedCount; }
    int getAvailable() const { return stock - loanedCount; } // 대출 가능 수량

    // ---- Setter (수정 가능 항목만 / 값을 설정하는 함수) ----
    // ISBN, ID는 의도적으로 setter 없음 (불변)
    void setTitle(const std::string& t) { title = t; }
    void setAuthor(const std::string& a) { author = a; }
    void setPublisher(const std::string& p) { publisher = p; }
    void setPubYear(int y) { pubYear = y; }

    // 재고 조정 (입고/폐기 등). 대출 수량보다 적게 줄이는 건 금지.
    void setStock(int s) {
        if (s < loanedCount)
            throw std::invalid_argument("stock cannot be less than loaned count");
        stock = s;
    }

    // ---- 대출 상태 조작 (대출/반납 모듈에서 호출) ----
    bool loanOneCopy() { // 대출 시 대출 변수의 값을 증가시켜 재고와 연산
        if (getAvailable() <= 0) return false;
        ++loanedCount;
        return true;
    }
    bool returnOneCopy() { // 반납 시 대출 변수의 값을 감소시켜 재고와 연산
        if (loanedCount <= 0) return false;
        --loanedCount;
        return true;
    }

    // ---- 삭제 가능 여부 ----
    bool isDeletable() const { return loanedCount == 0; } // 도서의 삭제 가능 여부 체크

    // ---- 파일 저장용 직렬화 ----
    //객체 → 문자열/파일로 변환 (저장할 때)
    // 구분자 '|' 사용 (제목/저자에 콤마가 들어가도 안전)
    std::string toCSV() const {
        std::ostringstream oss;
        oss << id << '|' << isbn << '|' << title << '|' << author << '|'
            << publisher << '|' << pubYear << '|' << stock << '|' << loanedCount;
        return oss.str();
    }

    // 파일 역직렬화 문자열/파일 → 객체로 복원 (불러올 때)
    static Book fromCSV(const std::string& line) {
        std::stringstream ss(line);
        std::string idStr, isbn_, title_, author_, publisher_, yearStr, stockStr, loanedStr;
        std::getline(ss, idStr, '|');
        std::getline(ss, isbn_, '|');
        std::getline(ss, title_, '|');
        std::getline(ss, author_, '|');
        std::getline(ss, publisher_, '|');
        std::getline(ss, yearStr, '|');
        std::getline(ss, stockStr, '|');
        std::getline(ss, loanedStr, '|');

        Book b(std::stoi(idStr), isbn_, title_, author_, publisher_,
               std::stoi(yearStr), std::stoi(stockStr), std::stoi(loanedStr));
        return b;
    }

    // 파일 로딩 후, 다음 ID가 겹치지 않도록 동기화
    static void syncNextId(int loadedMaxId) {
        if (loadedMaxId + 1 > nextId)
            nextId = loadedMaxId + 1;
    }
};

// static 멤버 정의 (cpp 파일 하나에서만!)
// Book_Class_Design.cpp 같은 파일을 만들어 아래 한 줄을 넣어주세요:
// int Book::nextId = 1;

#endif // BOOK_CLASS_DESIGN_H