#include "../include/stationmaster.h"
#include "../include/utilities.h"
#include<fstream>
#include<sstream>   
    stationmaster::stationmaster(string a,long long p)
    {
        this->name = a;
        this->phoneno = p;
    } 
    bool stationmaster::login()//i will check username and password
    {
        ifstream fil("data/stationmaster.txt");
        if(!fil.is_open())
        {
            cerr<<"error"<<endl;
            return 1;
        }
        string line;
        string number = to_string(this->phoneno);
        bool found = 0;
        while(getline(fil,line))
        {
            if(number==line.substr(0,10))
            {
                found = 1;
                break;
            }
        }
        if(!found)
        {
            cout<<"Your Details are not with us please sign up again..\n";
            return 0;
        }
        int p1 = line.find('|');
        int p2 = line.find('|',p1+1);
        int p3 = line.find('|',p2+1);
        string real_user = line.substr(p1+1,p2-p1-1);
        string real_pass = line.substr(p2+1,p3-p2-1);
        string username;
        string password;
        cout<<"Enter UserName :\n";
        cin>>username;
        cout<<"Enter Password :\n";
        cin>>password;
        while((username!=real_user)||(password!=real_pass))
        {
            cout<<"Either Username or password is wrong...try again"<<endl;
            cout<<"Enter UserName :\n";
            cin>>username;
            cout<<"Enter Password :\n";
            cin>>password;
        }
        fil.close();
        cout<<"Login succesfully"<<endl;
        return 1;
        
    }
    bool stationmaster:: checklogin()
    {
        ifstream file("data/stationmaster.txt");
        if(!file.is_open())
        {
            cerr<<"File is not opening "<<endl;
            return 0;
        }
        string s = to_string(this->phoneno);
        string line;
        while(getline(file,line))
        {
            if(s==line.substr(0,10)) return 1;
        }
        file.close();
        return 0;
    }
    void stationmaster:: signup()//I will write details of the passenger at the bottom 
    {
        ofstream write("data/stationmaster.txt",ios::app);
        if(!write.is_open())
        {
            cerr<<"error"<<endl;
            return ;
        }
        string username;
        string password;
        string reenter;
        cout<<"Please enter Your username: \n";
        cin>>username;
        cout<<"Please enter Your password: \n";
        cin>>password;
        cout<<"Reenter: \n";
        cin>>reenter;
        while(reenter!=password)
        {
            cout<<"enter the same password"<<endl;
            cin>>reenter;
        }
        string input = to_string(this->phoneno) + "|"+username+"|"+password;
        cin.ignore(10000,'\n');
        write<<input<<endl;
        write.close();
        cout<<"SignUp Completed successfully ...login Again\n";
    }    
    void stationmaster:: profile()
    {
        while(1)
        {
            cout<<"1-->View Profile\n2-->Edit Profile\n3-->exit\n";
            int val;
            cin>>val;
            if(val==1)
            {
         string username,password;
        ifstream read("data/stationmaster.txt");
        if(!read.is_open())
        {
            cerr<<"error"<<endl;
            return;
        }
        string line;
        int p1;
        while(getline(read,line))
        {
            p1 = line.find('|');
            if(to_string(this->phoneno)==line.substr(0,p1)) break;
        }
        int p2,p3;
        p2 = line.find('|',p1+1);
        p3 = line.find('|',p2+1);
        username = line.substr(p1+1,p2-p1-1);
        password = line.substr(p2+1,p3-p2-1);
        cout<<"<---------Profile--------->"<<endl;
        cout<<"name:-\t"<<this->name<<endl;
        cout<<"username:-\t"<<username<<endl;
        cout<<"Do you want to see password"<<endl;
        while(1)
        {
        cout<<"1-->Yes\n2-->No i will exit\n";
        int val;
        cin>>val;
        if(val==1)
        {
            cout<<"password:-\t"<<password<<endl;
            cout<<"Exitingg....\n";
            return;
        }
        else if(val==2)
        {
            return;
        }
        else
        {
            cout<<"Invalid choice...try again\n";
        }
        }
            }
            else if(val==2) 
            {
        while(1)
        {
        cout<<"What you want to edit :\n1-->username\n2-->password\n3-->exit\n";
        int val;
        cin>>val;
        if(val==1)
        {
       cout<<"To verify is it you...Please enter password\n";
            string password;
            cin>>password;
            ifstream check("data/stationmaster.txt");
            if(!check.is_open())
            {
                cerr<<"Error\n";
                return;
            }
            int p1,p2,p3;
            string oldline;
            while(1){
            bool found = 0;
            while(getline(check,oldline))
            {
                p1 = oldline.find('|');
                p2 = oldline.find('|',p1+1);
                p3 = oldline.find('|',p2+1);
                if(password==oldline.substr(p2+1,p3-p2-1))
                {
                    found = 1;
                    break;
                }
            }
            if(!found)
            {
                cout<<"You have entered wrong password..try again\n";
            }
            else{
                break;
            }
            }
            cout<<"Verification done successfully\n";
            check.close();
            string newuser;
            string temp;
            while(1)
            {
            cout<<"Enter Your new username\n";
            cin>>newuser;
            cout<<"Re-enter\n";
            while(1){
                cin>>temp;
                if(temp==newuser) break;
                cout<<"Re-enter again\n";
            }
            bool nonunique = 0;
            ifstream check("data/stationmaster.txt");
            if(!check.is_open())
            {
                cerr<<"Error\n";
                return;
            }
            string line;
            int q1,q2,q3;
            while(getline(check,line))
            {
                q1=line.find('|');
                q2=line.find('|',q1+1);
                if(newuser==line.substr(q1+1,q2-q1-1))
                {
                    nonunique = 1;
                    break;
                }

            }
            if(nonunique)
            {
                cout<<"This one taken...Please enter different username\n";
            }
            else 
            {
                cout<<"This one is unique\n";
                break;
            }
        }
        check.close();
        string prev = oldline.substr(0,p1);
        string suff = oldline.substr(p2+1);
        string newline = prev + '|'+newuser +'|'+suff;
        ifstream inFile("data/stationmaster.txt");
        ofstream outFile("data/dummy.txt");

        if (!inFile || !outFile) {
        cerr << "Error opening files!" << endl;
        return ;
        }
        string currentLine;
        while (getline(inFile, currentLine)) {
        if (currentLine == oldline) {
            outFile << newline << "\n"; // Write replacement
        } else {
            outFile << currentLine << "\n"; // Copy original
        }
        }

        inFile.close();
       outFile.close();
       if (remove("data/stationmaster.txt") != 0) {
       perror("Error deleting file");
       }
       if (rename("data/dummy.txt", "data/stationmaster.txt") != 0) {
        perror("Error renaming file");
        }
        cout<<"Username changed succesfully...\n";            
       }
    else if(val==2)
    {
        cout<<"Enter Your current password\n";
        string pass;
        cin>>pass;
        ifstream file("data/stationmaster.txt");
        if(!file.is_open()){
            cerr<<"Its an error\n";
            return;
        }
        string oldline;
        int p1,p2,p3;
        while(1)
        {
            bool found = 0;
           while(getline(file,oldline))
            {
            p1 = oldline.find('|');
            p2 = oldline.find('|',p1+1);
            if(pass==oldline.substr(p2+1))
            {
                found = 1;
                break;
            }
            }
          if(!found)
           {
            cout<<"wrong password.. try again\n";
           }
           else{
            break;
           }
            cin>>pass;
        }
        file.close();
        cout<<"Enter New Password\n";
        string newpass;
        cin>>newpass;
        cout<<"Reenter New Password\n";
        string temp;
        while(1)
        {
        cin>>temp;
        if(temp==newpass) break;
        cout<<"Wrong enter..Try again\n";
        }
        string prev = oldline.substr(0,p2);
        string newline = prev + '|'+newpass;
        ifstream inFile("data/stationmaster.txt");
        ofstream outFile("data/dummy.txt");

        if (!inFile || !outFile) {
        cerr << "Error opening files!" << endl;
        return ;
        }
        string currentLine;
        while (getline(inFile, currentLine)) {
        if (currentLine == oldline) {
            outFile << newline << "\n"; // Write replacement
        } else {
            outFile << currentLine << "\n"; // Copy original
        }
        }

        inFile.close();
       outFile.close();
       if (remove("data/stationmaster.txt") != 0) {
       perror("Error deleting file");
       }
       if (rename("data/dummy.txt", "data/stationmaster.txt") != 0) {
        perror("Error renaming file");
        }
        cout<<"Password changed succesfully...\n";      
    }
    else if(val==3) return;    
    else
    {
    cout<<"Invalid choice try again\n";
    }
    }
    }
            else if(val==3)
            {
                return;
            }
            else cout<<"Invalid choice...try again\n";
        }
    }
    void stationmaster:: update()
    {
        cout<<"Enter the trainno You want update timing\n";
        string trainno;
        cin>>trainno;
        while(countDigits(funcstoi(trainno))!=5)
        {
            cout<<"Digit exceeded...Try again\n";
            cin>>trainno;
        }
        ifstream read("data/traindetails.txt");
        if(!read.is_open())
        {
            perror("Error not opening\n");
            return;
        }
        string line;
        int p;
        bool found = 0;
        while(getline(read,line))
        {
            p = line.find('|');
            if(trainno==line.substr(0,p))
            {
                found = 1;
                break;
            }
        }
        read.close();
        if(!found)
        {
            cout<<"Either you entered wrong pnr or train is not there...\n";
            return;
        }
        int p1,p2,p3,p4,p5,p6,p7,p8;
        cout<<"1-->Update Time\n2-->Update Date\n";
        int val;
        cin>>val;
        if(val==1)
        {
            p1 = line.find('|');
            p2 = line.find('|',p1+1);
            p3 = line.find('|',p2+1);
            p4 = line.find('|',p3+1);
            p5 = line.find('|',p4+1);
            p6 = line.find('|',p5+1);
            p7 = line.find('|',p6+1);
            p8 = line.find('|',p7+1);
            cout<<"1-->Arraival Time\n2-->Departure Time\n";
            int val;
            cin>>val;
            if(val==1)
            {
                string arrtime;
                cout<<"Enter the new arraival time(hh:mm)\n";
                cin>>arrtime;
                string newline,prev,post;
                prev = line.substr(0,p6);
                post = line.substr(p7+1);
                newline = prev + '|' + arrtime +'|' + post;
                ifstream infile("data/traindetails.txt");
                ofstream outfile("data/dummy.txt");
                if(!infile||!outfile)
                {
                    cerr<<"Error"<<endl;
                    return;
                }
                string currline;
                while(getline(infile,currline))
                {
                    if(currline==line)
                    {
                        outfile<<newline<<endl;
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
                    perror("File is not deleting\n");
                    return;
                }
                if(rename("data/dummy.txt","data/traindetails.txt"))
                {
                    perror("File is not renamed\n");
                    return;
                }
                cout<<"Arraival time updated successfully\n";
            }
            else if(val==2)
            {
                string deptime;
                cout<<"Enter the new departure time(hh:mm)\n";
                cin>>deptime;
                string newline,prev,post;
                prev = line.substr(0,p7);
                post = line.substr(p8+1);
                newline = prev + '|' + deptime +'|' + post;
                ifstream infile("data/traindetails.txt");
                ofstream outfile("data/dummy.txt");
                if(!infile||!outfile)
                {
                    cerr<<"Error"<<endl;
                    return;
                }
                string currline;
                while(getline(infile,currline))
                {
                    if(currline==line)
                    {
                        outfile<<newline<<endl;
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
                    perror("File is not deleting\n");
                    return;
                }
                if(rename("data/dummy.txt","data/traindetails.txt"))
                {
                    perror("File is not renamed\n");
                    return;
                }
                cout<<"Departure Time updated succesfully\n";
            }
           
        }
        else if(val==2)
        {
            p1 = line.find('|');
            p2 = line.find('|',p1+1);
            p3 = line.find('|',p2+1);
            p4 = line.find('|',p3+1);
            p5 = line.find('|',p4+1);
                string arrdate;
                cout<<"Enter the new arraival date(dd/mm/yy)\n";
                cin>>arrdate;
                string newline,prev,post;
                prev = line.substr(0,p4);
                post = line.substr(p5+1);
                newline = prev + '|' + arrdate +'|' + post;
                ifstream infile("data/traindetails.txt");
                ofstream outfile("data/dummy.txt");
                if(!infile||!outfile)
                {
                    cerr<<"Error"<<endl;
                    return;
                }
                string currline;
                while(getline(infile,currline))
                {
                    if(currline==line)
                    {
                        outfile<<newline<<endl;
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
                    perror("File is not deleting\n");
                    return;
                }
                if(rename("data/dummy.txt","data/traindetails.txt"))
                {
                    perror("File is not renamed\n");
                    return;
                }
                cout<<"Arraival date updated succesfully\n";
        }
        else cout<<"Wrong choice...try again\n";
    }

    void stationmaster:: announce()
    {
        ifstream spread("data/traindetails.txt");
        if(!spread.is_open())
        {
            cerr<<"error"<<endl;
            return;
        }
        int pf = (1+rand())%6;
        cout<<"Enter the date you want to see(dd/mm/yy):\n";//rn my database is small so i use this after i will keep currdate for this
        string date;
        cin>>date;
        int p1,p2,p3,p4,p5,p6,p7,p8;
        string line;
        cout<<"Trainno\t"<<"TrainName\t"<<"Arraival Time\t"<<"Departure Time\t"<<"Platformno"<<endl;
        while(getline(spread,line))
        {
            p1 = line.find('|');
            p2 = line.find('|',p1+1);
            p3 = line.find('|',p2+1);
            p4 = line.find('|',p3+1);
            p5 = line.find('|',p4+1);
            if(date != line.substr(p4+1,p5-p4-1))
            {
                continue;
            }
            int pf = (1+rand())%6;
            p6 = line.find('|',p5+1);
            p7 = line.find('|',p6+1);
            p8 = line.find('|',p7+1);
            cout<<line.substr(0,p1)<<"\t"<<line.substr(p1+1,p2-p1-1)<<"\t"<<line.substr(p6+1,p7-p6-1)<<"\t"<<line.substr(p7+1,p8-p7-1)<<"\t\t"<<pf<<endl;
            
        }
        spread.close();
    }