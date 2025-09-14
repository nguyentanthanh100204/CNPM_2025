
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Hàm giải phương trình trùng phương
int solveQuartic(double a, double b, double c, double x[]) {
    if (a == 0 && b == 0 && c == 0) {
        return -1;
    }

    if (a == 0 && b == 0) {
        return 0;
    }
    if (a == 0) {
        double y = -c / b;
        if (y < 0) return 0;
        x[0] = sqrt(y);
        x[1] = -sqrt(y);
        return 2;
    }
    double delta = b * b - 4 * a * c;
    if (delta < 0) return 0;
    double y1 = (-b + sqrt(delta)) / (2 * a);
    double y2 = (-b - sqrt(delta)) / (2 * a);
    int count = 0;
    if (y1 >= 0) {
        x[count++] = sqrt(y1);
        x[count++] = -sqrt(y1);
    }
    if (y2 >= 0 && y2 != y1) {
        x[count++] = sqrt(y2);
        x[count++] = -sqrt(y2);
    }
    return count;
}

// Hàm so sánh nghiệm (cho phép sai số nhỏ với số thực)
bool compareSolutions(vector<double> expected, vector<double> actual, double eps = 1e-6) {
    if (expected.size() != actual.size()) return false;
    sort(expected.begin(), expected.end());
    sort(actual.begin(), actual.end());
    for (size_t i = 0; i < expected.size(); i++) {
        if (fabs(expected[i] - actual[i]) > eps) return false;
    }
    return true;
}

// Cấu trúc test case
struct TestCase {
    double a, b, c;
    int expectedCount;
    vector<double> expectedSolutions;
    string description;
};

int main() {
    vector<TestCase> tests = {
        {0, 0, 0, -1, {}, "Vô số nghiệm"},
        {0, 0, 5, 0, {}, "Vô nghiệm"},
        {0, 2, -8, 2, {2, -2}, "2 nghiệm: ±2"},
        {1, 0, -1, 2, {1, -1}, "2 nghiệm thực: ±1"},
        {1, -5, 4, 4, {2, -2, 1, -1}, "4 nghiệm thực: ±2, ±1"},
        {1, 2, 3, 0, {}, "Vô nghiệm (Δ < 0)"}
    };
    var Test = "111"; //để push lên coi có không
    int passCount = 0;
    for (size_t i = 0; i < tests.size(); i++) {
        double x[4];
        int n = solveQuartic(tests[i].a, tests[i].b, tests[i].c, x);
        vector<double> actual(x, x + n);

        bool pass = (n == tests[i].expectedCount);
        if (n > 0 && tests[i].expectedCount > 0)
            pass = pass && compareSolutions(tests[i].expectedSolutions, actual);

        cout << "Test " << i + 1 << " (" << tests[i].description << "): ";
        if (pass) {
            cout << "PASS\n";
            passCount++;
        } else {
            cout << "FAIL (Expected " << tests[i].expectedCount << " solutions, got " << n << ")\n";
            if (n > 0) {
                cout << "  Actual solutions: ";
                for (double sol : actual) cout << fixed << setprecision(6) << sol << " ";
                cout << "\n";
            }
        }
    }

    cout << "\nSummary: " << passCount << "/" << tests.size() << " test cases passed.\n";
    return 0;
}
