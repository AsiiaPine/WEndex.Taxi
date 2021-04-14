//
// Created by asiia on 10.04.2021.
//

#include "Order.h"
#include "Repository.h"
#include <cstdio>
//
//class OrderRepository : public Repository<Order> {
//private:
//    int file;
//public:
//    void OrderRepository(const char*path){
//        file = open("map.txt",O_RDWR);
//    }
//private:
//    int selectOrder(int index){
//        return lseek(file,0,SEEK_END);
//    }
//
//public:
//    int Create(Order* OrderPtr){
//        lseek(this->file,0,SEEK_END);
//        int filesize = tell(file);
//        OrderPtr->id=filesize/ sizeof(Order);
//        write(file,OrderPtr,sizeof(Order));
//    }
//    int Update(const Order* OrderPtr){
//        selectOrder(OrderPtr->id);
//        write(file,OrderPtr,sizeof(Order));
//    }
//};
//Order::Order(class Passenger *passenger, Address &address, const struct time &startTime, int id,
//             Address &startAddress, int cost) : Passenger(passenger), address(address), startTime(startTime), id(id), startAddress(startAddress),
//                                                      cost(cost) {}


OrderRepository::OrderRepository() : Repository("order.db",sizeof(Order)) {}
