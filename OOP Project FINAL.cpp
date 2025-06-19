#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// ---------- Abstract Base Class ----------
class User {
protected:
    string name, email, password;
public:
    User(string n, string e, string p) : name(n), email(e), password(p) {}
    string getEmail() const { return email; }
    string getPassword() const { return password; }
    string getName() const { return name; }
    virtual void displayDashboard() = 0;
    virtual void viewMarks() const = 0;
    virtual ~User() {}
};

// ---------- Course Content Classes ----------
class Assignment {
    string title, content;
public:
    Assignment(string t, string c) : title(t), content(c) {}
    void display() const {
        cout << "Assignment: " << title << "\nContent: " << content << endl;
    }
    string getTitle() const { return title; }
};

class Quiz {
    string topic, content;
public:
    Quiz(string t, string c) : topic(t), content(c) {}
    void display() const {
        cout << "Quiz: " << topic << "\nContent: " << content << endl;
    }
    string getTopic() const { return topic; }
};

class Material {
    string label, content;
public:
    Material(string l, string c) : label(l), content(c) {}
    void display() const {
        cout << "Material: " << label << "\nContent: " << content << endl;
    }
};

// ---------- Course Class ----------
class Course {
    string courseTitle;
    vector<Material> materials;
    vector<Assignment> assignments;
    vector<Quiz> quizzes;
public:
    Course(string title) : courseTitle(title) {}

    void addMaterial(string label, string content) {
        materials.emplace_back(label, content);
    }
    void addAssignment(string title, string content) {
        assignments.emplace_back(title, content);
    }
    void addQuiz(string topic, string content) {
        quizzes.emplace_back(topic, content);
    }

    void displayContent() const {
        cout << "\nCourse: " << courseTitle << "\n--- Materials ---\n";
        for (const auto& m : materials) m.display();
        cout << "--- Assignments ---\n";
        for (const auto& a : assignments) a.display();
        cout << "--- Quizzes ---\n";
        for (const auto& q : quizzes) q.display();
    }

    string getTitle() const { return courseTitle; }

    const vector<Material>& getMaterials() const { return materials; }
    const vector<Assignment>& getAssignments() const { return assignments; }
    const vector<Quiz>& getQuizzes() const { return quizzes; }
};

// ---------- Student Class ----------
class Student : public User {
    vector<Course*> enrolledCourses;
    map<string, string> quizAnswers;
    map<string, string> assignmentAnswers;
    map<string, int> quizMarks;
    map<string, int> assignmentMarks;
public:
    Student(string n, string e, string p) : User(n, e, p) {}

    void enroll(Course* c) {
        enrolledCourses.push_back(c);
        cout << "Enrolled in: " << c->getTitle() << endl;
    }

    void displayDashboard() override {
        cout << "\n[Student Dashboard] " << name << "\n";
        if (enrolledCourses.empty()) cout << "No enrolled courses.\n";
        else for (auto c : enrolledCourses) c->displayContent();
    }

    void viewMarks() const override {
        cout << name << "'s Marks:\n";
        for (const auto& course : enrolledCourses) {
            cout << "\nCourse: " << course->getTitle() << endl;
            cout << "--- Quiz Marks ---\n";
            bool quizHasMarks = false;
            for (const auto& q : course->getQuizzes()) {
                auto it = quizMarks.find(q.getTopic());
                if (it != quizMarks.end()) {
                    cout << q.getTopic() << ": " << it->second << endl;
                    quizHasMarks = true;
                }
            }
            if (!quizHasMarks) cout << "No quiz marks available.\n";

            cout << "--- Assignment Marks ---\n";
            bool assignmentHasMarks = false;
            for (const auto& a : course->getAssignments()) {
                auto it = assignmentMarks.find(a.getTitle());
                if (it != assignmentMarks.end()) {
                    cout << a.getTitle() << ": " << it->second << endl;
                    assignmentHasMarks = true;
                }
            }
            if (!assignmentHasMarks) cout << "No assignment marks available.\n";
        }
    }

