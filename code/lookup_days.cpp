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

    for(int i = 26; i < 34; i++) {
        cout << "For " << month_nm[2] << " day of " << i << " is ";
        if(i > last_day[2])
            cout << " not valid\n";
        else
            cout << " valid\n";
    }
}

