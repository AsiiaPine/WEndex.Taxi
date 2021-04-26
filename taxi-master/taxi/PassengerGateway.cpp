//
// Created by asiia on 01.04.2021.
//

#ifndef WENDEX_TAXI_PASSENGERGATEWAY_H
#define WENDEX_TAXI_PASSENGERGATEWAY_H


#include "UserAppData/paymentMethods.h"
#include "Address.h"
#include "CarType.h"
#include "UserAppData/paymentMethods.h"
#include "UserAppData/Passenger.h"
#include "Order.h"
#include "WendexTaxi.h"
#include "AccessManager.h"

class PassengerGateway {
private:

    AccessManager *accessManager;
    UserModel *identity;
    struct System *system;
    Passenger* passenger;
    Order* currentOrder;
    //static OrderRepository* orderRepository;
    static vector<Passenger*> AllPassengers;

    UserRepository *userRepository;
    OrderRepository *orderRepository;
    AddressRepository *addressRepository;
    PassengerRepository *passengerRepository;
    DriverRepository *driverRepository;
    CarRepository *carRepository;

public:

    PassengerGateway(System *system, UserModel *identity, AccessManager *accessManager);


    virtual vector<Order *> SeeOrderHistory() ;

    virtual PaymentMethod SeePaymentMethod();

    virtual void UpdatePaymentMethod(PaymentMethod newMethod) ;

    virtual Address SeePinnedAddress();

    virtual void UpdateAddress(Address adr);

    virtual void
    OrderTheRide(CarType type, Address startAddress, Address destinationAddress, int cost, PaymentMethod paymentMethod);

    virtual Coords CurrentCoordinates();

    virtual Order *TheBill(Order *order);

};


PassengerGateway *GetDefaultPassengerGateway(UserModel *identity);

#endif //WENDEX_TAXI_PASSENGERGATEWAY_H
