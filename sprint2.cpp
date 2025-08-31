#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include "StudentProfile.h"  // Declares StudentProfile and `extern std::vector<StudentProfile> profiles;`

void addAvailabilityToProfile(int profileIndex) {
    if (profileIndex < 0 || profileIndex >= static_cast<int>(profiles.size())) {
        std::cout << "Invalid profile index.\n";
        return;
    }
    std::string time;
    std::cout << "Enter availability time: ";

    std::getline(std::cin, time);
    profiles[profileIndex].addAvailability(time);
    std::cout << "Availability added!\n";
}

void searchByCourse(const std::string& course) {
    std::cout << "Students enrolled in " << course << ":\n";
    for (const auto& profile : profiles) {
        for (const auto& c : profile.courses) {
            if (c == course) {
                std::cout << profile.name << " - ";
                profile.displayAvailability();
            }
        }
    }
}

// Text format:
// PROFILES N
// NAME <line>
// ID <line>
// COURSES K
//   <line>*K
// AVAIL M
//   <line>*M
bool saveData(const std::string& path) {
    std::ofstream out(path);
    if (!out) {
        std::cout << "Failed to open '" << path << "' for writing.\n";
        return false;
    }
    out << "PROFILES " << profiles.size() << "\n";
    for (const auto& p : profiles) {
        out << "NAME " << p.name << "\n";
        out << "ID " << p.studentID << "\n";
        out << "COURSES " << p.courses.size() << "\n";
        for (const auto& c : p.courses) out << c << "\n";
        out << "AVAIL " << p.availability.size() << "\n";
        for (const auto& a : p.availability) out << a << "\n";
    }
    return true;
}

bool loadData(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        // First run: no file yet
        return false;
    }
    profiles.clear();

    std::string tag, line;
    size_t nProfiles = 0;
    if (!(in >> tag >> nProfiles) || tag != "PROFILES") return false;
    std::getline(in, line); // consume EOL

    for (size_t i = 0; i < nProfiles; ++i) {
        StudentProfile p;

        std::getline(in, line); // NAME ...
        if (line.rfind("NAME ", 0) != 0) return false;
        p.name = line.substr(5);

        std::getline(in, line); // ID ...
        if (line.rfind("ID ", 0) != 0) return false;
        p.studentID = line.substr(3);

        size_t k = 0;
        in >> tag >> k; // COURSES k
        if (tag != "COURSES") return false;
        std::getline(in, line);
        p.courses.resize(k);
        for (size_t j = 0; j < k; ++j) std::getline(in, p.courses[j]);

        size_t m = 0;
        in >> tag >> m; // AVAIL m
        if (tag != "AVAIL") return false;
        std::getline(in, line);
        p.availability.resize(m);
        for (size_t j = 0; j < m; ++j) std::getline(in, p.availability[j]);

        profiles.push_back(std::move(p));
    }
    return true;
}