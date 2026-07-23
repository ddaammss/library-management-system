// MemberManager.h에서 선언한 함수들의 실제 구현부
#include <iostream>
#include <fstream>
#include "header/MemberManager.h"

// 기능: MemberManager 객체가 처음 만들어질 때, 회원 ID를 1번부터 부여할 수 있도록 nextId 초기화
MemberManager::MemberManager() {
    // TODO: nextId 초기값 설정
    nextId = 1;
}

// 새 회원 정보(이름/연락처 등)를 받아서 nextId를 ID로 부여한 Member 객체를 만들고 members 목록에 추가한 뒤, 다음 가입자를 위해 nextId++
void MemberManager::addMember(string name, string phone, string joinDate) {
    
    Member m(nextId, name, phone, joinDate);
    
    // python의 .append()와 같은 개념
    members.push_back(m);
    nextId++;

}

bool MemberManager::removeMember(int id) {
    // TODO: id로 회원 찾아서 members에서 제거
    // 대출 중인 도서 있으면 삭제 거부 (대출 담당자(loan) 쪽 연동 필요)
    return false;
}

void MemberManager::printAllMembers() {
    // TODO: members 전체를 순회하며 출력
    // Member m : 원소를 복사해서 만듦 (비효율)
    // Member& m : 원본을 가리킴, 근데 이 함수 안에서 실수로 값을 바꿀 수도 있음
    // const Member& m : 원본을 가리키되 수정은 금지 → 복사 없이 안전하게 읽기만 할 때 표준적으로 쓰는 조합

    for (const Member& m : members) {
        cout << "id: " << m.getId() << endl;
        cout << "name: " << m.getName() << endl;
        cout << "phone_number: " << m.getPhone() << endl;
        cout << "join_date: " << m.getJoinDate() << endl;
    }
}

Member* MemberManager::findMemberById(int id) {
    // TODO: id로 members에서 검색, 없으면 nullptr 리턴
    // &는 복사본 말고 벡터 안에 원본을 가르키라는 표시
    for (Member& m : members) {
        if (m.getId() == id) {
            // m이 저장된 메모리 위치를 반환
            // 함수 리턴 타입이 Member* 즉, 포인터이기에 메모리 주소를 반환해야함
            return &m;
        }
    }
    return nullptr;
}

void MemberManager::saveToFile(string path) {
    // TODO: ofstream으로 members를 파일에 한 줄씩 저장
}

void MemberManager::loadFromFile(string path) {
    // TODO: ifstream으로 파일 읽어서 members 채우기
}
