#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <iostream>
#include "Vector.h"

using namespace std;

void listDir(const string& path)
{
  DIR *dir;
  struct dirent *ent;

  if((dir = opendir (path.c_str())) != NULL)
  {
    while ((ent = readdir (dir)) != NULL)
    {
      if(string(ent->d_name).compare(".") != 0)
      {
        cout<< ent->d_name << endl;
      }
      else
      {
        string nextDir = string(ent -> d_name);
        nextDir += "\\";
// files vector vs folder vector
//pass in two vec by Ref -> call function on folder
// instead of
        cout <<  nextDir << endl;

        listDir(nextDir);
      }
    }
  }

  closedir (dir);
}

int main(int param, char **args)
{
  string path = string(args[1]);
  listDir(path);

  return 0;
}
