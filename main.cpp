//Created By Daniyal Farooque
#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;
#define ll long long
ll int n=100003;

void cls()
{                       //CLEAR SCREEN FUNCTION
    system("cls");
}
class node
{                       // DOUBLY LINKED LIST NODE
    public:
    string name;
    string data;
    node*next=NULL;
    node*prev=NULL;
    node(string n,string dat)
    {
        name=n;
        data=dat;
    }
};
class LL
{                       // DOUBLY LINKED LIST CLASS
    public:
    node*head=NULL;
    node*tail=NULL;
    void insert_in_LL(string name,string data)
    {
        node*temp=new node(name,data);
        if(head==NULL)
        {
            head=temp;
            tail=temp;
            return ;
        }
        tail->next=temp;
        temp->prev=tail;
        tail=temp;
        return ;
    }
};

ll int getindex(string s)
{                           //Random Function Generator
 ll int index=1;
 ll int p=733;

    for(ll int i=0;i<s.size() && i<20;i++)
        {
            index+=(s[i]*p)%n;
            index=index%n;
            p=(p*p)%n;
        }
    if(index<0)
    {
     index+=n;
    }
    return index;
}
class umap
{                       //CUSTOM UNORDERED MAP uses OPEN ADDRESSING(CHAINING)
                        //template variable 1.for records is phno 2.for admins is pair<superuser_check,password>
    public:
        LL adjlist[100003];
        void insert(string name,string data)
        {
            int index=getindex(name);
            adjlist[index].insert_in_LL(name,data);
            return;
        }
        string search_word(string name)
        {
            int index=getindex(name);
            node *temp=adjlist[index].head;

            while(temp!=NULL)
            {
                if(temp->name==name)
                {
                    	return temp->data;
                }
                temp=temp->next;
            }
            if(temp==NULL)
            {
                return " ";
            }
        }
};

string get_password(){
	static char c;						//HIDDEN PASSWORD GETTER
	string password="";
	cout<<"PLEASE ENTER PASSWORD \n";
	c=getch();
	while(c!=13)
	{
	    password+=c;
	    putch('*');
	    c=getch();
	}
	cout<<endl;
	return password;
}

class administers{
    //Structure of admins
    public:
	    bool super_check;
	    string super_user,current_user;
	    //1.name 2.a.superuser b.password
	    umap adm;
	    administers(){
	        super_check=false;
	    }
	    bool check_superuser(){
	        if(super_check){
	            return true;
	        }
	        return false;
	    }
	    bool if_superuser(){
	        if(current_user==super_user){
	            return true;
	        }
	        return false;
	    }
	    void insert_admin(string name,string password){
	        if(!check_superuser()){
	            adm.insert(name,password);
	            super_user=name;
	            super_check=true;
	        }else
	            adm.insert(name,password);
	    }
	    bool admincheck()
	    {   start:
	        cls();
	        string nm;
	        static char c;
	        cout<<"PLEASE ENTER USERNAME \n";
	        cin.ignore();
	        getline(cin,nm);
	        string pass = adm.search_word(nm);
	        if(pass==" "){
	        	cout<<"INVALID USERNAME";
	        	getch();
	        	goto start;
	        }
	        string password=get_password();
	        if (pass==password){
	        	current_user=nm;
	            return true;
	        }
	        else
	        {
	            cout<<"WRONG PASSWORD\n";
	            cout<<"WANT TO CONTINUE AS USER(y/n)\n";
	            cin>>c;
	            if (c=='y')
	                return false;
	            else
	                return admincheck();
	        }
	    }
};

void loadfile( umap &tmp, administers &adm)
{	//DATABASE
    string tname,data;
    /*for(int i=1;i<20;i++)
    {
        cls();
        cout<<"\n\n\n\n\tLoading "<<"\t"<<"\t";
        for(int j=1;j<=i;j++)
        cout<<"²";
        cout<<"\n\n\t "<<2*i<<"%";
        cout<<"\n\n\tReading Database";
        Sleep(150 - i*4);
    }*/
    fstream file("Phonedirectory.txt",  ios::in);
    file.seekg(0,ios::beg);
    while(getline(file,tname))
    {
         getline(file,data);
         tmp.insert(tname,data);
    }
    file.close();

    fstream admfile("Administrators.txt",ios::in);
    admfile.seekg(0,ios::beg);
    while(getline(admfile,tname))
    {
         getline(admfile,data);
         //First entry in database will always be the SuperUser , insert automatcally does that
         adm.insert_admin(tname,data);
    }
    admfile.close();
    /*
     for(int i=20;i<=50;i++)
      { cls();
           cout<<"\n\n\n\n\tLoading "<<"\t"<<"\t";
        for(int j=1;j<=i;j++)
            cout<<"²";
            cout<<"\n\n\t "<<2*i<<"%";
        if(i>48)
            cout<<"\n\n\tComplete. Press Enter to Continue ";
        else
            cout<<"\n\n\tAccessing Main Memory";
      }*/
    getch();

}

