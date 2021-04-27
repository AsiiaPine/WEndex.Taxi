//
// Created by asiia on 01.04.2021.
//

#include "DriverGateway.h"
#include "Transform.h"

DriverGateway::DriverGateway(System *system, UserModel *identity, AccessManager *accessManager)
        : system(system), identity(identity), accessManager(accessManager),
        driverRepository(system->driverRepository), orderRepository(system->orderRepository) {
    auto dr = driverRepository->FindDriverByUserId(identity->id);
    auto carM = carRepository->FindEntityById(dr->car);
    auto car = new Car(carM);
    this->driver = new Driver(identity,dr,car);
}


void DriverGateway::AcceptOrder(Order *order) {
    order->setDriver(this->driver);
    this->driver->setCurrentOrderId(order->getId());
}

double DriverGateway::GetRating() {
    return this->driver->getRating();
}

Car DriverGateway::GetCurrentCar() {
    return *this->driver->getCurrentCar();
}

std::vector<Car> DriverGateway::GetAllCars() {
    //TODO:
    return std::vector<Car>();
}

void DriverGateway::DeclineOrder(Order *order) {
    if (order->getDriver() == this->driver) {
        order->setDriver(0);
        this->driver->setCurrentOrderId(0);
    }
}

int DriverGateway::Status() {
    return driver->getDriverStatus();
}

void DriverGateway::SetStatus(int newStatus) {
    driver->setDriverStatus(static_cast<DriverStatus>(newStatus));
}

std::vector<Order *> DriverGateway::GetOrderHistory() {
    //TODO:
    return std::vector<Order *>();
}

std::vector<Order *> DriverGateway::GetAvailableOrders() {
    auto freeStatus = DriverStatus::AVAILABLE;
    auto orders = orderRepository->FindEntitiesByFieldValue(&freeStatus,offsetof(OrderModel,driverId),sizeof(DriverStatus));
    return orderFromModel(system,orders);
}

void DriverGateway::StopTheRide() {
    if (driver->getCurrentOrderId()) {
        auto order = orderRepository->FindEntityById(driver->getCurrentOrderId());
        order->driverId = 0;
        SetStatus(DriverStatus::AVAILABLE);
    }
}
