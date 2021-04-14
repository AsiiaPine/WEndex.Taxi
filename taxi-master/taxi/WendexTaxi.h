//
// Created by asiia on 01.04.2021.
//

#ifndef WENDEX_TAXI_WENDEXTAXI_H
#define WENDEX_TAXI_WENDEXTAXI_H

#include "PassengerGateway.h"
#include "DriverGateway.h"

class WendexTaxi {
public:
    WendexTaxi();
public:
    InitSystem();
    PassengerGateway *GetPassengerGateway(string username,string password);
    DriverGateway *GetDriverGateway(string username,string password);
};
#endif //WENDEX_TAXI_WENDEXTAXI_H
