#ifndef SIGNUP_H
#define SIGNUP_H
#include<string>
#include<fstream>
#include<direct.h>
#include<dirent.h>
using namespace std;

class signUp{
string static userName;
string password;
public:
signUp();
signUp(string,string );
static void setUser(string);
void setpassWord(string);
static string getUser();
string getPass();
void checkU();
void createFolder();
};
#endif