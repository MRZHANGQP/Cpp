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

// Assessment 01 Q2; see 题面.pdf.
namespace aim::q2 {
struct LabelEdit { std::string from; std::string to; };

// BEGIN IMPLEMENTATION
// aim-cpp-cw
std::string edit_labels(std::string labels, const std::vector<LabelEdit>& edits) {
    std::vector<std::string> tags;
    std::istringstream input(labels);
    std::string tag;
    while (std::getline(input, tag, ',')) {
        tags.push_back(tag);
    }

    for (const LabelEdit& edit : edits) {
        if (edit.from.empty()) {
            if (!edit.to.empty()) tags.push_back(edit.to);
            continue;
        }

        for (std::size_t i = 0; i < tags.size(); ++i) {
            if (tags[i] != edit.from) continue;

            if (edit.to.empty()) {
                tags.erase(tags.begin() + static_cast<std::ptrdiff_t>(i));
            } else {
                tags[i] = edit.to;
            }
            break;
        }
    }

    std::string result;
    for (std::size_t i = 0; i < tags.size(); ++i) {
        if (i != 0) result += ',';
        result += tags[i];
    }
    return result;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q2;
int main() {
    try {
        { CHECK(edit_labels("cam,imu,radar",{{"imu","gyro"},{"cam",""},{"","lidar"}})=="gyro,radar,lidar"); }
        { CHECK(edit_labels("cam,cam2,cam",{{"cam","camera"},{"cam",""}})=="camera,cam2"); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
