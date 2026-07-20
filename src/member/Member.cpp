// Member.h에서 선언한 함수들의 실제 구현부
#include "header/Member.h"

Member::Member(int id, string name, string phone, string joinDate) {
    // 매개변수 이름(id, name...)이 멤버 변수 이름과 똑같아서
    // this->id 처럼 "this->"를 붙여야 "내 멤버 변수"라는 뜻이 됨.
    // this->를 안 붙이면 컴파일러가 매개변수 id를 자기 자신에 대입하는 걸로 봐서 아무 일도 안 일어남.
    this->id = id;
    this->name = name;
    this->phone = phone;
    this->joinDate = joinDate;

    // 가입 직후 기본 상태는 우리가 정하는 것 (매개변수로 안 받음)
    canBorrow = true;
    fineAmount = 0;
}


// getter
int Member::getId() const {
    // 그냥 멤버 변수를 돌려주기만 하는 함수는 이렇게 한 줄로 끝
    // 함수 끝에 붙는 const는 "이 함수는 멤버 변수를 안 바꾼다"는 약속.
    // getter는 값을 읽기만 하니까 항상 const를 붙여줌.
    return id;
}

string Member::getName() const {
    return name;
}

string Member::getPhone() const {
    // TODO
    return phone;
}

string Member::getJoinDate() const {
    // TODO
    return joinDate;
}

bool Member::isCanBorrow() const {
    // TODO
    return canBorrow;
}

int Member::getFineAmount() const {
    // TODO
    return fineAmount;
}




// setter
void Member::setName(string newName) {
    name = newName;
}

void Member::setPhone(string newPhone) {
    phone = newPhone;
}

void Member::setCanBorrow(bool status) {
    canBorrow = status;
}


// fine
void Member::addFine(int amount) {
    // TODO: 벌금 누적, 벌금 있으면 canBorrow false 처리

    fineAmount += amount;
    if (fineAmount > 0)
    canBorrow = false;

}
    

void Member::payFine(int amount) {
    // TODO: 벌금 차감, 다 갚으면 canBorrow true 처리

    fineAmount -= amount;
    if (fineAmount <= 0)
    canBorrow = true;

}
