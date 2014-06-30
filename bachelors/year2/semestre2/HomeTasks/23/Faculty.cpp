#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>
#include <memory.h>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <queue>
#include <stack>
#include <complex>
#include <limits.h>
#include <cassert>
#include <chrono>
#include <regex>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <valarray>

using namespace std;
using namespace std::chrono;

typedef long long ll;

const int N = 16005;
const int K = 605;
const ll InfL = 1000000000000000000LL;
const int MOD = 1000000007;

class Mark {
public:
    virtual string getValue() const = 0;
    virtual string getStudentName() const = 0;
    virtual string getSubjName() const = 0;
};

class StandMark : public Mark {
protected:
    static const string _marks;
    static const vector<double> _100mins;
    string _mark;
    class Person *_teacher, *_student;
    class Course *_course;
public:
    StandMark(double _100Grade, Course *c, Person *st, Person *t) {
        _100Grade = max(0., min(100., _100Grade));
        for (int i = 0; i < _100mins.size(); ++i) {
            if (_100Grade >= _100mins[i]) {
                _mark = _marks[i];
                break;
            }
        }
        _course = c;
        _student = st;
        _teacher = t;
    }
    virtual string getValue() const override {
        return _mark;
    }
    virtual string getStudentName() const override;
    virtual string getSubjName() const override;
};

const string StandMark::_marks = "ABCDEF";
const vector<double> StandMark::_100mins = { 90., 75., 60., 40., 20., 0. };

class Course {
    friend class Teacher;
protected:
    string _name;
    bool _finished;
    vector<Person*> teachers;
    vector<Person*> students;
    Course(string name) : _name(name) {}
    void addTeacher(Person *tc) {
        teachers.push_back(tc);
    }
public:
    string getName() const {
        return _name;
    }
    void addStudent(Person *st) {
        students.push_back(st);
    }
    bool findStudent(Person *st) {
        return find(students.begin(), students.end(), st) != students.end();
    }
    bool findTeacher(Person *st) {
        return find(teachers.begin(), teachers.end(), st) != teachers.end();
    }
};

class Archive {
protected:
    vector<Mark*> _marks;
public:
    virtual void addMark(Mark *nm) {
        _marks.push_back(nm);
    }
    void show() {
        cout << "Mark\t Student's Name\t Course's Name\t\n";
        for (auto i : _marks)
            cout << i->getValue() << "\t " << i->getStudentName() << "\t " << i->getSubjName() << "\t" << endl;
    }
};

class Person {
protected:
    string _name;
public:
    Person(string name) : _name(name) {}
    virtual string getName() {
        return _name;
    }
};

class Student : public Person {
public:
    Student(string name) : Person(name) {}
    void subscribe(Course& course) {
        course.addStudent(this);
    }
};

class Teacher : public Person {
    virtual Mark* putMark(Course &course, Student &st, Archive &arch) {
        if (!course.findStudent(&st) || !course.findTeacher(this))
            return nullptr;
        Mark *res = new StandMark(rand() % 100 * 1., &course, &st, this);
        arch.addMark(res);
        return res;
    }
public:
    Teacher(string name) : Person(name) {}
    Course startCourse(string name) {
        Course res = Course(name);
        res.addTeacher(this);
        return res;
    }
    vector<Mark*> endCourse(Course &c, Archive &arc) {
        vector<Mark*> res;
        if (!c.findTeacher(this))
            return res;
        for (auto i : c.students)
            res.push_back(putMark(c, *((Student*)i), arc));
        return res;
    }
};

string StandMark::getStudentName() const {
    return _student->getName();
}

string StandMark::getSubjName() const {
    return _course->getName();
}

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Teacher tc("teacher");
    Course c = tc.startCourse("C1");
    Student st("student");
    st.subscribe(c);
    Archive ar;
    tc.endCourse(c, ar);
    ar.show();
    system("pause");
    return 0;
}