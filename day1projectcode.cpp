#include <iostream>
#include <vector>
#include <string>

class StudentProfile {
public:
    std::string name;
    std::string studentID;
    std::vector<std::string> courses;

    void createProfile(const std::string& n, const std::string& id, const std::vector<std::string>& c) {
        name = n;
        studentID = id;
        courses = c;
    }

    void displayProfile() const {
        std::cout << "Name: " << name << "\nID: " << studentID << "\nCourses: ";
        for (const auto& course : courses) {
            std::cout << course << " ";
        }
        std::cout << std::endl;
    }

    void updateProfile(const std::string& n, const std::vector<std::string>& c) {
        name = n;
        courses = c;
    }
};

std::vector<StudentProfile> profiles;

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
    std::cin.ignore(); // Clear newline character from input buffer

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