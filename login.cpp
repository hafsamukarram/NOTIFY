#include <iostream>
#include <fstream>
#include <direct.h>
#include <dirent.h>
#include "login.h"
#include "signUp.h"
using namespace std;

login::login() {
    userName  = "";
    password  = "";
    dir       = NULL;
    loggedIn  = false;
}

login::login(string u, string p) {
    userName  = u;
    password  = p;
    dir       = NULL;
    loggedIn  = false;
}

void login::setU(string u)    { userName = u; }
void login::setpass(string p) { password = p; }
string login::getU()          { return userName; }
string login::getP()          { return password; }
bool login::isLoggedIn()      { return loggedIn; }

void login::loginCheck() {
    cout << "Enter Username: ";
    cin  >> userName;
    cout << "Enter Password: ";
    cin  >> password;

    ifstream fin("login.txt");
    string fileUser, filePass;
    bool found = false;

    while (fin >> fileUser >> filePass) {
        if (fileUser == userName && filePass == password) {
            found = true;
            break;
        }
    }
    fin.close();

    if (found) {
        loggedIn = true;
        signUp::setUser(userName);
        cout << "Login Successful!" << endl;
    } else {
        loggedIn = false;
        cout << "Invalid username or password." << endl;
    }
}

void login::openFolder() {
    string path = "users/" + userName;
    dir = opendir(path.c_str());
    if (dir) {
        cout << "Folder opened: " << path << endl;
        closedir(dir);
    }
}

void login::logout() {
    loggedIn = false;
    userName = "";
    password = "";
    cout << "Logged out." << endl;
}