/*
 * WorkExperience.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: k1
 */

// Sample code to read in test cases:
#include "mylibs.h"

int get_date_offset(string s, const map<string, int> months){
    string month = s.substr(0, 3);
    transform(month.begin(), month.end(), month.begin(), ::tolower);
    return 12 * (atoi(s.substr(4,8).c_str()) - 1990) + months.at(month);
}

vi get_range_offset(string s, const map<string, int> months) {
    vi range = vi(2, 0);
    range[0] = get_date_offset(s.substr(0, 8), months);
    range[1] = get_date_offset(s.substr(9, 17), months);
    return range;
}
void create_map(map<string, int> &months) {
    string month_arr[] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
    for (int i = 0; i < 12; ++i)
        months[month_arr[i]] =  i + 1;
}

bool predicate(const vi& a, const vi& b)
{
    return a[0] < b[0];
}

int get_exp_years(vvi dates) {
    sort(dates.begin(), dates.end(), predicate);
    int start, end;
    int total_len = dates.size();
    if (total_len == 0)
        return 0;
    start = dates[0][0];
    end = dates[0][1];
    int i = 0;
    int sum_month = 0;
    while (i < total_len) {
        i++;
        if (i == total_len) {
            sum_month += (end - start + 1);
            break;
        } else if (dates[i][0] > end) {
            sum_month += (end - start + 1);
            start = dates[i][0];
            end = dates[i][1];
        } else if (dates[i][1] > end)
            end = dates[i][1];
    }
    return sum_month / 12;
}
//void print_dates(vvi dates) {
//    for (vvi::iterator it = dates.begin(); it!= dates.end(); ++it)
//        cout << (*it)[0] << "-" << (*it)[1] << ";";
//}

int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
    string line;
    string delimeter = "; ";
    string date_str;
    map<string, int> months;
    create_map(months);

    while (getline(stream, line)) {
        if (!line.length())
            continue;
        vvi dates;
        int idx = 0;
        int i = 0;
        do {
            idx = line.find(delimeter);
            if (idx == string::npos) {
                dates.push_back(get_range_offset(line.substr(0, line.length()), months));
                break;
            }
            dates.push_back(get_range_offset(line.substr(0, idx), months));
            line = line.substr(idx + delimeter.length(), line.length());
        } while (line.length());
//        print_dates(dates);
        cout << get_exp_years(dates) << endl;
//        cout << "****************************************\n";
    }

    return 0;
}


