#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "DynamicArray.h"
#include "MovieRating.h"

int main() {
    std::string dataFile = "data/projekt1_dane.csv";
    std::ifstream filesize(dataFile, std::ios::ate | std::ios::binary);
    std::ifstream infile(dataFile);
    if(!filesize) {
        std::cout << "Blad otwarcia pliku\n";
        return 1;
    }
    std::streamoff pos = filesize.tellg();  // typ liczbowy
    char c;
    std::string line;

    for(std::streamoff i = pos - 1; i >= 0; i--) {

        filesize.seekg(i);
        filesize.get(c);

        if(c == '\n' && i != pos - 1)
            break;

        line = c + line;
    }
    std::string s1 = line.substr(0,line.find(","));
    int size = std::stoi(s1);
    size+=2; // id pomija dwie pierwsze linie bo nie maja id
    MovieRating* tab = new MovieRating[size];
    int k=0;
    for(int i = 1 ; i < size ; i++) {
        std::string s;
        getline(infile,s);
        std::string temp = s.substr(0,s.find(","));
        std::string temp2 ="";
        if(s.size()- s.rfind(",")+1 > 1) temp2 = s.substr(s.rfind(","),s.size()-s.rfind(","));
        std::string temp3 = s.substr(s.find(","+1,s.rfind(",")));
        if(temp2[temp2.size()-1] == '0' && temp2.size() >= 2) {
            std::string temp4 = s.substr(s.rfind(",")+1,s.size()-s.rfind(","));
            tab[k].id = std::stoi(temp);
            tab[k].rating = std::stoi(temp4);
            tab[k].title = temp3;
            k++;
        }
    }
    std::cout<<"Loading Done: "<<k<<"\n";
    return 0;
}