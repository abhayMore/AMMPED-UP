#pragma once
#include <mongocxx/instance.hpp>

class MongoInstance {
private:
    static mongocxx::instance instance; // Private static member variable

public:
    static mongocxx::instance& getInstance() {
        return instance;
    }
};