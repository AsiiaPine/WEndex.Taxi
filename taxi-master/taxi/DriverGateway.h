//
// Created by asiia on 01.04.2021.
//

#ifndef WENDEX_TAXI_DRIVERGATEWAY_H
#define WENDEX_TAXI_DRIVERGATEWAY_H

#include "UserAppData/Driver.h"
#include "Order.h"
#include "AccessManager.h"
#include "WendexTaxi.h"

class DriverGateway {
//    IsRiding isRiding;
    double rating;
private:
    AccessManager *accessManager;
    UserModel *identity;

    DriverRepository *driverRepository;
    OrderRepository *orderRepository;
    CarRepository *carRepository;
public:
    struct System *system;
    Driver *driver;
    DriverGateway(System *system, UserModel *identity, AccessManager *accessManager);

//    DriverGateway(System *pSystem, UserModel *pModel);

public:

    double GetRating();

    Car GetCurrentCar();

    std::vector<Car> GetAllCars();

    void AcceptOrder(Order *order);

    void DeclineOrder(Order *order);

    int Status();

    void SetStatus(int newStatus);

    std::vector<Order*> GetOrderHistory();

    std::vector<Order*> GetAvailableOrders();

    void StopTheRide();

};


#endif //WENDEX_TAXI_DRIVERGATEWAY_H
