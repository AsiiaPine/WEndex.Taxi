//
// Created by asiia on 01.04.2021.
//

#ifndef WENDEX_TAXI_DRIVERGATEWAY_H
#define WENDEX_TAXI_DRIVERGATEWAY_H
#include "UserAppData/Driver.h"
#include "Order.h"
class DriverGateway {
    Driver* driver;
//    IsRiding isRiding;
    double rating;
    void AcceptOrder(Order* order);
//    void ChoseStatus(Status newStatus);
    void IamRiding();
    void StopTheRide();
};


#endif //WENDEX_TAXI_DRIVERGATEWAY_H
