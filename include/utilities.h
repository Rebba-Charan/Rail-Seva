#ifndef UTILITIES_H
#define UTILITIES_H

#include<bits/stdc++.h>
using namespace std;

long long int funcstoi(string a);

bool checknum(string a);

string calculate_end_date(string start_date,string duration);

int countDigits(int n);

int countDigit(long long int n);

bool findsubstring(string b,string a);

string generatepnr();

void cutticket(string bhogi,int n,string line);

#endif