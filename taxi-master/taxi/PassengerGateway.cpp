//
// Created by asiia on 01.04.2021.
//

#include <iostream>
#include "PassengerGateway.h"
#include "Repository.h"
#include "AccessManager.h"

std::vector<Passenger *> PassengerGateway::AllPassengers;


PassengerGateway::PassengerGateway(System *system, UserModel *identity, AccessManager *accessManager)
        : system(system), identity(identity), accessManager(accessManager), userRepository(system->userRepository),
          orderRepository(system->orderRepository), addressRepository(system->addressRepository),
          driverRepository(system->driverRepository), passengerRepository(system->passengerRepository) {
}

//PassengerGateway::PassengerGateway(Passenger *passenger) : passenger(passenger), currentOrder(NULL) {}

//PassengerGateway* PassengerGateway::SignUp(string UserName, string password, string email) {
//    if(password.size()<8){
//        cout<<"Length of password is less than 8 symbols"<<endl;
//        return nullptr;
//    }
//    auto passenger=new Passenger(UserName,password,email);
//    auto gate=new PassengerGateway(passenger);
//    AllPassengers.push_back(passenger);
//}

//void PassengerGateway::LogIn(string username, string password){
//    for(Passenger* aPassenger: PassengerGateway::AllPassengers){
//        if((aPassenger->name == username) & (aPassenger->password == password)){
//            std::cout << "Welcome!" << aPassenger->name << endl;
//            PassengerGateway* gateway= new PassengerGateway(aPassenger);
//            return;
//        }
//    }
//    cout<<"Wrong user name or password"<<endl;
//}

vector<Order *> PassengerGateway::SeeOrderHistory() {
    auto orderModels = this->orderRepository->FindAllByPassengerId(this->identity->id);
    auto orders = std::vector<Order *>();
    for (auto model : orderModels) {
        // endAddress repo
        auto a1 = addressRepository->FindEntityById(model->startAddressId);
        auto a2 = addressRepository->FindEntityById(model->endAddressId);
        auto pM = passengerRepository->FindPassengerByUserId(model->passengerId);
        auto upM = userRepository->FindEntityById(model->passengerId);
        auto p = new Passenger(upM,pM);

        auto dM = driverRepository->FindDriverByUserId(model->driverId);
        auto udM = userRepository->FindEntityById(model->driverId);
        //TODO: extract
        auto car = new Car(carRepository->FindEntityById(dM->car));
        auto d = new Driver(udM, dM, car);
        //
        orders.push_back(new Order(model,*a1,*a2,PaymentMethod::Card,p,d));
        // TODO: transform to dto
    }
    return orders;
}

void PassengerGateway::OrderTheRide(
        CarType type,
        Address startAddress,
        Address destinationAddress,
        int cost,
        PaymentMethod paymentMethod
) {
    if (accessManager->requireAccess(this->identity, Action::ORDER_RIDE)) {
        // TODO: create order
        auto order = OrderModel{.passengerId=identity->id,.driverId = 0, .cost = cost,
                                .startAddressId=startAddress.id,.endAddressId=destinationAddress.id,
                                .startTime=0, .endTime=0, };
        //auto order = new Order(this->passenger, startAddress, destinationAddress, cost, paymentMethod, Driver());
        this->orderRepository->Create(&order);
    }
}

void PassengerGateway::UpdateAddress(Address address) {
    if (this->currentOrder) {
        this->currentOrder->setEndAddress(address);
    }
}

PaymentMethod PassengerGateway::SeePaymentMethod() {
    return this->passenger->getPaymentMethod();
}

Coords PassengerGateway::CurrentCoordinates() {
    if (this->currentOrder) {
        //TODO: get coords of a currentCar
        auto car = this->currentOrder->getDriver()->getCurrentCar();
        return Coords(car->getCoordX(),car->getCoordY());
    } else {
        //TODO: get coords if not on currentCar
        return Coords(0.0, 0.0);
    }
}

void PassengerGateway::UpdatePaymentMethod(PaymentMethod newMethod) {
    if (this->accessManager->requireAccess(this->identity, Action::UPDATE_PAYMENT_METHOD)) {
        this->currentOrder->setPaymentMethod(newMethod);
    }
}

Order *PassengerGateway::TheBill(Order *order) {
    return order;
}

Address PassengerGateway::SeePinnedAddress() {
    return Address();
}
