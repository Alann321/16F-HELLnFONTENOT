
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <cstring>
#include "Ltring.h"

using namespace std;

void iterateDirectory(char*);
void dirVisit(dirent*);

//Commented out to prevent multiple main

int main(int argc, char* argv[])
{
    iterateDirectory(argv[1]);

    return 0;
}

//check if the file type is of certain type (c/c++ extensions)
bool extensionCheck(dirent* entry)
{
    Lstring fileName = entry->d_name;
    if(fileName.substr(fileName.length()-4, fileName.length()) == ".cpp")
        return true;

    else if(fileName.substr(fileName.length()-4, fileName.length()) == ".hpp")
        return true;

    else if(fileName.substr(fileName.length()-2, fileName.length()) == ".h")
        return true;

    else if(fileName.substr(fileName.length()-2, fileName.length()) == ".c")
        return true;

    else
        return false;
}

//Utility function for iterator.
void dirVisit(dirent* entry)
{
    char abs[200];

    cout<<"File: "<< entry->d_name <<endl;

    //buffer string for reading in the opened file
    std::string buffer;
    realpath(entry->d_name, abs);

    cout<<"Abs_File: "<<abs<<endl;

    //open each file in the directory
    ifstream fin(abs);

    //Get sample from a file
    if(fin.is_open())
    {
        cout<<"File opened."<<endl;
//        while(getline(fin, buffer))
//        {
//            cout<<buffer<<endl;
//        }
    }
    else
    {
        cout<<"The file was not opened. Please check the file name again."<<endl;
    }

    fin.close();
}

//File iterator using dirent.h
void iterateDirectory(char* filePath)
{
    //create a DIR*, the pointer to directory
    DIR* dirPtr = nullptr;

    //struct dirent* for readdir()
    dirent* dirEntry = nullptr;

    //char* for absolute path
    char abs[200];

    //open directory from input (command line argument)
    dirPtr = opendir(filePath);

    //check if the directory was open correctly.
    if(dirPtr == nullptr)
    {
        cout<<"The directory was not opened correctly. Please check the directory name."<<endl;
        exit(1);
    }

    //read directory
    while((dirEntry = readdir(dirPtr)))
    {
        //if the entry is another directory
        if(dirEntry->d_type == DT_DIR)
        {
            //make sure the directory is not itself or parent directory
            if((strcmp(dirEntry->d_name, ".") != 0) && (strcmp(dirEntry->d_name, "..") != 0))
            {
                cout<<"Directory: "<<dirEntry->d_name<<endl;
                //recursively go down to the subdirectory
                realpath(dirEntry->d_name, abs);
                cout<<"Abs_Dir: "<<abs<<endl;
                iterateDirectory(abs);
            }
        }

        //if the entry is regular file
        else if(dirEntry->d_type == DT_REG)
        {
            //and the file is c/c++ file
            if(extensionCheck(dirEntry) == true)
            {
                //perform visit
                dirVisit(dirEntry);
            }
        }
    }

    //close the directory when all are read.
    closedir(dirPtr);
}
