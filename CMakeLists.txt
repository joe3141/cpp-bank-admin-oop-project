cmake_minimum_required(VERSION 3.13)
project(BankOOP)

set(CMAKE_CXX_STANDARD 14)

add_executable(BankOOP main.cpp Account.h Account.cpp StudentAccount.h StudentAccount.cpp StandardAccount.cpp StandardAccount.h Transaction.cpp Transaction.h)