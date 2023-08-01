#pragma once
#include <mongocxx/instance.hpp>
class MongoInstance {
private:
    static MongoInstance* m_instance;
    mongocxx::instance instance;
    // Private constructor
    MongoInstance();
public:
    // Deleted copy constructor and assignment operator to enforce singleton
    MongoInstance(const MongoInstance&) = delete;
    MongoInstance& operator=(const MongoInstance&) = delete;
    ~MongoInstance();
    static MongoInstance* getInstance();
};
