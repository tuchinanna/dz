#include "timetable.hpp"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " <файл_с_преподавателями>" << std::endl;
        return 1;
    }

    std::vector<Teacher> teachers;
    readTeachersFromFile(argv[1], teachers);




    if (teachers.size() < 15) {
        std::cerr << "Ошибка: должно быть не менее 15 преподавателей." << std::endl;
        return 1;
    }

    std::vector<Timetable> timetables;
    generateSchedule(teachers, timetables);

    printSchedule(timetables);
    saveTimetable(timetables, "timetable.txt");

    return 0;
}
