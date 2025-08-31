#include <iostream>
#include <vector>
#include <string>
#include "StudentProfile.h" // Include the header file

void addAvailabilityToProfile(int profileIndex) {
    std::string time;
    std::cout << "Enter availability time: ";
    std::getline(std::cin, time);
    profiles[profileIndex].addAvailability(time);
    std::cout << "Availability added!" << std::endl;
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

int main() {
    addProfile();
    displayAllProfiles();
    addAvailabilityToProfile(0); // Add availability to the first profile
    searchByCourse("CS101"); // Example search for a course

    return 0;
}