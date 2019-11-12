#include <iostream>
#include <vector>

int main()
{
    std::vector<int> xs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //std::vector<int> xs{0};    // Works
    //std::vector<int> xs{0, 0};    // Works

    for (auto it = xs.begin(); it != xs.end(); ++it) {
        for (int i = 0; i < *it; i++) {
            xs.push_back(*it);
        }
    }

    std::cout << "Vector: ";
    for (const auto &x : xs) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}
