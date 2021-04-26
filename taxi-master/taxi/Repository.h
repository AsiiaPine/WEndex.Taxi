//
// Created by asiia on 13.04.2021.
//

#ifndef WENDEX_TAXI_REPOSITORY_H
#define WENDEX_TAXI_REPOSITORY_H

#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <concepts>
#include <hash_map>


class Database {
public:
    virtual int OpenTable(const char *tableName) = 0;

    virtual int CloseTable(int tableId) = 0;

    virtual int GetTableSize(int tableId) = 0;

    virtual int ReadAt(int tableId, int nOffset, int nBytes, void *dataOutPtr) = 0;

    virtual void *ReadAt(int tableId, int nOffset, int nBytes) = 0;

    virtual int WriteAt(int tableId, int nOffset, int nBytes, void *dataPtr) = 0;
};

Database *CreateFileDatabase(const char *filesPath);

Database *CreateMmapDatabase(const char *filesPath);


template<typename Entity>
concept EntityWithIntId = requires(Entity e) {
    { e.id } -> std::convertible_to<int32_t>;
};


template<typename Entity, int entitySize> requires EntityWithIntId<Entity>
class Repository {
protected:
    Database *database;
    int tableId;
    int idCounter = 1000;
public:
    explicit Repository(Database *database, int tableId)
            : database(database), tableId(tableId) {
        if (tableId == -1) {
            abort();
        }
        this->idCounter = GetTableLength()+1;
    }

    explicit Repository(Database *database, const char *tableName)
            : Repository(database,database->OpenTable(tableName)) {};

    ~Repository() {
        fprintf(stderr,"closing\n");
        database->CloseTable(tableId);
    }

protected:

    int getOffsetById(int32_t id) {
        return (id - 1) * entitySize;
    }

public:
    int GetTableLength() {
        return database->GetTableSize(tableId);
    }

    void WriteAt(int offset, Entity *entityPtr) {
        database->WriteAt(tableId, offset, entitySize, entityPtr);
    }

    void ReadAt(int offset, Entity *entityOutPtr) {
        database->ReadAt(tableId, offset, entitySize, entityOutPtr);
    }

    Entity *ReadAt(int offset) {
        return reinterpret_cast<Entity *>(database->ReadAt(tableId, offset, entitySize));
    }

    void Create(Entity *entityPtr) {
        entityPtr->id = idCounter++;
        WriteAt(-1, entityPtr);
    }

    void Update(Entity *entityPtr) {
        WriteAt(getOffsetById(entityPtr->id), entityPtr);
    }

    Entity *FindEntityById(int32_t entityId) {
        return ReadAt(getOffsetById(entityId));
    }

    Entity *FindEntityByFieldValue(const void* lookupValue,int offset,int size) {
        auto cursor = 0;
        auto tableSize = this->GetTableLength();
        while (cursor < tableSize) {
            //Entity entity;
            auto entity = this->ReadAt(cursor);
            //this->ReadAt(cursor, &entity);
            if (std::memcmp(lookupValue,reinterpret_cast<char*>(entity)+offset,size) == 0) {
                return entity;
            }
            cursor+=entitySize;
        }
    }

    std::vector<Entity*> FindEntitiesByFieldValue(void* lookupValue,int offset,int size) {
        std::vector<Entity*> entityPtrList;
        auto cursor = 0;
        auto tableSize = this->GetTableLength();
        while (cursor < tableSize) {
            Entity entity;
            this->ReadAt(cursor, &entity);
            if (std::memcmp(lookupValue,&entity+offset,size) == 0) {
                entityPtrList.push_back(&entity);
            }
            cursor++;
        }
        return entityPtrList;
    }
};


template<typename Entity>
concept EntityWithNameChar32 = requires(Entity e) {
    EntityWithIntId<Entity>;
    { e.name } -> std::convertible_to<char*>;
};

template<typename Entity, int entitySize> requires EntityWithNameChar32<Entity>
class NamedRepository : public Repository<Entity, entitySize> {
public:
    explicit NamedRepository(Database *database, int tableId)
            : Repository<Entity, entitySize>(database, tableId) {}

    Entity *FindEntityByName(const char* name) {
        char buffer[32];
        std::memset(buffer,0,32);
        std::strcpy(buffer,name);
        this->FindEntityByFieldValue(buffer,offsetof(Entity,name),32);
    }

#endif //WENDEX_TAXI_REPOSITORY_H