    void viewMarksByCourse() const {
        if (enrolledCourses.empty()) {
            cout << "You are not enrolled in any courses.\n";
            return;
        }
        cout << name << "'s Marks by Course:\n";
        for (const auto& course : enrolledCourses) {
            cout << "\nCourse: " << course->getTitle() << endl;
            cout << "1. View Marks of Assignments\n2. View Marks of Quizzes\nEnter choice: ";
            int choice; cin >> choice; cin.ignore();
            if (choice == 1) {
                bool hasMarks = false;
                for (const auto& a : course->getAssignments()) {
                    auto it = assignmentMarks.find(a.getTitle());
                    if (it != assignmentMarks.end()) {
                        cout << a.getTitle() << ": " << it->second << endl;
                        hasMarks = true;
                    }
                }
                if (!hasMarks) cout << "No assignment marks available.\n";
            } else if (choice == 2) {
                bool hasMarks = false;
                for (const auto& q : course->getQuizzes()) {
                    auto it = quizMarks.find(q.getTopic());
                    if (it != quizMarks.end()) {
                        cout << q.getTopic() << ": " << it->second << endl;
                        hasMarks = true;
                    }
                }
                if (!hasMarks) cout << "No quiz marks available.\n";
            } else {
                cout << "Invalid choice.\n";
            }
        }
    }

    void viewMaterials() const {
        for (auto c : enrolledCourses) {
            cout << "\nCourse: " << c->getTitle() << " - Materials:\n";
            for (const auto& m : c->getMaterials()) m.display();
        }
    }

    void viewAssignments() const {
        for (auto c : enrolledCourses) {
            cout << "\nCourse: " << c->getTitle() << " - Assignments:\n";
            for (const auto& a : c->getAssignments()) a.display();
        }
    }

    void viewQuizzes() const {
        for (auto c : enrolledCourses) {
            cout << "\nCourse: " << c->getTitle() << " - Quizzes:\n";
            for (const auto& q : c->getQuizzes()) q.display();
        }
    }

    void answerQuiz() {
        for (auto c : enrolledCourses) {
            const auto& quizzes = c->getQuizzes();
            for (const auto& q : quizzes) {
                string answer;
                cout << "\nQuiz: " << q.getTopic() << "\nContent: " << endl;
                q.display();
                cout << "Enter your answer: ";
                getline(cin, answer);
                quizAnswers[q.getTopic()] = answer;
            }
        }
    }

    void answerAssignments() {
        for (auto c : enrolledCourses) {
            const auto& assigns = c->getAssignments();
            for (const auto& a : assigns) {
                string ans;
                cout << "\nAssignment: " << a.getTitle() << "\nContent: " << endl;
                a.display();
                cout << "Enter your answer: ";
                getline(cin, ans);
                assignmentAnswers[a.getTitle()] = ans;
            }
        }
    }

    const vector<Course*>& getEnrolledCourses() const { return enrolledCourses; }

    friend class Instructor;
};

// ---------- Instructor Class ----------
class Instructor : public User {
public:
    Instructor(string n, string e, string p) : User(n, e, p) {}

    void displayDashboard() override {
        cout << "\n[Instructor Dashboard] " << name << endl;
    }

    void viewMarks() const override {}

    void addMaterial(Course& c) {
        string label, content;
        cout << "Enter material label: "; cin.ignore(); getline(cin, label);
        cout << "Enter material content: "; getline(cin, content);
        c.addMaterial(label, content);
        cout << "Material added.\n";
    }

    void addAssignment(Course& c) {
        string title, content;
        cout << "Enter assignment title: "; cin.ignore(); getline(cin, title);
        cout << "Enter assignment content: "; getline(cin, content);
        c.addAssignment(title, content);
        cout << "Assignment added.\n";
    }

    void addQuiz(Course& c) {
        string topic, content;
        cout << "Enter quiz topic: "; cin.ignore(); getline(cin, topic);
        cout << "Enter quiz content: "; getline(cin, content);
        c.addQuiz(topic, content);
        cout << "Quiz added.\n";
    }

    void viewStudentPerformance(Student* student) {
        cout << "\nPerformance of: " << student->getName() << endl;
        student->viewMarks();
        student->viewAssignments();
        student->viewQuizzes();
    }

