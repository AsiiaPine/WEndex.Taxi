//
// Created by asiia on 01.04.2021.
//

#include "Passenger.h"


Passenger::Passenger(const string &name, const string &password, const string &email) : name(name), password(password),
                                                                                        email(email) {

    this->rating=5.0;
}
