#include <iostream>
#include <vector>
#include <string>
#include "StudentProfile.h" // Include the header file

std::vector<StudentProfile> profiles; // Define the profiles vector

void addProfile() {
    // Clear leftover '\n' from the menu choice (done once, here)
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    StudentProfile newProfile;
    std::string name, id;
    int courseCount = 0;

    std::cout << "Enter Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Student ID: ";
    std::getline(std::cin, id);

    std::cout << "Enter number of courses: ";
    // You can keep operator>> for the integer…
    if (!(std::cin >> courseCount)) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        std::cout << "Invalid number. Aborting add.\n";
        return;
    }

    // …but since the next step uses getline, clear the newline ONCE
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    std::vector<std::string> courses;
    courses.reserve(std::max(0, courseCount));
    for (int i = 0; i < courseCount; ++i) {
        std::string c;
        std::cout << "Enter Course " << (i + 1) << ": ";
        std::getline(std::cin, c);
        courses.push_back(c);
    }

    newProfile.createProfile(name, id, courses);
    profiles.push_back(std::move(newProfile));
    std::cout << "Profile created successfully!\n";
}

void displayAllProfiles() {
    for (const auto& profile : profiles) {
        profile.displayProfile();
    }
}