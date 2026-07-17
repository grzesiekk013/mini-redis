# Mini-Redis: In-Memory Cache Engine

A minimalist, high-performance in-memory key-value storage engine built from scratch using **Modern C++17**. This project demonstrates clean memory management, efficient data structures, precise time tracking, and persistence without external dependencies.

## Key Features
* **Fast Lookups:** Powered by `std::unordered_map` for `O(1)` average time complexity operations.
* **TTL Expiration:** Automatic and lazy data invalidation using high-resolution `std::chrono::steady_clock`.
* **CSV Persistence:** Complete state save and recovery (`save` / `load`) to disk using a custom, safe CSV parser.
* **Type-Safe Null Handling:** Clean API design leveraging `std::optional` to represent missing or expired keys safely.
* **Zero Pointers:** 100% safe memory management utilizing RAII principles (no manual `new`/`delete`).
* **CI/CD Ready:** Automated building and testing workflow via GitHub Actions.

## Tech Stack & Concepts
* **Language Standard:** C++17
* **Key Components:** `std::string`, `std::optional`, `std::chrono`, `std::unordered_map`, `std::filesystem`
* **Compiler:** GCC / Clang / MinGW

## Getting Started

### Prerequisites
* A C++17 compatible compiler (GCC 9+ or Clang 10+)

### Building and Running the Example
To see the engine, persistence, and TTL expiration in action:
```bash
# Compile the main application
g++ -std=c++17 main.cpp src/mini-redis.cpp -Iinc -o mini_redis

# Run the executable
./mini_redis
```
### Running the Tests
```bash
# Compile the test runner
g++ -std=c++17 tests/tests.cpp src/mini-redis.cpp -Iinc -o test_runner

# Run the tests
./test_runner
```