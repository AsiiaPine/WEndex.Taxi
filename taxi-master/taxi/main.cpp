#include <iostream>
#include <cassert>
#include "PassengerGateway.h"
#include "Repository.h"
#include "Models.h"
#include "CLI.h"
#include "UserAppData/User.h"


int setup(System *sys) {
    auto db = CreateMmapDatabase(".");
    sys->db = db;
    sys->accessManager = new AccessManager();
    sys->userRepository = new UserRepository(db);
    sys->orderRepository = new OrderRepository(db);
    sys->addressRepository = new AddressRepository(db);
    sys->passengerRepository = new PassengerRepository(db);
    sys->driverRepository = new DriverRepository(db,sys->userRepository);
    sys->carRepository = new CarRepository(db);
    return 0;
}

int cleanup(System *sys) {
    delete sys->userRepository;
    delete sys->orderRepository;
    delete sys->addressRepository;
    delete sys->driverRepository;
    delete sys->passengerRepository;
    delete sys->db;
    return 0;
}

int login(System *sys, UserModel **identity) {
    std::cout << "Enter your username" << std::endl;
    std::string loginUsername;
    std::cin >> loginUsername;
    UserModel * userModel;
    userModel->id = 1;
    userModel->role = ROLE_PASSENGER;
    strcpy(userModel->name, "Alesha");
    sys->userRepository->Create(userModel);
    auto user = sys->userRepository->FindUserByName(loginUsername.c_str());
    if (user) {
        std::cout << "Welcome, " << loginUsername.c_str() << std::endl;
        *identity = user;
        return 0;
    } else {
        std::cout << "Identification failed" << std::endl;
        return 1;
    }
}

int test();

int main1() {
    test();
}

int main() {
    System system;
    setup(&system);
    UserModel *userIdentity;
    if (login(&system,&userIdentity)) {
        exit(1);
    }
    UserCli *cli = nullptr;
    switch (userIdentity->role) {
        case ROLE_ADMIN: {
            cli = CreateAdminCli(&system,userIdentity);
            break;
        }
        case ROLE_PASSENGER: {
            cli = CreatePassengerCli(&system,userIdentity);
            break;
        }
        case ROLE_DRIVER: {
            cli = CreateDriverCli(&system,userIdentity);
            break;
        }
        default: {
            abort();
        }
    }
    cli->setup();
    cli->run();
    cli->stop();
    cleanup(&system);
}

int test() {
    std::cout << "Hello, World!" << std::endl;
    auto database = CreateMmapDatabase(".");
    auto userRepository = new UserRepository(database);
    auto passRepository = new PassengerRepository(database);
    auto drivRepository = new DriverRepository(database,userRepository);
    auto userFetched1 = userRepository->FindUserByName("admin");
    UserModel user = {
            .id = 9233490,
            .role = ROLE_ADMIN,
    };
    std::strcpy(user.name,"admin");
    userRepository->Create(&user);
    userRepository->Create(&user);
    auto userFetched = userRepository->FindUserByName("admin");
    assert(userFetched != nullptr);
    assert(userFetched->id == user.id);
    assert(userFetched->role == ROLE_ADMIN);
    delete drivRepository;
    delete passRepository;
    delete userRepository;
    delete database;
    return 0;
}
