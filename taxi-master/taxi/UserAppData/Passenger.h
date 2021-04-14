//
// Created by asiia on 01.04.2021.
//

#ifndef WENDEX_TAXI_PASSENGER_H
#define WENDEX_TAXI_PASSENGER_H
#include <string>
#include <vector>
#include "paymentMethods.h"
#include "../Order.h"
#include "../Address.h"

using namespace std;

struct PassengerModel {
    char name[64];
    char pass[64];
    char email[64];
    int32_t rating;
};

class Passenger {
protected:
    PassengerModel model;
public:
    explicit Passenger(PassengerModel model);

    Passenger(const string &name, const string &password, const string &email);

    string name;

    string password;
    string email;
    double rating;

    //vector<Order*> orderHistory;

    PaymentMethod methods;
    //Order* currentOrd;
public:

    void setName(string name) {
        //TODO: strcpy
        //strcpy(name.c_str(),this->model.name);
    }

    string getName() {
        std::string(this->model.name);
    }


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
};


#endif //WENDEX_TAXI_PASSENGER_H