    void assignMarks(Student* student) {
        const auto& enrolled = student->getEnrolledCourses();
        if (enrolled.empty()) {
            cout << "Student not enrolled in any course.\n";
            return;
        }
        cout << "Select course to assign marks:\n";
        for (size_t i = 0; i < enrolled.size(); ++i)
            cout << i + 1 << ". " << enrolled[i]->getTitle() << endl;
        int csel; cin >> csel; cin.ignore();
        if (csel < 1 || csel > (int)enrolled.size()) return;
        Course* selected = enrolled[csel - 1];
        int opt;
        cout << "1. Assign Quiz Marks\n2. Assign Assignment Marks\nEnter: ";
        cin >> opt; cin.ignore();
        if (opt == 1) {
            const auto& quizzes = selected->getQuizzes();
            if (quizzes.empty()) {
                cout << "No quizzes available in this course.\n";
                return;
            }
            cout << "Select quiz to assign marks:\n";
            for (size_t i = 0; i < quizzes.size(); ++i)
                cout << i + 1 << ". " << quizzes[i].getTopic() << endl;
            int q; cout << "Select quiz: "; cin >> q; cin.ignore();
            if (q >= 1 && q <= (int)quizzes.size()) {
                cout << "Student's answer for quiz \"" << quizzes[q - 1].getTopic() << "\":\n";
                if (student->quizAnswers.find(quizzes[q - 1].getTopic()) != student->quizAnswers.end()) {
                    cout << student->quizAnswers.at(quizzes[q - 1].getTopic()) << endl;
                } else {
                    cout << "No answer submitted by student.\n";
                }
                int m; cout << "Enter marks: "; cin >> m; cin.ignore();
                student->quizMarks[quizzes[q - 1].getTopic()] = m;
                cout << "Marks assigned.\n";
            } else {
                cout << "Invalid selection.\n";
            }
        } else if (opt == 2) {
            const auto& assigns = selected->getAssignments();
            if (assigns.empty()) {
                cout << "No assignments available in this course.\n";
                return;
            }
            cout << "Select assignment to assign marks:\n";
            for (size_t i = 0; i < assigns.size(); ++i)
                cout << i + 1 << ". " << assigns[i].getTitle() << endl;
            int a; cout << "Select assignment: "; cin >> a; cin.ignore();
            if (a >= 1 && a <= (int)assigns.size()) {
                cout << "Student's answer for assignment \"" << assigns[a - 1].getTitle() << "\":\n";
                if (student->assignmentAnswers.find(assigns[a - 1].getTitle()) != student->assignmentAnswers.end()) {
                    cout << student->assignmentAnswers.at(assigns[a - 1].getTitle()) << endl;
                } else {
                    cout << "No answer submitted by student.\n";
                }
                int m; cout << "Enter marks: "; cin >> m; cin.ignore();
                student->assignmentMarks[assigns[a - 1].getTitle()] = m;
                cout << "Marks assigned.\n";
            } else {
                cout << "Invalid selection.\n";
            }
        } else {
            cout << "Invalid option.\n";
        }
    }
};

vector<Student*> students;
vector<Instructor*> instructors;
vector<Course*> courses;

Student* loginStudent(string email, string pass) {
    for (auto s : students)
        if (s->getEmail() == email && s->getPassword() == pass) return s;
    return nullptr;
}
Instructor* loginInstructor(string email, string pass) {
    for (auto i : instructors)
        if (i->getEmail() == email && i->getPassword() == pass) return i;
    return nullptr;
}

