cmake_minimum_required(VERSION 3.17)
project(WEndex_Taxi)

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SRC_FILES_LIST "**/**.cpp" "**.cpp")
#add_executable(WEndex_Taxi main.cpp UserAppData/Passenger.cpp  UserAppData/Driver.cpp UserAppData/Driver.h UserAppData/Car.cpp UserAppData/Car.h UserAppData/CarType.h PassengerGateway.cpp PassengerGateway.h DriverGateway.cpp DriverGateway.h UserAppData/paymentMethods.h Order.cpp Order.h Address.h)
add_executable(WEndex_Taxi ${SRC_FILES_LIST})