#include <iostream>
#include <vector>
#include <string>
#include "StudentProfile.h" // Include the header file

void scheduleStudySession(int studentIndex1, int studentIndex2) {
    std::cout << profiles[studentIndex1].name << " and " << profiles[studentIndex2].name << " have scheduled a study session!" << std::endl;
}

void matchAndSchedule(int profileIndex) {
    std::cout << "Matching available students for " << profiles[profileIndex].name << ":\n";
    for (size_t i = 0; i < profiles.size(); ++i) {
        if (i != profileIndex && profiles[profileIndex].hasOverlap(profiles[i].availability)) {
            std::cout << profiles[i].name << " is available to study.\n";
            scheduleStudySession(profileIndex, i);
        }
    }
}

int findProfileIndexByID(const std::string& id) {
    for (size_t i = 0; i < profiles.size(); ++i)
        if (profiles[i].studentID == id) return static_cast<int>(i);
    return -1;
}


// Optionally, you can call matchAndSchedule from day2.cpp after adding students