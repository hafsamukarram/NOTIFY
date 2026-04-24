#ifndef LOGIN_H
#define LOGIN_H
#include<string>
#include<fstream>
#include<direct.h>
#include<dirent.h>
using namespace std;

class login{
string userName;
string password;
DIR *dir;
bool loggedIn;
public:
login();
login(string,string );
void setU(string);
void setpass(string);
string getU();
string getP();
void loginCheck();
void openFolder();
void logout();
bool isLoggedIn();
};
#endif

