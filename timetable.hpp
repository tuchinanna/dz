#ifndef TIMETABLE_HPP
#define TIMETABLE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

// Структура для хранения информации о преподавателе
struct Teacher {
    std::string name;
    bool filled;
    std::map<std::string, std::vector<std::string> > availability; // Доступность по дням недели
};

// Структура для хранения расписания
struct Timetable {
    std::string day;
    std::map<std::string, std::string> classes; // Время - имя преподавателя
};

// Функции для работы с расписанием
void readTeachersFromFile(const std::string& filename, std::vector<Teacher>& teachers);
void generateSchedule(std::vector<Teacher>& teachers, std::vector<Timetable>& timetables);
void printSchedule(const std::vector<Timetable>& timetables);
void saveTimetable(const std::vector<Timetable>& timetables, const std::string& filename);

#endif // TIMETABLE_HPP
