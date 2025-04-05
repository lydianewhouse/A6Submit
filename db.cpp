//db.cpp
#include "db.h"

//Initializes to be nullptr the first time
Database* Database::instance = nullptr;

Database::Database(std::string input_db, std::string input_username, std::string input_password)
{
    //Refreshes connection
    instance->refreshConnection();

    //Initializes all variables
    db = input_db;
    username = input_username;
    password = input_password;
    connected = true;
}

Database::~Database()
{
    connected = false;
}

Database* Database::getInstance(const std::string input_database, const std::string input_username, const std::string input_password)
{
    //Refreshes connection
    instance->refreshConnection();

    //Check if instance doesn't exist, if so, create instance
    if (instance == nullptr)
    {
        //Creates space for instance
        instance = new Database(input_database, input_username, input_password);

        return instance;
    }
    else
    {
        //Check if inputs match the existing instance
        if (input_database == instance->get_db() && input_username == instance->get_username() && input_password == instance->get_password())
        {
            return instance;
        }
        else
        {
            //Invalid arguments
            throw std::runtime_error("invalid database name, usernae, or password");
        }
    }
}


void Database::connect()
{
    //Refreshes connection
    instance->refreshConnection();

    connected = true;
}

void Database::disconnect()
{
    //Refreshes connection
    instance->refreshConnection();

    connected = false;
}

bool Database::isConnected()
{
    //Refreshes connection
    instance->refreshConnection();

    return connected;
}


void* Database::operator new(size_t size)
{
    //Refreshes connection
    instance->refreshConnection();

    //Creates new database with malloc
    std::cout << " overloaded new " << std::endl;
    void * new_database = malloc(size);

    //Check if unable to allocate
    if (new_database == NULL)
    {
        throw std::bad_alloc();
    }

    return new_database;
}

void Database::operator delete(void* new_database)
{
    //Refreshes connection
    instance->refreshConnection();

    std::cout << " overloaded delete " << std::endl;

    free(new_database);
}




void Database::set_username(const std::string new_username)
{
    //Refreshes connection
    instance->refreshConnection();

    username = new_username;
}



std::string Database::get_username() const
{
    //Refreshes connection
    instance->refreshConnection();

    return username;
}

void Database::set_password(const std::string new_password)
{
    //Refreshes connection
    instance->refreshConnection();

    password = new_password;
}

std::string Database::get_password() const
{
    //Refreshes connection
    instance->refreshConnection();

    return password;
}

void Database::set_db(std::string new_db)
{
    //Refreshes connection
    instance->refreshConnection();

    db = new_db;
}

std::string Database::get_db()
{
    //Refreshes connection
    instance->refreshConnection();

    return db;
}


void Database::resetInstance() {
    //Refreshes connection
    instance->refreshConnection();

    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

//Copy constructor
Database::Database(const Database &database)
{
    throw std::runtime_error("Cannot use copy constructor on Singleton");
}

//Copy assignment operator
Database& Database::operator=(const Database &database)
{
    throw std::runtime_error("Cannot use copy assignment operator on Singleton");
}

//Move constructor
Database::Database(Database &&database)
{
    throw std::runtime_error("Cannot use move constructor on Singleton");
}

//Move assignment operator
Database& Database::operator=(Database &&database)
{
    throw std::runtime_error("Cannot use move assignment operator on Singleton");
}

// Checks if the connection has been inactive for longer than TIMEOUT seconds
// Returns true if the timeout threshold has been exceeded, false otherwise
bool Database::isTimeout()
{
    //Gets the current time
    time_t currentTime = std::time(nullptr);

    //Compares it to the last refreshed time, sees if it is exceeding TIMEOUT
    time_t elapsedTime = currentTime - last_activity;

    if (elapsedTime < TIMEOUT)
    {
        //Refreshes connection
        instance->refreshConnection();

        //Connection has not timed out
        return false;
    }
    else
    {
        //Refreshes connection
        instance->refreshConnection();

        //Conection has timed out, need to disconnect
        disconnect();

        return true;
    }
}

// Updates the last_activity timestamp to the current time
// Should be called whenever there is interaction with the database to reset the timeout
void Database::refreshConnection()
{
    //Updates the last_activity timestamp to current time
    last_activity = std::time(nullptr);
}
