#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Function to evaluate the sum of sine functions
double evaluateFunction(const vector<int>& A, const vector<int>& B, double x) {
    double result = 0.0;
    for (size_t i = 0; i < A.size(); ++i) {
        result += sin(A[i] * x + B[i]);
    }
    return result;
}

// Function to find local maxima
vector<double> findLocalMaxima(const vector<int>& A, const vector<int>& B, double step) {
    vector<double> peaks;
    double prevValue = evaluateFunction(A, B, 0);
    double currentValue;
    double nextValue;
    double x = step;

    for (double i = step; i <= 2 * M_PI; i += step) {
        currentValue = evaluateFunction(A, B, i);
        nextValue = evaluateFunction(A, B, i + step);

        if (prevValue < currentValue && currentValue > nextValue) {
            peaks.push_back(i);
        }
        prevValue = currentValue;
    }
    return peaks;
}

// Function to find the widest valley
int findWidestValley(const vector<double>& peaks) {
    int maxWidthIndex = 1;
    double maxWidth = 0.0;

    for (size_t i = 1; i < peaks.size(); ++i) {
        double width = peaks[i] - peaks[i - 1];
        if (width > maxWidth) {
            maxWidth = width;
            maxWidthIndex = i;
        }
    }

    return maxWidthIndex;
}

int main() {
    int n;
    cin >> n;

    vector<int> A(n);
    vector<int> B(n);

    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> B[i];
    }

    // Find local maxima
    vector<double> peaks = findLocalMaxima(A, B, 0.01); // Step size for evaluation

    // Check if we have at least 2 peaks to form a valley
    if (peaks.size() < 2) {
        cout << "No valleys detected" << endl;
        return 0;
    }

    // Find the widest valley
    int valleyIndex = findWidestValley(peaks);

    // Output the valley index (1-based)
    cout << valleyIndex << endl;

    return 0;
}
