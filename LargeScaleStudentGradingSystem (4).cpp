// LargeScaleStudentGradingSystem.cpp
// A comprehensive student grading system for schools and universities  
#include<iostream>
#include<string>
#include<fstream>
#include<limits>
#include<iomanip>
using namespace std;

const int MAX_STUDENT=100;
const int MAX_SUBJECTS=20;
const int MAX_TEACHER=1;

struct Subject  //to hold subject details
{
    string name;
    int max_marks;
    double obtained_marks;
    int credit_hours;
    double quiz_marks;
    double assignment_marks;
    double mid_marks;
    double final_marks;
    double pbl_marks;
    string overall_grade;
};

struct Teacher  //to hold teacher details
{
    int id;
    string name;
    string password;
};

struct Student  //to hold student details
{
    int roll_number;
    string name;
    int current_class;
    string group_stream;
    string college_school_name;
    string principal_name;
    string class_teacher_name;
    Subject subjects[MAX_SUBJECTS];
    int subject_count;
    double total_obtained;
    double total_max_marks;
    double final_percentage;
    string overall_grade;
    double final_gpa;
    string department_name;
    string degree_level;
    int current_semester;
    bool marks_entered;
    bool result_calculated;
};
// Global Arrays and Counters
Student records[MAX_STUDENT];
Teacher teachers[MAX_TEACHER];
int student_count=0;
int teacher_count=0;
// Function Prototypes
void teacherLogin();
void initializeTeachers();
void DisplayMainMenu();
void EnterStudentDetails();
void EnterStudentMarks();
void CalculateResult();
void DisplayReport();
void SearchStudentRecord();
void loadAllData();
void saveData();
void InitialUserSelect();
int findStudentIndex(int rollNo);
double marksToGradePoints(double percentage);
string getGradeLetter(double percentage);
string getSchoolGrade(double percentage);
// Main Function
int main()
{
    initializeTeachers();
    loadAllData();
    InitialUserSelect();
    saveData();
    return 0;
}
// Function Definitions
void InitialUserSelect()
{
    int choice;
    do{
        cout<<"\n==============================================\n";
        cout<<"  STUDENT GRADING SYSTEM - USER SELECTION\n";
        cout<<"\n==============================================\n";
        cout<<"1. Teacher Portal\n";
        cout<<"2. Student Portal\n";
        cout<<"3. Exit\n";
        cout<<"Enter your choice: ";

        if(!(cin>>choice))
        {
            cout<<"Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }

        switch(choice)
        {
            case 1:
                teacherLogin();
                break;
            case 2:
                DisplayReport();
                break;
            case 3:
                cout<<"\nThank you for using our student grading system, Please come again!\n";
                return;
            default:
                cout<<"Invalid option. Please try again.\n";
        }
    }while(choice!=3);
}
// Initialize Teacher Accounts
void initializeTeachers()
{
    teachers[0].id=101;
    teachers[0].name="Asfand Yar";
    teachers[0].password="asfand(#123)";
    teacher_count=1;
    cout<<"Teacher account initialized: Asfand Yar (ID: 101)\n";
}
// Teacher Login Function
void teacherLogin()
{
    cout<<"\n==================Login Menu=======================\n";
    int input_id;
    string input_password;
    cout<<"Enter Teacher ID: ";
    cin>>input_id;  // Read integer ID
    cin.ignore(numeric_limits<streamsize>::max(),'\n');  //clear input buffer
    cout<<"Enter Password: ";
    getline(cin,input_password);

    for(int i=0;i<teacher_count;i++)  //check credentials
    {
        if((input_id==teachers[i].id) && (input_password==teachers[i].password))
        {
            cout<<"\n********************************************************\n";
            cout<<"*** LOGIN SUCCESSFUL! Welcome: "<<teachers[i].name<<" ***\n";
            cout<<"********************************************************\n";
            DisplayMainMenu();  // Navigate to main menu
            return;
        }
    }
    cout<<"Login Failed. Invalid Id or Password.\n";
    cout<<"Press Enter to continue...";
    cin.get();  //wait for user to press enter
}
// Main Menu Display Function
void DisplayMainMenu()
{
    int choice;
    do
    {
        cout<<"\n===============================================================================\n";
        cout<<"                      STUDENT GRADING SYSTEM - TEACHER PORTAL                   \n";
        cout<<"===============================================================================\n";
        cout<<"\n1. Enter Student Details";
        cout<<"\n2. Enter Student Marks";
        cout<<"\n3. Calculate Result";
        cout<<"\n4. Display Report";
        cout<<"\n5. Search Student Record";
        cout<<"\n6. Load All Student Data";
        cout<<"\n7. Save All Student Data";
        cout<<"\n8. Exit";
        cout<<"\nEnter Choice (1-8): ";

        if(!(cin>>choice))
        {
            cout<<"ERROR: Invalid input for Choice, Please Enter a Number: ";
            cin.clear();  //clear error flag
            cin.ignore(numeric_limits<streamsize>::max(),'\n');//clear input buffer
            choice=-1; // set choice to invalid value to trigger re-prompt
            continue;
        }

        switch(choice)
        {
        case 1:
            EnterStudentDetails();
            break;
        case 2:
            EnterStudentMarks();
            break;
        case 3:
            CalculateResult();
            break;
        case 4:
            DisplayReport();
            break;
        case 5:
            SearchStudentRecord();
            break;
        case 6:
            loadAllData();
            break;
        case 7:
            saveData();
            break;
        case 8:
            saveData();
            cout<<"\nReturning to main menu...\n";
            cout<<"Press Enter to continue...";
            cin.ignore();  //clear input buffer
            cin.get();
            return;
                
        default:
            cout<<"Invalid choice! Please enter 1-8.\n";
            break;
        }
    }while(choice!=8);  // Loop until exit option is chosen
}
// Function to find student index by roll number using binary search
int findStudentIndex(int rollNo)
{
	int low=0,high=student_count-1,mid;
	while(low<=high)
	{
		mid=((low+high)/2);
			if(rollNo==records[mid].roll_number)
	        	{
	            	return mid;
	        	}
	        else if(rollNo<records[mid].roll_number)
	        	{
	        		high=mid-1;
				}
			else
				{
					low=mid+1;
				}
	}
		return -1;
		
//	for(int i=0; i<student_count; i++)
//    {
//        if(records[i].roll_number == rollNo)
//        {
//            return i;
//        }
//    }
//    return -1;
}
// Function to enter new student details
void EnterStudentDetails()
{
    if(student_count==MAX_STUDENT)
    {
        cout<<"ERROR: Maximum Student Capacity Reached, cannot enroll more than 100 students\n";
        return;
    }
    int current_index=student_count;
    int input_roll;

    do
    {
        cout<<"\nEnter new Student roll number (must be unique): ";
        cin.clear();
        if(!(cin>>input_roll))
        {
        cout<<"Invalid input! Please enter a number.\n";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        input_roll=-1;
        continue; 
        }
        if(findStudentIndex(input_roll)!=-1)
        {
            cout<<"ERROR: Roll Number already exists. Please enter a different one.\n";
        }
        else if(input_roll <= 0)
        {
            cout<<"ERROR: Roll number must be positive.\n";
        }
    }while(input_roll<=0 || findStudentIndex(input_roll)!=-1);

    records[current_index].roll_number=input_roll;//assign unique roll number
    cin.ignore(numeric_limits<streamsize>::max(),'\n'); 

    cout<<"Enter Student Name: ";
    getline(cin,records[current_index].name);  // Read full name including spaces

    do
    {
        cout<<"Enter Class (1-12) or 33 for university: ";
        cin>>records[current_index].current_class;
        if((records[current_index].current_class<1||records[current_index].current_class>12)&&records[current_index].current_class!=33)
        {
            cout<<"ERROR: Invalid class entry. Please enter 1-12 or 33 for university.\n";
        }
    }while((records[current_index].current_class<1||records[current_index].current_class>12)&&records[current_index].current_class!=33);//validate class input
// Initialize other fields
    records[current_index].marks_entered=false;  //initialize flags and totals
    records[current_index].result_calculated=false;
    records[current_index].total_obtained=0;
    records[current_index].total_max_marks=0;
    records[current_index].final_percentage=0;
    records[current_index].final_gpa=0;

    if(records[current_index].current_class>=1&&records[current_index].current_class<=12)
    {
        cout<<"\n----------- Entering School/College Data ----------\n";
        records[current_index].subject_count=0;
        records[current_index].group_stream="School/College";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        cout<<"Enter School/College Name: ";
        getline(cin,records[current_index].college_school_name);

        cout<<"Enter Principal Name: ";
        getline(cin,records[current_index].principal_name);

        cout<<"Enter Class Teacher Name: ";
        getline(cin,records[current_index].class_teacher_name);

        cout<<"\n-------- Setting Subject Curriculum for Class "<<records[current_index].current_class<<" --------\n";

        int class_level=records[current_index].current_class;
 // Set subjects based on class level
        switch(class_level)
        {
            case 1:
            case 2:
                records[current_index].subject_count=5;
                records[current_index].subjects[0].name="English (100)";
                records[current_index].subjects[0].max_marks=100;
                records[current_index].subjects[1].name="Urdu (100)";
                records[current_index].subjects[1].max_marks=100;
                records[current_index].subjects[2].name="Maths (100)";
                records[current_index].subjects[2].max_marks=100;
                records[current_index].subjects[3].name="General Knowledge GK (100)";
                records[current_index].subjects[3].max_marks=100;
                records[current_index].subjects[4].name="Islamiyat (100)";
                records[current_index].subjects[4].max_marks=100;
                records[current_index].subjects[5].name="Drawing (50)";
                records[current_index].subjects[5].max_marks=50;
                break;

            case 3:
                records[current_index].subject_count=6;
                records[current_index].subjects[0].name="English (100)";
                records[current_index].subjects[0].max_marks=100;
                records[current_index].subjects[1].name="Urdu (100)";
                records[current_index].subjects[1].max_marks=100;
                records[current_index].subjects[2].name="Maths (100)";
                records[current_index].subjects[2].max_marks=100;
                records[current_index].subjects[3].name="General Science (100)";
                records[current_index].subjects[3].max_marks=100;
                records[current_index].subjects[4].name="Islamiyat (100)";
                records[current_index].subjects[4].max_marks=100;
                records[current_index].subjects[5].name="Social Studies (100)";
                records[current_index].subjects[5].max_marks=100;
                break;

            case 4:
            case 5:
                records[current_index].subject_count=7;
                records[current_index].subjects[0].name="English (100)";
                records[current_index].subjects[0].max_marks=100;
                records[current_index].subjects[1].name="Urdu (100)";
                records[current_index].subjects[1].max_marks=100;
                records[current_index].subjects[2].name="Maths (100)";
                records[current_index].subjects[2].max_marks=100;
                records[current_index].subjects[3].name="General Science (100)";
                records[current_index].subjects[3].max_marks=100;
                records[current_index].subjects[4].name="Islamiyat (100)";
                records[current_index].subjects[4].max_marks=100;
                records[current_index].subjects[5].name="Social Studies (100)";
                records[current_index].subjects[5].max_marks=100;
                records[current_index].subjects[6].name="Computer Science (100)";
                records[current_index].subjects[6].max_marks=100;
                break;

            case 6:
            case 7:
            case 8:
                records[current_index].subject_count=8;
                records[current_index].subjects[0].name="English (100)";
                records[current_index].subjects[0].max_marks=100;
                records[current_index].subjects[1].name="Urdu (100)";
                records[current_index].subjects[1].max_marks=100;
                records[current_index].subjects[2].name="Maths (100)";
                records[current_index].subjects[2].max_marks=100;
                records[current_index].subjects[3].name="Science (100)";
                records[current_index].subjects[3].max_marks=100;
                records[current_index].subjects[4].name="Islamiyat (100)";
                records[current_index].subjects[4].max_marks=100;
                records[current_index].subjects[5].name="History (100)";
                records[current_index].subjects[5].max_marks=100;
                records[current_index].subjects[6].name="Computer Science (100)";
                records[current_index].subjects[6].max_marks=100;
                records[current_index].subjects[7].name="Geography (100)";
                records[current_index].subjects[7].max_marks=100;
                break;

            default:
            {
                int stream_choice=0;
                cout<<"\n------ Stream Selection for Class "<<class_level<<" ------\n";
//stream selection for classes 9-12
                if(class_level==9||class_level==10)
                {
                    do{
                        cout<<"Select Stream:\n1. BIO\n2. Computer Science\nEnter Choice(1-2): ";
                        cin>>stream_choice;
                        if(stream_choice<1||stream_choice>2)
                        {
                            cout<<"ERROR: Invalid Choice, Please enter 1 or 2\n";
                        }
                    }while(stream_choice<1||stream_choice>2);

                    records[current_index].subject_count=8;

                    if(stream_choice==1)
                    {
                        records[current_index].group_stream="9/10 Biology";
                        records[current_index].subjects[0].name="English (75)";
                        records[current_index].subjects[0].max_marks=75;
                        records[current_index].subjects[1].name="Urdu (75)";
                        records[current_index].subjects[1].max_marks=75;
                        records[current_index].subjects[2].name="Math (75)";
                        records[current_index].subjects[2].max_marks=75;
                        records[current_index].subjects[3].name="Biology (75)";
                        records[current_index].subjects[3].max_marks=75;
                        records[current_index].subjects[4].name="Chemistry (75)";
                        records[current_index].subjects[4].max_marks=75;
                        records[current_index].subjects[5].name="Physics (75)";
                        records[current_index].subjects[5].max_marks=75;
                        records[current_index].subjects[6].name="Islamiyat (50)";
                        records[current_index].subjects[6].max_marks=50;
                        records[current_index].subjects[7].name="Pakistan Studies (50)";
                        records[current_index].subjects[7].max_marks=50;
                    }
                    else
                    {
                        records[current_index].group_stream="9/10 Computer Science";
                        records[current_index].subjects[0].name="English (75)";
                        records[current_index].subjects[0].max_marks=75;
                        records[current_index].subjects[1].name="Urdu (75)";
                        records[current_index].subjects[1].max_marks=75;
                        records[current_index].subjects[2].name="Math (75)";
                        records[current_index].subjects[2].max_marks=75;
                        records[current_index].subjects[3].name="Computer (75)";
                        records[current_index].subjects[3].max_marks=75;
                        records[current_index].subjects[4].name="Chemistry (75)";
                        records[current_index].subjects[4].max_marks=75;
                        records[current_index].subjects[5].name="Physics (75)";
                        records[current_index].subjects[5].max_marks=75;
                        records[current_index].subjects[6].name="Islamiyat (50)";
                        records[current_index].subjects[6].max_marks=50;
                        records[current_index].subjects[7].name="Pakistan Studies (50)";
                        records[current_index].subjects[7].max_marks=50;
                    }
                }
                // stream selection for classes 11-12
                else if(class_level==11||class_level==12)
                {
                    do{
                        cout<<"Select Stream:\n1. ICS\n2. Pre-Engineering\n3. Pre-Medical\nEnter Choice(1-3): ";
                        cin>>stream_choice;
                        if(stream_choice<1||stream_choice>3)
                        {
                            cout<<"ERROR: Invalid Choice, Please enter 1 to 3\n";
                        }
                    }while(stream_choice<1||stream_choice>3);

                    records[current_index].subject_count=6;
                    if(stream_choice==1)
                    {
                        records[current_index].group_stream="11/12 ICS";
                        records[current_index].subjects[0].name="English (100)";
                        records[current_index].subjects[0].max_marks=100;
                        records[current_index].subjects[1].name="Urdu (100)";
                        records[current_index].subjects[1].max_marks=100;
                        records[current_index].subjects[2].name="Math (100)";
                        records[current_index].subjects[2].max_marks=100;
                        records[current_index].subjects[3].name="Computer Science (100)";
                        records[current_index].subjects[3].max_marks=100;
                        records[current_index].subjects[4].name="Physics (100)";
                        records[current_index].subjects[4].max_marks=100;
                        records[current_index].subjects[5].name="Islamiyat/Pak_study (50)";
                        records[current_index].subjects[5].max_marks=50;
                    }
                    else if(stream_choice==2)
                    {
                        records[current_index].group_stream="11/12 Pre-Engineering";
                        records[current_index].subjects[0].name="English (100)";
                        records[current_index].subjects[0].max_marks=100;
                        records[current_index].subjects[1].name="Urdu (100)";
                        records[current_index].subjects[1].max_marks=100;
                        records[current_index].subjects[2].name="Math (100)";
                        records[current_index].subjects[2].max_marks=100;
                        records[current_index].subjects[3].name="Chemistry (100)";
                        records[current_index].subjects[3].max_marks=100;
                        records[current_index].subjects[4].name="Physics (100)";
                        records[current_index].subjects[4].max_marks=100;
                        records[current_index].subjects[5].name="Islamiyat/Pak_study (50)";
                        records[current_index].subjects[5].max_marks=50;
                    }
                    else
                    {
                        records[current_index].group_stream="11/12 Pre-Medical";
                        records[current_index].subjects[0].name="English (100)";
                        records[current_index].subjects[0].max_marks=100;
                        records[current_index].subjects[1].name="Urdu (100)";
                        records[current_index].subjects[1].max_marks=100;
                        records[current_index].subjects[2].name="Biology (100)";
                        records[current_index].subjects[2].max_marks=100;
                        records[current_index].subjects[3].name="Chemistry (100)";
                        records[current_index].subjects[3].max_marks=100;
                        records[current_index].subjects[4].name="Physics (100)";
                        records[current_index].subjects[4].max_marks=100;
                        records[current_index].subjects[5].name="Islamiyat/Pak_study (50)";
                        records[current_index].subjects[5].max_marks=50;
                    }
                }
            }
            break;
        }

        for(int i=0;i<records[current_index].subject_count;i++)
        {
            records[current_index].subjects[i].credit_hours=1;
            records[current_index].subjects[i].quiz_marks=0;
            records[current_index].subjects[i].assignment_marks=0;
            records[current_index].subjects[i].mid_marks=0;
            records[current_index].subjects[i].final_marks=0;
            records[current_index].subjects[i].pbl_marks=0;
        }
    }
    else if(records[current_index].current_class==33)
    {
        cout<<"\n---------- Enter University Data Collection (Nutech University) ----------\n";
        records[current_index].subject_count=0;
// Degree Level Selection
        int degree_choice;
        do
        {
            cout<<"\nSelect Degree Level:";
            cout<<"\n1. BS (Bachelor of Science)";
            cout<<"\n2. MS (Master of Science)";
            cout<<"\nEnter Degree Choice (1-2): ";
            if(!(cin>>degree_choice)||degree_choice<1||degree_choice>2){
                cout<<"ERROR: Invalid Degree Choice. Please enter 1-2.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }while(degree_choice<1||degree_choice>2);

        if(degree_choice==1)records[current_index].degree_level="BS";
        else records[current_index].degree_level="MS";

        records[current_index].college_school_name="Nutech University";
        records[current_index].principal_name="Lt. Gen. Moazzam Ejaz (Rector)";
        records[current_index].class_teacher_name="Asfand Yar";
        records[current_index].department_name="N/A";
        records[current_index].group_stream=records[current_index].degree_level+" Program";

        int dept_choice=0;
        int program_choice=0;
        int semester_input=0;
        int max_sem=0;
// Department and Program Selection
        if(degree_choice==1){
            // BS programs have 8 semesters
            max_sem=8;
            
            do{
                cout<<"\nSelect Department:";
                cout<<"\n1. Computing & IT Department";
                cout<<"\n2. Engineering Department";
                cout<<"\nEnter Department Choice (1-2): ";
                if(!(cin>>dept_choice)||dept_choice<1||dept_choice>2){
                    cout<<"ERROR: Invalid Department Choice.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
            }while(dept_choice<1||dept_choice>2);
            
            if(dept_choice==1){
                records[current_index].department_name="Computing & IT Department";
                do{
                    cout<<"\nSelect Program:";
                    cout<<"\n1. BS Computer Science";
                    cout<<"\n2. BS Software Engineering";
                    cout<<"\nEnter Choice (1-2): ";
                    if(!(cin>>program_choice)||program_choice<1||program_choice>2){
                        cout<<"ERROR: Invalid Program Choice.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    }
                }while(program_choice<1||program_choice>2);
                
                if(program_choice==1)
                    records[current_index].group_stream="BS Computer Science";
                else
                    records[current_index].group_stream="BS Software Engineering";
            }
            else{
                records[current_index].department_name="Engineering Department";
                do{
                    cout<<"\nSelect Program:";
                    cout<<"\n1. BS Civil Engineering";
                    cout<<"\n2. BS Mechanical Engineering";
                    cout<<"\nEnter Choice (1-2): ";
                    if(!(cin>>program_choice)||program_choice<1||program_choice>2){
                        cout<<"ERROR: Invalid Program Choice.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    }
                }while(program_choice<1||program_choice>2);
                
                if(program_choice==1)
                    records[current_index].group_stream="BS Civil Engineering";
                else
                    records[current_index].group_stream="BS Mechanical Engineering";
            }
        }
        else{
            // MS programs have 3 semesters
            max_sem=3;
            records[current_index].department_name="Post-Graduate";
            
            do{
                cout<<"\nSelect Program:";
                cout<<"\n1. MS Computer Science";
                cout<<"\n2. MS Civil Engineering";
                cout<<"\nEnter Choice (1-2): ";
                if(!(cin>>program_choice)||program_choice<1||program_choice>2){
                    cout<<"ERROR: Invalid Program Choice.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
            }while(program_choice<1||program_choice>2);
            
            if(program_choice==1)
                records[current_index].group_stream="MS Computer Science";
            else
                records[current_index].group_stream="MS Civil Engineering";
        }

        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        do{
            cout<<"\nEnter Current Semester (1-"<<max_sem<<"): ";
            if(!(cin>>semester_input)||semester_input<1||semester_input>max_sem){
                cout<<"ERROR: Invalid Semester Input.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }while(semester_input<1||semester_input>max_sem);
        
        records[current_index].current_semester=semester_input;

        cout<<"\n--- Loading Curriculum for "<<records[current_index].group_stream<<" Semester "<<semester_input<<" ---\n";

        if(degree_choice==1){ // BS Programs
            if(dept_choice==1){ // Computing & IT Department
                if(program_choice==1){ // BS Computer Science
                    if(semester_input==1){
                        records[current_index].subject_count=7;
                        records[current_index].subjects[0].name="Programming Fundamentals (3 Cr)";
                        records[current_index].subjects[0].credit_hours=3;
                        records[current_index].subjects[1].name="Calculus and Analytical Geometry (3 Cr)";
                        records[current_index].subjects[1].credit_hours=3;
                        records[current_index].subjects[2].name="Functional English (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Discrete Structures (3 Cr)";
                        records[current_index].subjects[3].credit_hours=3;
                        records[current_index].subjects[4].name="ICT (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="ICT LAB (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="PF LAB (1 Cr)";
                        records[current_index].subjects[6].credit_hours=1;
                    }
                    else if(semester_input==2){
                        records[current_index].subject_count=8;
                        records[current_index].subjects[0].name="Database Systems (3 Cr)";
                        records[current_index].subjects[0].credit_hours=3;
                        records[current_index].subjects[1].name="Database Systems Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Object Oriented Programming (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Object Oriented Programming Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Digital Logic Design (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Digital Logic Design lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Multivariable Calculus (3 Cr)";
                        records[current_index].subjects[6].credit_hours=3;
                        records[current_index].subjects[7].name="Linear Algebra (3 Cr)";
                        records[current_index].subjects[7].credit_hours=3;
                    }
                    else if(semester_input==3){
                        records[current_index].subject_count=10;
                        records[current_index].subjects[0].name="Artificial Intelligence (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Artificial Intelligence Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Data Structures (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Data Structures Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Information Security (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Information Security Lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Computer Networks (2 Cr)";
                        records[current_index].subjects[6].credit_hours=2;
                        records[current_index].subjects[7].name="Computer Networks Lab (1 Cr)";
                        records[current_index].subjects[7].credit_hours=1;
                        records[current_index].subjects[8].name="Software Engineering (3 Cr)";
                        records[current_index].subjects[8].credit_hours=3;
                        records[current_index].subjects[9].name="Probability & statistics (3 Cr)";
                        records[current_index].subjects[9].credit_hours=3;

                    }
                    else if(semester_input==4){
                        records[current_index].subject_count=9;
                        records[current_index].subjects[0].name="Computer Organization and Assembly Language (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Computer Organization and Assembly Language Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Theory of Automata (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Advance Database Management Systems (2 Cr)";
                        records[current_index].subjects[3].credit_hours=2;
                        records[current_index].subjects[4].name="Advance Database Management Systems Lab (1 Cr)";
                        records[current_index].subjects[4].credit_hours=1;
                        records[current_index].subjects[5].name="Applied Physics (2 Cr)";
                        records[current_index].subjects[5].credit_hours=2;
                        records[current_index].subjects[6].name="Applied Physics Lab (1 Cr)";
                        records[current_index].subjects[6].credit_hours=1;
                        records[current_index].subjects[7].name="Expository writing (3 Cr)";
                        records[current_index].subjects[7].credit_hours=3;
                        records[current_index].subjects[8].name="Islamic Studies (2 Cr)";
                        records[current_index].subjects[8].credit_hours=2;
                    }
                    else if(semester_input==5){
                        records[current_index].subject_count=11;
                        records[current_index].subjects[0].name="Operating Systems (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Operating Systems Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="HCI & Computer Graphics (2 Cr)";
                        records[current_index].subjects[2].credit_hours=2;
                        records[current_index].subjects[3].name="HCI & Computer Graphics Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Computer Architecture (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Computer Architecture Lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="AI/ML (2 Cr)";
                        records[current_index].subjects[6].credit_hours=2;
                        records[current_index].subjects[7].name="AI/ML Lab (1 Cr)";
                        records[current_index].subjects[7].credit_hours=1;
                        records[current_index].subjects[8].name="Web Development (2 Cr)";
                        records[current_index].subjects[8].credit_hours=2;
                        records[current_index].subjects[9].name="Web Development Lab (1 Cr)";
                        records[current_index].subjects[9].credit_hours=1;
                        records[current_index].subjects[10].name="Introduction to Management (2 Cr)";
                        records[current_index].subjects[10].credit_hours=2;
                    }
                    else if(semester_input==6){
                        records[current_index].subject_count=10;
                        records[current_index].subjects[0].name="Compiler Construction (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Compiler Construction Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Parallel & Distributed Computing (2 Cr)";
                        records[current_index].subjects[2].credit_hours=2;
                        records[current_index].subjects[3].name="Parallel & Distributed Computing Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Advanced AI/ML (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Advanced AI/ML Lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Advanced Web Development (2 Cr)";
                        records[current_index].subjects[6].credit_hours=2;
                        records[current_index].subjects[7].name="Advanced Web Development Lab (1 Cr)";
                        records[current_index].subjects[7].credit_hours=1;
                        records[current_index].subjects[8].name="Cloud Computing (2 Cr)";
                        records[current_index].subjects[8].credit_hours=2;
                        records[current_index].subjects[9].name="Cloud Computing Lab (1 Cr)";
                        records[current_index].subjects[9].credit_hours=1;
                    }
                    else if(semester_input==7){
                        records[current_index].subject_count=7;
                        records[current_index].subjects[0].name="Final Year Project - I (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Analysis of Algorithms (3 Cr)";
                        records[current_index].subjects[1].credit_hours=3;
                        records[current_index].subjects[2].name="Technical & Business Writing (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Entrepreneurship (2 Cr)";
                        records[current_index].subjects[3].credit_hours=2;
                        records[current_index].subjects[4].name="Cyber Security (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Cyber Security Lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Introduction to Marketing (3 Cr)";
                        records[current_index].subjects[6].credit_hours=3;
                    }
                    else if(semester_input==8){
                        records[current_index].subject_count=4;
                        records[current_index].subjects[0].name="Final Year Project - II (4 Cr)";
                        records[current_index].subjects[0].credit_hours=4;
                        records[current_index].subjects[1].name="Ideology and Constitution of Pakistan (2 Cr)";
                        records[current_index].subjects[1].credit_hours=2;
                        records[current_index].subjects[2].name="Professional Practices (2 Cr)";
                        records[current_index].subjects[2].credit_hours=2;
                        records[current_index].subjects[3].name="Civics and Community Engagement (2 Cr)";
                        records[current_index].subjects[3].credit_hours=2;
                    }
                }
                else{ // BS Software Engineering
                    if(semester_input==1){
                        records[current_index].subject_count=7;
                        records[current_index].subjects[0].name="Programming Fundamentals (3 Cr)";
                        records[current_index].subjects[0].credit_hours=3;
                        records[current_index].subjects[1].name="Calculus and Analytical Geometry (3 Cr)";
                        records[current_index].subjects[1].credit_hours=3;
                        records[current_index].subjects[2].name="Functional English (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Discrete Structures (3 Cr)";
                        records[current_index].subjects[3].credit_hours=3;
                        records[current_index].subjects[4].name="ICT (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="ICT LAB (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="PF LAB (1 Cr)";
                        records[current_index].subjects[6].credit_hours=1;
                    }
                    else if(semester_input==2){
                        records[current_index].subject_count=8;
                        records[current_index].subjects[0].name="Database Systems (3 Cr)";
                        records[current_index].subjects[0].credit_hours=3;
                        records[current_index].subjects[1].name="Database Systems Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Object Oriented Programming (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Object Oriented Programming Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Digital Logic Design (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Digital Logic Design lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Multivariable Calculus (3 Cr)";
                        records[current_index].subjects[6].credit_hours=3;
                        records[current_index].subjects[7].name="Linear Algebra (3 Cr)";
                        records[current_index].subjects[7].credit_hours=3;
                    }
                    else if(semester_input==3){
                        records[current_index].subject_count=10;
                        records[current_index].subjects[0].name="Artificial Intelligence (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Artificial Intelligence Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Data Structures (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Data Structures Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Information Security (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Information Security Lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Computer Networks (2 Cr)";
                        records[current_index].subjects[6].credit_hours=2;
                        records[current_index].subjects[7].name="Computer Networks Lab (1 Cr)";
                        records[current_index].subjects[7].credit_hours=1;
                        records[current_index].subjects[8].name="Software Engineering (3 Cr)";
                        records[current_index].subjects[8].credit_hours=3;
                        records[current_index].subjects[9].name="Probability & statistics (3 Cr)";
                        records[current_index].subjects[9].credit_hours=3;
                    }
                    else if(semester_input==4){
                        records[current_index].subject_count=9;
                        records[current_index].subjects[0].name="Computer Organization and Assembly Language (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Computer Organization and Assembly Language Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Theory of Automata (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Software Construction and Development (2 Cr)";
                        records[current_index].subjects[3].credit_hours=2;
                        records[current_index].subjects[4].name="Software Construction and Development (1 Cr)";
                        records[current_index].subjects[4].credit_hours=1;
                        records[current_index].subjects[5].name="Applied Physics (2 Cr)";
                        records[current_index].subjects[5].credit_hours=2;
                        records[current_index].subjects[6].name="Applied Physics Lab (1 Cr)";
                        records[current_index].subjects[6].credit_hours=1;
                        records[current_index].subjects[7].name="Expository writing (3 Cr)";
                        records[current_index].subjects[7].credit_hours=3;
                        records[current_index].subjects[8].name="Islamic Studies (2 Cr)";
                        records[current_index].subjects[8].credit_hours=2;
                    }
                    else if(semester_input==5){
                        records[current_index].subject_count=11;
                        records[current_index].subjects[0].name="Operating Systems (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Operating Systems Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Software Quality Engineering (2 Cr)";
                        records[current_index].subjects[2].credit_hours=2;
                        records[current_index].subjects[3].name="Software Quality Engineering Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Software Requirement Engineering (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Software Requirement Engineering Lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="AI/ML (2 Cr)";
                        records[current_index].subjects[6].credit_hours=2;
                        records[current_index].subjects[7].name="AI/ML Lab (1 Cr)";
                        records[current_index].subjects[7].credit_hours=1;
                        records[current_index].subjects[8].name="Web Development (2 Cr)";
                        records[current_index].subjects[8].credit_hours=2;
                        records[current_index].subjects[9].name="Web Development Lab (1 Cr)";
                        records[current_index].subjects[9].credit_hours=1;
                        records[current_index].subjects[10].name="Introduction to Management (2 Cr)";
                        records[current_index].subjects[10].credit_hours=2;
                    }
                    else if(semester_input==6){
                        records[current_index].subject_count=10;
                        records[current_index].subjects[0].name="Software Project Management (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Software Project Management Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Parallel & Distributed Computing (2 Cr)";
                        records[current_index].subjects[2].credit_hours=2;
                        records[current_index].subjects[3].name="Parallel & Distributed Computing Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Advanced AI/ML (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Advanced AI/ML Lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Advanced Web Development (2 Cr)";
                        records[current_index].subjects[6].credit_hours=2;
                        records[current_index].subjects[7].name="Advanced Web Development Lab (1 Cr)";
                        records[current_index].subjects[7].credit_hours=1;
                        records[current_index].subjects[8].name="Cloud Computing (2 Cr)";
                        records[current_index].subjects[8].credit_hours=2;
                        records[current_index].subjects[9].name="Cloud Computing Lab (1 Cr)";
                        records[current_index].subjects[9].credit_hours=1;
                    }
                    else if(semester_input==7){
                        records[current_index].subject_count=7;
                        records[current_index].subjects[0].name="Final Year Project - I (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Analysis of Algorithms (3 Cr)";
                        records[current_index].subjects[1].credit_hours=3;
                        records[current_index].subjects[2].name="Technical & Business Writing (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Entrepreneurship (2 Cr)";
                        records[current_index].subjects[3].credit_hours=2;
                        records[current_index].subjects[4].name="Cyber Security (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Cyber Security Lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Introduction to Marketing (3 Cr)";
                        records[current_index].subjects[6].credit_hours=3;
                    }
                    else if(semester_input==8){
                        records[current_index].subject_count=4;
                        records[current_index].subjects[0].name="Final Year Project - II (4 Cr)";
                        records[current_index].subjects[0].credit_hours=4;
                        records[current_index].subjects[1].name="Ideology and Constitution of Pakistan (2 Cr)";
                        records[current_index].subjects[1].credit_hours=2;
                        records[current_index].subjects[2].name="Professional Practices (2 Cr)";
                        records[current_index].subjects[2].credit_hours=2;
                        records[current_index].subjects[3].name="Civics and Community Engagement (2 Cr)";
                        records[current_index].subjects[3].credit_hours=2;
                    }
                }
            }
            else{ // Engineering Department
                if(program_choice==1){ 
                    // BS Civil Engineering
                    if(semester_input==1){
                        records[current_index].subject_count=10;
                        records[current_index].subjects[0].name="Civil Engineering Materials (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Civil Engineering Materials Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Engineering Mechanics (2 Cr)";
                        records[current_index].subjects[2].credit_hours=2;
                        records[current_index].subjects[3].name="Engineering Mechanics Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Engineering Drawing Lab (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Quantitative Reasoning - I (3 Cr)";
                        records[current_index].subjects[5].credit_hours=3;
                        records[current_index].subjects[6].name="Applied Physics and Electro-Mechanical Fundamentals (2 Cr)";
                        records[current_index].subjects[6].credit_hours=2;
                        records[current_index].subjects[7].name="Applied Physics and Electro-Mechanical Fundamentals Lab (1 Cr)";
                        records[current_index].subjects[7].credit_hours=1;
                        records[current_index].subjects[8].name="Islamic Studies/Ethics (2 Cr)";
                        records[current_index].subjects[8].credit_hours=2;
                        records[current_index].subjects[9].name="Functional English (2 Cr)";
                        records[current_index].subjects[9].credit_hours=2;
                    }
                    else if(semester_input==2){
                        records[current_index].subject_count=10;
                        records[current_index].subjects[0].name="Engineering Surveying (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Engineering Surveying Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Mechanics of Solids I (2 Cr)";
                        records[current_index].subjects[2].credit_hours=2;
                        records[current_index].subjects[3].name="Mechanics of Solids I Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Geology for Engineers (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Quantitative Reasoning - II (3 Cr)";
                        records[current_index].subjects[5].credit_hours=3;
                        records[current_index].subjects[6].name="Expository Writing (2 Cr)";
                        records[current_index].subjects[6].credit_hours=2;
                        records[current_index].subjects[7].name="Applications of ICT (2 Cr)";
                        records[current_index].subjects[7].credit_hours=2;
                        records[current_index].subjects[8].name="Application of ICT Lab (1 Cr)";
                        records[current_index].subjects[8].credit_hours=1;
                        records[current_index].subjects[9].name="Ideology and Constitution of Pakistan (2 Cr)";
                        records[current_index].subjects[9].credit_hours=2;
                    }
                    else if(semester_input==3){
                        records[current_index].subject_count=10;
                        records[current_index].subjects[0].name="Civil Engineering Drawing and Graphics (1 Cr)";
                        records[current_index].subjects[0].credit_hours=1;
                        records[current_index].subjects[1].name="Civil Engineering Drawing and Graphics Lab (2 Cr)";
                        records[current_index].subjects[1].credit_hours=2;
                        records[current_index].subjects[2].name="Structural Analysis I (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Computer Programming (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Computer Programming lab (1 Cr)";
                        records[current_index].subjects[4].credit_hours=1;
                        records[current_index].subjects[5].name="Advanced Engineering Survey (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Advanced Engineering Survey Lab (1 Cr)";
                        records[current_index].subjects[6].credit_hours=1;
                        records[current_index].subjects[7].name="Mechanics of Solid II (2 Cr)";
                        records[current_index].subjects[7].credit_hours=2;
                        records[current_index].subjects[8].name="Mechanics of Solid II Lab (1 Cr)";
                        records[current_index].subjects[8].credit_hours=1;
                        records[current_index].subjects[9].name="Advanced Calculus (3 Cr)";
                        records[current_index].subjects[9].credit_hours=3;
                    }
                    else if(semester_input==4){
                         records[current_index].subject_count=10;
                        records[current_index].subjects[0].name="Transportation Engineering Fundamentals (1 Cr)";
                        records[current_index].subjects[0].credit_hours=1;
                        records[current_index].subjects[1].name="Fluid Mechanics (2 Cr)";
                        records[current_index].subjects[1].credit_hours=2;
                        records[current_index].subjects[2].name="Fluid Mechanics Lab (1 Cr)";
                        records[current_index].subjects[2].credit_hours=1;
                        records[current_index].subjects[3].name="Soil Mechanics (2 Cr)";
                        records[current_index].subjects[3].credit_hours=2;
                        records[current_index].subjects[4].name="Soil Mechanics Lab (1 Cr)";
                        records[current_index].subjects[4].credit_hours=1;
                        records[current_index].subjects[5].name="Reinforced Concrete Design I (3 Cr)";
                        records[current_index].subjects[5].credit_hours=3;
                        records[current_index].subjects[6].name="Reinforced Concrete Design I Lab (1 Cr)";
                        records[current_index].subjects[6].credit_hours=1;
                        records[current_index].subjects[7].name="Structural Analysis II (3 Cr)";
                        records[current_index].subjects[7].credit_hours=3;
                        records[current_index].subjects[8].name="Applied Mathematics (3 Cr)";
                        records[current_index].subjects[8].credit_hours=3;
                        records[current_index].subjects[9].name="Translation of The Holy Quran (1 Cr)";
                        records[current_index].subjects[9].credit_hours=1;
                    }
                    else if(semester_input==5){
                        records[current_index].subject_count=11;
                        records[current_index].subjects[0].name="Artificial Intelligence and Machine Learning Lab (1 Cr)";
                        records[current_index].subjects[0].credit_hours=1;
                        records[current_index].subjects[1].name="Advanced Fluid Mechanics (3 Cr)";
                        records[current_index].subjects[1].credit_hours=3;
                        records[current_index].subjects[2].name="Advanced Fluid Mechanics Lab (1 Cr)";
                        records[current_index].subjects[2].credit_hours=1;
                        records[current_index].subjects[3].name="Highway and Traffic Engineering (3 Cr)";
                        records[current_index].subjects[3].credit_hours=3;
                        records[current_index].subjects[4].name="Geotechnical Engineering (3 Cr)";
                        records[current_index].subjects[4].credit_hours=3;
                        records[current_index].subjects[5].name="Geotechnical Engineering Lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Reinforced Concrete Design II (3 Cr)";
                        records[current_index].subjects[6].credit_hours=3;
                        records[current_index].subjects[7].name="Reinforced Concrete Design II Lab (1 Cr)";
                        records[current_index].subjects[7].credit_hours=1;
                        records[current_index].subjects[8].name="Numerical Analysis (2 Cr)";
                        records[current_index].subjects[8].credit_hours=2;
                        records[current_index].subjects[9].name="Numerical Analysis Lab (1 Cr)";
                        records[current_index].subjects[9].credit_hours=1;
                        records[current_index].subjects[10].name="Civics and Community Engagement (2 Cr)";
                        records[current_index].subjects[10].credit_hours=2;
                    }
                    else if(semester_input==6){
                        records[current_index].subject_count=11;
                        records[current_index].subjects[0].name="Occupational Health and Safety (1 Cr)";
                        records[current_index].subjects[0].credit_hours=1;
                        records[current_index].subjects[1].name="Environmental Engineering (3 Cr)";
                        records[current_index].subjects[1].credit_hours=3;
                        records[current_index].subjects[2].name="Environmental Engineering Lab (1 Cr)";
                        records[current_index].subjects[2].credit_hours=1;
                        records[current_index].subjects[3].name="Quantity & Cost Estimation (3 Cr)";
                        records[current_index].subjects[3].credit_hours=3;
                        records[current_index].subjects[4].name="Quantity & Cost Estimation Lab (1 Cr)";
                        records[current_index].subjects[4].credit_hours=1;
                        records[current_index].subjects[5].name="Engineering Hydrology (3 Cr)";
                        records[current_index].subjects[5].credit_hours=3;
                        records[current_index].subjects[6].name="Engineering Hydrology Lab (1 Cr)";
                        records[current_index].subjects[6].credit_hours=1;
                        records[current_index].subjects[7].name="Modelling & Simulation (1 Cr)";
                        records[current_index].subjects[7].credit_hours=1;
                        records[current_index].subjects[8].name="Modelling & Simulation Lab (1 Cr)";
                        records[current_index].subjects[8].credit_hours=1;
                        records[current_index].subjects[9].name="Pavement Analysis and Design (3 Cr)";
                        records[current_index].subjects[9].credit_hours=3;
                        records[current_index].subjects[10].name="Construction Project Management (2 Cr)";
                        records[current_index].subjects[10].credit_hours=2;
                    }
                    else if(semester_input==7){
                        records[current_index].subject_count=9;
                        records[current_index].subjects[0].name="Construction Engineering (3 Cr)";
                        records[current_index].subjects[0].credit_hours=3;
                        records[current_index].subjects[1].name="Geo Informatics Engineering (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Geo Informatics Engineering Lab (1 Cr)";
                        records[current_index].subjects[2].credit_hours=1;
                        records[current_index].subjects[3].name="Steel Structures (3 Cr)";
                        records[current_index].subjects[3].credit_hours=3;
                        records[current_index].subjects[4].name="Hydraulics Engineering (3 Cr)";
                        records[current_index].subjects[4].credit_hours=3;
                        records[current_index].subjects[5].name="Hydraulics Engineering Lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Foundation Engineering (3 Cr)";
                        records[current_index].subjects[6].credit_hours=3;
                        records[current_index].subjects[7].name="Capstone Project I (3 Cr)";
                        records[current_index].subjects[7].credit_hours=3;
                        records[current_index].subjects[8].name="Engineering Economics and Financial Management (2 Cr)";
                        records[current_index].subjects[8].credit_hours=2;
                    }
                    else if(semester_input==8){
                        records[current_index].subject_count=8;
                        records[current_index].subjects[0].name="Architecture and Town Planning (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Building Information Modelling Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Irrigation Engineering (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Irrigation Engineering Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Earthquake Engineering (1 Cr)";
                        records[current_index].subjects[4].credit_hours=1;
                        records[current_index].subjects[5].name="Earthquake Engineering Lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Capstone Project II (3 Cr)";
                        records[current_index].subjects[6].credit_hours=3;
                        records[current_index].subjects[7].name="Entrepreneurship (2 Cr)";
                        records[current_index].subjects[7].credit_hours=2;
                    }
                }
                else{ // BS Mechanical Engineering
                     if(semester_input==1){
                        records[current_index].subject_count=10;
                        records[current_index].subjects[0].name="Islamic Studies / Ethics (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Calculus and Analytical Geometry (3 Cr)";
                        records[current_index].subjects[1].credit_hours=3;
                        records[current_index].subjects[2].name="Functional English (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Applied Physics (2 Cr)";
                        records[current_index].subjects[3].credit_hours=2;
                        records[current_index].subjects[4].name="Applied Chemistry (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Application of ICT (2 Cr)";
                        records[current_index].subjects[5].credit_hours=2;
                        records[current_index].subjects[6].name="Application of ICT Lab (1 Cr)";
                        records[current_index].subjects[6].credit_hours=1;
                        records[current_index].subjects[7].name="WorkShop Practice - I (1 Cr)";
                        records[current_index].subjects[7].credit_hours=1;
                        records[current_index].subjects[8].name="Engineering Drawings and Graphics (1 Cr)";
                        records[current_index].subjects[8].credit_hours=1;
                        records[current_index].subjects[9].name="Engineering Drawings and Graphics Lab (1 Cr)";
                        records[current_index].subjects[9].credit_hours=1;
                    }
                    else if(semester_input==2){
                        records[current_index].subject_count=9;
                        records[current_index].subjects[0].name="Linear Algebra & Differential Equations (3 Cr)";
                        records[current_index].subjects[0].credit_hours=3;
                        records[current_index].subjects[1].name="Translation of The Holy Quran/ Becoming Humane (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Ideology and Constitution of Pakistan (2 Cr)";
                        records[current_index].subjects[2].credit_hours=2;
                        records[current_index].subjects[3].name="Arts & Humanities Elective (2 Cr)";
                        records[current_index].subjects[3].credit_hours=2;
                        records[current_index].subjects[4].name="Thermodynamics-I (3 Cr)";
                        records[current_index].subjects[4].credit_hours=3;
                        records[current_index].subjects[5].name="Workshop Practice-II (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Computer Aided Drawing (1 Cr)";
                        records[current_index].subjects[6].credit_hours=1;
                        records[current_index].subjects[7].name="Engineering Mechanics-I (Statics) (2 Cr)";
                        records[current_index].subjects[7].credit_hours=2;
                        records[current_index].subjects[8].name="Materials Engineering (2 Cr)";
                        records[current_index].subjects[8].credit_hours=2;

                    }
                    else if(semester_input==3){
                        records[current_index].subject_count=8;
                        records[current_index].subjects[0].name="Complex Variables & Transforms (3 Cr)";
                        records[current_index].subjects[0].credit_hours=3;
                        records[current_index].subjects[1].name="Thermodynamics-II (3 Cr)";
                        records[current_index].subjects[1].credit_hours=3;
                        records[current_index].subjects[2].name="Thermodynamics Lab (1 Cr)";
                        records[current_index].subjects[2].credit_hours=1;
                        records[current_index].subjects[3].name="Fluid Mechanics-I (3 Cr)";
                        records[current_index].subjects[3].credit_hours=3;
                        records[current_index].subjects[4].name="Mechanics of Materials-I (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Engineering Mechanics-II (Dynamics) (3 Cr)";
                        records[current_index].subjects[5].credit_hours=3;
                        records[current_index].subjects[6].name="Engineering Mechanics Lab (1 Cr)";
                        records[current_index].subjects[6].credit_hours=1;
                        records[current_index].subjects[7].name="Electrical Engineering (2 Cr)";
                        records[current_index].subjects[7].credit_hours=2;
                    }
                    else if(semester_input==4){
                        records[current_index].subject_count=10;
                        records[current_index].subjects[0].name="Fluid Mechanics-II (3 Cr)";
                        records[current_index].subjects[0].credit_hours=3;
                        records[current_index].subjects[1].name="Fluid Mechanics Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Mechanics of Materials-II (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Mechanics of Materials Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Machine Design-I (2 Cr)";
                        records[current_index].subjects[4].credit_hours=2;
                        records[current_index].subjects[5].name="Measurement & Instrumentation (2 Cr)";
                        records[current_index].subjects[5].credit_hours=2;
                        records[current_index].subjects[6].name="Electronics Engineering (2 Cr)";
                        records[current_index].subjects[6].credit_hours=2;
                        records[current_index].subjects[7].name="Electrical & Electronics Engineering Lab (1 Cr)";
                        records[current_index].subjects[7].credit_hours=1;
                        records[current_index].subjects[8].name="Computer Systems and Programming (2 Cr)";
                        records[current_index].subjects[8].credit_hours=2;
                        records[current_index].subjects[9].name="Computer Systems and Programming Lab (1 Cr)";
                        records[current_index].subjects[9].credit_hours=1;
                    }
                    else if(semester_input==5){
                        records[current_index].subject_count=9;
                        records[current_index].subjects[0].name="Numerical Analysis (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Numerical Analysis Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Expository Writing (2 Cr)";
                        records[current_index].subjects[2].credit_hours=2;
                        records[current_index].subjects[3].name="Expository Writing Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Heat & Mass Transfer (3 Cr)";
                        records[current_index].subjects[4].credit_hours=3;
                        records[current_index].subjects[5].name="Machine Design-II (3 Cr)";
                        records[current_index].subjects[5].credit_hours=3;
                        records[current_index].subjects[6].name="Mechanics of Machines (3 Cr)";
                        records[current_index].subjects[6].credit_hours=3;
                        records[current_index].subjects[7].name="Control Engineering (3 Cr)";
                        records[current_index].subjects[7].credit_hours=3;
                        records[current_index].subjects[8].name="Control & MI Lab (1 Cr)";
                        records[current_index].subjects[8].credit_hours=1;
                    }
                    else if(semester_input==6){
                        records[current_index].subject_count=10;
                        records[current_index].subjects[0].name="Probability and Stochastic (3 Cr)";
                        records[current_index].subjects[0].credit_hours=3;
                        records[current_index].subjects[1].name="Civics and Community Engagement (2 Cr)";
                        records[current_index].subjects[1].credit_hours=2;
                        records[current_index].subjects[2].name="Social Sciences Elective (2 Cr)";
                        records[current_index].subjects[2].credit_hours=2;
                        records[current_index].subjects[3].name="Engineering Project Management (2 Cr)";
                        records[current_index].subjects[3].credit_hours=2;
                        records[current_index].subjects[4].name="Manufacturing Processes (3 Cr)";
                        records[current_index].subjects[4].credit_hours=3;
                        records[current_index].subjects[5].name="Manufacturing Processes Lab (1 Cr)";
                        records[current_index].subjects[5].credit_hours=1;
                        records[current_index].subjects[6].name="Reverse Engineering and Inspection Techniques (3 Cr)";
                        records[current_index].subjects[6].credit_hours=3;
                        records[current_index].subjects[7].name="Reverse Engineering and Inspection Techniques Lab (1 Cr)";
                        records[current_index].subjects[7].credit_hours=1;
                        records[current_index].subjects[8].name="Applied Artificial Intelligence & Machine Learning (3 Cr)";
                        records[current_index].subjects[8].credit_hours=3;
                        records[current_index].subjects[9].name="Applied AI & ML Lab (1 Cr)";
                        records[current_index].subjects[9].credit_hours=1;
                    }
                    else if(semester_input==7){
                        records[current_index].subject_count=8;
                        records[current_index].subjects[0].name="Refrigeration & Air Conditioning (3 Cr)";
                        records[current_index].subjects[0].credit_hours=3;
                        records[current_index].subjects[1].name="RAC & HMT Lab (1 Cr)";
                        records[current_index].subjects[1].credit_hours=1;
                        records[current_index].subjects[2].name="Finite Element Methods (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Finite Element Methods Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Final Year Design Project-I (3 Cr)";
                        records[current_index].subjects[4].credit_hours=3;
                        records[current_index].subjects[5].name="Mechanical Vibrations (3 Cr)";
                        records[current_index].subjects[5].credit_hours=3;
                        records[current_index].subjects[6].name="Mechanisms & Mechanical Vibrations Lab (1 Cr)";
                        records[current_index].subjects[6].credit_hours=1;
                        records[current_index].subjects[7].name="Technical Elective-I (3 Cr)";
                        records[current_index].subjects[7].credit_hours=3;
                    }
                    else if(semester_input==8){
                        records[current_index].subject_count=7;
                        records[current_index].subjects[0].name="Entrepreneurship (2 Cr)";
                        records[current_index].subjects[0].credit_hours=2;
                        records[current_index].subjects[1].name="Renewable Energy Technology (3 Cr)";
                        records[current_index].subjects[1].credit_hours=3;
                        records[current_index].subjects[2].name="Internal Combustion Engines (3 Cr)";
                        records[current_index].subjects[2].credit_hours=3;
                        records[current_index].subjects[3].name="Internal Combustion Engines Lab (1 Cr)";
                        records[current_index].subjects[3].credit_hours=1;
                        records[current_index].subjects[4].name="Final Year Design Project-II (3 Cr)";
                        records[current_index].subjects[4].credit_hours=3;
                        records[current_index].subjects[5].name="Technical Elective-II (3 Cr)";
                        records[current_index].subjects[5].credit_hours=3;
                        records[current_index].subjects[6].name="Occupational Health & Safety (1 Cr)";
                        records[current_index].subjects[6].credit_hours=1;
                    }
                }
            }
        }
        else{ // MS Programs (3 semesters)
            if(program_choice==1){ // MS Computer Science
                if(semester_input==1){
                    records[current_index].subject_count=4;
                    records[current_index].subjects[0].name="Deep Learning (3 Cr)";
                    records[current_index].subjects[0].credit_hours=3;
                    records[current_index].subjects[1].name="Natural Language Processing (3 Cr)";
                    records[current_index].subjects[1].credit_hours=3;
                    records[current_index].subjects[2].name="Pattern Recognition (3 Cr)";
                    records[current_index].subjects[2].credit_hours=3;
                    records[current_index].subjects[3].name="Research Methodology (Audit)";
                    records[current_index].subjects[3].credit_hours=0;
                }
                else if(semester_input==2){
                    records[current_index].subject_count=4;
                    records[current_index].subjects[0].name="Advanced Cloud Computing (3 Cr)";
                    records[current_index].subjects[0].credit_hours=3;
                    records[current_index].subjects[1].name="Distributed Systems (3 Cr)";
                    records[current_index].subjects[1].credit_hours=3;
                    records[current_index].subjects[2].name="Containerization & Microservices (3 Cr)";
                    records[current_index].subjects[2].credit_hours=3;
                    records[current_index].subjects[3].name="Serverless Architecture (3 Cr)";
                    records[current_index].subjects[3].credit_hours=3;
                }
                else if(semester_input==3){
                    records[current_index].subject_count=2;
                    records[current_index].subjects[0].name="Cryptography (3 Cr)";
                    records[current_index].subjects[0].credit_hours=3;
                    records[current_index].subjects[1].name="Research Thesis (6 Cr)";
                    records[current_index].subjects[1].credit_hours=6;
                }
            }
            else{ // MS Civil Engineering
                if(semester_input==1){
                    records[current_index].subject_count=4;
                    records[current_index].subjects[0].name="Advanced Structural Analysis (3 Cr)";
                    records[current_index].subjects[0].credit_hours=3;
                    records[current_index].subjects[1].name="Advanced Reinforced Concrete (3 Cr)";
                    records[current_index].subjects[1].credit_hours=3;
                    records[current_index].subjects[2].name="Properties of Structural Materials (3 Cr)";
                    records[current_index].subjects[2].credit_hours=3;
                    records[current_index].subjects[3].name="Research Methodology (Audit)";
                    records[current_index].subjects[3].credit_hours=0;
                }
                else if(semester_input==2){
                    records[current_index].subject_count=4;
                    records[current_index].subjects[0].name="Bridge Engineering (3 Cr)";
                    records[current_index].subjects[0].credit_hours=3;
                    records[current_index].subjects[1].name="Structural Dynamics (3 Cr)";
                    records[current_index].subjects[1].credit_hours=3;
                    records[current_index].subjects[2].name="Advanced Steel Structures (3 Cr)";
                    records[current_index].subjects[2].credit_hours=3;
                    records[current_index].subjects[3].name="Finite Element Method (3 Cr)";
                    records[current_index].subjects[3].credit_hours=3;
                }
                else if(semester_input==3){
                    records[current_index].subject_count=2;
                    records[current_index].subjects[0].name="Advanced Solid Mechanics (3 Cr)";
                    records[current_index].subjects[0].credit_hours=3;
                    records[current_index].subjects[1].name="Research Thesis (6 Cr)";
                    records[current_index].subjects[1].credit_hours=6;
                }
            }
        }

        for(int i=0;i<records[current_index].subject_count;i++)
        {
            records[current_index].subjects[i].max_marks=100;
            records[current_index].subjects[i].quiz_marks=0;
            records[current_index].subjects[i].assignment_marks=0;
            records[current_index].subjects[i].mid_marks=0;
            records[current_index].subjects[i].final_marks=0;
            records[current_index].subjects[i].pbl_marks=0;
        }
    }
    // Enrollment Summary
    student_count++;
    cout<<"\n=============================================\n";
    cout<<"Enrollment Complete!\n";
    cout<<"Student Name: "<<records[current_index].name<<"\n";
    cout<<"Roll Number: "<<records[current_index].roll_number<<endl;
    cout<<"Total Enrolled Students: "<<student_count<<endl;
    cout<<"=============================================\n";
    cout<<"Press Enter to continue...";
    cin.ignore();
    cin.get();
}
// Function to enter marks for a student
void EnterStudentMarks()
{
    cout<<"\n================= Enter Student Marks ===================\n";

    if(student_count==0)
    {
        cout<<"ERROR: No Students Enrolled yet. Please use Option 1 first.\n";
        cout<<"Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    int target_roll;
    cout<<"Enter Student Roll number to enter marks for: ";

    if(!(cin>>target_roll))
    {
        cout<<"ERROR: Invalid input for Roll Number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        return;
    }

    int target_index=findStudentIndex(target_roll);

    if(target_index==-1)
    {
        cout<<"ERROR: Student Not Found with Roll Number "<<target_roll<<".\n";
        cout<<"Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    Student& s=records[target_index];

    cout<<"\n--- Student Found: "<<s.name<<" ---\n";

    if(s.current_class>=1 && s.current_class<=12)
    {
        cout<<"Class: "<<s.current_class<<" ("<<s.group_stream<<")\n";
    }
    else
    {
        cout<<"University: "<<s.group_stream<<" (Semester "<<s.current_semester<<")\n";
    }
    // Confirm overwrite if marks already entered
    if(s.marks_entered)
    {
        char confirm;
        cout<<"WARNING: Marks are already entered for this student. Overwrite? (Y/N): ";
        cin>>confirm;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        if(confirm=='N'||confirm=='n')
        {
            cout<<"Marks entry Cancelled.\n";
            cout<<"Press Enter to continue...";
            cin.get();
            return;
        }
    }

    s.marks_entered=false;
    s.result_calculated=false;
    // Marks Entry
    if(s.current_class>=1 && s.current_class<=12)
    {
        cout<<"\n--- School/College Marks Entry ---\n";

        for(int i=0; i<s.subject_count; i++)
        {
            Subject& subj=s.subjects[i];
            cout<<"\nSubject: "<<subj.name<<" (Max: "<<subj.max_marks<<")\n";

            double marks;
            do{
                cout<<"Enter Obtained Marks (0-"<<subj.max_marks<<"): ";
                if(!(cin>>marks) || marks<0 || marks>subj.max_marks)
                {
                    cout<<"ERROR: Invalid marks. Please enter between 0 and "<<subj.max_marks<<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
                else
                {
                    subj.obtained_marks=marks;
                    break;
                }
            }while(true);

            subj.quiz_marks=subj.assignment_marks=subj.mid_marks=subj.final_marks=subj.pbl_marks=0;
        }
    }
    else if(s.current_class==33)
    {
        cout<<"\n--- University Component Marks Entry ---\n";
        cout<<"Component Weightage: Quiz(10%), Assignment(10%), PBL(10%), Mid(20%), Final(50%)\n";

        for(int i=0; i<s.subject_count; i++)
        {
            Subject& subj=s.subjects[i];
            cout<<"\nSubject: "<<subj.name<<" ("<<subj.credit_hours<<" Credit Hours)\n";

            do{
                cout<<"Enter Quiz Marks (0-10): ";
                if(!(cin>>subj.quiz_marks)||subj.quiz_marks<0||subj.quiz_marks>10){
                    cout<<"ERROR: Invalid marks. Please enter between 0 and 10\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
                else break;
            }while(true);

            do{
                cout<<"Enter Assignment Marks (0-10): ";
                if(!(cin>>subj.assignment_marks)||subj.assignment_marks<0||subj.assignment_marks>10){
                    cout<<"ERROR: Invalid marks. Please enter between 0 and 10\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
                else break;
            }while(true);

            do{
                cout<<"Enter PBL Marks (0-10): ";
                if(!(cin>>subj.pbl_marks)||subj.pbl_marks<0||subj.pbl_marks>10){
                    cout<<"ERROR: Invalid marks. Please enter between 0 and 10\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
                else break;
            }while(true);

            do{
                cout<<"Enter Midterm Marks (0-20): ";
                if(!(cin>>subj.mid_marks)||subj.mid_marks<0||subj.mid_marks>20){
                    cout<<"ERROR: Invalid marks. Please enter between 0 and 20\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
                else break;
            }while(true);

            do{
                cout<<"Enter Final Exam Marks (0-50): ";
                if(!(cin>>subj.final_marks)||subj.final_marks<0||subj.final_marks>50){
                    cout<<"ERROR: Invalid marks. Please enter between 0 and 50\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
                else break;
            }while(true);

            subj.obtained_marks=subj.quiz_marks+subj.assignment_marks+subj.pbl_marks+subj.mid_marks+subj.final_marks;
            subj.max_marks=100;

            cout<<"-> Total marks for "<<subj.name<<": "<<subj.obtained_marks<<"/100\n";
        }
    }

    s.marks_entered=true;
    cout<<"\n✅ Marks entry for "<<s.name<<" completed successfully.\n";
    cout<<"Now, use Option 3 to calculate the result.\n";
    cout<<"Press Enter to continue...";
    cin.ignore();
    cin.get();
}
// Function to convert marks percentage to grade points
double marksToGradePoints(double percentage)
{
    if(percentage>=85)return 4.0;
    if(percentage>=80)return 3.7;
    if(percentage>=75)return 3.3;
    if(percentage>=70)return 3.0;
    if(percentage>=65)return 2.7;
    if(percentage>=60)return 2.3;
    if(percentage>=55)return 2.0;
    if(percentage>=50)return 1.7;
    if(percentage>=45)return 1.3;
    if(percentage>=40)return 1.0;
    return 0.0;
}
// Function to get grade letter based on percentage
string getGradeLetter(double percentage)
{
    if(percentage>=85)return "A+";
    if(percentage>=80)return "A";
    if(percentage>=75)return "B+";
    if(percentage>=70)return "B";
    if(percentage>=65)return "C+";
    if(percentage>=60)return "C";
    if(percentage>=55)return "D+";
    if(percentage>=50)return "D";
    if(percentage>=40)return "E";
    return "F";
}
// Function to get school grade description based on percentage
string getSchoolGrade(double percentage)
{
    if(percentage>=80)return "A+ (Excellent)";
    if(percentage>=70)return "A (Very Good)";
    if(percentage>=60)return "B (Good)";
    if(percentage>=50)return "C (Satisfactory)";
    if(percentage>=40)return "D (Pass)";
    return "F (Fail)";
}
// Function to calculate result for a student
void CalculateResult()
{
    cout<<"\n================= Calculate Student Result ===================\n";

    if(student_count==0)
    {
        cout<<"ERROR: No Students Enrolled yet. Please use Option 1 first.\n";
        cout<<"Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    int target_roll;
    cout<<"Enter Student Roll number to calculate result for: ";
    if(!(cin>>target_roll))
    {
        cout<<"ERROR: Invalid input for Roll Number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        return;
    }

    int target_index=findStudentIndex(target_roll);

    if(target_index==-1)
    {
        cout<<"ERROR: Student Not Found with Roll Number "<<target_roll<<".\n";
        cout<<"Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    Student& s=records[target_index];

    if(!s.marks_entered)
    {
        cout<<"ERROR: Marks have not been entered for this student. Please use Option 2 first.\n";
        cout<<"Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    s.total_obtained=0.0;
    s.total_max_marks=0.0;
    s.final_percentage=0.0;
    s.final_gpa=0.0;
// Calculation Logic
    if(s.current_class>=1&&s.current_class<=12)
    {
        cout<<"Processing result for School/College student...\n";

        for(int i=0;i<s.subject_count;++i)
        {
            s.total_obtained+=s.subjects[i].obtained_marks;
            s.total_max_marks+=s.subjects[i].max_marks;

            double subject_percentage=(s.subjects[i].obtained_marks/s.subjects[i].max_marks)*100;
            s.subjects[i].overall_grade=getGradeLetter(subject_percentage);
        }

        if(s.total_max_marks>0)
        {
            s.final_percentage=(s.total_obtained/s.total_max_marks)*100.0;
            s.overall_grade=getSchoolGrade(s.final_percentage);
        }

        s.final_gpa=marksToGradePoints(s.final_percentage);
    }
    else if(s.current_class==33)
    {
        cout<<"Processing result for University student (GPA system)...\n";

        double total_credit_hours=0.0;
        double weighted_grade_points=0.0;

        for(int i=0;i<s.subject_count;++i)
        {
            Subject& subj=s.subjects[i];
            double subject_percentage=subj.obtained_marks;
            double grade_points=marksToGradePoints(subject_percentage);
            weighted_grade_points+=(grade_points*subj.credit_hours);
            total_credit_hours+=subj.credit_hours;
            s.subjects[i].overall_grade=getGradeLetter(subject_percentage);
            s.total_obtained+=subj.obtained_marks;
            s.total_max_marks+=100.0;
        }

        if(total_credit_hours>0)
        {
            s.final_gpa=weighted_grade_points/total_credit_hours;
            s.final_percentage=(s.total_obtained/s.total_max_marks)*100.0;

            if(s.final_gpa>=3.5)s.overall_grade="Distinction (A+)";
            else if(s.final_gpa>=3.0)s.overall_grade="Excellent (A)";
            else if(s.final_gpa>=2.5)s.overall_grade="Good (B+)";
            else if(s.final_gpa>=2.0)s.overall_grade="Satisfactory (B)";
            else if(s.final_gpa>=1.5)s.overall_grade="Pass (C)";
            else s.overall_grade="Fail (F)";
        }
    }
// Mark result as calculated
    s.result_calculated=true;

    cout<<"\n=========================================\n";
    cout<<"✅ RESULT CALCULATED SUCCESSFULLY!\n";
    if(s.current_class==33){
        cout<<"Final CGPA: "<<fixed<<setprecision(2)<<s.final_gpa<<"/4.0\n";
    }
    else{
        cout<<"Final Percentage: "<<fixed<<setprecision(2)<<s.final_percentage<<"%\n";
    }
    cout<<"Overall Grade: "<<s.overall_grade<<endl;
    cout<<"Use Option 4 (Display Report) to view the full result card.\n";
    cout<<"=========================================\n";
    cout<<"Press Enter to continue...";
    cin.ignore();
    cin.get();
}
// Function to display student report
void DisplayReport()
{
    cout<<"\n================= Display Student Report ===================\n";

    if(student_count==0)
    {
        cout<<"ERROR: No Students Enrolled yet.\n";
        cout<<"Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    int target_roll;
    cout<<"Enter Student Roll number to display report for: ";

    if(!(cin>>target_roll))
    {
        cout<<"ERROR: Invalid input for Roll Number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        return;
    }

    int target_index=findStudentIndex(target_roll);

    if(target_index==-1)
    {
        cout<<"ERROR: Student Not Found with Roll Number "<<target_roll<<".\n";
        cout<<"Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    Student& s=records[target_index];

    if(!s.result_calculated)
    {
        cout<<"ERROR: Result has not been calculated for this student. Please use Option 3 first.\n";
        cout<<"Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }
// Display Report
    cout<<"\n================================================================================\n";
    cout<<"                    STUDENT ACADEMIC REPORT CARD\n";
    cout<<"================================================================================\n";

    cout<<left<<setw(25)<<"Institution:"<<s.college_school_name<<endl;
    cout<<left<<setw(25)<<"Head:"<<s.principal_name<<endl;
    cout<<left<<setw(25)<<"Class Teacher:"<<s.class_teacher_name<<endl;
    cout<<left<<setw(25)<<"Academic Year:"<<"2024-2025"<<endl;

    cout<<"\n";
    cout<<"-----------------------------------------------------------------\n";

    cout<<left<<setw(25)<<"Student Name:"<<s.name<<endl;
    cout<<left<<setw(25)<<"Roll Number:"<<s.roll_number<<endl;

    if(s.current_class==33){
        cout<<left<<setw(25)<<"Program:"<<s.group_stream<<endl;
        cout<<left<<setw(25)<<"Department:"<<s.department_name<<endl;
        cout<<left<<setw(25)<<"Semester:"<<s.current_semester<<endl;
        cout<<left<<setw(25)<<"Degree Level:"<<s.degree_level<<endl;
    }
    else{
        cout<<left<<setw(25)<<"Class:"<<s.current_class<<endl;
        cout<<left<<setw(25)<<"Stream:"<<s.group_stream<<endl;
    }

    cout<<"\n";
    cout<<"================================================================================\n";
    cout<<"                             SUBJECT WISE MARKS\n";
    cout<<"================================================================================\n";

    if(s.current_class>=1&&s.current_class<=12)
    {
        cout<<left<<setw(40)<<"SUBJECT"<<right<<setw(10)<<"MAX"<<right<<setw(10)<<"OBTAINED"<<right<<setw(10)<<"GRADE"<<endl;
        cout<<"-----------------------------------------------------------------\n";

        for(int i=0;i<s.subject_count;++i)
        {
            Subject& subj=s.subjects[i];
            cout<<left<<setw(40)<<subj.name.substr(0,39)<<right<<setw(10)<<subj.max_marks<<right<<setw(10)<<fixed<<setprecision(0)<<subj.obtained_marks<<right<<setw(10)<<subj.overall_grade<<endl;
        }
    }
    else if(s.current_class==33)
    {
        cout<<left<<setw(40)<<"COURSE"<<right<<setw(10)<<"CR.HRS"<<right<<setw(10)<<"MARKS"<<right<<setw(10)<<"GRADE"<<right<<setw(15)<<"COMPONENTS"<<endl;
        cout<<"-----------------------------------------------------------------\n";

        for(int i=0;i<s.subject_count;++i)
        {
            Subject& subj=s.subjects[i];
            string components=" Q:"+to_string((int)subj.quiz_marks)+" A:"+to_string((int)subj.assignment_marks)+" M:"+to_string((int)subj.mid_marks)+" F:"+to_string((int)subj.final_marks);

            cout<<left<<setw(40)<<subj.name.substr(0,39)<<right<<setw(10)<<subj.credit_hours<<right<<setw(10)<<fixed<<setprecision(0)<<subj.obtained_marks<<right<<setw(10)<<subj.overall_grade<<right<<setw(15)<<components<<endl;
        }
    }

    cout<<"\n";
    cout<<"================================================================================\n";
    cout<<"                              FINAL RESULT\n";
    cout<<"================================================================================\n";

    if(s.current_class>=1&&s.current_class<=12)
    {
        cout<<left<<setw(30)<<"Total Marks:"<<right<<setw(10)<<fixed<<setprecision(0)<<s.total_obtained<<" out of "<<s.total_max_marks<<endl;
        cout<<left<<setw(30)<<"Percentage:"<<right<<setw(10)<<fixed<<setprecision(2)<<s.final_percentage<<"%"<<endl;
        cout<<left<<setw(30)<<"Overall Grade:"<<right<<setw(10)<<s.overall_grade<<endl;
        cout<<left<<setw(30)<<"GPA (Approx):"<<right<<setw(10)<<fixed<<setprecision(2)<<s.final_gpa<<"/4.0"<<endl;
    }
    else
    {
        cout<<left<<setw(30)<<"Total Credit Hours:"<<right<<setw(10)<<fixed<<setprecision(1)<<(s.total_max_marks/100.0)<<endl;
        cout<<left<<setw(30)<<"CGPA:"<<right<<setw(10)<<fixed<<setprecision(2)<<s.final_gpa<<"/4.0"<<endl;
        cout<<left<<setw(30)<<"Percentage Equivalent:"<<right<<setw(10)<<fixed<<setprecision(2)<<s.final_percentage<<"%"<<endl;
        cout<<left<<setw(30)<<"Overall Status:"<<right<<setw(10)<<s.overall_grade<<endl;
    }

    cout<<"\n";
    cout<<"================================================================================\n";
    cout<<"Remarks: ";
    if(s.current_class==33){
        if(s.final_gpa>=2.0)cout<<"PASS - Eligible for next semester";
        else cout<<"FAIL - Academic probation";
    }
    else{
        if(s.final_percentage>=40)cout<<"PASS - Promoted to next class";
        else cout<<"FAIL - Must repeat the class";
    }
    cout<<"\n";
    cout<<"================================================================================\n";

    cout<<"\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
// Function to search for a student record
void SearchStudentRecord()
{
    cout<<"\n================= Search Student Record ===================\n";

    if(student_count==0)
    {
        cout<<"ERROR: No Students Enrolled yet.\n";
        cout<<"Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }
// Search Options
    int search_choice;
    cout<<"Search by:\n1. Roll Number\n2. Name\nEnter choice (1-2): ";
    if(!(cin>>search_choice))
    {
        cout<<"ERROR: Please enter correct Choice ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"Please enter to continue...";
        cin.get();
        return;
    }
    cin.ignore();
    if(search_choice==1)
    {
        int target_roll;
        cout<<"Enter Roll Number to search: ";
        cin>>target_roll;

        int index=findStudentIndex(target_roll);
        if(index==-1)
        {
            cout<<"Student not found with Roll Number "<<target_roll<<endl;
        }
        else
        {
            Student& s=records[index];
            cout<<"\n--- STUDENT FOUND ---\n";
            cout<<"Name: "<<s.name<<endl;
            cout<<"Roll No: "<<s.roll_number<<endl;
            if(s.current_class==33){
                cout<<"Program: "<<s.group_stream<<endl;
                cout<<"Semester: "<<s.current_semester<<endl;
            }
            else{
                cout<<"Class: "<<s.current_class<<endl;
                cout<<"Stream: "<<s.group_stream<<endl;
            }
            cout<<"Institution: "<<s.college_school_name<<endl;

            if(s.result_calculated){
                cout<<"\nResult Status: CALCULATED\n";
                if(s.current_class==33){
                    cout<<"CGPA: "<<fixed<<setprecision(2)<<s.final_gpa<<endl;
                }
                else{
                    cout<<"Percentage: "<<fixed<<setprecision(2)<<s.final_percentage<<"%\n";
                }
                cout<<"Grade: "<<s.overall_grade<<endl;
            }
            else{
                cout<<"\nResult Status: NOT CALCULATED\n";
            }

            char choice;
            cout<<"\nView full report? (Y/N): ";
            cin>>choice;
            if(choice=='Y'||choice=='y'){
                DisplayReport();
            }
        }
    }
    else if(search_choice==2)
    {
        string target_name;
        cout<<"Enter Student Name to search: ";
        cin.ignore();
        getline(cin,target_name);

        bool found=false;
        for(int i=0;i<student_count;i++)
        {
            if(records[i].name.find(target_name)!=string::npos)
            {
                found=true;
                Student& s=records[i];
                cout<<"\n--- STUDENT FOUND ---\n";
                cout<<"Name: "<<s.name<<endl;
                cout<<"Roll No: "<<s.roll_number<<endl;
                if(s.current_class==33){
                    cout<<"Program: "<<s.group_stream<<endl;
                }
                else{
                    cout<<"Class: "<<s.current_class<<endl;
                }
                cout<<"Institution: "<<s.college_school_name<<endl;
                cout<<"------------------------\n";
            }
        }

        if(!found){
            cout<<"No student found with name containing: "<<target_name<<endl;
        }
    }
    else
    {
        cout<<"Invalid choice!\n";
    }

    cout<<"\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
// Function to load all student data from file
void loadAllData()
{
    cout<<"\n================= Loading Student Data ===================\n";

    ifstream inFile("student_data.txt");
    if(!inFile.is_open())
    {
        cout<<"INFO: No saved data found. Starting fresh.\n";
        return;
    }
// Clear existing records
    student_count=0;
    string line;
// Read number of saved records
    getline(inFile,line);
    int saved_count=stoi(line); // Number of saved student records

    for(int i=0;i<saved_count && i<MAX_STUDENT;i++)
    {
        Student& s=records[student_count];

        getline(inFile,s.name);
        getline(inFile,line);s.roll_number=stoi(line);
        getline(inFile,line);s.current_class=stoi(line);
        getline(inFile,s.group_stream);
        getline(inFile,s.college_school_name);
        getline(inFile,s.principal_name);
        getline(inFile,s.class_teacher_name);
        getline(inFile,s.department_name);
        getline(inFile,s.degree_level);
        getline(inFile,line);s.current_semester=stoi(line);
        getline(inFile,line);s.subject_count=stoi(line);
        getline(inFile,line);s.marks_entered=(line=="1");
        getline(inFile,line);s.result_calculated=(line=="1");
        getline(inFile,line);s.total_obtained=stod(line);
        getline(inFile,line);s.total_max_marks=stod(line);
        getline(inFile,line);s.final_percentage=stod(line);
        getline(inFile,s.overall_grade);
        getline(inFile,line);s.final_gpa=stod(line);

        for(int j=0;j<s.subject_count;j++)
        {
            getline(inFile,s.subjects[j].name);
            getline(inFile,line);s.subjects[j].max_marks=stoi(line);
            getline(inFile,line);s.subjects[j].obtained_marks=stod(line);
            getline(inFile,line);s.subjects[j].credit_hours=stoi(line);
            getline(inFile,line);s.subjects[j].quiz_marks=stod(line);
            getline(inFile,line);s.subjects[j].assignment_marks=stod(line);
            getline(inFile,line);s.subjects[j].mid_marks=stod(line);
            getline(inFile,line);s.subjects[j].final_marks=stod(line);
            getline(inFile,line);s.subjects[j].pbl_marks=stod(line);
            getline(inFile,s.subjects[j].overall_grade);
        }

        student_count++;
    }
// Close file after loading
    inFile.close();
    cout<<"Loaded "<<student_count<<" student records from file.\n";
    
    // Display all loaded student data
    cout<<"\n================= ALL STUDENT RECORDS ===================\n";
    
    if(student_count==0)
    {
        cout<<"No student records available.\n";
        cout<<"Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout<<"Total Students: "<<student_count<<endl;
    cout<<"\n";
    cout<<left<<setw(10)<<"ROLL NO"<<left<<setw(25)<<"NAME"<<left<<setw(20)<<"CLASS/PROGRAM"<<left<<setw(15)<<"STATUS"<<endl;
    cout<<"----------------------------------------------------------------------------\n";
// Display each student summary
    for(int i=0;i<student_count;i++)
    {
        Student& s=records[i];
        string class_info;
        if(s.current_class==33){
            class_info=s.group_stream;
        }
        else{
            class_info="Class "+to_string(s.current_class);
        }

        string status;
        if(s.result_calculated){
            status="Result Ready";
        }
        else if(s.marks_entered){
            status="Marks Entered";
        }
        else{
            status="Enrolled";
        }

        cout<<left<<setw(10)<<s.roll_number<<left<<setw(25)<<s.name.substr(0,24)<<left<<setw(20)<<class_info.substr(0,19)<<left<<setw(15)<<status<<endl;
    }

    cout<<"\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
// Function to save all student data to file
void saveData()
{
    cout<<"\n================= Saving Student Data ===================\n";

    ofstream outFile("student_data.txt");
    if(!outFile.is_open())
    {
        cout<<"ERROR: Could not create save file.\n";
        return;
    }

    outFile<<student_count<<endl;

    for(int i=0;i<student_count;i++)
    {
        Student& s=records[i];

        outFile<<s.name<<endl;
        outFile<<s.roll_number<<endl;
        outFile<<s.current_class<<endl;
        outFile<<s.group_stream<<endl;
        outFile<<s.college_school_name<<endl;
        outFile<<s.principal_name<<endl;
        outFile<<s.class_teacher_name<<endl;
        outFile<<s.department_name<<endl;
        outFile<<s.degree_level<<endl;
        outFile<<s.current_semester<<endl;
        outFile<<s.subject_count<<endl;
        outFile<<(s.marks_entered?"1":"0")<<endl;
        outFile<<(s.result_calculated?"1":"0")<<endl;
        outFile<<s.total_obtained<<endl;
        outFile<<s.total_max_marks<<endl;
        outFile<<s.final_percentage<<endl;
        outFile<<s.overall_grade<<endl;
        outFile<<s.final_gpa<<endl;

        for(int j=0;j<s.subject_count;j++)
        {
            outFile<<s.subjects[j].name<<endl;
            outFile<<s.subjects[j].max_marks<<endl;
            outFile<<s.subjects[j].obtained_marks<<endl;
            outFile<<s.subjects[j].credit_hours<<endl;
            outFile<<s.subjects[j].quiz_marks<<endl;
            outFile<<s.subjects[j].assignment_marks<<endl;
            outFile<<s.subjects[j].mid_marks<<endl;
            outFile<<s.subjects[j].final_marks<<endl;
            outFile<<s.subjects[j].pbl_marks<<endl;
            outFile<<s.subjects[j].overall_grade<<endl;
        }
    }

    outFile.close();
    cout<<"✅ Saved "<<student_count<<" student records to 'student_data.txt'.\n";
    cout<<"Press Enter to continue...";
    cin.ignore();
    cin.get();
}