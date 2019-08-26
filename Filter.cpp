#include <string>

using namespace std;

class Filter {
    int n;
    string name;
    double mPixels[9][9];

  public:
    void set_values (int,int);
    int area (void);
};
