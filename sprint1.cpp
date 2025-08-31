#include <iostream>
#include <vector>
#include <string>
#include "StudentProfile.h" // Include the header file

std::vector<StudentProfile> profiles; // Define the profiles vector

void addProfile() {
    StudentProfile newProfile;
    std::string name, id;
    int courseCount;

    std::cout << "Enter Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Student ID: ";
    std::getline(std::cin, id);

    std::cout << "Enter number of courses: ";
    std::cin >> courseCount;
    std::cin.ignore();

    std::vector<std::string> courses(courseCount);
    for (int i = 0; i < courseCount; ++i) {
        std::cout << "Enter Course " << (i + 1) << ": ";
        std::getline(std::cin, courses[i]);
    }

    newProfile.createProfile(name, id, courses);
    profiles.push_back(newProfile);
    std::cout << "Profile created successfully!" << std::endl;
}

void displayAllProfiles() {
    for (const auto& profile : profiles) {
        profile.displayProfile();
    }
}