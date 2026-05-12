#ifndef PASSENGER_H
#define PASSENGER_H

#include<bits/stdc++.h>
#include "people.h"

using namespace std;

class passenger : public people{

    private:
    string name;
    long long int phoneno;
    int age;
    char gender;

    public:

    passenger(string name,long long int a,int b,char c);

    bool login();

    bool checklogin();

    void signup();

    void book_ticket();

    void view_ticket();

    void view_profile();

    void edit_profile();

    void cancel_ticket();
};

#endif