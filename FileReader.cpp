/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on June 26, 2018, 1:49 PM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <bits/c++config.h>
#include <map>

/*
 * 
 */
char replaceJunk(char c){
    //Only keep alphas, space as delimiter and '''
    return std::isdigit(c) ? c : ' ';
}

std::string cutString(const std::string& search) {
    
}

inline std::string removeWhiteSpaces(const std::string& s) {
    if(s.length() == 0) {
        return s;
    }
    int begin = s.find_first_not_of(" \a\b\f\n\r\t\v");
    int end = s.find_last_not_of(" \a\b\f\n\r\t\v");
    
    if(begin == std::string::npos) {    //No Non-space
        return "";
    }
    return std::string(s, begin, end - begin + 1);
}

void readFile(const std::string& file, const std::string& writeTo, const std::string& series) {
    std::ifstream readFrom(file);
    
    if(!readFrom.is_open()) {
        std::cerr << "! Error. File cant be open! file: "  << file << std::endl;
    }
    std::ofstream writeFile;
    writeFile.open(writeTo, std::fstream::in | std::fstream::out | std::fstream::app);
    
    std::string line;
    std::string result = "";
    result.append("|GameID|");
    writeFile << result << std::right << "------------------------------|" <<series << "|------------------------------|" << std::endl;
    while(std::getline(readFrom, line)) {
        
        std::stringstream keystream{line};
        
        std::string type;
        keystream >> type;
        
        if(type == "<area") {
            break;
        }
        if(type != "<game") {
            continue;
        }
        
        std::string formatedLine = removeWhiteSpaces(line);

        std::string gameId;
        
        keystream >> gameId;
        
        std::string num;
        for(int i = 0; i < gameId.length(); ++i) {
            num += replaceJunk(gameId.at(i));
        }
        num = removeWhiteSpaces(num);
        writeFile << std::right << std::setw(5) << num << '|';

        std::string searchedString = "name=";
        std::string lastQuote = "\" ";
        
        std::size_t gameNameQuote = formatedLine.find(searchedString);
        std::size_t findLastNameQuote = formatedLine.find(lastQuote, gameNameQuote + 1);
        
        std::string gameName = formatedLine.substr(gameNameQuote + 6, findLastNameQuote - 6 - gameNameQuote);
        writeFile << std::right <<std::setw(35) << gameName << '|';

        std::string findDir = "dir=";
        std::size_t beginDir = formatedLine.find(findDir);
        std::size_t endDir = formatedLine.find(lastQuote, beginDir + 1);
        std::string gamePath = formatedLine.substr(beginDir + 5, endDir - 5 - beginDir);
        writeFile << std::right << std::setw(35) << gamePath << '|' << std::endl;
        
        result = "";
    }
    writeFile <<"======================================================================================\n\n";
    readFrom.close();
    writeFile.close();
}

void sortFile(const std::string& readFile, const std::string& sortedFile = "") {
    std::ifstream readFrom(readFile);
    
    if(!readFrom.is_open()) {
        std::cerr << "! File cannot be open for reading: " << readFile << std::endl;
        return;
    }
    std::ofstream writeTo(sortedFile);
    if(!writeTo.is_open()) {
        std::cerr << "! File cannot be open for sorting: " << sortedFile << std::endl;
        return;
    }
    std::string line;
    std::map<int, std::string> myMap;
    while(std::getline(readFrom, line)) {
        std::stringstream keystream{line};
        
        std::string type = "";
        keystream >> type;
//        if(type[0] == '=') {
//            for(std::map<int, std::string>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
////                std::cout << it->first << " " << it->second << std::endl;
//                writeTo << it->second << std::endl;
//            }
//            myMap.clear(); 
//        }
        if(type == "" || type.at(0) == '|' || type.at(0) == '=') {
//            writeTo << line << std::endl;
            continue;
        }
        
//        std::string number = "";
//        keystream >> number;
        
        type = removeWhiteSpaces(type);
        type = type.erase(type.length() - 1, 1);
//        int num = stoi(number.c_str());
        int pos = stoi(type);
        myMap[pos] = line;
        for(int i = 0; i < line.length(); i++) {
            if(line.at(5) == '|') {
                break;
            }

        }
    }
    for(std::map<int, std::string>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
//                std::cout << it->first << " " << it->second << std::endl;
        writeTo << it->second << std::endl;
    }
    
} 

int main(int argc, char** argv) {
    
    sortFile("result/games.txt", "result/sortedGames2.txt");
    
    return 0;
}

