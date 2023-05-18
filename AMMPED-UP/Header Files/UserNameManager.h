#pragma once
#include <string>

class UserNameManager
{
private:
    std::string m_username;
    static UserNameManager* m_instance;
    UserNameManager() {
        // Private constructor to prevent direct instantiation
        m_username = "";
    }

public:
    static UserNameManager* getInstance();
    void setUsername(const std::string& name);
    std::string getUsername() const;
};

