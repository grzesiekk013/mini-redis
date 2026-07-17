#include "../inc/mini-redis.h"

namespace fs = std::filesystem;

void MiniRedis::set(std::string key, std::string value, int duration_seconds) {
    
    auto now = std::chrono::steady_clock::now();
    auto expiration_time = now + std::chrono::seconds(duration_seconds);
    // -- -- -- 
    CacheEntry entry;
    entry.value = value;
    entry.expiration_time = expiration_time;
    // -- -- -- 
    cache[key] = entry;
}

std::optional<std::string> MiniRedis::get(const std::string& key) {
    auto iterator = cache.find(key);
    // -- -- --
    if (iterator == cache.end())
        return std::nullopt;
    // -- -- --
    auto now = std::chrono::steady_clock::now();
    // -- -- --  
    if (now > iterator->second.expiration_time) {
        cache.erase(key);
        return std::nullopt;
    } else {
        return iterator->second.value;
    }
}

bool MiniRedis::exists(const std::string& key) {
    auto search = cache.find(key);
    return search != cache.end();
}

bool MiniRedis::del(const std::string& key) {
    size_t removed_cnt =  cache.erase(key);
    return removed_cnt > 0;
}

int MiniRedis::ttl(const std::string& key) {
    auto iterator = cache.find(key);
    // -- -- --
    if (iterator == cache.end())
        return -1;
    // -- -- --
    auto now = std::chrono::steady_clock::now();
    // -- -- --  
    if (now > iterator->second.expiration_time) {
        cache.erase(key);
        return 0;
    } else {
        auto difference = iterator->second.expiration_time - now;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(difference);
        return seconds.count();
    }
}

void MiniRedis::clean_expired() {
    auto now = std::chrono::steady_clock::now();
    // -- -- --
    auto iterator = cache.begin();
    while (iterator != cache.end()) {
        if (now > iterator->second.expiration_time) {
            iterator = cache.erase(iterator);
        } else {
            iterator++;
        }
    }
}

int MiniRedis::size() {
    return cache.size();
}

void MiniRedis::clear() {
    cache.clear();
}

void MiniRedis::save(const std::string& directory, const std::string& filename) {
    fs::create_directories(directory);
    std::filesystem::path full_path = std::filesystem::path(directory) 
                                    / std::filesystem::path(filename);
    std::ofstream file(full_path);
    // -- -- --
    auto now = std::chrono::steady_clock::now();
    // -- -- --
    // clean_expired();
    // -- -- -- 
    for (const auto& [key, entry] : cache) {
        int last_seconds = std::chrono::duration_cast<std::chrono::seconds>(entry.expiration_time - now).count();
        file << key << ';' << entry.value << ';' << last_seconds << '\n';
    }
    file.close();
}

void MiniRedis::load(const std::string& directory, const std::string& filename) {
    std::filesystem::path full_path = std::filesystem::path(directory) 
                                    / std::filesystem::path(filename);
    std::ifstream file(full_path);
    // -- -- --
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty())
                continue;
            // -- -- --
            std::stringstream ss(line);
            std::string key;
            std::string value;
            std::string ttl_s;
            // -- -- --
            std::getline(ss, key, ';');
            std::getline(ss, value, ';');
            std::getline(ss, ttl_s, ';');
            int ttl = std::stoi(ttl_s);
            set(key, value, ttl);
        }
    }

    file.close();
}

void MiniRedis::print() {
    for (const auto& [key, entry] : cache) {
        std::cout << key << " | " << entry.value << " | " << ttl(key) << std::endl;
    }
}