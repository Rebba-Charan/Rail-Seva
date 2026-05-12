#ifndef RAILADMIN_H
#define RAILADMIN_H

#include<bits/stdc++.h>
#include "people.h"

using namespace std;

class railadmin : public people{

    private:
    string name;
    long long phoneno;

    public:

    railadmin(string a,long long p);

    bool login();

    bool checklogin();

    void signup();

    void Addtrain();

    void Canceltrain();

    void profile();
};

#endif