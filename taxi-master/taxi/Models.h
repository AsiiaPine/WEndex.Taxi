#ifndef WENDEX_TAXI_MODELS_H
#define WENDEX_TAXI_MODELS_H

#include "Repository.h"
#include <set>

using namespace std;

enum UserRole : uint32_t {
    ROLE_ADMIN = 0,
    ROLE_PASSENGER = 1,
    ROLE_DRIVER = 2,
};

struct UserModel {
    int32_t id = 0;
    UserRole role = ROLE_PASSENGER;
    char name[32] = {0};
};

class UserRepository : public NamedRepository<UserModel, sizeof(UserModel)> {
public:
    explicit UserRepository(Database *db)
            : NamedRepository(db, db->OpenTable("users.table")) {};

    UserModel *FindUserByName(const char *name) {
        return FindEntityByName(name);
    }

    std::vector<UserModel *> FindUsersByRole(UserRole role) {
        return FindEntitiesByFieldValue(&role, offsetof(UserModel, role), sizeof(UserRole));
    }
};

enum DriverStatus : uint32_t {
    HOME,
    AVAILABLE,
    BUSY,
};

struct DriverModel {
    int32_t id = 0;
    int32_t userId = 0;
    int32_t car = 0;
    int32_t order = 0;
    DriverStatus status = AVAILABLE;
    double rating = 5;
};

class DriverRepository : public Repository<DriverModel, sizeof(DriverModel)> {
public:
    explicit DriverRepository(Database *db, UserRepository *userRepository)
            : Repository(db, db->OpenTable("drivers.table")) {};

    DriverModel *FindDriverByUserId(int32_t userId) {
        return FindEntityByFieldValue(&userId,offsetof(DriverModel, userId), sizeof(int32_t));
    }

    DriverModel *FindDriverByOrderId(int32_t orderId) {
        return FindEntityByFieldValue(&orderId, offsetof(DriverModel, order), sizeof(int32_t));
    }

    DriverModel *FindDriverByCurrentCarId(int32_t carId) {
        return FindEntityByFieldValue(&carId, offsetof(DriverModel, car), sizeof(int32_t));
    }

    std::vector<DriverModel *> FindAllDriversByStatus(DriverStatus status) {
        return FindEntitiesByFieldValue(&status, offsetof(DriverModel, status), sizeof(DriverStatus));
    }

};

enum PassengerPermission : uint32_t {
    VIEW_HISTORY = 0
};

struct PassengerModel {
    int32_t id = 0;
    int32_t userId = 0;
    int32_t paymentMethod = 1;
    int32_t u0 = 0;
    set<PassengerPermission> permissions;
};

class PassengerRepository : public Repository<PassengerModel, sizeof(PassengerModel)> {
public:
    explicit PassengerRepository(Database *db) : Repository(db,db->OpenTable("passenger.table")) {};

    PassengerModel *FindPassengerByUserId(uint32_t userId) {
        return FindEntityByFieldValue(&userId,offsetof(PassengerModel, userId), sizeof(int32_t));
    }
};



#endif //WENDEX_TAXI_MODELS_H
