//
// Created by asiia on 10.04.2021.
//

#ifndef WENDEX_TAXI_ADDRESS_H
#define WENDEX_TAXI_ADDRESS_H
#include <filesystem>
#include <fcntl.h>
//
// Created by asiia on 10.04.2021.
//
#include <string>
struct Coords{
    double x;
    double y;
};

using namespace std;
struct Address{
    Coords coordinate;
    char city[32];
    string street;
    string numberOfBuilding;
};
void PrintTheAddress(Address address){
    cout<<"City: "<<address.city<<"\n Street: "<<address.street<<"\n Number of building: "<<address.numberOfBuilding<<endl;
}
//FILE Map=open(Map.txt,)


#endif //WENDEX_TAXI_ADDRESS_H
