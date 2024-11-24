#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <vector>

using namespace std;

struct Point {
    double x, y;
};

struct Circle {
    Point center;
    double radius;

    bool contains(const Point& p) const {
        return (pow(p.x - center.x, 2) + pow(p.y - center.y, 2)) <= pow(radius, 2); // <= for points on the border
    }
};

Point generate_random_point(double x_min, double x_max, double y_min, double y_max, mt19937& gen) {
    uniform_real_distribution<> x_distr(x_min, x_max);
    uniform_real_distribution<> y_distr(y_min, y_max);
    return {x_distr(gen), y_distr(gen)};
}

double calculate_true_area() {
    return 0.25 * M_PI + 1.25 * asin(0.8) - 1.0;
}

int main() {
    Circle c1 = {{1, 1}, 1};
    Circle c2 = {{1.5, 2}, sqrt(5) / 2.0};
    Circle c3 = {{2, 1.5}, sqrt(5) / 2.0};

    double true_area = calculate_true_area();
    cout << "True Area: " << true_area << endl;

    random_device rd;
    mt19937 generator(rd());

    vector<pair<double, double>> ranges = {{0, 3.5}, {0.3, 2.7}, {0.7, 2.3}};

    for (int range_index = 0; range_index < ranges.size(); ++range_index) {
        ofstream outputFile("../data/monte_carlo_data_" + to_string(range_index) + ".csv");
        outputFile << "N,Area,RelativeError\n";

        double approx_area, relative_error = 0;

        double x_min = ranges[range_index].first;
        double x_max = ranges[range_index].second;
        double y_min = ranges[range_index].first;
        double y_max = ranges[range_index].second;

        double rect_area = (x_max - x_min) * (y_max - y_min);

        for (int n = 100; n <= 100000; n += 500) {
            long long count = 0;
            for (int i = 0; i < n; ++i) {
                Point p = generate_random_point(x_min, x_max, y_min, y_max, generator);
                if (c1.contains(p) && c2.contains(p) && c3.contains(p)) {
                    count++;
                }
            }

            approx_area = (static_cast<double>(count) / n) * rect_area;
            relative_error = abs(approx_area - true_area) / true_area;

            outputFile << n << "," << approx_area << "," << relative_error << "\n";
        }
        outputFile.close();
        cout << "Range " << range_index + 1 << ": " << approx_area << " " << relative_error << "\n";

    }
    return 0;
}