void instructorPanel(Instructor* i) {
    int ch;
    while (true) {
        cout << "\n1. View Dashboard\n2. Create Course\n3. Add Material\n4. Add Assignment\n5. Add Quiz\n6. View Student Performance\n7. Assign Marks\n8. Logout\nEnter: ";
        cin >> ch; cin.ignore();
        if (ch == 1) i->displayDashboard();
        else if (ch == 2) {
            string title;
            cout << "Enter course title: "; getline(cin, title);
            courses.push_back(new Course(title));
            cout << "Course created.\n";
        } else if (ch >= 3 && ch <= 5) {
            if (courses.empty()) { cout << "No courses available.\n"; continue; }
            for (size_t j = 0; j < courses.size(); j++)
                cout << j + 1 << ". " << courses[j]->getTitle() << endl;
            int sel; cout << "Select course: "; cin >> sel; cin.ignore();
            if (sel >= 1 && sel <= (int)courses.size()) {
                if (ch == 3) i->addMaterial(*courses[sel - 1]);
                else if (ch == 4) i->addAssignment(*courses[sel - 1]);
                else if (ch == 5) i->addQuiz(*courses[sel - 1]);
            }
        } else if (ch == 6) {
            if (students.empty()) { cout << "No students registered.\n"; continue; }
            for (size_t j = 0; j < students.size(); j++)
                cout << j + 1 << ". " << students[j]->getName() << endl;
            int sel; cout << "Select student: "; cin >> sel; cin.ignore();
            if (sel >= 1 && sel <= (int)students.size())
                i->viewStudentPerformance(students[sel - 1]);
        } else if (ch == 7) {
            if (students.empty()) { cout << "No students registered.\n"; continue; }
            for (size_t j = 0; j < students.size(); j++)
                cout << j + 1 << ". " << students[j]->getName() << endl;
            int sel; cout << "Select student: "; cin >> sel; cin.ignore();
            if (sel >= 1 && sel <= (int)students.size())
                i->assignMarks(students[sel - 1]);
        } else if (ch == 8) break;
        else cout << "Invalid option.\n";
    }
}

void studentPanel(Student* s) {
    int ch;
    while (true) {
        cout << "\n1. View Dashboard\n2. Enroll in Course\n3. View Marks\n4. View Marks by Course\n5. View Materials\n6. View Assignments\n7. View Quizzes\n8. Answer Quizzes\n9. Answer Assignments\n10. Logout\nEnter: ";
        cin >> ch; cin.ignore();
        if (ch == 1) s->displayDashboard();
        else if (ch == 2) {
            if (courses.empty()) { cout << "No courses.\n"; continue; }
            for (size_t i = 0; i < courses.size(); i++)
                cout << i + 1 << ". " << courses[i]->getTitle() << endl;
            int sel; cout << "Select course: "; cin >> sel; cin.ignore();
            if (sel >= 1 && sel <= (int)courses.size())
                s->enroll(courses[sel - 1]);
        } else if (ch == 3) s->viewMarks();
        else if (ch == 4) s->viewMarksByCourse();
        else if (ch == 5) s->viewMaterials();
        else if (ch == 6) s->viewAssignments();
        else if (ch == 7) s->viewQuizzes();
        else if (ch == 8) s->answerQuiz();
        else if (ch == 9) s->answerAssignments();
        else if (ch == 10) break;
        else cout << "Invalid option.\n";
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n--- E-Learning System ---\n";
        cout << "1. Register Instructor\n2. Login Instructor\n3. Register Student\n4. Login Student\n5. Exit\nEnter: ";
        cin >> choice; cin.ignore();

        if (choice == 1) {
            string name, email, pass;
            cout << "Name: "; getline(cin, name);
            cout << "Email: "; getline(cin, email);
            cout << "Password: "; getline(cin, pass);
            instructors.push_back(new Instructor(name, email, pass));
            cout << "Instructor registered.\n";
        } else if (choice == 2) {
            string email, pass;
            cout << "Email: "; getline(cin, email);
            cout << "Password: "; getline(cin, pass);
            Instructor* i = loginInstructor(email, pass);
            if (i) instructorPanel(i);
            else cout << "Invalid login.\n";
        } else if (choice == 3) {
            string name, email, pass;
            cout << "Name: "; getline(cin, name);
            cout << "Email: "; getline(cin, email);
            cout << "Password: "; getline(cin, pass);
            students.push_back(new Student(name, email, pass));
            cout << "Student registered.\n";
        } else if (choice == 4) {
            string email, pass;
            cout << "Email: "; getline(cin, email);
            cout << "Password: "; getline(cin, pass);
            Student* s = loginStudent(email, pass);
            if (s) studentPanel(s);
            else cout << "Invalid login.\n";
        } else if (choice == 5) {
            cout << "Goodbye!\n";
            break;
        } else cout << "Invalid option.\n";
    }
    for (auto s : students) delete s;
    for (auto i : instructors) delete i;
    for (auto c : courses) delete c;
    return 0;
}
