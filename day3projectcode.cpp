#include <iostream>
#include <vector>
#include <string>
#include "day1projectcode.cpp" // Include Day 1 functionality
#include "day2projectcode.cpp" // Include Day 2 functionality

class StudentProfile; // Forward declaration

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

int main() {
    // Adding profiles and availability
    StudentProfile student1;
    student1.createProfile("Alice", "123", {"CS101", "MATH201"});
    student1.addAvailability("Monday 10AM");
    profiles.push_back(student1);

    StudentProfile student2;
    student2.createProfile("Bob", "456", {"CS101", "MATH201"});
    student2.addAvailability("Monday 10AM");
    profiles.push_back(student2);

    StudentProfile student3;
    student3.createProfile("Charlie", "789", {"CS102"});
    student3.addAvailability("Tuesday 2PM");
    profiles.push_back(student3);

    // Match and schedule for the first profile
    matchAndSchedule(0); // Match availability for Alice

    return 0;
}