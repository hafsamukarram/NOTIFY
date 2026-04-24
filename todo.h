#ifndef TODO_H
#define TODO_H
#include <string>
#include "note.h"  
using namespace std;

class Todo : public Content {   
private:
    int id;
    string task;
    bool done;
    string priority;
public:
    Todo();
    Todo(int id, string task, string priority);
    int getId();
    string getTask();
    bool isDone();
    string getPriority();
    void setTask(string t);
    void toggle();
    void show()override;  
    string toLine();
    void fromLine(string line);
};

class TodoList {
private:
    Todo* items[100];
    int count;
    int nextId;
    string owner;

public:
    TodoList(string owner);
    ~TodoList();
    void add(string task, string priority);
    void remove(int id);
    void edit(int id, string newTask);
    void markDone(int id);
    void listAll();
    void listPending();
    void listDone();
    void save();
    void load();
};

#endif
