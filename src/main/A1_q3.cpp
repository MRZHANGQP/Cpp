#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q3; see 题面.pdf.
namespace aim::q3 {


// BEGIN IMPLEMENTATION
// aim-cpp-cw
std::vector<int> alarms(const std::vector<int>& values, int k, long long threshold) {
    const std::size_t n = values.size();
    if (k < 1 || static_cast<std::size_t>(k) > n) {
        return {};
    }

    const std::size_t window = static_cast<std::size_t>(k);
    long long window_sum = 0;
    for (std::size_t i = 0; i < window; ++i) {
        window_sum += values[i];
    }

    std::vector<int> alarm_indices;
    alarm_indices.reserve(n - window + 1);

    if (window_sum > threshold) {
        alarm_indices.push_back(k - 1);
    }

    for (std::size_t right = window; right < n; ++right) {
        window_sum += static_cast<long long>(values[right]) - values[right - window];
        if (window_sum > threshold) {
            alarm_indices.push_back(static_cast<int>(right));
        }
    }

    return alarm_indices;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q3;
int main() {
    try {
        { CHECK((alarms({1,2,3,4},2,4)==std::vector<int>{2,3})); }
        { CHECK(alarms({},1,0).empty()); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
