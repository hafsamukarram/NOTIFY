#include<iostream>
#include<fstream>
#include<direct.h>
#include<dirent.h>
#include"signUp.h"
using namespace std;
string signUp::userName = "";

signUp::signUp():password(""){}
signUp::signUp(string u,string p):password(p){}
void signUp::setUser(string n){
userName=n;
}
void signUp::setpassWord(string n){
password=n;
}
string signUp::  getUser(){
    return userName;
}
string signUp::getPass(){
    return password;
}
void signUp::createFolder(){
    string path="users/"+userName;
    mkdir(path.c_str());
    // string filePath = "users/"+userName + "/.gitkeep";
    // ofstream f(filePath);
    // f.close();
    string pathfr="users/"+userName+"/friendRequest.txt";
    ofstream friendRequest(pathfr);
    string pathfl="users/"+userName+"/friendList.txt";
    ofstream friendlist(pathfl);
    string pathfm="users/"+userName+"/friendMessage.txt";
    ofstream messages(pathfm);
}
void signUp::checkU(){
    string fileUsename="";
    string filePassword="";
    cout<<"Enter Username: ";
    cin>>userName;
    cout<<"Enter password: ";
    cin>>password;
    int found=0;
    ofstream fout;
    ifstream fin;
    fin.open("login.txt");
    while(fin>>fileUsename>>filePassword){
        if(fileUsename==userName){
found=1;
break;
        }
   
    }
    fin.close();
    if(found){
cout<<"Username already exists"<<endl;
    }
    else{
        fout.open("login.txt",ios::app);
        fout<<userName<<" "<<password<<endl;
        fout.close();
        createFolder();
        cout<<"====Account Created Successfully====="<<endl;
    }


}


