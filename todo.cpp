#include "todo.h"
#include <iostream>
#include <fstream>
#include <direct.h>   // _mkdir (Windows)
using namespace std;

// --------------- path helper (replaces missing File.h) ---------------
static string userFolder(const string& owner) {
    string path = "users/" + owner + "/";
    _mkdir(("users/" + owner).c_str());   // create if absent (safe to call repeatedly)
    return path;
}

// ========================== Todo ==========================

Todo::Todo() { id = 0; done = false; priority = "medium"; }

Todo::Todo(int i, string t, string p) {
    id = i; task = t; priority = p; done = false;
}

int    Todo::getId()           { return id; }
string Todo::getTask()         { return task; }
bool   Todo::isDone()          { return done; }
string Todo::getPriority()     { return priority; }
void   Todo::setTask(string t) { task = t; }

void Todo::toggle() { done = !done; }

void Todo::show() {
    string mark = done ? "[x]" : "[ ]";
    cout << mark << " [" << id << "] " << task << " (" << priority << ")\n";
}

string Todo::toLine() {
    return to_string(id) + "|" + task + "|" + (done ? "1" : "0") + "|" + priority;
}

void Todo::fromLine(string line) {
    string parts[4];
    int pc = 0;
    string tok;
    for (int i = 0; i <= (int)line.size(); i++) {
        if (i == (int)line.size() || line[i] == '|') {
            parts[pc++] = tok;
            tok = "";
        } else {
            tok += line[i];
        }
    }
    id = stoi(parts[0]);
    task = parts[1];
    done= (parts[2] == "1");
    priority = parts[3];
}

// ========================== TodoList ==========================

TodoList::TodoList(string o) {
    owner = o;
    count = 0;
    nextId = 1;
    load();
}

TodoList::~TodoList() {
    for (int i = 0; i < count; i++)
        delete items[i];
}

void TodoList::add(string task, string priority) {
    if (count >= 100) { cout << "Storage full!\n"; return; }
    items[count++] = new Todo(nextId++, task, priority);
    save();
    cout << "Task added!\n";
}

void TodoList::remove(int id) {
    for (int i = 0; i < count; i++) {
        if (items[i]->getId() == id) {
            delete items[i];
            for (int j = i; j < count - 1; j++)
                items[j] = items[j + 1];
            count--;
            save();
            cout << "Task deleted.\n";
            return;
        }
    }
    cout << "Task not found.\n";
}

void TodoList::edit(int id, string newTask) {
    for (int i = 0; i < count; i++) {
        if (items[i]->getId() == id) {
            items[i]->setTask(newTask);
            save();
            cout << "Task updated.\n";
            return;
        }
    }
    cout << "Task not found.\n";
}

void TodoList::markDone(int id) {
    for (int i = 0; i < count; i++) {
        if (items[i]->getId() == id) {
            items[i]->toggle();
            save();
            cout << "Status changed.\n";
            return;
        }
    }
    cout << "Task not found.\n";
}

void TodoList::listAll() {
    if (count == 0) { cout << "No tasks.\n"; return; }
    cout << "--- Todo List ---\n";
    for (int i = 0; i < count; i++)
        items[i]->show();
}

void TodoList::listPending() {
    cout << "--- Pending ---\n";
    bool found = false;
    for (int i = 0; i < count; i++)
        if (!items[i]->isDone()) { items[i]->show(); found = true; }
    if (!found) cout << "All done!\n";
}

void TodoList::listDone() {
    cout << "--- Completed ---\n";
    bool found = false;
    for (int i = 0; i < count; i++)
        if (items[i]->isDone()) { items[i]->show(); found = true; }
    if (!found) cout << "None completed.\n";
}

void TodoList::save() {
    ofstream f(userFolder(owner) + "todo.txt");
    for (int i = 0; i < count; i++)
        f << items[i]->toLine() << "\n";
    f.close();
}

void TodoList::load() {
    ifstream f(userFolder(owner) + "todo.txt");
    if (!f.is_open()) return;
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        Todo* t = new Todo();
        t->fromLine(line);
        items[count++] = t;
        if (t->getId() >= nextId)
            nextId = t->getId() + 1;
    }
    f.close();
}
