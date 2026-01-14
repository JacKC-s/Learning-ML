#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

// Structure for data point
struct Point {
    float x;
    float y;
};

struct Dataset {
    vector<Point> data;
    size_t size() {
        return data.size();
    }

    void append(Point p) {
        data.push_back(p);
    }
};

Dataset loadCSV(const string& filename) {
    Dataset df;
    // Opens up file stream
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("File failed to open");
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string xVal, yVal;

        // Some funky c++ behavior; the getline method also executes
        if (!getline(ss, xVal, ',')) continue;
        if (!getline(ss, yVal, ',')) continue;

        Point p;
        p.x = stof(yVal); // Just swapped these...
        p.y = stof(xVal);

        df.append(p);
    }
    return df;
};

class Regression {
    public:
        Dataset ds;
        double meanx;
        double meany;
        double b_naught;
        double b_1;
        void compileDataFrame(Dataset set) {
            ds = set;            
        }   
        void findMeans() {
            double totalx = 0.0;
            double totaly = 0.0;
            int len = ds.size();
            for (auto i = 0; i < len; i++) {
                Point& p = ds.data[i]; //Reference to the point, doesnt create new point
                totalx += p.x;
                totaly += p.y;
            }
            meanx = totalx / len;
            meany = totaly / len;
            cout << "Mean X and Y: " << meanx << " " << meany << endl;
        }
        void calcRegression() {
            long double sumxy = 0.0;
            long double sumxsquared = 0.0;
            long double sumysquared = 0.0;
            long double sumy = 0.0;
            long double sumx = 0.0;
            int len = ds.size();
            

            // Summing data
            for (auto i = 0; i < len; i ++) {
                Point& p = ds.data[i];
                sumxy += p.x * p.y;
                sumxsquared += pow(p.x, 2);
                sumysquared += pow(p.y, 2);
                sumx += p.x;
                sumy += p.y;
            }
            
            b_naught = (((sumy)*(sumxsquared) - (sumx)*(sumxy)) / (len*(sumxsquared)-(pow(sumx,2))));
            b_1 = ((len*(sumxy)-(sumx)*(sumy)) / (len*(sumxsquared)-(pow(sumx,2))));

            cout << "y = " << b_naught << " + " << b_1 << "x";
        }
};


int main() {
    Regression Reg;
    Reg.compileDataFrame(loadCSV("data.csv"));
    cout << Reg.ds.size() << endl;
    Reg.findMeans();
    Reg.calcRegression();
    return 0;
}