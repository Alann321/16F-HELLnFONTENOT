/*
  LEE, SEUNG KI

  DATE: 2016/11/23 (W)
  COURSE NAME: CSE 2341
  PROJECT: Final Project - Static Code Analyzer
  CODE: Directory Iterator

  This code will meet following criteria.

  1. Use only custom built data structure -> need to change std::string to DSString.h
  2. Take a directory as input from commandline argument -> DONE
  3. Open files if and only if it is extension of c/c++ (.c, .h, .cpp, .hpp) -> DONE
  4. For files opened, get samples to analyze -> DONE
  5. Recursively do the same to all subdirectories -> DONE
*/

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <cstring>

using namespace std;

void iterateDirectory(char*);
void dirVisit(dirent*, char*);

//Commented out to prevent multiple main

//int main(int argc, char* argv[])
//{
//    iterateDirectory(argv[1]);

//    return 0;
//}

//check if the file type is of certain type (c/c++ extensions)
bool extensionCheck(dirent* entry)
{
    string fileName = entry->d_name;
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
void dirVisit(dirent* entry, char* pPath)
{
    char actualPath[PATH_MAX+1];
    char* correctPath;

    cout<<"File Name: "<< entry->d_name <<endl;

    correctPath = realpath(pPath, actualPath);
    //buffer string for reading in the opened file
    string buffer = correctPath;
    //append the file name to the path
    buffer.append("/");
    buffer.append(entry->d_name);
    cout<<"File Path: "<< buffer <<endl;


    //open each file in the directory
    ifstream fin(buffer.c_str());

    //Get sample from a file
    if(fin.is_open())
    {
        cout<<"FILE OPENED"<<endl;
        cout<<endl;
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

    char actualPath[PATH_MAX+1];
    char* correctPath;

    //open directory from input (command line argument)
    dirPtr = opendir(filePath);

    //check if the directory was open correctly.
    if(dirPtr == nullptr)
    {
        cout<<"The directory was not opened correctly. Please check the directory name."<<endl;
        exit(1);
    }

    cout<<"DIR OPENED"<<endl;
    cout<<endl;

    //read directory
    while((dirEntry = readdir(dirPtr)))
    {
        //if the entry is another directory
        if(dirEntry->d_type == DT_DIR)
        {
            //make sure the directory is not itself or parent directory
            if((strcmp(dirEntry->d_name, ".") != 0) && (strcmp(dirEntry->d_name, "..") != 0))
            {
                cout<<"Directory Name: "<<dirEntry->d_name<<endl;
                //recursively go down to the subdirectory
                correctPath = realpath(filePath, actualPath);
                //store the path in a string for appending
                string temp = correctPath;
                //add the next directory name
                temp.append("/");
                temp.append(dirEntry->d_name);
                //turn string.c_str() into char*
                const char* cc = temp.c_str();
                char* c = (char*) cc;
                cout<<"Directory Path: "<<temp<<endl;
                iterateDirectory(c);
            }
        }

        //if the entry is regular file
        else if(dirEntry->d_type == DT_REG)
        {
            //and the file is c/c++ file
            if(extensionCheck(dirEntry) == true)
            {
                //perform visit
                dirVisit(dirEntry, filePath);
            }
        }
    }

    //close the directory when all are read.
    closedir(dirPtr);
}
