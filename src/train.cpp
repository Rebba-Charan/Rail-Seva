#include "../include/train.h"
#include "../include/utilities.h"
#include<fstream>
void train :: showtrains(string from,string to,string date,string classes)
    {
        ifstream search("data/traindetails.txt");
        if(!search.is_open())
        {
            cerr<<"Error"<<endl;
            return;
        }
        string line;
        bool found = 0;
        while(getline(search,line))
        {
            int p1 = line.find('|');
            int p2 = line.find('|',p1+1);
            int p3 = line.find('|',p2+1);
            int p4 = line.find('|',p3+1);
            int p5 = line.find('|',p4+1);
            int p6 = line.find('|',p5+1);
            
            string a = line.substr(p2+1,p3-p2-1);
            string b = line.substr(p3+1,p4-p3-1);
            string c = line.substr(p4+1,p5-p4-1);
            string d = line.substr(p5+1,p6-p5-1);
            if((findsubstring(a,from))&&(findsubstring(b,to))&&(c==date)&&(findsubstring(d,classes)))
            {
                found = 1;
                cout<<"Train:"<<endl;
                cout<<line<<endl;
            } 
        }
        if(!found)
        {
            cout<<"Sorry but There is No Train"<<endl;
        }
        else{
            cout<<"End of the list"<<endl;
        }
        
        search.close();
    }