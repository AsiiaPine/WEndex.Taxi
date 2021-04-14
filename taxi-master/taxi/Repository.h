//
// Created by asiia on 13.04.2021.
//

#ifndef WENDEX_TAXI_REPOSITORY_H
#define WENDEX_TAXI_REPOSITORY_H

#include <cinttypes>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <concepts>

template<typename Entity>
concept EntityWithIntId = requires(Entity e) {
    { e.id } -> std::convertible_to<int32_t>;
};


template<typename Entity> requires EntityWithIntId<Entity>
class Repository {
private:
    FILE *file;
    int entitySize = 0;
public:
    Repository(const char *path, int entitySize): entitySize(entitySize) {
        file = fopen(path, "rw");
    }

protected:
    int selectEntity(int index) {
        return fseek(file, index * entitySize,SEEK_SET);
    }

    bool hasCurrent() {
        int current = ftell(file);
        fseek(file, 0, SEEK_END);
        int end = ftell(file);
        fseek(file, current, SEEK_SET);
        return current < end;
    }

    int readCurrent(Entity *entityOutPtr) {
        return fread(entityOutPtr,entitySize,1,file);
    }

public:
    void Create(Entity *entityPtr) {
        fseek(this->file, 0, SEEK_END);
        int filesize = ftell (file);
        entityPtr->id = filesize / entitySize;
        fwrite(entityPtr, entitySize,1,file);
    }

    void Update(Entity *entityPtr) {
        selectEntity(entityPtr->id);
        fwrite(file, entityPtr, entitySize);
    }


};

#endif //WENDEX_TAXI_REPOSITORY_H
