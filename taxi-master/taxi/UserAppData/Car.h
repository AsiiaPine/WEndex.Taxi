//
// Created by asiia on 01.04.2021.
//

#ifndef WENDEX_TAXI_CAR_H
#define WENDEX_TAXI_CAR_H

#include <string>
#include "CarType.h"
using namespace std;

struct CarCoords {
    int32_t x;
    int32_t y;
};

struct CarModel {
    int64_t id;
    char* model[32];
    CarType type;
    CarCoords coords;
};

class Car {
    CarModel model;
    CarType type;
public:
    Car(CarModel model) : model(model) {

    }
public:
    const int getId() {
        return model.id;
    }

    char* getModel() {
        return reinterpret_cast<char *>(model.model);
    }

    int getCoordX() const {
        return model.coords.x;
    }

    int getCoordY() const {
        return model.coords.y;
    }

    CarType getType() const {
        return type;
    }
};

class EconomyCar : public Car {
public:
    EconomyCar(CarModel model);
};

class ComfortCar : public Car {
    int freeBottleOfWater;
public:
    explicit ComfortCar(CarModel model);
    int getFreeBottleOfWater() {
        return freeBottleOfWater;
    }
};

class BusinessCar : public Car {
public:
    explicit BusinessCar(CarModel model);
    int parkRightInFrontOfTheEntrance();
};


#endif //WENDEX_TAXI_CAR_H
