// 회원 전체 목록을 관리(가입/탈퇴/검색/출력/파일저장)하는 클래스를 선언하는 파일
#ifndef MEMBER_MANAGER_H
#define MEMBER_MANAGER_H

#include <vector>
#include <string>
#include "Member.h"

using namespace std;

class MemberManager {
private:
    vector<Member> members;
    int nextId;

public:
    MemberManager();

    void addMember(string name, string phone, string joinDate);
    bool removeMember(int id);
    void printAllMembers();
    Member* findMemberById(int id);

    void saveToFile(string path);
    void loadFromFile(string path);
};

#endif
