#include <unordered_map>
#include <string>
#include <chrono>
#include <optional>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

struct CacheEntry{
    std::string value;
    std::chrono::steady_clock::time_point expiration_time;
};


class MiniRedis {

private:
    std::unordered_map<std::string, CacheEntry> cache; 

public:
    /**
     * @brief Inserts or updates a key=value pair with Time To Live
     * 
     * If the key already exists, its value and expiration time will be overwritten.
     * 
     * @param key The unique indentifier for the cached data.
     * @param value The string content to be stored.
     * @param duration_seconds Number of seconds until the key expires.
    */
    void set(std::string key, std::string value, int duration_seconds);

    /**
     * @brief Retrieves the value assiciated with the given key.
     * 
     * This method perform lazy deletion: if the key is found and it is expired,
     * it will be automatically removed from the memory
     * 
     * @param key The unique identifier to look up
     * @return std::optional<std::string> The value if found and alive, else std::nullopt.
    */
    [[nodiscard]] std::optional<std::string> get(const std::string& key);

    /**
     * @brief Dumps the current active database state into a single CSV file 
     * 
     * Calling clean_expired() is required before perform the function.
    */
    void save(const std::string& directory, const std::string& file);

    /**
     * @brief Loads and restores the database state from a saved CSV file.
     * 
     * Reads the file line by line, parses the key-value pairs along their remaining TTLS, and populates to the RAM
    */
    void load(const std::string& directory, const std::string& file);

    /**
     * @brief Removing selected entity. 
    */
    bool del(const std::string& key);

    /**
     * @brief Clean all expired entities. 
    */
    void clean_expired(); 

    /**
     * @brief Clean the entire collection.
    */
    void clear();
    
    /**
     * @brief Shows current database state in format key | value | ttl. 
    */
    void print();

    /**
     * @brief Returns remaining seconds to live or -1 if does not exist 
    */
    [[nodiscard]] int ttl(const std::string& key);

    /**
     * @brief Checks if entity does exist. 
    */
    [[nodiscard]] bool exists(const std::string& key);

    /**
     * @brief Returns entire collection size. 
    */
    [[nodiscard]] int size();
};