#include <iostream>         //standard input/output operations
#include <fstream>          //file input/output operations
#include <sstream>          //string stream operations (used to parse lines)
#include <vector>           //using the vector container to store student data
#include <string>           //using the string class

//struct to hold student data (first name and last name)
struct STUDENT_DATA
{
    std::string firstName;      //first name of the student
    std::string lastName;       //last name of the student
    std::string email;          //email address of the student (only for pre-release)
};

//function to read student data from the file and return a vector of STUDENT_DATA
std::vector<STUDENT_DATA> readStudentData(const std::string& filename, bool isPreRelease = false)
{
    std::ifstream file(filename);       //open the file with the given filename
    std::vector<STUDENT_DATA> students;         //vector to store student data
    std::string line;       //string to hold each line read from the file

    //check if the file was successfully opened
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;          //error message if file cannot be opened
        return students;        //return empty vector if file opening failed
    }

    //loop to read each line from the file
    while (std::getline(file, line))
    {
        std::stringstream ss(line);         //create a string stream to parse the line
        std::string firstName, lastName, email;

        //split the line by the comma (the file contains "firstName, lastName" for standard and "firstName, lastName, email" for pre-release)
        if (std::getline(ss, firstName, ',') && std::getline(ss, lastName, ','))
        {
            if (isPreRelease && std::getline(ss, email, ','))
            {
                students.push_back({ firstName, lastName, email });    //add student with email for pre-release
            }
            else
            {
                students.push_back({ firstName, lastName, "" });    //add student without email for standard version
            }
        }
    }

    file.close();           //close the file after reading all the data
    return students;    //return the vector of students
}


int main()
{
    std::string studentDataFile = "StudentData.txt";            //the file for standard version
    std::string emailDataFile = "StudentData_Emails.txt";       //the file for pre-release email data

    //print whether the app is running in standard or pre-release mode
    #ifdef PRE_RELEASE
        std::cout << "Running in Pre-Release mode" << std::endl;
        std::vector<STUDENT_DATA> students = readStudentData(emailDataFile, true);
    #else
        std::cout << "Running in Standard mode" << std::endl;
        std::vector<STUDENT_DATA> students = readStudentData(studentDataFile, false);
    #endif

    //display loaded students (debug mode only)
    if (!students.empty())
    {
        std::cout << "Total students loaded: " << students.size() << std::endl;

        #ifdef _DEBUG
            std::cout << "\nPrinting the student data (using DEBUG mode):\n" << std::endl;
            for (const auto& student : students)
            {
                std::cout << "First Name: " << student.firstName << ", Last Name: " << student.lastName;
                if (!student.email.empty())
                {
                    std::cout << ", Email: " << student.email;
                }
                std::cout << std::endl;
                std::cout << "-----------------------------------" << std::endl;
            }
        #endif
    }
    else
    {
        std::cout << "No students were loaded." << std::endl;       //print a message if no students were loaded
    }

    return 1;
}
