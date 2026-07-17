#include "../inc/mini-redis.h"
#include <cassert>
#include <thread>
#include <iostream>

int main() {
    MiniRedis database;

    // Test 1
    database.set("test1", "123", 10);
    assert(database.get("test1") == "123");

    // Test 2
    assert(database.get("test2") == std::nullopt);

    // Test 3
    database.del("test1");
    assert(!database.exists("test1"));

    // Test 4
    database.set("test4", "123", 0);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    database.clean_expired();
    assert(database.size() == 0);

    // Test 5
    database.set("test5", "123", 1);
    assert(database.size() == 1);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Test 6
    database.set("test6", "123", 7);
    assert(database.ttl("test6") != 7);

    // Test 7
    database.set("test7", "1234", 3);
    database.clean_expired();
    database.save("tmp", "database_dump.csv");
    database.clear();
    assert(database.size() == 0);

    // Test 8
    database.load("tmp", "database_dump.csv");
    database.print();
    assert(database.size() == 2);

    // Test 9
    auto value1 = database.get("test6");
    auto value2 = database.get("test7");
    assert(value1.has_value() && value2.has_value());
    assert(value1 == "123");
    assert(value2 == "1234");

    // Test 10
    std::this_thread::sleep_for(std::chrono::seconds(3));
    database.clean_expired();
    assert(database.size() == 1);

    // Test 11
    std::this_thread::sleep_for(std::chrono::seconds(5));
    database.clean_expired();
    assert(database.size() == 0);

    return 0;
}