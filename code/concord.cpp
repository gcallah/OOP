#include "std_lib_facilities.h"

int main()
{
    cout << "Enter the words of a text and we will make a concordance:\n";
    
    vector<string> concordance;
    for(string iword; cin>>iword; )
        concordance.push_back(iword);

    sort(concordance);

    bool first_word = true;
    string prev_word = "";
    int count = 0;
    for(string word : concordance) {
        if(first_word) {
            prev_word = word;
            first_word = false;
        }
        if(word != prev_word) {
            cout << prev_word << " occurred " << count << " times." << '\n';
            count = 1;
        }
        else
            count++;
        prev_word = word;
    }
    cout <<prev_word << " occurred " << count << " times." << '\n';
    keep_window_open();
    return 0;
}
