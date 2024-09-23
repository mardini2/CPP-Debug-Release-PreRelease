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
};

//function to read student data from the file and return a vector of STUDENT_DATA
std::vector<STUDENT_DATA> readStudentData(const std::string& filename)
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
        std::string firstName, lastName;        //variables to hold first name and last name

        //split the line by the comma (the file contains "firstName, lastName")
        if (std::getline(ss, firstName, ',') && std::getline(ss, lastName, ','))
        {
            students.push_back({ firstName, lastName });    //add the parsed student data to the vector
        }
    }

    file.close();           //close the file after reading all the data
    return students;    //return the vector of students
}


int main()
{
    std::string filename = "StudentData.txt";          //the name of the file containing student data

    //read student data from the file and store it in a vector
    std::vector<STUDENT_DATA> students = readStudentData(filename);

    //check if any students were loaded and print the number of students
    if (!students.empty())
    {
        std::cout << "Total students loaded: " << students.size() << std::endl;
    }
    else
    {
        std::cout << "No students were loaded." << std::endl;       //print a message if no students were loaded
    }

    return 1;           //end of program, returning 1 as required by the instructions
}
