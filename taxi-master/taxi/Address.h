//
// Created by asiia on 10.04.2021.
//

#ifndef WENDEX_TAXI_ADDRESS_H
#define WENDEX_TAXI_ADDRESS_H
#include <filesystem>
#include <fcntl.h>
#include "Repository.h"

#include <string>
struct Coords{
    double x = 0;
    double y = 0;

    Coords() {}

    Coords(double x, double y) : x(x), y(y) {}
};

using namespace std;
struct Address{
    int32_t id;
    Coords coordinate;
    char city[32];
    char street[32];
    char numberOfBuilding[32];

    explicit Address(char *a) {
        std::strcpy(street,a);
        coordinate = Coords( *((double*)a+1),*((double*)a+2) );
    }
};

class AddressRepository : public Repository<Address,sizeof(Address)> {
public:
    explicit AddressRepository(Database *db) : Repository(db,db->OpenTable("endAddress.table")) {};

//    Address *FindPassengerByUserId(uint32_t addressId) {
//        return FindEntityByFieldValue(&userId,offsetof(PassengerModel, userId), sizeof(int32_t));
//    }
};
//void PrintTheAddress(Address endAddress){
//    cout<<"City: "<<endAddress.city<<"\n Street: "<<endAddress.street<<"\n Number of building: "<<endAddress.numberOfBuilding<<endl;
//}
//FILE Map=open(Map.txt,)


#endif //WENDEX_TAXI_ADDRESS_H
