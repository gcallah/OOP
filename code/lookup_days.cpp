#include "std_lib_facilities.h"

vector<int> last_day{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
vector<int> leap_last_day{0, 31, 29, 31, 30, 31, 30, 31, 31,
                            30, 31, 30, 31};
vector<string> month_nm{"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", 
                        "Aug", "Sep", "Oct", "Nov", "Dec"};

int main()
{
    for(int i = 1; i < 13; i++)
        cout << "The last day of " << month_nm[i] << " is " << last_day[i]
            << '\n';

    for(int m = 1; m < 13; m++) {
        for(int d = 27; d < 32; d++) {
            cout << "For " << month_nm[m] << " day of " << d << " is ";
            if(d > last_day[m])
                cout << " not valid\n";
            else
                cout << " valid\n";
        }
    }
}

