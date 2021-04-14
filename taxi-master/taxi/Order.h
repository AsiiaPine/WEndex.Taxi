//
// Created by asiia on 10.04.2021.
//

#ifndef WENDEX_TAXI_ORDER_H
#define WENDEX_TAXI_ORDER_H
#include <cinttypes>
#include <ctime>
#include"Repository.h"
#include <stdio.h>
#include <iostream>
#include <vector>
//
//using namespace std;
//struct time{
//    std::time_t t = std::time(0);   // get time now
//    std::tm* now = std::localtime(&t);
//    int hours=now->tm_hour;
//    int minutes=now->tm_min;
//};
//void PrintTheTime(struct time Time){
//    printf("%s",ctime(&Time.t));
//    cout<<Time.hours<<":"<<Time.minutes;
//}
#include "Address.h"
#include "UserAppData/Driver.h"

using namespace std;
enum OrderType{

};


struct OrderModel {
    int32_t id;
    int32_t passengerId;
    int32_t cost;
    int32_t startAddressId;
    int32_t endAddressId;
    uint64_t startTime;
    uint64_t endTime;
};

struct Order {
    //Order(Passenger *passenger, Address &address, const struct time &startTime, int id, Address &startAddress, int cost);
//    Address address;
//    struct time startTime, finishTime;
//    int id;
//    Address startAddress;
//    int cost;
};

//int ComputeCost(struct time start, struct time finish){
//
//}
void PrintTheOrder(Order order){
//    cout<<"Address: ";
//    PrintTheAddress(order.address);
//    cout<<"Initial address:";
//    PrintTheAddress(order.startAddress);
//    cout<<"Cost: "<<order.cost;
//    cout<<"Start time: ";
//    PrintTheTime(order.startTime);
//    cout<<endl;
//    cout<<"Start time: ";
//    PrintTheTime(order.finishTime);
//    cout<<endl;
}
vector<Order> AllOrders;
vector<Order> Finished;



class OrderRepository : public Repository<OrderModel> {
public:
    OrderRepository();

    vector<OrderModel> GetOrdersByPassengerId(int passengerId) {
        vector<OrderModel> orderList;
        for (int i = 0; ; i++) {
            selectEntity(i);
            if (!hasCurrent()) {
                break;
            }
            OrderModel order;
            readCurrent(&order);
            if (order.passengerId == passengerId) {
                orderList.emplace_back(order);
            }
        }
        return orderList;
    }
};
//
//class OrderRepository1 : public Repository<Order> {
//private:
//    int file;
//
//public:
//    int amountOfOrders=0;
//
//    OrderRepository(const char *path1, int entitySize, const char *path) : Repository(path1, entitySize) {
//        file = open("map.txt",O_RDWR);
//    }
//protected:
//    int selectOrder(int index) {
//        return lseek(file,index * sizeof(struct Order), SEEK_SET);
//    }
//
//    bool hasNext() {
//        return f
//    }
//
//private:
//    int &getId(Order *entity) override {
//        return entity->id;
//    }
//
//public:
//    Order GetOrder(int index){
//        selectOrder(index);
//        return read(file,&Order,sizeof(struct Order));
//    }
////protected:
//public:
////    int Create(Order* OrderPtr){
////        lseek(this->file,0,SEEK_END);
////        int filesize = tell(file);
////        OrderPtr->id=filesize/ sizeof(Order);
////        write(file,OrderPtr,sizeof(Order));
////        this->amountOfOrders++;
////    }
//    int Update(const Order* OrderPtr){
//        selectOrder(OrderPtr->id);
//        write(file,OrderPtr,sizeof(Order));
//    }
//};


#endif //WENDEX_TAXI_ORDER_H
