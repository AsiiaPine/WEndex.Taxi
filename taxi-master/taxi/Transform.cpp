#include "Transform.h"

std::vector<Order *> orderFromModel(System *sys, std::vector<OrderModel *> orderModels) {
    auto orders = std::vector<Order *>();
    for (auto model : orderModels) {
        // endAddress repo
        auto a1 = sys->addressRepository->FindEntityById(model->startAddressId);
        auto a2 = sys->addressRepository->FindEntityById(model->endAddressId);
        auto pM = sys->passengerRepository->FindPassengerByUserId(model->passengerId);
        auto upM = sys->userRepository->FindEntityById(model->passengerId);
        auto p = new Passenger(upM,pM);

        auto dM = sys->driverRepository->FindDriverByUserId(model->driverId);
        auto udM = sys->userRepository->FindEntityById(model->driverId);
        //TODO: extract
        auto car = new Car(sys->carRepository->FindEntityById(dM->car));
        auto d = new Driver(udM, dM, car);
        //
        orders.push_back(new Order(model,*a1,*a2,PaymentMethod::Card,p,d));
        // TODO: transform to dto
    }
    return orders;
}

