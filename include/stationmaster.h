#ifndef STATIONMASTER_H
#define STATIONMASTER_H

#include<bits/stdc++.h>
#include "people.h"

using namespace std;

class stationmaster : public people{

    private:
    string name;
    long long phoneno;

    public:

    stationmaster(string a,long long p);

    bool login();

    bool checklogin();

    void signup();

    void profile();

    void update();

    void announce();
};

#endif