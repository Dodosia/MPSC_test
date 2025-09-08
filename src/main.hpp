#pragma once
#include <cstdlib>

// Multi-Purpose
#if !defined(_LIBCPP_VERSION) && defined(_MSC_VER) && _MSC_VER >= 1'928
#include <execution>  // C++17 (Requires TBB on Linux)
#endif

// Language Support
#include <cfloat>
#include <climits>
#include <compare>           // C++20
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>           // C++11
#if __has_include(<contracts>)
#include <contracts>         // C++26
#endif
#include <coroutine>         // C++20
#include <exception>
#include <initializer_list>  // C++11
#include <limits>
#include <new>
#include <source_location>   // C++20
#include <stdfloat>          // C++23
#include <typeindex>         // C++11
#include <typeinfo>
#include <version>           // C++20

// Concepts
#include <concepts>  // C++20

// Diagnostics
#include <cassert>
#include <cerrno>
#if __has_include(<debugging>)
#include <debugging>     // C++26
#endif
#include <stacktrace>    // C++23
#include <stdexcept>
#include <system_error>  // C++11

// Memory Management
#include <memory>
#include <memory_resource>   // C++17
#include <scoped_allocator>  // C++11

// Metaprogramming
#include <ratio>        // C++11
#include <type_traits>  // C++11

// General Utilities
#include <any>       // C++17
#include <bit>       // C++20
#include <bitset>
#include <expected>  // C++23
#include <functional>
#include <optional>  // C++17
#include <tuple>     // C++11
#include <utility>
#include <variant>   // C++17

// Containers
#include <array>           // C++11
#include <deque>
#if __has_include(<flat_map>)
#include <flat_map>        // C++23
#endif
#if __has_include(<flat_set>)
#include <flat_set>        // C++23
#endif
#include <forward_list>    // C++11
#if __has_include(<hive>)
#include <hive>            // C++26
#endif
#if __has_include(<inplace_vector>)
#include <inplace_vector>  // C++26
#endif
#include <list>
#include <map>
#if __has_include(<mdspan>)
#include <mdspan>          // C++23
#endif
#include <queue>
#include <set>
#include <span>            // C++20
#include <stack>
#include <unordered_map>   // C++11
#include <unordered_set>   // C++11
#include <vector>

// Iterators
#include <iterator>

// Ranges
#include <generator>  // C++23
#include <ranges>     // C++20

// Algorithms
#include <algorithm>
#include <numeric>

// Strings
#include <cstring>
#include <string>
#include <string_view>  // C++17

// Text Processing
#include <cctype>
#include <charconv>       // C++17
#include <clocale>
#include <cuchar>         // C++11
#include <cwchar>
#include <cwctype>
#include <format>         // C++20
#include <locale>
#include <regex>          // C++11
#if __has_include(<text_encoding>)
#include <text_encoding>  // C++26
#endif

// Numerics
#include <cfenv>    // C++11
#include <cmath>
#include <complex>
#if __has_include(<linalg>)
#include <linalg>   // C++26
#endif
#include <numbers>  // C++20
#include <random>   // C++11
#if __has_include(<simd>)
#include <simd>     // C++26
#endif
#include <valarray>

// Time
#include <chrono>  // C++11
#include <ctime>

// Input/Output
#include <cinttypes>   // C++11
#include <cstdio>
#include <filesystem>  // C++17
#include <fstream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <ostream>
#include <print>       // C++23
#include <spanstream>  // C++23
#include <sstream>
#include <streambuf>
#include <syncstream>  // C++20

// Concurrency
#include <atomic>              // C++11
#include <barrier>             // C++20
#include <condition_variable>  // C++11
#include <future>              // C++11
#if __has_include(<hazard_pointer>)
#include <hazard_pointer>      // C++26
#endif
#include <latch>               // C++20
#include <mutex>               // C++11
#if __has_include(<rcu>)
#include <rcu>                 // C++26
#endif
#include <semaphore>           // C++20
#include <shared_mutex>        // C++14
#include <stop_token>          // C++20
#include <thread>              // C++11

#ifdef LOGGER_USE_BOOST_ASIO
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>
#endif

#ifdef LOGGER_USE_BOOST_LOCKFREE
#include <boost/lockfree/queue.hpp>
#endif

#ifdef LOGGER_USE_SPDLOG
#include <spdlog/spdlog.h>
#endif

#ifdef LOGGER_USE_TBB
#include <tbb/concurrent_queue.h>
#include <tbb/scalable_allocator.h>
#endif

using namespace std::literals;