int main()
{
    system("Color 7C");
    umap mp;                           // CONTAINS STRING
    administers admin;                         // CONTAINS ADMIN
    loadfile(mp,admin);  //LOADS DATA FILE
    cls();
    if(!admin.check_superuser()){
        cout<<"No Superuser present\nPlease create a Superuser\n";
        string name,password;
        cout<<"ENTER YOUR USER NAME\n";
        getline(cin,name);
        password=get_password();
        admin.insert_admin(name, password);
        fstream admfile("Administrators.txt",  ios::app | ios::out);
        admfile<<name<<"\n";
        admfile<<password<<"\n";
        admfile.close();
    }
    cls();
    bool status ;
    string choice, control="-1";
    cout<<"\t\t\t\tWELCOME";
    cout<<"\n\nCONTINUE AS \nADMIN OR \nUSER\n\nENTER\n";
    cin>>choice;
    if (choice == "admin")
    status = admin.admincheck();
    bool flags[2]={0};
    cls();
    if(status)
    {
        if(admin.if_superuser()){
            cout<<"WELCOME SUPER_ADMIN "<<admin.current_user<<"\n";
            flags[0]=1,flags[1]=1;
            cout<<"\nTYPE \"add_admin\" TO ADD AN ADMIN,\nTYPE \"add\" TO ADD A CALLER PROFILE(subscriber),\nTYPE \"show\" TO DISPLAY DATABASE,";
        }else{
            cout<<"WELCOME ADMIN "<<admin.current_user<<"\n";
            flags[1]=1;
            cout<<"\nTYPE \"add\" TO ADD A CALLER PROFILE(subscriber),\nTYPE \"show\" TO DISPLAY DATABASE,";
        }
    }
    else
        {
            cout<<"WELCOME  USER\n";
        }
    cout<<"\nTYPE \"search\" TO SEARCH FOR ANY SUBSCRIBER AND TYPE \"exit\" TO TERMINATE\n";
    cin>>control;
    //Deactivate feature flags added so that unauthorized personnel can't cheat
    while(control=="add" or control=="search" or control=="show" or control=="add_admin")
    {
        if(control=="add_admin" && flags[0]==1){
            string name,password;
            cout<<"ENTER YOUR USER NAME OR 0 TO TERMINATE\n";
            cin.ignore();
            getline(cin,name);
            if(name=="0")
            {
                    goto next;
            }
            password=get_password();

            fstream admfile("Administrators.txt",  ios::app | ios::out);
            admfile<<name<<"\n";
            admfile<<password<<"\n";
            admfile.close();

            admin.insert_admin(name, password);
	        cout<<"Admin Added to Database\n";
        }
        if(control=="add" && flags[1]==1)
        {
            string name,phno;
            cout<<"ENTER NAME OF THE SUBSCRIBER OR 0 TO TERMINATE\n";
            cin.ignore();
            getline(cin,name);
            if(name=="0")
            {
                    goto next;
            }
            cout<<"ENTER THE PHONE NUMBER OF SUBSCRIBER OR 0 TO TERMINATE INSERTION\n";
            getline(cin,phno);
            if(phno=="0")
            {
                    goto next;
            }
            fstream file1("Phonedirectory.txt",  ios::app | ios::out);
            file1<<name<<"\n";
            file1<<phno<<"\n";
            file1.close();
            mp.insert(name,phno);
            cout<<"INSERTION COMPLETE"<<endl;
            cout<<" AFTER INSERTION "<<name<<" "<<phno<<endl;
        }
        else if(control=="search")
        {
            cout<<"SEARCH PHONE NUMBER\nENTER NAME OF SUBSCRIBER"<<endl;
            string name;
            cin.ignore();
            getline(cin,name);
            string result=mp.search_word(name);
            if(result==""){
                cout<<"NO SUCH SUBSCRIBER EXISTS"<<endl;
            }else{
                cout<<result<<endl;
            }
        }
        else if(control=="show")
        {
            fstream file1("Phonedirectory.txt", ios::in);
            string name,phno;
                 file1.seekg(0,ios::beg);
                 while(getline(file1,name))
                {
                     getline(file1,phno);
                     cout<<name<<endl;
                     cout<<phno<<endl;
                }
                file1.close();
                getch();
        }

        next:
        getch();
        cls();
        if(status)
        {
        	cout<<"WELCOME "<<admin.current_user<<"\n";
            if(admin.if_superuser())
                cout<<"TYPE \"add_admin\" TO ADD AN ADMIN,\n";
            cout<<"TYPE \"add\" TO ADD A CALLER PROFILE(subscriber),\nTYPE \"show\" TO DISPLAY DATABASE,\n";
        }
        cout<<"\"search\" TO SEARCH FOR ANY SUBSCRIBER AND \"exit\" TO TERMINATE\n";


        cin>>control;
    }
    return 0;
}
