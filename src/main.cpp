#include <iostream>
#include "member/header/Member.h"

using namespace std;

int main() {
    Member m(1, "홍길동", "010-1234-5678", "2026-07-16");

    cout << "id: " << m.getId() << endl;
    cout << "name: " << m.getName() << endl;

    return 0;
}
