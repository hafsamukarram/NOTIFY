#include "note.h"
#include <iostream>
#include <fstream>
#include <direct.h>

using namespace std;

// ---------------- Folder ----------------
void ensureFolder(string owner) {
    string path = "users/" + owner;
    _mkdir(path.c_str());
}

// ================= NOTE =================
Note::Note() {
    id = 0;
    shareCount = 0;
}
Note::Note(int i, string t, string b, string s, string o) {
    id = i;
    title = t;
    body = b;
    subject = s;
    owner = o;
    shareCount = 0;
}
int Note::getId(){return id;}
string Note::getTitle(){return title;}
string Note::getBody(){return body;}
string Note::getSubject(){return subject;}
string Note::getOwner(){return owner;}
void Note::setTitle(string t){title = t;}
void Note::setBody(string b){body = b;}

// ---------------- Sharing ----------------
void Note::shareTo(string user) {
    for (int i = 0; i < shareCount; i++)
        if (sharedWith[i] == user) return;

    if (shareCount < 10)
        sharedWith[shareCount++] = user;
}
bool Note::canSee(string user) {
    if (user == owner) return true;

    for (int i = 0; i < shareCount; i++)
        if (sharedWith[i] == user) return true;

    return false;
}
void Note::revokeFrom(string user) {
    for (int i = 0; i < shareCount; i++) {
        if (sharedWith[i] == user) {
            for (int j = i; j < shareCount - 1; j++)
                sharedWith[j] = sharedWith[j + 1];

            shareCount--;
            return;
        }
    }
}

// ---------------- Equality ----------------
bool Note::operator==(Note& other) {
    return id == other.id;
}

// ---------------- Show ----------------
void Note::show() {
    cout << "\n[" << id << "] " << title << endl;
    cout << "Subject: " << subject << endl;
    cout << "Owner  : " << owner << endl;
    cout << "Shared : ";
    if (shareCount == 0) cout << "None";
    else {
        for (int i = 0; i < shareCount; i++)
            cout << sharedWith[i] << " ";
    }
    cout << "\nContent:\n" << body << endl;
    cout << "----------------------\n";
}

// ---------------- File Save ----------------
string Note::toLine() {
    string line = to_string(id) + "|" + title + "|" + subject + "|" + owner + "|" + to_string(shareCount);
    for (int i = 0; i < shareCount; i++)
        line += "|" + sharedWith[i];
    string safeBody = body;
    for (int i = 0; i < (int)safeBody.size(); i++) {
        if (safeBody[i] == '\n') {
            safeBody.replace(i, 1, "\\n");
            i++;
        }
    }
    line += "|" + safeBody;
    return line;
}
void Note::fromLine(string line) {
    string parts[30];
    int pc = 0, tempIndex = 0;
    string temp = "";
    for (int i = 0; i <= (int)line.size(); i++) {
        if (i == (int)line.size() || line[i] == '|') {
            parts[pc++] = temp;
            temp = "";
        } else temp += line[i];
    }
    id = stoi(parts[0]);
    title = parts[1];
    subject = parts[2];
    owner = parts[3];
    shareCount = stoi(parts[4]);
    int base = 5;
    for (int i = 0; i < shareCount; i++)
        sharedWith[i] = parts[base + i];
    body = parts[base + shareCount];
    for (int i = 0; i < (int)body.size() - 1; i++) {
        if (body[i] == '\\' && body[i + 1] == 'n')
            body.replace(i, 2, "\n");
    }
}

// =========== NOTE LIST =================

NoteList::NoteList(string o) {
    owner = o;
    count = 0;
    nextId = 1;
    ensureFolder(owner);
    load();
}
NoteList::~NoteList() {
    for (int i = 0; i < count; i++)
        delete notes[i];
}

// -------- ADD ----------------
void NoteList::add() {
    if (count >= 100) {
        cout << "Storage full!\n";
        return;
    }

    string title, body, subject, line;
    cin.ignore();
    cout << "Enter title: ";
    getline(cin, title);
    cout << "Enter subject: ";
    getline(cin, subject);
    cout << "Enter body (END to finish):\n";
    while (getline(cin, line) && line != "END")
        body += line + "\n";
    notes[count++] = new Note(nextId++, title, body, subject, owner);
    save();
    cout << "Note added!\n";
}

// ---------------- REMOVE -------
void NoteList::remove() {
    int id;
    cout << "Enter note ID: ";
    cin >> id;
    for (int i = 0; i < count; i++) {
        if (notes[i]->getId() == id && notes[i]->getOwner() == owner) {
            delete notes[i];
            for (int j = i; j < count - 1; j++)
                notes[j] = notes[j + 1];
            count--;
            save();
            cout << "Deleted!\n";
            return;
        }
    }
    cout << "Not found!\n";
}

// -----------EDIT -------
void NoteList::edit() {
    int id;
    cout << "Enter ID: ";
    cin >> id;
    Note* n = find(id);
    if (!n || !n->canSee(owner)) {
        cout << "No access.\n";
        return;
    }
    cin.ignore();
    string t, b, line;
    cout << "New title: ";
    getline(cin, t);
    cout << "New body (END to finish):\n";
    while (getline(cin, line) && line != "END")
        b += line + "\n";
    if (!t.empty()) n->setTitle(t);
    if (!b.empty()) n->setBody(b);
    save();
    cout << "Updated!\n";
}

// ---------------- LIST --------
void NoteList::listAll() {
    for (int i = 0; i < count; i++) {
        if (notes[i]->canSee(owner))
            notes[i]->show();
    }
}

// ---------------- SEARCH ----------------
void NoteList::search() {
    string key;
    cin.ignore();
    cout << "Enter keyword: ";
    getline(cin, key);
    for (int i = 0; i < count; i++) {
        if (notes[i]->canSee(owner) &&
            notes[i]->getTitle().find(key) != string::npos) {
            notes[i]->show();
        }
    }
}

// ---------------- SHARE ----------------
void NoteList::shareNote() {
    int id;
    string user;
    cout << "Note ID: ";
    cin >> id;
    cout << "User: ";
    cin >> user;
    Note* n = find(id);
    if (!n || n->getOwner() != owner) {
        cout << "Cannot share.\n";
        return;
    }
    n->shareTo(user);
    save();
    cout << "Shared!\n";
}

// ---------REVOKE ----------------
void NoteList::revoke() {
    int id;
    string user;
    cout << "Note ID: ";
    cin >> id;
    cout << "User: ";
    cin >> user;
    Note* n = find(id);
    if (!n || n->getOwner() != owner) {
        cout << "Cannot revoke.\n";
        return;
    }
    n->revokeFrom(user);
    save();
    cout << "Revoked!\n";
}

// ---------------- FIND -------
Note* NoteList::find(int id) {
    for (int i = 0; i < count; i++)
        if (notes[i]->getId() == id)
            return notes[i];
    return NULL;
}

// ---------- SAVE -------------
void NoteList::save() {
    string path = "users/" + owner + "/notes.txt";
    ofstream f(path.c_str());
    for (int i = 0; i < count; i++)
        f << notes[i]->toLine() << "\n";
    f.close();
}

// ---------------- LOAD ---------
void NoteList::load() {
    string path = "users/" + owner + "/notes.txt";
    ifstream f(path.c_str());
    if (!f.is_open()) return;
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        Note* n = new Note();
        n->fromLine(line);
        notes[count++] = n;
        if (n->getId() >= nextId)
            nextId = n->getId() + 1;
    }
    f.close();
}
