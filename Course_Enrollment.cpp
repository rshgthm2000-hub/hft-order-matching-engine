#include <bits/stdc++.h>
using namespace std;
class Course;
class Student
{
private:
    string student_id;
    string student_name;
    int year_of_study;
    set<string> completed_courses;
    set<string> enrolled_courses;
    set<char> enrolled_slots;

public:
    Student()
    {
        student_id = "";
    }
    Student(string id, string name, int year, set<string> &c)
    {
        student_id = id;
        student_name = name;
        year_of_study = year;
        completed_courses = c;
    }
    void add_student(map<string, Student> &students)
    {
        students[student_id] = *this;
    }
    friend class Course;
};
class Course
{
private:
    string course_code;
    string course_name;
    int no_of_credits;
    int capacity;
    set<string> prerequisites;
    map<int, string> students_enrolled1;
    map<string, int> students_enrolled2;
    queue<string> waiting_list;
    int nos;
    char slot;

public:
    Course()
    {
        course_code = "";
    }
    Course(string cc, string cn, int noc, int cap, set<string> &prereq, char sl)
    {
        course_code = cc;
        course_name = cn;
        no_of_credits = noc;
        capacity = cap;
        prerequisites = prereq;
        slot = sl;
        nos = 0;
    }
    void add_course(map<string, Course> &courses)
    {
        for (auto itr : prerequisites)
        {
            if (courses.find(itr) == courses.end())
            {
                return;
            }
        }
        courses[course_code] = *this;
    }
    bool can_enroll(Student &student, map<string, Student> &students, map<string, Course> &courses)
    {
        for (auto i : prerequisites)
        {
            if (student.completed_courses.find(i) == student.completed_courses.end())
                return false;
        }
        if (capacity == students_enrolled1.size())
        {
            return false;
        }
        if (student.enrolled_slots.find(slot) != student.enrolled_slots.end())
        {
            return false;
        }
        if (student.enrolled_courses.find(course_code) != student.enrolled_courses.end())
        {
            return false;
        }
        return true;
    }
    void enroll_student(Student &student, map<string, Student> &students, map<string, Course> &courses)
    {
        if (!can_enroll(student, students, courses))
        {
            if (capacity == students_enrolled1.size())
            {
                waiting_list.push(student.student_id);
                return;
            }
        }
        else
        {
            nos++;
            student.enrolled_courses.insert(course_code);
            students_enrolled1[nos] = student.student_id;
            students_enrolled2[student.student_id] = nos;
            student.enrolled_slots.insert(slot);
        }
    }
    void drop(Student &student, map<string, Student> &students, map<string, Course> &courses)
    {
        student.enrolled_courses.erase(course_code);
        int nos1 = students_enrolled2[student.student_id];
        students_enrolled1.erase(nos1);
        students_enrolled2.erase(student.student_id);
        while (!waiting_list.empty())
        {
            if (can_enroll(students.find(waiting_list.front())->second, students, courses))
            {
                enroll_student(students.find(waiting_list.front())->second, students, courses);
                waiting_list.pop();
                break;
            }
            else
            {
                waiting_list.pop();
            }
        }
    }
    void print(map<string, Course> &courses)
    {
        if (!students_enrolled1.empty())
        {
            cout << "Enrolled students in " << course_code << ":\n";
            for (auto itr : students_enrolled1)
            {
                cout << itr.second << " ";
            }
            cout << "\n";
        }
    }
    friend class Student;
};
int main()
{
    map<string, Student> students;
    map<string, Course> courses;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        if (s == "add_student")
        {
            string s1, s2;
            int y, n1;
            cin >> s1 >> s2 >> y >> n1;
            set<string> cc;
            for (int j = 0; j < n1; j++)
            {
                string s3;
                cin >> s3;
                cc.insert(s3);
            }
            Student stud(s1, s2, y, cc);
            stud.add_student(students);
        }
        else if (s == "add_course")
        {
            string s1, s2;
            int cre, cap, n1;
            char sl;
            cin >> s1 >> s2 >> cre >> cap >> sl >> n1;
            set<string> prereq;
            for (int j = 0; j < n1; j++)
            {
                string s3;
                cin >> s3;
                prereq.insert(s3);
            }
            Course cour(s1, s2, cre, cap, prereq, sl);
            cour.add_course(courses);
        }
        else if (s == "enroll")
        {
            string s1, s2;
            cin >> s1 >> s2;
            if (courses.find(s2) != courses.end() && students.find(s1) != students.end())
                courses.find(s2)->second.enroll_student(students.find(s1)->second, students, courses);
        }
        else if (s == "drop")
        {
            string s1, s2;
            cin >> s1 >> s2;
            if (courses.find(s2) != courses.end() && students.find(s1) != students.end())
                courses.find(s2)->second.drop(students.find(s1)->second, students, courses);
        }
        else if (s == "print")
        {
            string s1;
            cin >> s1;
            if (courses.find(s1) != courses.end())
                courses.find(s1)->second.print(courses);
            else
                cout << "Invalid Course " << s1 << endl;
        }
    }
}
