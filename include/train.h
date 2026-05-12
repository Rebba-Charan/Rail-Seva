#ifndef TRAIN_H
#define TRAIN_H

#include<bits/stdc++.h>
using namespace std;

class train{
    private:
    int train_no;
    string train_name;
    string from;
    string to;
    string date;
    string classes;
    string a_time;
    string a_place;
    string d_time;
    string d_place;
    int duration;

    public:
    void showtrains(string from,string to,string date,string classes);
};

#endif