#include "../include/utilities.h"
#include<fstream>
#include<sstream>
#include<ctime>
long long int funcstoi(string a)
{
    long long int ans = 0;
    for(int i = 0;i<a.size();i++)
    {
        ans = ans*10 + (a[i]-'0');
    }
    return ans;
}
bool checknum(string a)
{
    int n = a.size();
    for(int i = 0;i<n;i++)
    {
        int t = a[i]-'0';
        if(!((t>=0)&&(t<=9))) return false;
    }
    return true;
}
string calculate_end_date(string start_date,string duration)
{
    int p1 = start_date.find('/');
    int day = funcstoi(start_date.substr(0,p1));
    string remaining = start_date.substr(p1);
    int p2 = duration.find('h');
    int time = funcstoi(duration.substr(0,p2));
    day+= (time/24);
    return (to_string(day) + remaining);
}
int countDigits(int n) {
    int count = 0;
    if (n == 0) return 1;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}
int countDigit(long long int n) {
    int count = 0;
    if (n == 0) return 1;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}
bool findsubstring(string b,string a)// a-->substr b-->mainstr
{

    int i ;
    int k = 0;
    for(i = 0;i<b.size();i++)
    {
        if(b[i]==a[k])
        {
            while((k<a.size())&&(b[i]==a[k]))
            {
                if(b[i]!=a[k])
                {
                    k = 0;
                    break;
                }
                i++;
                k++;
            }
            if(k==a.size())
            {
                return 1;
            }
        }
    }
    return 0;

}
string generatepnr()
{
    int zones[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int firstDigit = zones[rand() % 9];

    string pnr = to_string(firstDigit);

    // Generate the remaining 9 digits randomly
    for (int i = 0; i < 9; ++i) {
        pnr += to_string(rand() % 10);
    }

    return pnr;
}
void cutticket(string bhogi,int n,string line)
{
    ifstream read("data/traindetails.txt");
    if(!read.is_open())
    {
        cerr<<"Error"<<endl;
    }
    string coach;
    int p1 = line.find('|');
    int p2 = line.find('|',p1+1);    
    int p3 = line.find('|',p2+1);
    int p4 = line.find('|',p3+1);
    int p5 = line.find('|',p4+1);
    int p6 = line.find('|',p5+1);
    coach = line.substr(p5+1,p6-p5-1);
    stringstream ss(coach);
    string q;
    string final  = "";
    while(getline(ss,q,'/'))
    {
    int l1 = q.find('-');
    string b1 = q.substr(0,l1);
    if(b1 == bhogi)
    {
        int seat = funcstoi(q.substr(l1+1));
        seat-=n;
        string dum = b1 + "-" + to_string(seat);
        final += dum + "/";
    }
    else
    {
        final+= q + "/";
    } 
    }
    string prev = line.substr(0,p5);
    string next = line.substr(p6+1);
    string eline = prev + "|" + final + "|" + next;
    read.close();
    ifstream infile("data/traindetails.txt");
    ofstream outfile("data/dummy.txt");
    if(!infile||!outfile)
    {
        perror("Error");
        return;
    }
    string currline;
    while(getline(infile,currline))
    {
        if(currline == line)
        {
            outfile<<eline<<endl;

        }
        else
        {
            outfile<<currline<<endl;
        }
        
    }
    infile.close();
    outfile.close();
    if(remove("data/traindetails.txt"))
    {
        perror("Error\n");
    }
    if(rename("data/dummy.txt","data/traindetails.txt"))
    {
        perror("Error\n");
    }

}