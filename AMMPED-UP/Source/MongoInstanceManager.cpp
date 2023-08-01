#include "../Header Files/MongoInstanceManager.h"

MongoInstance* MongoInstance::m_instance = nullptr;
MongoInstance::MongoInstance() :instance{} {
}

MongoInstance::~MongoInstance() {}

MongoInstance* MongoInstance::getInstance() {
    // Double-checked locking for thread safety
    if (!m_instance) {
        //static MongoInstance instance;
        m_instance = new MongoInstance;
    }
    return m_instance;
}
