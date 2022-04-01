#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::string CURRENT_DIR = "/home/paulk/Desktop/Soviet/CCCP/";
std::string BUILD_ROOT = CURRENT_DIR + "build-root/";

int install_package (std::string PName);
int install_binary ();
std::vector<std::string> open_spm (std::string PName);
std::vector<std::string> init_pkg_list ();
std::vector<std::string> split(std::string str, std::string token);

std::vector<std::string> installed_packages = init_pkg_list ();

int main () {

  install_package("lolcat");

  return 0;
}

//Getting package data from file
std::vector<std::string> open_spm (std::string PName)
{
    std::streampos size;
    char * memblock;

    std::string PPath = CURRENT_DIR + "testing/" + PName + "/";
    std::cout << PPath + PName + ".spm \n";
    std::ifstream file_spm (PPath + PName + ".spm", std::ios::in);
    std::string line;
    std::vector<std::string> pkg_info;
    if (file_spm.is_open())
    {
        std::cout << "file opened " << "\n";
        while ( getline (file_spm,line) )
        {
        pkg_info.push_back(line);
        }
        file_spm.close();
        return pkg_info;
    }

    else {
        std::cout << "Unable to open file \n";
        return std::vector<std::string> () ;
    }

    

}
int install_binary ()
{

}

std::vector<std::string> init_pkg_list ()
{

    std::streampos size;
    char * memblock;

    std::vector<std::string> pkg_list;

    std::ifstream list_file ( CURRENT_DIR + "pkg.list", std::ios::in);
    std::string line;
    if (list_file.is_open())
    {
        std::cout << "file opened " << "\n";
        while ( getline (list_file,line) )
        {
            pkg_list.push_back(line);
        }
        list_file.close();
    }
    else std::cout << "ITS BAD"<< "\n";

    return pkg_list;
}

//parsing data and installing package
int install_package (std::string PName)
{
    std::cout << "processing package" << "\n";
    std::vector<std::string> pkg_info = open_spm("lolcat");
    std::vector<std::string> pkg_deps = split(pkg_info[0], " ");
    std::cout << "package info parsed" << "\n";
    if ( pkg_info[0] != "")
    {
        for (int i = 1; i < pkg_deps.size(); i++)
        {
            if (std::find(installed_packages.begin(), installed_packages.end(), pkg_deps[i]) != installed_packages.end()) std::cout << "deps all good !!!" << std::endl;
            else
            {
                std::cout << "NOT GOOD STOP RN !!!" << std::endl;
                
                // Dependencies stuff to complicated  
            }
        }
        
    }
    else std::cout << "No dependencies" << "\n";      

    //END OF DEPENDENCIES CHECK
    
    if ( pkg_info[1] == "source") 
    {
        std::cout << "building from source" << "\n";
        if (pkg_info[2] == "make")
        {
            std::cout << "Making pkg" << "\n";
            std::string cmd_make = "( cd " + CURRENT_DIR + "testing/" + PName + "/" + PName + " && make && make DESTDIR=" + BUILD_ROOT + " install )  ";
            std::cout << cmd_make << std::endl;
            system(cmd_make.c_str());
        }
    }
    else if ( pkg_info[1] == "binary")
    {
        install_binary();
    }
    
}

std::vector<std::string> split(std::string str, std::string token){
    std::vector<std::string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=std::string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}