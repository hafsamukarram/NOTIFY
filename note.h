#ifndef NOTE_H
#define NOTE_H
#include <string>
using namespace std;

class Content {
public:
    virtual void show() = 0;
    virtual ~Content() {}
};

class Note : public Content {
private:
    int id;
    string title;
    string body;
    string subject;
    string owner;
    string sharedWith[10];
    int shareCount;
public:
    Note();
    Note(int id, string title, string body, string subject, string owner);
    int getId();
    string getTitle();
    string getBody();
    string getSubject();
    string getOwner();
    void setTitle(string t);
    void setBody(string b);
    void shareTo(string user);
    bool canSee(string user);
    void revokeFrom(string user);
    void show() override;
    bool operator==(Note& other);
    string toLine();
    void fromLine(string line);
};

class NoteList {
private:
    Note* notes[100];
    int count;
    int nextId;
    string owner;
public:
    NoteList(string owner);
    ~NoteList();
    void add();        
    void remove();     
    void edit();       
    void listAll();
    void search();
    void shareNote();  
    void revoke();    
    Note* find(int id);
    void save();
    void load();
};

#endif
