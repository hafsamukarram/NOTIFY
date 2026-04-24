#include<iostream>
#include<fstream>
#include<unistd.h>
#include"friend.h"
#include"login.h"
#include"signUp.h"
#include"todo.h"
#include"note.h"
#include"audioBook.h"
using namespace std;
int main(){
    signUp SIGNUP;
    login LOGIN;
    string n;
    int choose;
    cout<<"Enter 1 to login and 0 to signup: ";
    cin>>choose;
   switch(choose){
case 0:
SIGNUP.checkU();
case 1:
LOGIN.loginCheck();
if(LOGIN.isLoggedIn())
{cout<<"\nLoading ";
for(int i=0;i<6;i++){
    cout<<".";
    sleep(1);
}
cout<<endl;

                                    ////AFTER LOGIN
cout<<"========WELCOME TO NOTIFY: "<<signUp::getUser()<<"========="<<endl;
int options;
do
{
cout<<"CHOOSE:\n 1: Making Notes\n 2: AudioBook\n 3: TODO-LIST\n 4: Social Networks\n 5:End"<<endl;
cin>>options;
switch(options){
    case 1:
    {Note NOTES;
NoteList NOTELIST(signUp::getUser());
 int noteOpt;
        do{
            cout<<"\n--- NOTES MENU ---\n";
            cout<<"1. Add Note\n";
            cout<<"2. View All Notes\n";
            cout<<"3. Edit Note\n";
            cout<<"4. Delete Note\n";
            cout<<"5. Search Notes\n";
            cout<<"6. Share Note\n";
            cout<<"7. Revoke Share\n";
            cout<<"0. Back\n";
            cout<<"Choice: ";
            cin>>noteOpt;
            switch(noteOpt){
                case 1: NOTELIST.add(); break;
                case 2: NOTELIST.listAll(); break;
                case 3: NOTELIST.edit(); break;
                case 4: NOTELIST.remove(); break;
                case 5: NOTELIST.search(); break;
                case 6: NOTELIST.shareNote(); break;
                case 7: NOTELIST.revoke(); break;
                case 0: break;
                default: cout<<"Invalid option.\n";
            }
        }while(noteOpt!=0);
    break;}
    case 2:
   { 
    Audiobook book;
    int opt;
    do
{
cout<<"Enter 1: for notes audio and 0 for exit";
cin>>opt;
switch(opt){
    case 1:
 book.speak();
 break;
 case 0:
    break;
 
}}
while(opt!=0);
   

    break;}
    case 3: 
    {Todo TODO;
    TodoList TODOLIST(signUp::getUser());
    int todoOpt;
        do{
            cout<<"\n--- TODO MENU ---\n";
            cout<<"1. Add Task\n";
            cout<<"2. View All Tasks\n";
            cout<<"3. View Pending\n";
            cout<<"4. View Completed\n";
            cout<<"5. Mark Task Done/Undone\n";
            cout<<"6. Edit Task\n";
            cout<<"7. Delete Task\n";
            cout<<"0. Back\n";
            cout<<"Choice: ";
            cin>>todoOpt;
            switch(todoOpt){
                case 1:{
                    string task, priority;
                    cin.ignore();
                    cout<<"Task: ";
                    getline(cin,task);
                    cout<<"Priority (low/medium/high): ";
                    getline(cin,priority);
                    TODOLIST.add(task,priority);
                    break;
                }
                case 2: TODOLIST.listAll(); break;
                case 3: TODOLIST.listPending(); break;
                case 4: TODOLIST.listDone(); break;
                case 5:{
                    int id;
                    cout<<"Task ID: ";
                    cin>>id;
                    TODOLIST.markDone(id);
                    break;
                }
                case 6:{
                    int id; string newTask;
                    cout<<"Task ID: ";
                    cin>>id;
                    cin.ignore();
                    cout<<"New task: ";
                    getline(cin,newTask);
                    TODOLIST.edit(id,newTask);
                    break;
                }
                case 7:{
                    int id;
                    cout<<"Task ID: ";
                    cin>>id;
                    TODOLIST.remove(id);
                    break;
                }
                case 0: break;
                default: cout<<"Invalid option.\n";
            }
        }while(todoOpt!=0);
    break;}
    case 4:
    {
        friendGroup FRIENDS;
        int friendOpt;
        do{
            cout<<"\n--- SOCIAL MENU ---\n";
            cout<<"1. Send Friend Request\n";
            cout<<"2. Accept Friend Request\n";
            cout<<"3. View Friend List\n";
            cout<<"4. Message a Friend\n";
            cout<<"0. Back\n";
            cout<<"Choice: ";
            cin>>friendOpt;
            switch(friendOpt){
                case 1: FRIENDS.sendRequest();break;
                case 2: FRIENDS.acceptRequest(); break;
                case 3: FRIENDS.viewFriendList(); break;
                case 4: FRIENDS.message(); break;
                case 0: break;
                default: cout<<"Invalid option.\n";
            }
        }while(friendOpt!=0);
        break;}
        case 5:{
            break;
        }
    
}
}
while(options!=5);
}
else{
    return 1;
}
}



}
}