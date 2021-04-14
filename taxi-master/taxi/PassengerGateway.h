//
// Created by asiia on 01.04.2021.
//

#ifndef WENDEX_TAXI_PASSENGERGATEWAY_H
#define WENDEX_TAXI_PASSENGERGATEWAY_H


#include "UserAppData/paymentMethods.h"
#include "Address.h"
#include "UserAppData/CarType.h"
#include "UserAppData/paymentMethods.h"
#include "UserAppData/Passenger.h"
#include "Order.h"

class PassengerGateway {
private:
    Passenger* passenger;
    Order* currentOrder;
    static OrderRepository* orderRepository;
    static vector<Passenger*> AllPassengers;

public:



    //void LogOut() = 0;

    //static PassengerGateway* SignUp(string UserName, string password, string email) = 0;

    virtual void SeeOrderHistory() = 0;

    virtual void SeePayMethod() = 0;

    virtual void UpdatePay(PaymentMethod newMethod) = 0;

    virtual void PinnedAddr() = 0;

    virtual void UpdateAddr(Address adr) = 0;

    virtual void OrderTheRide(CarType type, Address address, Address startAddress, PaymentMethod paymentMethod) = 0;

    virtual Coords CurrentCoordinates() = 0;

    virtual void TheBill(Order* order) = 0;

    virtual void LogIn(string UserName, string password) = 0;

};

PassengerGateway *GetDefaultPassengerGateway(Passenger passenger);

//
//    A Passenger has name, rating, order history, payment methods, pinned
//    addresses. He can
//    – login, see order history, see and update payment methods, see and
//    update pinned addresses.
//    – select any two addresses (from, to) and carType to check the time
//            and price of the ride. There are 4 car types: Economy, Comfort,
//            ComfortPlus, Business.
//    – order the ride if he agree with conditions (there is possibility to
//                                                  change default payment method for this particular ride).
//    – ask for the current coordinates of the car during the ride.
//    – see the ride in the order history after the end of the ride and ask for
//    the bill of that ride.



#endif //WENDEX_TAXI_PASSENGERGATEWAY_H
