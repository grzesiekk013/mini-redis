# Mini-Redis: In-Memory Cache Engine

A minimalist, high-performance in-memory key-value storage engine built from scratch using **Modern C++17**. This project demonstrates clean memory management, efficient data structures, and precise time tracking without external dependencies.

## Key Features
* **Fast Lookups:** Powered by `std::unordered_map` for $O(1)$ average time complexity operations.
* **TTL Expiration:** Automatic data invalidation using the high-resolution `std::chrono::steady_clock`.
* **Type-Safe Null Handling:** Clean API design leveraging `std::optional` to represent missing or expired keys safely.
* **Zero Pointers:** 100% safe, modern memory management utilizing RAII principles (no manual `new`/`delete`).

## Tech Stack & Concepts
* **Language Standard:** C++17
* **Key Components:** `std::string_view`, `std::optional`, `std::chrono`, `std::unordered_map`
* **Compiler:** GCC / MinGW

### Prerequisites
* A C++17 compatible compiler (GCC 9+ or Clang)

### Build & Run
```bash
# Compile the project
g++ -std=c++17 main.cpp -o mini_redis

# Run the executable
./mini_redis
