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
#include "Address.h"
#include "UserAppData/User.h"

using namespace std;
enum OrderType {

};


struct OrderModel {
    int32_t id = 0;
    int32_t passengerId = 0;
    int32_t driverId = 0;
    int32_t cost = 0;
    int32_t startAddressId = 0;
    int32_t endAddressId = 0;
    uint64_t startTime = 0;
    uint64_t endTime = 0;
};

class Order {
private:

    OrderModel *m;
    Address endAddress;
    Address startAddress;
    PaymentMethod paymentMethod;
    Passenger *passenger;
    Driver *driver;

public:
    explicit Order(OrderModel *model, Address startAddress, Address endAddress, PaymentMethod method,Passenger *pass, Driver *driver)
            : m(model), startAddress(startAddress), endAddress(endAddress), paymentMethod(method), passenger(passenger), driver(driver) {}

    int getId() {
        return m->id;
    }

    Passenger *getPassenger() {
        return passenger;
    }

    Driver *getDriver() {
        return driver;
    }

    void setDriver(Driver *driver) {
        this->driver = driver;
    }

    Address getStartAddress() {
        return startAddress;
    }

    Address getEndAddress() {
        return endAddress;
    }

    PaymentMethod getPaymentMethod() {
        return paymentMethod;
    }

    void setPaymentMethod(PaymentMethod method) {
        paymentMethod = method;
    }

    void setStartAddress(Address address) {
        startAddress = address;
        m->startAddressId = address.id;
    }

    void setEndAddress(Address address) {
        endAddress = address;
        m->endAddressId = address.id;
    }

};

class OrderRepository : public Repository<OrderModel, sizeof(OrderModel)> {
public:
    explicit OrderRepository(Database *db) : Repository(db, db->OpenTable("order.table")) {};

    std::vector<OrderModel *> FindAllByPassengerId(int32_t passId) {
        return FindEntitiesByFieldValue(&passId, offsetof(OrderModel, passengerId), sizeof(int32_t));
    }
};

#endif //WENDEX_TAXI_ORDER_H
