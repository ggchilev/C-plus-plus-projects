
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#pragma region Student
class Student
{
private:
	string name;
	string facNum;
	int groupNum;

public:
	Student();
	void SetName(string name);
	string GetName();
	void SetFacNum(string facNum);
	string GetFacNum();
	void SetGroupNum(int groupNum);
	int GetGroupNum();
	void SetCourse(int course);
	int GetCourse();
	friend ostream& operator<<(ostream& os, Student& student);
};


Student::Student()
{
}

void Student::SetName(string name)
{
	Student::name = name;
}

string Student::GetName()
{
	return Student::name;
}

void Student::SetFacNum(string facNum)
{
	Student::facNum = facNum;
}

string Student::GetFacNum()
{
	return Student::facNum;
}

void Student::SetGroupNum(int groupNum)
{
	Student::groupNum = groupNum;
}

int Student::GetGroupNum()
{
	return Student::groupNum;
}

int Student::GetCourse()
{
	return Student::course;
}

#pragma endregion

#pragma region StudentGradePointAverage
class StudentGPA : public Student
{
private:
	vector<int> grades;
public:
	StudentGPA();
	StudentGPA SetSubjectGrades(StudentGPA student, int length);
	double CalculateGPA(StudentGPA student);
	vector<int> GetGrades();
};

StudentGPA::StudentGPA() : Student()
{
}

StudentGPA StudentGPA::SetSubjectGrades(StudentGPA student, int length)
{
	int grade;
	ofstream file;

	file.open("studentInfo.txt", ios::app);
	if (file.is_open())
	{
		file << student << endl;
		for (int i = 0; i < length; i++)
		{
			cout << i << ".";
			cin >> grade;
			file << i << "." << grade << endl;
			student.grades.insert(student.grades.end(), grade);
		}
	}
	file.close();
	return student;
}
double StudentGPA::CalculateGPA(StudentGPA student)
{
	int length = (student.grades.size());
	double average = 0;

	for (int i = 0; i < length; i++)
	{
		average += student.grades[i];
	}
	average = average / length;
	return average;
}
vector<int> StudentGPA::GetGrades()
{
	return grades;
}
#pragma endregion

ostream& operator<<(ostream& os, Student& student)
{
	os << "\"" << student.GetName() << "\" \"" << student.GetFacNum() << "\" \"" << student.GetGroupNum() << "\" \"" << student.GetCourse() << "\"";
	return os;
}

#pragma region Main
void PrintStudentInfoByFacNum(vector<StudentGPA> studentList)
{
	string facNum;
	cout << "Insert faculty number: ";
	cin >> facNum;

	for each (StudentGPA student in studentList)
	{
		if (facNum == student.GetFacNum())
		{
			cout << student << endl;
			int index = 0;
			for each (int grade in student.GetGrades())
			{
				cout << index++ << ". " << grade << endl;
			}
		}
	}
}

void PrintStudentInfo(vector<StudentGPA> studentList)
{
	int index = 0;
	for each (StudentGPA student in studentList)
	{
		cout << index++ << ". " << student << endl;
	}
}

void CalculateGroupGPA(vector<StudentGPA> studentList)
{
	int group = 0, count = 0;
	ofstream file;

	file.open("studentInfo.txt", ios::app);
	cout << "Choose group :";
	cin >> group;

	double result = 0;
	for each (StudentGPA student in studentList)
	{
		if (student.GetGroupNum() == group)
		{
			result += student.CalculateGPA(student);
			count++;
		}
	}
	if (count > 0 && file.is_open())
	{
		result = result / count;
		cout << "GPA of the group " << group << " is " << result << endl;
		file << "GPA of the group " << group << " is " << result << endl;
	}
	file.close();
}

void CalculateStudentGPA(vector<StudentGPA> studentList)
{
	StudentGPA student;
	int index = 0, studentIndex;
	double result;
	ofstream file;

	file.open("studentInfo.txt", ios::app);

	for each (Student student in studentList)
	{
		cout << index++ << "." << student << endl << flush;
	}
	if (studentList.size() > 0 && file.is_open())
	{
		cout << "Select student:";
		cin >> studentIndex;
		result = student.CalculateGPA(studentList[studentIndex]);
		cout << "GPA of the student " << studentList[studentIndex] << " is " << result << endl;
		file << "GPA of the student " << studentList[studentIndex] << " is " << result << endl;
	}
	file.close();
}

vector<StudentGPA> InsertGrades(vector<StudentGPA> studentList)
{
	StudentGPA student;
	int subjectsNum, studentIndex, k = 0;
	do {
		if (studentList.size() > 0)
		{
			int index = 0;
			for each (Student student in studentList)
			{
				cout << index++ << "." << student << endl << flush;
			}
			cout << "Select student:";
			cin >> studentIndex;
			cout << "Number of subjects:";
			cin >> subjectsNum;
			if (subjectsNum > 0)
			{
				studentList[studentIndex] = student.SetSubjectGrades(studentList[studentIndex], subjectsNum);
			}
			cout << "Add more grades? yes - 1, no - 0 : ";
			cin >> k;
		}
	} while (k != 0);

	return studentList;
}

vector<StudentGPA> AddStudent(vector<StudentGPA> studentList)
{
	StudentGPA student;
	string name, facNum;
	int groupNum, course, k;
	ofstream file;

	file.open("studentInfo.txt", ios::app);
	if (file.is_open())
	{
		do {
			cout << "Name:";
			cin >> name;
			student.SetName(name);
			cout << "Faculty number:";
			cin >> facNum;
			student.SetFacNum(facNum);
			cout << "Group number:";
			cin >> groupNum;
			student.SetGroupNum(groupNum);
			cout << "Course:";
			cin >> course;
			student.SetCourse(course);

			studentList.insert(studentList.end(), student);
			file << student << endl;
			cout << "Add more students? yes - 1, no - 0 : ";
			cin >> k;
		} while (k != 0);
	}

	file.close();
	return studentList;
}

int main()
{
	vector<StudentGPA> studentList;
	int k, j;
	ofstream file ("studentInfo.txt");

	do {
		cout << "1. Add student." << endl;
		cout << "2. Insert student's grades." << endl;
		cout << "3. Calculate student GPA." << endl;
		cout << "4. Calculate group GPA." << endl;
		cout << "5. Print students info." << endl;
		cout << "6. Print student info by facylti number." << endl;
		cout << "Your choice: ";
		cin >> k;

		switch (k)
		{
		case 1:
			studentList = AddStudent(studentList);
			break;
		case 2:
			studentList = InsertGrades(studentList);
			break;
		case 3:
			CalculateStudentGPA(studentList);
			break;
		case 4:
			CalculateGroupGPA(studentList);
			break;
		case 5:
			PrintStudentInfo(studentList);
			break;
		case 6:
			PrintStudentInfoByFacNum(studentList);
			break;
		default:
			break;
		}
		cout << "Quit? yes - 1, no - 0 : ";
		cin >> j;

	} while (j != 1);

	system("pause");
	return 0;
}
#pragma endregion



