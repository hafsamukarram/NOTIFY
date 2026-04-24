#include<iostream>
#include<fstream>
#include<dirent.h>
#include<vector>
#include"signUp.h"
#include"friend.h"
using namespace std;

friendGroup::friendGroup(){
 string path = "users/" + signUp::getUser() + "/friendList.txt";
    ifstream fin(path);
    string name;
    while(fin >> name) {
        f.push_back(name);
    }
    fin.close();
}
void friendGroup::sendRequest(){
    vector<string>availPeople;
    //ofstream fout("login.txt");
ifstream fin("login.txt");
string fileUsername="";
int count =0;
 string temp;
    while(fin>>fileUsername){
//fin>>availPeople[count++];

 fin>>temp;
availPeople.push_back(fileUsername);
count++;
    }
    cout<<"Available People: ";
    for(int i=0;i<count;i++){
        int found=0;

        for(int j=0;j<f.size();j++)
        {
            if(availPeople[i]==f[j]){found=1; break;}
        }
if(!found &&availPeople[i]!=signUp::getUser()){
    cout<<availPeople[i]<<endl;
}
}
string name;
cout<<"Enter name of user to send friend request: ";
cin>>name;
for(int i=0;i<count;i++){
    if(name==availPeople[i]){
    
        ofstream send;
        string path="users/"+availPeople[i]+"/friendRequest.txt";
        send.open(path,ios::app);
        if(send.is_open())
{       send<<signUp::getUser()<<endl;
       send.close();
    cout<<"Request Sent"<<endl;
    }
       else{
        cout<<"Could not open path: "<<path<<endl;
        cout<<"Could not send request"<<endl;
       }
       break;
    
}
}}
void friendGroup::acceptRequest(){
    string friendRequest="";
    vector<string>fr;
    int count =0;
    string rePath="users/"+ signUp::getUser()+"/friendRequest.txt";
    ifstream accept(rePath);
    while(accept>>friendRequest)
{
fr.push_back(friendRequest);
count++;
}
accept.close();

for(int i=0;i<count;i++){
    cout<<fr[i]<<endl;
}
string nameU;
cout<<"Write username to accept friend request: ";
cin>>nameU;
int found=0;
for(int i=0;i<count;i++){
    if(nameU==fr[i]){
        found=1;
        f.push_back(fr[i]);
        string myListPath="users/"+ signUp::getUser()+"/friendList.txt";
        ofstream officialFriend(myListPath,ios::app);
        if(officialFriend.is_open())
 {       officialFriend<<fr[i]<<endl;
        officialFriend.close();
        string OtherListpath="users/"+  fr[i]+"/friendList.txt";
        ofstream addToOtherList(OtherListpath,ios::app);
        if(addToOtherList.is_open())
     {   addToOtherList<<signUp::getUser()<<endl;
        addToOtherList.close();

     cout<<"Now you Both are friends"<<endl;
    }
    else{
        cout<<"Error in accepting request"<<endl;
    }
       }
       else{
        cout<<"Error"<<endl;
       }
ofstream rewrite(rePath);
if(rewrite.is_open()){
    for(int j=0;j<count;j++){
        if(fr[j]!=nameU){
            rewrite<<fr[j]<<endl;
        }
    }
    rewrite.close();
}





       break; // if error check here

    }
 

}
if(!found){
    cout<<"No such UserName exists"<<endl;
}
}
void friendGroup::viewFriendList(){
    cout<<"=====MY FRIENDLIST======="<<endl;
    
    for(int i=0;i<f.size();i++){
        cout<<f[i]<<endl;
    }
}

void friendGroup::message(){
cout<<"-----------WELCONE TO  CHAT SECTION---------------"<<endl;
cout<<"=====Your Friends are====="<<endl;
viewFriendList();
if(f.size()==0){
    cout<<"You have no friends yet!"<<endl;
    return;
}
cout<<"------------------------------"<<endl;
string n;
cout<<"Write name of user to start conversation: ";
cin>>n;
// for(int i=0;i<f.size();i++){
//     if(f[i]==n){
//         ofstream typeM("friendMessage.txt",ios::ate);
//         cout<<"Message from: "<<signUp::getUser()<<endl;
//         string n;
//         typeM<<n;
//         typeM.close();
//     }
// }
    int isFriend = 0;
    for(int i = 0; i < f.size(); i++) {
        if(f[i] == n) { isFriend = 1; break; }
    }
    if(!isFriend) {
        cout << "This user is not your friend!" << endl;
        return;
    }
string myMsgPath="users/"+signUp::getUser()+"/messages.txt";
cout<<"=========Previous Messages=========="<<endl;
ifstream readOld(myMsgPath);
string line;
while(getline(readOld,line)){
    if((line.find(n)!=string::npos)){
cout<<line<<endl;
    }
}
readOld.close();
cout<<"============================"<<endl;
cout<<"\n========== Send Message========"<<endl;
string msg;
cout<<"Enter message(or 'exit' to quit): ";
cin.ignore();
getline(cin,msg);
if(msg=="exit"){return;}
string formatted=signUp::getUser()+"->"+n+": "+msg;

    ofstream senderFile("users/"+signUp::getUser()+"/messages.txt", ios::app);
    if(senderFile.is_open()){
        senderFile<<formatted<<endl;
        senderFile.close();
    } else {
        cout<<"Failed to save to your message file"<<endl;
    }

    // Write to receiver's file
    ofstream receiverFile("users/"+n+"/messages.txt", ios::app);
    if(receiverFile.is_open()){
        receiverFile<<formatted<<endl;
        receiverFile.close();
        cout<<"Message sent!"<<endl;
    } else {
        cout<<"Failed to save to receiver's message file"<<endl;
    }
}






