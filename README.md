# E-Learning-System
🎓 E-Learning Management System
This is a C++ console-based E-Learning Management System designed using Object-Oriented Programming (OOP) principles. It allows students and instructors to interact in a virtual course environment, with functionality for course management, content sharing, assignment submissions, quiz evaluations, and grade tracking.

💡 Features
👩‍🏫 Instructor Panel
Register and log in
Create courses
Add course materials, assignments, and quizzes
View student performance
Assign marks for quizzes and assignments
👨‍🎓 Student Panel
Register and log in
Enroll in courses
View materials, assignments, and quizzes
Submit answers for assignments and quizzes
View marks (overall and course-wise)
🧠 OOP Concepts Used
Concept	Implementation Example
Classes & Objects	User, Student, Instructor, Course, etc.
Inheritance	Student and Instructor inherit from User
Polymorphism	Overridden displayDashboard() and viewMarks()
Encapsulation	Private/protected data members accessed through methods
Abstraction	User is an abstract base class
Friend Class	Instructor is a friend of Student for grading access
🛠️ How It Works
Start the application
Choose to register or log in as either a Student or an Instructor
Instructors can:
Create a course
Add learning materials, quizzes, and assignments
Assign marks to students
Students can:
Enroll in courses
Submit answers
View results and content
🔃 Data Structures Used
vector for dynamic lists (courses, assignments, quizzes, etc.)
map for storing answers and marks by title/topic
🗂️ File Structure
All code is written in a single main.cpp file for simplicity. You can split it into headers and source files for scalability.
