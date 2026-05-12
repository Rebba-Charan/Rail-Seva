#include<bits/stdc++.h>
#include "include/passenger.h"
#include "include/railadmin.h"
#include "include/stationmaster.h"
#include "include/train.h"

using namespace std;
int main()
{
    cout<<"Running";
    srand(time(0));
    int choice;
    while(1)
    {
    cout<<"<----Please select your Role---->\n1)Passenger\n2)RailAdmin\n3)StationMaster\n4)exit"<<endl;
    cin>>choice;
    if(choice==1){
    passenger P("Rebba Charan",7989262757,20,'M');
    //login first
    if(P.checklogin()==0)
    {
        cout<<"You have No account Please create one\n";
        P.signup();
    }
    while(!P.login())//Right now iam just thinking the user will enter the exact username and password in future i will keep forget passowrd or forgot username
    {
        P.signup();
    }
    //menu
    cout<<"Menu:"<<endl;
    int choice;
    while(1)
    {
        cout<<"1-->Search Trains\n2-->Book Tickets\n3-->View Profile\n4-->logout\n";
        cin>>choice;
        if(choice==1)//search Train
        {
            train t;
            string from;
            string to;
            string date;
            string classes;
            cout<<"Enter from: \n";
            cin.ignore();
            getline(cin,from);
            cout<<"Enter to: \n";
            
            getline(cin,to);
            cout<<"Enter Date(it should be in this order dd/mm/yyyy): \n";
            
            getline(cin,date);
            cout<<"Enter the class you want if you have no specialization write any (3AC/2AC/1AC/Sleeper/General): \n";
            getline(cin,classes);
            t.showtrains(from,to,date,classes);
        }
        else if(choice==2)//Booking viewing and canceling ticket
        {
            int choice;
            while(1)
            {
            cout<<"1-->Book Ticket\n2-->View Ticket\n3-->Cancel Ticket\n4-->Exit\n";
            cin>>choice;
            if(choice==1)
            {
                P.book_ticket();
            }
            else if(choice==2)
            {
                P.view_ticket();
            }
            else if(choice==3)
            {
                P.cancel_ticket();
            }
            else if(choice==4) break;
            else{
                cout<<"Choice InValid...choose from 1/2/3\n";
            }
            }
        }
        else if(choice ==3)//view and edit profile
        {
            while(1)
            {
            cout<<"1-->View Profile\n2-->Edit Profile\n3-->Exit\n";
            int val;
            cin>>val;
            if(val==1)
            {
                P.view_profile();
            }else if(val==2)
            {
                P.edit_profile();

            }else if(val==3)
            {
                break;
            }
            else{
                cout<<"Invalid choice..please enter (1/2/3)...\n";
            }
            }
        }
        else if(choice ==4)//exit
        {
            break;
        }
        else
        {
            cout<<"Choice InValid...choose from 1/2/3/4\n";
        }
    }
    }
    else if(choice==2)
    {
    railadmin R("Rebba Charan",7989262757);
    //login first
    if(R.checklogin()==0)
    {
        cout<<"You have No account Please create one\n";
        R.signup();
    }
    while(!R.login())//Right now iam just thinking the user will enter the exact username and password in future i will keep forget passowrd or forgot username
    {
        R.signup();
    }
    //menu
    cout<<"Menu:"<<endl;
    while(1){
    cout<<"1-->Add Trains\n2-->Cancel Train\n3-->View Profile\n4-->Exit\n";
    int val;
    cin>>val;
    if(val==1)
    {
        R.Addtrain();
    }
    else if(val==2)
    {
        R.Canceltrain();
    }
    else if(val==3)
    {
        R.profile();
    }
    else if(val==4) break;
    else cout<<"invalid entry ....try again\n";
    }
    }else if(choice==3)//
    {
        stationmaster S("Charan Rebba",7989262757);
        if(S.checklogin()==0)
    {
        cout<<"You have No account Please create one\n";
        S.signup();
    }
    while(!S.login())//Right now iam just thinking the user will enter the exact username and password in future i will keep forget passowrd or forgot username
    {
        S.signup();
    }
        cout<<"Menu:\n";
        while(1)
        {
            //i want to add a help centre function which will act as a centre in railway station which 
            //will inform if i tell train no/train name it will tell the arraival time and from one 
            //location how many trains are there 
        
        cout<<"1-->Update Timing\n2-->Announce Timing\n3-->Profile\n4-->Exit\n";
        int val;
        cin>>val;
        if(val==1)
        {
            S.update();
        }
        else if(val==2)
        {
            S.announce();
        }
        else if(val==3)
        {
            S.profile();
        }
        else if(val==4) break;
        else cout<<"Invalid choice...Try again\n";
    }
    }
    // else if(choice==4)
    // {
    //     cout<<"you are a TicketInspector\n";
    //     break;
    // }
    else if(choice==4)
    {
    cout<<"Exit\n";
    break;
    }
    else
    {
        cout<<"InValid Choice Enter either among these 1/2/3/4/5\n";
    } 
}  
cout<<"Thankyou For visiting our website...Wish You a Wonderful day\n"; 
system("pause");
}
