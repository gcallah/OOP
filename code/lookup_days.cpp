#include "std_lib_facilities.h"

vector<int> last_day{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
vector<int> leap_last_day{0, 31, 29, 31, 30, 31, 30, 31, 31,
                            30, 31, 30, 31};

int main()
{
    for(int i = 1; i < 13; i++)
        cout << "The last day of month " << i << " is " << last_day[i]
            << '\n';
}

