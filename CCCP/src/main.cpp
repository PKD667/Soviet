#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string CURRENT_DIR = "/home/paulk/Desktop/Soviet/CCCP/";
string BUILD_ROOT = CURRENT_DIR + "build-root/";

//Getting package data from file
vector<string> open_spm (string PName)
{
    streampos size;
    char * memblock;

    string PPath = CURRENT_DIR + "testing/" + PName + "/";
    cout << PPath + PName + ".spm \n";
    ifstream file_spm (PPath + PName + ".spm", ios::in);
    string line;
    vector<string> pkg_info;
    if (file_spm.is_open())
    {
        cout << "file opened " << "\n";
        while ( getline (file_spm,line) )
        {
        pkg_info.push_back(line);
        }
        file_spm.close();
        return pkg_info;
    }

    else {
        cout << "Unable to open file \n";
        return vector<string> () ;
    }

    

}
int install_binary ()
{

}
//parsing data and installing package
int install_package (string PName)
{
    cout << "processing package" << "\n";
    vector<string> pkg_info = open_spm("lolcat");
    cout << "package info parsed" << "\n";
    if ( pkg_info[0] != "nothing")
    {
    //Dependencies stuff for LATER
    }
    else {
        cout << "No dependencies" << "\n";
        if ( pkg_info[1] == "source") 
        {
            cout << "building from source" << "\n";
            if (pkg_info[2] == "make")
            {
                cout << "Making pkg" << "\n";
                string cmd_make = "( cd " + CURRENT_DIR + "testing/" + PName + "/" + PName + " && make && make DESTDIR=" + BUILD_ROOT + " install )  ";
                cout << cmd_make << endl;
                system(cmd_make.c_str());
            }
        }
        else if ( pkg_info[1] == "binary")
        {
            install_binary();
        }
    }
}

int main () {

  install_package("lolcat");

  return 0;
}
