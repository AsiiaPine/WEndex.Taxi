#include <sys/mman.h>
#include <sys/stat.h>
#include "Repository.h"

class FileDatabase : public Database {
public:
    int tableCounter = 1000;
    std::unordered_map<int, FILE *> tableMap;
public:
    explicit FileDatabase() = default;

    int OpenTable(const char *tableName) override {
        if (auto file = fopen(tableName, "rw"); file != nullptr) {
            tableMap[++tableCounter] = file;
            return tableCounter;
        } else {
            return -1;
        }
    }

    int CloseTable(int tableId) override {
        if (tableMap.contains(tableId)) {
            fclose(tableMap[tableId]);
            return 0;
        } else {
            return -1;
        }
    }

    int GetTableSize(int tableId) override {
        auto file = tableMap[tableId];
        auto savedPos = ftell(file);
        fseek(file, 0, SEEK_END);
        auto endPos = ftell(file);
        fseek(file, savedPos, SEEK_SET);
        return endPos;
    }

    int ReadAt(int tableId, int nOffset, int nBytes, void *dataOutPtr) override {
        fseek(tableMap[tableId], nOffset, SEEK_SET);
        return fread(dataOutPtr, 1, nBytes, tableMap[tableId]);
    }

    void *ReadAt(int tableId, int nOffset, int nBytes) override {
        fseek(tableMap[tableId], nOffset, SEEK_SET);
        auto objectPtr = malloc(nBytes);
        fread(objectPtr, 1, nBytes, tableMap[tableId]);
        return objectPtr;
    }

    int WriteAt(int tableId, int nOffset, int nBytes, void *dataPtr) override {
        if (nOffset == -1) {
            fseek(tableMap[tableId], 0, SEEK_END);
        } else {
            fseek(tableMap[tableId], nOffset, SEEK_SET);
        }
        return fwrite(dataPtr, nBytes, 1, tableMap[tableId]);
    }
};



struct MmapDesc {
    FILE* file;
    void* ptr;
    int nUsed;
};

class MmapDatabase : public Database {
public:
    int tableCounter = 1000;
    std::unordered_map<int, MmapDesc> mmapMap;
public:
    explicit MmapDatabase() = default;

    int OpenTable(const char *tableName) override {
        if (auto file = fopen(tableName, "a+"); file != nullptr) {
             auto desc = MmapDesc {
                .file = file,
                .ptr = mmap(nullptr, 1U << 30, PROT_READ | PROT_WRITE,
                            MAP_ANONYMOUS | MAP_PRIVATE | MAP_NORESERVE, -1, 0),
                .nUsed = 0,
            };tableCounter += 1;

            mmapMap[++tableCounter] = desc;
            struct stat buffer;
            auto ret = stat(tableName,&buffer);
            if (ret == 0) {
                mmapMap[tableCounter].nUsed = buffer.st_size;
                fread(desc.ptr,1,buffer.st_size,file);
            } else {
            }

            return tableCounter;
        } else {
            fprintf(stderr,strerror(errno));
            return -1;
        }
    }

    int CloseTable(int tableId) override {
        if (mmapMap.contains(tableId)) {
            auto &mapping = mmapMap[tableId];
            fprintf(stderr,"nUsed = %d",mapping.nUsed);
            fwrite(mapping.ptr, mapping.nUsed, 1, mapping.file);
            fclose(mapping.file);
            return 0;
        } else {
            fprintf(stderr, "no table id");
            return -1;
        }
    }

    int GetTableSize(int tableId) override {
        auto &mapping = mmapMap[tableId];
        return mapping.nUsed;
    }

    int ReadAt(int tableId, int nOffset, int nBytes, void *dataOutPtr) override {
        auto &mapping = mmapMap[tableId];
        memcpy(dataOutPtr,reinterpret_cast<uint8_t*>(mapping.ptr)+nOffset,nBytes);
        return 0;
    }

    void *ReadAt(int tableId, int nOffset, int nBytes) override {
        auto objectPtr = malloc(nBytes);
        auto &mapping = mmapMap[tableId];
        std::memcpy(objectPtr,reinterpret_cast<uint8_t*>(mapping.ptr)+nOffset,nBytes);
        return objectPtr;
    }

    int WriteAt(int tableId, int nOffset, int nBytes, void *dataPtr) override {
        auto &mapping = mmapMap[tableId];
        auto offset = nOffset == -1 ? mapping.nUsed : nOffset;
        std::memcpy(reinterpret_cast<uint8_t*>(mapping.ptr)+offset,dataPtr,nBytes);
        mapping.nUsed += (nOffset == -1 ? nBytes : 0);
        return 0;
    }

};



Database *CreateFileDatabase(const char *filesPath) {
    return new FileDatabase();
}

Database *CreateMmapDatabase(const char *filesPath) {
    return new MmapDatabase();
}
