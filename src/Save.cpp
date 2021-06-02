/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Save.cpp
*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>

const char *FILEPATH_TO_SAVE = "save.txt";

std::string getNameFromSave()
{
    std::string name;
    std::string line;
    std::size_t pos = 0;
    std::ifstream file;

    file.open(FILEPATH_TO_SAVE);

    if (file.is_open()) {
        while (std::getline(file, line))
            name = line;
        pos = name.find("|");
        name = name.substr(0, pos - 1);
    } else
        return ("");
    file.close();
    return (name);
}

int getScoreFromSave()
{
    int score;
    std::string line;
    std::string s_score;
    std::size_t pos = 0;
    std::ifstream file;

    file.open(FILEPATH_TO_SAVE);

    if (file.is_open()) {
        while (std::getline(file, line))
            s_score = line;
        pos = s_score.find("|");
        s_score = s_score.substr(pos + 1, s_score.size());
    } else
        return (0);
    file.close();
    score = atoi(s_score.c_str());
    return (score);
}

bool saveNameAndScore(const std::string& Name, int Score)
{
    std::ofstream file;
    std::string s_score = std::to_string(Score);
 
    file.open(FILEPATH_TO_SAVE);
    if (file.is_open())
        file << Name << " | " << s_score;
    else
        return (false);
    file.close();
    return (true);
}