#include "../include/railadmin.h"
#include "../include/utilities.h"
#include<fstream>
#include<sstream>
railadmin::railadmin(string a,long long p)
    {
        this->name = a;
        this->phoneno = p;
    }
    bool railadmin::login()//i will check username and password
    {
        ifstream fil("data/railadmindetails.txt");
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
    bool railadmin:: checklogin()
    {
        ifstream file("data/railadmindetails.txt");
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
    void railadmin:: signup()//I will write details of the passenger at the bottom 
    {
        ofstream write("data/railadmindetails.txt",ios::app);
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
    void railadmin::  Addtrain()
    {
        while(1)
        {
            cout<<"1-->AddTrain\n2-->Exit\n";
            int val;
            cin>>val;
            if(val==1)
            {
                cout<<"Enter the details of the Train:\n";
                string Trainname,Trainno,from,to,date,departuretime,arraivaltime,duration;
                cout<<"Enter Train name \n";
                cin>>Trainname;
                cout<<"Enter Train no \n";
                cin>>Trainno;
                cout<<"Enter from \n";
                cin>>from;
                cout<<"Enter to \n";
                cin>>to;
                cout<<"Enter date(format dd:mm:yy):\n";
                cin>>date;
                cout<<"Enter departuretime \n";
                cin>>departuretime;
                cout<<"Enter arraivaltime \n";
                cin>>arraivaltime;
                cout<<"Enter duration \n";
                cin>> duration;
                vector<string> temp = {"3AC","2AC","1AC","Sleeper","General"};
                cout<<"Enter the no of seats respectively\n";
                string bhogi = "";
                int n;
                for(int i = 0;i<temp.size();i++)
                {
                    bhogi+='/';
                    cout<<"Enter the number of seats for "<<temp[i]<<endl;
                    cin>>n;
                    bhogi += temp[i] + '-'+to_string(n);
                }
                bhogi = bhogi +'/';
                ofstream train("data/traindetails.txt",ios::app);
                if(!train)
                {
                    perror("File not opened\n");
                }
                string Train = Trainno + '|' + Trainname +'|' + from +'|' + to + '|'+ date + '|' + bhogi + '|'+departuretime + '|'+arraivaltime+'|'+duration;
                train<<Train<<"\n";
                cout<<"Train added succesfully\n";
                train.close(); 
                continue;

            }
            else if(val==2) return;
            else cout<<"Invalid choice .... try again\n";
        }
    }
    void railadmin:: Canceltrain()
    {
        while(1)
        {
            cout<<"1-->Cancel/Suspend Train\n2-->Exit\n";
            int val;
            cin>>val;
            if(val==1)
            {
                cout<<"Enter the train number you want suspend:\n";
                int traino;
                cin>>traino;
                ifstream infile("data/traindetails.txt");
                ofstream outfile("data/dummy.txt");
                if(!infile||!outfile)
                {
                    perror("File unable to open\n");
                    return;
                }
                string line;
                string straino = to_string(traino);
                while(getline(infile,line))
                {
                    int p = line.find('|');
                    if(line.substr(0,p)==straino) continue;
                    else outfile<<line<<"\n";
                }
                infile.close();
                outfile.close();
                if(remove("data/traindetails.txt")!=0)
                {
                    perror("File is unable to delete\n");
                    return;
                }
                if(rename("data/dummy.txt","data/traindetails.txt")!=0)
                {
                    perror("File is unable rename\n");
                    return;
                }
            }
            else if(val==2) return;
            else cout<<"Invalid choice ...Try again\n";
        }

    }
    void railadmin:: profile()
    {
        while(1)
        {
            cout<<"1-->View Profile\n2-->Edit Profile\n3-->exit\n";
            int val;
            cin>>val;
            if(val==1)
            {
         string username,password;
        ifstream read("data/railadmindetails.txt");
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
            ifstream check("data/railadmindetails.txt");
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
            ifstream check("data/railadmindetails.txt");
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
        ifstream inFile("data/railadmindetails.txt");
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
       if (remove("data/railadmindetails.txt") != 0) {
       perror("Error deleting file");
       }
       if (rename("data/dummy.txt", "data/railadmindetails.txt") != 0) {
        perror("Error renaming file");
        }
        cout<<"Username changed succesfully...\n";            
       }
    else if(val==2)
    {
        cout<<"Enter Your current password\n";
        string pass;
        cin>>pass;
        ifstream file("data/railadmindetails.txt");
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
        ifstream inFile("data/railadmindetails.txt");
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
       if (remove("data/railadmindetails.txt") != 0) {
       perror("Error deleting file");
       }
       if (rename("data/dummy.txt", "data/railadmindetails.txt") != 0) {
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