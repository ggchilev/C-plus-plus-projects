#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string text = "";

class Student
{
private:
	string name;
	string facNum;
	int groupNum;
public:
	Student(string n, string facNum, int groupNum){
    SetName(n);
    SetFacNum(facNum);
    SetGroupNum(groupNum);
    }

void SetName(string n)
{
	name = n;
}

string GetName()
{
	return name;
}

void SetFacNum(string facNm)
{
	facNum = facNm;
}

string GetFacNum()
{
	return facNum;
}

void SetGroupNum(int groupNm)
{
	groupNum = groupNm;
}

int GetGroupNum()
{
	return groupNum;
}

};



class StudentGrades:Student{

private:
    int semester1[5];
    int semester2[5];

public:
    StudentGrades(int sem1[5], int sem2[5], string name, string facNum, int groupNum):Student(name, facNum, groupNum){
        for(int i=0; i<5; i++){
            semester1[i] = sem1[i];
        }
        for(int j=0; j<5; j++){
            semester2[j] = sem2[j];
        }
    }

        static void minMaxAvgGrades(int grNum, StudentGrades students[5]){
        double maxGrade = 0;
        double minGrade = 7;
        double srUsp = 0;
        for(int i=0; i<5; i++){
            if(students[i].GetGroupNum() == grNum){
                for(int j=0; j<5; j++){
                    srUsp += students[i].semester1[j];
            }
                for(int k=0; k<5; k++){
                    srUsp += students[i].semester2[k];
                }
            if(srUsp/10 > maxGrade){
                maxGrade = srUsp/10;
                cout<<"MAX: "<<maxGrade<<endl;

            }
            if(srUsp/10 < minGrade){
                minGrade = srUsp/10;
                cout<<"MIN: "<<minGrade<<endl;
            }
            srUsp = 0;
            }
        }
        cout<<"Min avg grade for group "<<grNum<<" is "<<minGrade<<endl;
        cout<<"Max avg grade for group "<<grNum<<" is "<<maxGrade<<endl;
        //text += "Max avg grade for group " + grNum + " is " + maxGrade + "\n";
        //text += "Min avg grade for group " + grNum + " is " + minGrade + "\n";
        writeFile(text);


    }
    static void showStudentGrades(StudentGrades students[5]){
        for(int i=0; i<5; i++){
            cout<<endl<<"Grades for student "<<students[i]<<" : "<<endl;
            cout<<endl<<"Semester 1 : "<<endl;
            text += "\n Grades for student " + students[i].GetName() + " : " + "\n";
            text += "\n Semester 1 : \n";
            for(int j=0; j<5; j++){
                cout<<students[i].semester1[j]<<", ";
                text += students[i].semester1[j] + ", ";
            }
            cout<<endl<<"Semester 2 : "<<endl;
            text += "\n Semester 2 : \n";
            for(int k=0; k<5; k++){
                cout<<students[i].semester2[k]<<", ";
                text += students[i].semester2[k] + ", ";
            }
        }
        writeFile(text);
    }
    static void showStudentGradesForGroup(StudentGrades students[5], int grNum){
       for(int i=0; i<5; i++){
       if(students[i].GetGroupNum() == grNum){
            cout<<endl<<"Grades for student "<<students[i]<<" : "<<endl;
            cout<<endl<<"Semester 1 : "<<endl;
            text += "\n Grades for student " + students[i].GetName() + " : " + "\n";
            text += "\n Semester 1 : \n";
            for(int j=0; j<5; j++){
                cout<<students[i].semester1[j]<<", ";
                text += students[i].semester1[j] + ", ";
            }
            cout<<endl<<"Semester 2 : "<<endl;
            for(int k=0; k<5; k++){
                cout<<students[i].semester1[k]<<", ";
                text += students[i].semester2[k] + ", ";
            }
        }
       }
       writeFile(text);
    }
    static void showAvgGradesForGroup(StudentGrades students[5], int grNum){

        double srUsp = 0;
        int num = 0;
        for(int i=0; i<5; i++){
            if(students[i].GetGroupNum() == grNum){
                num += 1;
                for(int j=0; j<5; j++){
                    srUsp += students[i].semester1[j];
            }
                for(int k=0; k<5; k++){
                    srUsp += students[i].semester2[k];
                }
        }
}
 cout<<"Avg grade for group "<<grNum<<" is "<<srUsp/10/num<<endl;
// text += "Avg grade for group " + grNum + " is " + srUsp/10/num + "\n";
writeFile(text);
}

    static int writeFile (string text){

      ofstream myfile;
      myfile.open ("example.txt");
      myfile << text << "\n";
      myfile.close();
      return 0;

}


	friend ostream& operator<<(ostream& os, StudentGrades student);

};



ostream& operator<<(ostream& os, StudentGrades st)
{
    os <<"Name: "<< st.GetName() << ", FacNum: "<<st.GetFacNum()<<", Group: "<<st.GetGroupNum()<<endl;
    return os;
}



int main()
{
    int grades1[5] = {2, 3, 4, 5, 6};
    int grades2[5] = {3, 3, 3, 3, 4};
    int grades3[5] = {6, 6, 6, 6, 6};
    int grades4[5] = {3, 5, 3, 2, 4};
    int grades5[5] = {2, 5, 6, 5, 6};
    int grades6[5] = {5, 5, 4, 3, 4};
    StudentGrades dancho(grades1, grades2, "Dancho", "11212231", 42);
    StudentGrades cenev(grades3, grades4, "Cenev", "11212231", 42);
    StudentGrades chilev(grades3, grades5, "Chilev", "11212231", 42);
    StudentGrades bota(grades4, grades6, "Bota", "11212231", 41);
    StudentGrades minka_svirkata(grades5, grades1, "Minka", "11212231", 41);

    StudentGrades st[5] = {dancho, cenev, chilev, bota, minka_svirkata};
    StudentGrades::showStudentGrades(st);
    StudentGrades::showStudentGradesForGroup(st, 42);
    StudentGrades::minMaxAvgGrades(42, st);
    StudentGrades::showAvgGradesForGroup(st, 42);

    return 0;
}

