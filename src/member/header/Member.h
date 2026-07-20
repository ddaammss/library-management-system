// 회원 한 명의 정보(이름, 연락처, 벌금 등)와 관련 함수를 선언하는 파일
#ifndef MEMBER_H
#define MEMBER_H

#include <string>
using namespace std;

class Member {
private:
    int id;
    string name;
    string phone;
    string joinDate;
    bool canBorrow;
    int fineAmount;

public:
    Member(int id, string name, string phone, string joinDate);

    // getter
    int getId() const;
    string getName() const;
    string getPhone() const;
    string getJoinDate() const;
    bool isCanBorrow() const;
    int getFineAmount() const;

    // setter
    void setName(string newName);
    void setPhone(string newPhone);
    void setCanBorrow(bool status);

    // 벌금 처리
    void addFine(int amount);
    void payFine(int amount);
};

#endif
