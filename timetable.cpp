#include "timetable.hpp"

void ltrim(std::string &s) {
    int i = 0;
     
    while (s[i] == ' ') {
       s.erase(0, 1);
       i++;
    }
}

void readTeachersFromFile(const std::string& filename, std::vector<Teacher>& teachers) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }

    std::string line;
    Teacher currentTeacher;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            // Если строка не содержит двоеточие, это имя преподавателя
            if (line.find(':') == std::string::npos) {
                if (!currentTeacher.name.empty()) {
                    teachers.push_back(currentTeacher);
                }
                currentTeacher.name = line;
                currentTeacher.availability.clear();
            } else {
                line.pop_back();
                // Это строка с доступностью
                std::string day = line.substr(0, 2); // Первые 2 символа - это день
                std::string slots = line.substr(3);   // Остальная часть - временные слоты
                std::stringstream ss(slots);
                // ss.ignore(1);

                // Разделяем временные слоты по запятой и добавляем в availability
                std::string slot;
                while (std::getline(ss, slot, ',')) {
                    ltrim(slot);
                    currentTeacher.availability[day].push_back(slot);
                }
            }
        }
    }

    if (!currentTeacher.name.empty()) {
        teachers.push_back(currentTeacher);
    }
}

void generateSchedule(std::vector<Teacher>& teachers, std::vector<Timetable>& timetables) {
    const std::vector<std::string> days = {"mn", "tu", "we", "th", "fr", "sa"};
    const int maxClassesPerDay = 4;

    for (const auto& day : days) {
        Timetable timetable;
        timetable.day = day;
        int classCount = 0;

        for (int i = 0; i < teachers.size(); i++) {            
            if (teachers[i].availability.count(day) > 0 && !teachers[i].filled) {
                for (const auto& slot : teachers[i].availability.at(day)) {
                    if (classCount < maxClassesPerDay && timetable.classes[slot].empty()) {
                        timetable.classes[slot] = teachers[i].name; // Добавляем слот и имя преподавателя
                        classCount++;
                        teachers[i].filled = true;
                        break;
                    } else {
                        break; // Прекращаем добавление, если достигли лимита пар в день
                    }
                }
            }
        }

        timetables.push_back(timetable);
    }
}

void saveTimetable(const std::vector<Timetable>& timetables, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
        return;
    }

    for (const auto& timetable : timetables) {
        if (!timetable.classes.empty()) {
            file << timetable.day << ":\n";
            for (const auto& cls : timetable.classes) {
                file << cls.first << ": " << cls.second << "\n";
            }
        }
    }

    file.close();
}
 
void printSchedule(const std::vector<Timetable>& timetables) {
    for (const auto& timetable : timetables) {
        if (!timetable.classes.empty()) {
            std::cout << timetable.day << ":\n";
            for (const auto& cls : timetable.classes) {
                std::cout << cls.first << ": " << cls.second << "\n"; // Выводим слот и имя преподавателя
            }
        }
    }
}


