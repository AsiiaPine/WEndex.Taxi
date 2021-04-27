//
// Created by asiia on 01.04.2021.
//

#include "PassengerGateway.h"

class DefaultPassengerGateway : public PassengerGateway {
private:
    Passenger passenger;
    Order* currentOrder;
    //static OrderRepository* orderRepository;
    static vector<Passenger*> AllPassengers;
public:
    explicit DefaultPassengerGateway(Passenger passenger) : PassengerGateway(), passenger(passenger) {}

    virtual void SeeOrderHistory() override {

    }

    virtual void SeePayMethod() override {

    }

    virtual void UpdatePay(PaymentMethod newMethod) override {

    }

    virtual void PinnedAddr() override {

    }

    virtual void UpdateAddr(Address adr) override {

    }

    virtual void
    OrderTheRide(CarType type, Address address, Address startAddress, PaymentMethod paymentMethod) override {

    }

    virtual Coords CurrentCoordinates() override {
        //TODO: coords
        return Coords{ .x = 0, .y = 0};
    }

    virtual void TheBill(Order *order) override {

    }

    virtual void LogIn(string UserName, string password) override {

    }
};

PassengerGateway *GetDefaultPassengerGateway(Passenger passenger) {
    return new DefaultPassengerGateway(passenger);
}
