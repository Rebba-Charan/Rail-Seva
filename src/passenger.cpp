#include "../include/passenger.h"
#include "../include/utilities.h"
#include "../include/train.h"
#include<fstream>
#include<sstream>
#include<ctime>
passenger::passenger(string name,long long int a,int b,char c)
{
    this->name = name;
    this->phoneno = a;
    this->age = b;
    this->gender = c;
}
bool passenger :: login()//i will check username and password
    {
        ifstream fil("data/passengerdetails.txt");
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
    bool passenger:: checklogin()
    {
        ifstream file("data/passengerdetails.txt");
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
    void passenger:: signup()//I will write details of the passenger at the bottom 
    {
        ofstream write("data/passengerdetails.txt",ios::app);
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
        string input = to_string(this->phoneno) + "|"+username+"|"+password+"|"+this->gender+"|"+to_string(this->age);
        write<<input<<endl;
        write.close();
        cout<<"SignUp Completed successfully ...login Again\n";
    }
    void passenger:: book_ticket()
    {
    string train_name,train_no,line;
    int p1,p2;
    cout<<"Search Train:-\n1-->TrainName\n2-->TrainNo\n";
    bool found = 0;
    int val;
    cin>>val;
    if(val==1)
    {
    cout<<"Enter Train Name:\n";
    cin.ignore(500000,'\n');
    getline(cin,train_name);
    ifstream search("data/traindetails.txt");
    if(!search.is_open())
    {
        cerr<<"error"<<endl;
        return;
    }
    while(getline(search,line))
    {
        p1 = line.find('|');
        p2 = line.find('|',p1+1);
        string train = line.substr(p1+1,p2-p1-1);
        if(train_name==train)
        {
            cout<<"Yes there is a train \n";
            found = 1;
            break;
        }

    }
    }else if(val==2)
    {
    cout<<"Enter Train No:\n";
    cin.ignore(500000,'\n');
    getline(cin,train_no);
    ifstream search("data/traindetails.txt");
    if(!search.is_open())
    {
        cerr<<"error"<<endl;
        return;
    }
    while(getline(search,line))
    {
        p1 = line.find('|');
        p2 = line.find('|',p1+1);
        string train = line.substr(0,p1);
        if(train_no==train)
        {
            cout<<"Yes there is a train \n";
            found = 1;
            break;
        }

    }
    }
    else{
        cout<<"Invalid choice...Try again\n";
    }
    if(!found) 
    {
        cout<<"train not found or you entered wrong try again..\n";
        return;
    }
    // cin.ignore(500000,'\n');
    string from,to,start_date,coach,start_time,end_time,duration,end_date;
    int p3 = line.find('|',p2+1);
    int p4 = line.find('|',p3+1);
    int p5 = line.find('|',p4+1);
    int p6 = line.find('|',p5+1);
    int p7 = line.find('|',p6+1);
    int p8 = line.find('|',p7+1);
    train_no = line.substr(0,p1);
    from = line.substr(p2+1,p3-p2-1);
    to = line.substr(p3+1,p4-p3-1);
    start_date = line.substr(p4+1,p5-p4-1);
    coach = line.substr(p5+1,p6-p5-1);
    start_time = line.substr(p6+1,p7-p6-1);
    end_time = line.substr(p7+1,p8-p7-1);
    duration = line.substr(p8+1);
    train_name = line.substr(p1+1,p2-p1-1);
    string pnr = generatepnr();
    map<string,int> mapy;
    stringstream ss(coach);
    string q;
    // cin.ignore(50000,'\n');
    while(getline(ss,q,'/'))
    {
    int l1 = q.find('-');
    string b1 = q.substr(0,l1);
    int n1 = funcstoi(q.substr(l1+1));
    mapy[b1] = n1;
    }
    cout<<"Train Bhogi Details:\n";
    for(auto& a : mapy)
    {
        cout<<a.first<<"-"<<a.second<<endl;
    }
    cout<<"Enter the number of passenger including yourself\n";     
    int n;
    cin>>n;
    cout<<"Enter the Bhogi :\n";
    string bhogi;
    bool exiti = 0;
    while(1)
    {
        cin>>bhogi;
        if(mapy[bhogi]>=n) 
        {
            cout<<"Available...You can book\n";
            cout<<"1-->Yes i will book\n2-->No i will see another Train\n";
            int val;
            cin>>val;
            if(val==1)
            {
                break;
            }
            else if(val==2)
            {
                return;
            }
            else{
                cout<<"Invalid choice..please enter (1/2)\n";
            }
            
        }
        else
        {
            cout<<"1-->choose another bhogi\n2-->exit\n";
            int val;
            cin>>val;
            if(val==2){
                exiti = 1;
                break;
            }
        }
    }
    if(exiti==1) return;//ticketinspector->phnno|passengername|age|gender  ticket->pnr|phnno|ticketstaus(booking|current)|traindetails
    cutticket(bhogi,n,line);
    long long int phno = this->phoneno;
    ofstream input("data/ticket.txt",ios::app);
    if(!input.is_open())
    {
        cerr<<"Error"<<endl;
        return;
    }
    string book_time;
    time_t now = time(nullptr);
    book_time = ctime(&now);
    end_date = calculate_end_date(start_date,duration);
    string tic = pnr + "|" + to_string(phno) +"|"+from+"|"+to+"|"+start_date +"*|"+end_date+"*|"+train_name+"|"+train_no+"|"+bhogi+"|"+book_time;
    input<<tic<<endl;
    input.close();
    cout<<"Enter the details of the "<<n<<" passengers:-"<<endl;//here i want to create something which shows train inside so that we can give preference to passenger
    string name;
    int age;
    char gender;
    ofstream train_inspe("data/ticketinspector.txt",ios::app);
    if(!train_inspe.is_open())
    {
        cerr<<"Error"<<endl;
        return;
    }
    for(int i =0;i<n;i++)
    {
        cout<<"Enter name:\n";
        cin.ignore(500000,'\n');
        getline(cin,name);
        cout<<"Enter Age:\n";
        cin>>age;
        cout<<"Enter Gender(M/F/Other):\n";
        cin>>gender;
        string entry = pnr+"|"+to_string(phno) + "|"+name+"|" + to_string(age) + "|"+gender;
        train_inspe<<entry<<endl;
    }
    cout<<"Your tickets are booked succesfully"<<endl;
    cout<<"This is Your pnr "<<pnr<<" From this you can see status\n";
    train_inspe.close();
    }
    void passenger:: view_ticket()
    {
        cout<<"Enter your PNR number(It should be 10 digits):\n";
        string s;
        while(1)
        {
            cin>>s;
            if(checknum(s)==false)
            {
                cout<<"Please enter only numericals..try again\n";
            }
            else{
                break;
            }
        }
        long long int n = funcstoi(s);
        while(countDigit(n)!=10)
        {
            cout<<"Please Enter 10 digits..Try again\n";
            cin>>n;
        }
        bool found = 0;
        string spnr = s;
        ifstream details("data/ticket.txt");
        if(!details.is_open())
        {
            cerr<<"Error"<<endl;
            return;
        }
        string lini;
        while(getline(details,lini))
        {
            int p = lini.find('|');
            string temp = lini.substr(0,p);
            if(temp==spnr)
            {
                found = 1;
                break;
            }
        }
        if(!found)
        {
            cout<<"Either You entered wrong pnr or there is no info... please try again\n";
            return;
        }
        int p1 = lini.find('|');
        int p2 = lini.find('|',p1+1);
        int p3 = lini.find('|',p2+1);
        int p4 = lini.find('|',p3+1);
        int p5 = lini.find('|',p4+1);
        int p6 = lini.find('|',p5+1);
        int p7 = lini.find('|',p6+1);
        int p8 = lini.find('|',p7+1);
        int p9 = lini.find('|',p8+1);
        string from,to,from_date,to_date,train_name,train_no,bhogi,time;
        from = lini.substr(p2+1,p3-p2-1);
        to = lini.substr(p3+1,p4-p3-1);
        from_date = lini.substr(p4+1,p5-p4-1);
        to_date = lini.substr(p5+1,p4-p3-1);
        train_name = lini.substr(p6+1,p7-p6-1);
        train_no = lini.substr(p7+1,p8-p7-1);
        bhogi = lini.substr(p8+1,p9-p8-1);
        time = lini.substr(p9+1);
        cout<<"Ticket:-"<<endl;
        cout<<from<<"\t\t\t\t\t\t\t\t"<<to<<endl;
        cout<<from_date<<"\t\t\t\t\t\t\t\t"<<to_date<<endl;
        cout<<spnr<<"\t\t\t"<<train_name<<"/"<<train_no<<"\t\t\t"<<"Ecomony"<<endl;
        cout<<bhogi<<"\t\t\t\t"<<"*means not sure check there"<<"\t\t\t"<<time<<endl;
        cout<<"Passenger Details:-\n";
        ifstream spnrf("data/ticketinspector.txt");
        if(!spnrf.is_open())
        {
            cerr<<"Error"<<endl;
            return;
        }
        string line;
        while(getline(spnrf,line))
        {
            int p = line.find('|');
            string temp = line.substr(0,p);
            if(temp==spnr)
            {
                cout<<line<<endl;
            }
        }
    }
    void passenger:: view_profile()
    {
        string username,password;
        ifstream read("data/passengerdetails.txt");
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
        cout<<"age:-\t\t"<<this->age<<endl;
        cout<<"gender:-\t"<<this->gender<<endl;
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
    void passenger:: edit_profile()
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
            ifstream check("data/passengerdetails.txt");
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
            ifstream check("data/passengerdetails.txt");
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
        ifstream inFile("data/passengerdetails.txt");
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
       if (remove("data/passengerdetails.txt") != 0) {
       perror("Error deleting file");
       }
       if (rename("data/dummy.txt", "data/passengerdetails.txt") != 0) {
        perror("Error renaming file");
        }
        cout<<"Username changed succesfully...\n";            
       }
    else if(val==2)
    {
        cout<<"Enter Your current password\n";
        string pass;
        cin>>pass;
        ifstream file("data/passengerdetails.txt");
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
            p3 = oldline.find('|',p2+1);
            if(pass==oldline.substr(p2+1,p3-p2-1))
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
        string suff = oldline.substr(p3+1);
        string newline = prev + '|'+newpass +'|'+suff;
        ifstream inFile("data/passengerdetails.txt");
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
       if (remove("data/passengerdetails.txt") != 0) {
       perror("Error deleting file");
       }
       if (rename("data/dummy.txt", "data/passengerdetails.txt") != 0) {
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
    void passenger:: cancel_ticket()
    {
        while(1)
        {
            cout<<"1-->Cancel Ticket\n2-->Exit\n";
            int val;
            cin>>val;
            if(val==1)
            {
                cout<<"Enter pnr of the ticket:\n";
                string s;
                cin>>s;
                while(1)
                {
                if(checknum(s)==false)
                  {
                  cout<<"Please enter only numericals..try again\n";
                }
                else{
                break;
                 }
                }

               long long int n = funcstoi(s);
               while(countDigit(n)!=10)
               {
                 cout<<"Please Enter 10 digits..Try again\n";
                 cin>>n;
               }
                 bool found = 0;
                string spnr = s;
                ifstream details("data/ticket.txt");
            if(!details.is_open())
             {
              cerr<<"Error"<<endl;
              return;
              }
               string lini;
        while(getline(details,lini))
        {
            int p = lini.find('|');
            string temp = lini.substr(0,p);
            if(temp==spnr)
            {
                found = 1;
                break;
            }
        }
        if(!found)
        {
            cout<<"Either You entered wrong pnr or there is no info... please try again\n";
            return;
        }    
        details.close();            
        ifstream inFile("data/ticket.txt");
        ofstream outFile("data/dummy.txt");
        ifstream inFile1("data/ticketinspector.txt");
        ofstream outFile1("data/dummy2.txt");
        if (!inFile || !outFile ||!inFile1 ||!outFile1) {
        cerr << "Error opening files!" << endl;
        return ;
        }
        string currentLine;
        while (getline(inFile, currentLine)) {
        if (currentLine == lini) {
            continue;
        } else {
            outFile << currentLine << "\n"; 
        }
        }
        string currline;
        while(getline(inFile1,currline))
        {
            int p = currline.find('|');
            if(spnr == currline.substr(0,p)) continue;
            else outFile1<<currline<<"\n";
        }
        inFile.close();
        outFile.close();
        inFile1.close();
        outFile1.close();
       if (remove("data/ticket.txt") != 0) {
       perror("Error deleting file 0");
       }
       if (rename("data/dummy.txt", "data/ticket.txt") != 0) {
        perror("Error renaming file 0");
        }
        if(remove("data/ticketinspector.txt")!=0)
        {
            perror("Error deleting file 1");
        }
        if(rename("data/dummy2.txt","data/ticketinspector.txt")!=0)
        {
            perror("Error remaining file 1");
        }
        cout<<"Ticket cancelled succesfully...\n";           
        }
        else if(val==2) return;
        else cout<<"Enter either of 1/2\n";
        }
       
    }