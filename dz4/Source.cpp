#include <iostream>
#include <vector>
#include <iterator>
#include <tuple>
#include <algorithm>
#include <random>
#include <functional>
#include <math.h>
#include <numeric>
int main()
{
    using namespace std;
    vector<int> first;
    first.reserve(30);
    {
        int i = 1;
        generate_n(back_inserter(first), 10, [i]()mutable {return i++; });
    }
    cout << "1) First sequence: ";
    for_each(first.begin(), first.end(), [](int i) {cout << i << " "; });
    cout << "\n2) Add few numbers: " << endl;
    copy(istream_iterator <int>(cin), istream_iterator <int>(), back_inserter(first));
    cout << endl;
    for_each(first.begin(), first.end(), [](int i) {cout << i << " "; });
    {
        cout << "\n3) Shuffle:" << endl;
        random_device rd;
        mt19937 RD(rd());
        shuffle(first.begin(), first.end(), RD);
        for_each(first.begin(), first.end(), [](int i) { cout << i << " "; });
    }
    cout << "\n4) Erase duplicates: " << endl;
    sort(first.begin(), first.end());
    auto fel = unique(first.begin(), first.end());
    first.erase(fel, first.end());
    for_each(first.begin(), first.end(), [](int i) {cout << i << " "; });
    cout << endl;
    {
        auto j = count_if(first.begin(), first.end(), [](int i) { return i % 2 != 0; });
        cout << "5) Amount of odd numbers is " << j << endl;
    }
    {
        auto [min,max] = minmax_element(first.begin(), first.end());
        cout << "6) Max is " << *max << ", min is " << *min << endl;


        int j = 2;
        vector<int> a = { 2 };
        generate_n(back_inserter(a), static_cast<int>(sqrt(abs(*max))), [j]() mutable {return j++; });
        auto k = find_if(first.begin(), first.end(), [a](int i) {
            auto b = count_if(a.begin(), a.end(), [i](int h) {
                if (i == 0) { return 0; }
                else if (i != h) {
                    if (i % h == 0)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else { return 0; }});
            if (b == 0 && i != 1)
            {
                return 1;
            }
            else {
                return 0;
            }

        });
        if (k != first.end()) {
            cout << "7) First prime element: " << *k << endl;
        }
        else {
            cout << "7) No prime elements" << endl;
        }
    }
    for_each(first.begin(), first.end(), [](int& i) { i = i * i; });
    cout << "8) Squared sequence:" << endl;
    for_each(first.begin(), first.end(), [](int i) {cout << i << " "; });
    cout << endl;

    vector<int> second;
    second.reserve(first.size());
    random_device rd;
    mt19937 RD(rd());
    generate_n(back_inserter(second), first.size(), RD);
    cout << "9) Second sequence: " << endl;
    for_each(second.begin(), second.end(), [](int i) {cout << i << " "; });
    cout << endl;
    {
        auto sum = accumulate(second.begin(), second.end(), 0);
        cout << "10) Sum of second sequence = " << sum << endl;
    }
    fill_n(second.begin(), 3, 1);
    cout << "11) Replacing elements with one: " << endl;
    for_each(second.begin(), second.end(), [](int i) {cout << i << " "; });
    cout << endl;
    vector<int> third;
    third.reserve(first.size());
    {
        int i = -1;
        generate_n(back_inserter(third), first.size(), [first, second, i]() mutable {i++;  return first[i] - second[i]; });
    }
    cout << "12) Third sequence: " << endl;
    for_each(third.begin(), third.end(), [](int i) {cout << i << " "; });
    cout << endl;
    for_each(third.begin(), third.end(), [](int& i) {if (i < 0) { i = 0; } });
    //sort(third.begin(), third.end(), greater<int>());
    cout << "13) Replacing negative numbers with 0: " << endl;
    for_each(third.begin(), third.end(), [](int i) {cout << i << " "; });
    cout << endl;
    {
        while (find(third.begin(), third.end(), 0) != third.end()) {
            third.erase(find(third.begin(), third.end(), 0));
        }
    }
    cout << "14) Sequence without 0:" << endl;
    for_each(third.begin(), third.end(), [](int i) {cout << i << " "; });
    cout << endl;
    {
        int a = 1;
        for_each(third.begin(), prev(third.end(), third.size() / 2), [a, &third](int& i)mutable {swap(i, *prev(third.end(), a)); a++; });//15
    }
    cout << "15) Reverse sequence: " << endl;
    for_each(third.begin(), third.end(), [](int i) {cout << i << " "; });
    cout << endl;
    {
        if (third.size() <= 3) {
            for_each(third.begin(), third.end(), [](int i) {cout << i << " "; });
            cout << endl;
        }
        else {
            vector<int> max = { third[0],third[1],third[2] };
            sort(max.begin(), max.end(), less<int>());
            for_each(next(third.begin(), 3), third.end(), [&max](int i) {if (max[0] < i) {
                max[0] = i; sort(max.begin(), max.end(), less<int>());
            }});
            cout << "16) Top 3 max elements: " << endl;
            for_each(max.begin(), max.end(), [](int i) {cout << i << " "; });
            cout << endl;
        }
    }
    sort(second.begin(), second.end(), less<int>());
    cout << "17) Second sorted sequence: " << endl;
    for_each(second.begin(), second.end(), [](int i) {cout << i << " "; });
    cout << endl;
    vector<int> fourth;
    fourth.reserve(first.size() * 2);
    merge(first.begin(), first.end(), second.begin(), second.end(), back_inserter(fourth), less<int>());
    cout << "18) Fourth merged sequence: " << endl;
    for_each(fourth.begin(), fourth.end(), [](int i) {cout << i << " "; });
    cout << endl;
    {
        auto k = upper_bound(fourth.begin(), fourth.end(), 1);
        auto c = lower_bound(fourth.begin(), fourth.end(), 1);
        pair<int, int> lownumber = { 0,0 };
        find_if(fourth.begin(), fourth.end(),
                [&lownumber, c](int i) mutable {if (lownumber.second == 0) { if (i == *c) { return lownumber.second = 1; } else { lownumber.first++; return 0; } } else return 0; });
        pair<int, int> upnumber = { 0,0 };
        find_if(fourth.begin(), fourth.end(),
                [&upnumber, k](int i) mutable {if (upnumber.second == 0) { if (i == *k) { return upnumber.second = 1; } else { upnumber.first++; return 0; } } else return 0; });
        cout << "Between " << lownumber.first << " - " << upnumber.first << endl;//19
    }



    cout << "First sequence:" << endl;
    for_each(first.begin(), first.end(), [](int i) {cout << i << " "; });
    cout << endl << "Second sequence:" << endl;;
    for_each(second.begin(), second.end(), [](int i) {cout << i << " "; });
    cout << endl << "Third sequence:" << endl;;
    for_each(third.begin(), third.end(), [](int i) {cout << i << " "; });
    cout << endl << "Fourth sequence:" << endl;;
    for_each(fourth.begin(), fourth.end(), [](int i) {cout << i << " "; });
    cout << endl;
}
