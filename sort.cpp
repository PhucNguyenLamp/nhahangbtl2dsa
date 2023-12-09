// main.h
#include <bits/stdc++.h>
#include <string>
using namespace std;
// bool sortlist(pair<char, int> a, pair<char, int> b)
//     {
//         return a.second > b.second;
//     }
int main(){
    vector<pair<char, int>> list;
    string name = "aab";
    for (int i = 0; i < name.length(); i++)
    {
        bool found = false;
        for (int j = 0; j < list.size(); j++)
        {
            if (list[j].first == name[i])
            {
                list[j].second++;
                found = true;
                break;
            }
        }
        if (!found) list.push_back(make_pair(name[i], 1));
    }
    // caesar cipher the letter of the list, shift equals to frequency of the letter
    // for example a+2 = c and z+2 = b and Z+2 = B
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].first >= 'a' && list[i].first <= 'z')
        {
            list[i].first += list[i].second;
            if (list[i].first > 'z')
            {
                list[i].first -= 26;
            }
        }
        else if (list[i].first >= 'A' && list[i].first <= 'Z')
        {
            list[i].first += list[i].second;
            if (list[i].first > 'Z')
            {
                list[i].first -= 26;
            }
        }
        else //để cho vui thôi, không có chữ cái nào khác cả
        {
            list[i].first += list[i].second;
        }
    }
    // if there are 2 letters that is the same, combine them into 1
    for (int i = 0; i < list.size(); i++)
    {
        for (int j = i + 1; j < list.size(); j++)
        {
            if (list[i].first == list[j].first)
            {
                list[i].second += list[j].second;
                list.erase(list.begin() + j);
            }
        }
    }
    // sort the list from the highest frequency to the lowest
    // sort(list.begin(), list.end(), sortlist);
    //print
    for (int i = 0; i < list.size(); i++)
    {
        cout << list[i].first << " " << list[i].second << endl;
    }
}