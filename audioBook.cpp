#include"audioBook.h"
using namespace std;
string Audiobook::extract(){
    string notes;
    NoteList nl(signUp::getUser());

int id;
cout<<"Enter Notes id: ";
cin>>id;
Note* n=nl.find(id);
if(n!=NULL){
    notes=n->getBody();
}
    
return notes;}
string escapePowerShell(const string &text){
    string escaped;
    for(char c:text){
        if(c=='\''){
            escaped+="''";
            }
            else if(c=='\n'||c=='\r'){
                escaped +=' ';
            }
            else if(c=='"'){
                escaped+=' ';
            }
            else if(c=='`'){
                escaped+=' ';
            }
else if(c=='\0'){
    continue;
}
            else{
                escaped+=c;
            }
    }
    return escaped;
}
void Audiobook::speak(){
string text=extract();
string safeText=escapePowerShell(text);
string command="powershell -command \""
                "Add-Type -AssemblyName System.Speech;"
                "$synth= New-Object System.Speech.Synthesis.SpeechSynthesizer; "
                "$synth.Speak('"+ safeText +"')\"";
    system(command.c_str());
}
