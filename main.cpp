#include <iostream>
#include <thread>
#include "inc/mini-redis.h"

int main() {

    std::cout << "=========================================" << std::endl;
    std::cout << "    MiniRedis - Usage Showcase" << std::endl;
    std::cout << "=========================================" << std::endl << std::endl;
    // -- -- --
    MiniRedis database;
    // -- basic set and get operations -- //
    std::cout << "-- 1. basic wrtite and read --" << std::endl;
    database.set("user:100", "Grzegorz Lademann", 5);
    database.set("user:101", "Jan Kowalski", 60);
    //
    std::cout << "Retrieved 'user:100': " << database.get("user:100").value_or("NOT FOUND") << std::endl;
    std::cout << "Current TTL for 'user:100': " << database.ttl("user:100") << " sec" << std::endl;
    std::cout << "Elements in database: " << database.size() << std::endl;
    // -- existence and deletion -- //
    std::cout << "-- 2. existence and deletion --" << std::endl;
    if (database.exists("user:101")) {
        std::cout << "Element 'user:101' exists. Deleting..." << std::endl;
        std::cout << (database.del("user:101")? "Deleted." : "Not deleted.") << std::endl;
        std::cout << "Checking if 'user:101' exists again: " << ((database.exists("user:101")? "Exists." : "Does not exist.")) << std::endl;
    }
    // -- print database -- //
    std::cout << "-- 3. curren database state --" << std::endl;
    database.set("user:102", "Święty Mikołaj", 3);
    database.print();
    // -- save and load -- //
    std::cout << "-- 4. persistence - save and load --" << std::endl;
    std::cout << "Cleaning up expired keys and dumping database to CSV file" << std::endl;
    database.clean_expired();
    database.save("tmp", "database_dump.csv");
    std::cout << "Current database size: " << database.size() << ". Clearing RAM cache..." << std::endl;
    database.clear();
    std::cout << "Current database size: " << database.size() << std::endl;
    std::cout << "Loading database state back from CSV file..." << std::endl;
    database.load("tmp", "database_dump.csv");
    std::cout << "Database contents after restoration: " << std::endl;
    database.print();
    // -- time elapse simulation -- //
    std::cout << "-- 5. time elapse simulation --" << std::endl;
    std::cout << "Waiting 2 seconds for the 'user:102' key expire..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Trying to get('user:102') expired entity..." << std::endl;
    std::cout << "key: 'user:102', value: " << database.get("user:102").value_or("NOT FOUND") << ", ttl:" << database.ttl("user:102") << std::endl;
    std::cout << "Database state: " << std::endl;
    database.print();
    // -- --
    return 0;
}