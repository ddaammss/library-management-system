CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = library

SRCS = src/main.cpp \
       src/book/Book.cpp \
       src/book/BookManager.cpp \
       src/member/Member.cpp \
       src/member/MemberManager.cpp \
       src/loan/Loan.cpp \
       src/loan/Reservation.cpp \
       src/loan/LoanManager.cpp \
       src/search/Search.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
