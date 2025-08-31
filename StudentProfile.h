#ifndef STUDENTPROFILE_H
#define STUDENTPROFILE_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>

class StudentProfile {
public:
    std::string name;
    std::string studentID;
    std::vector<std::string> courses;
    std::vector<std::string> availability;

    void createProfile(const std::string& n, const std::string& id, const std::vector<std::string>& c) {
        name = n;
        studentID = id;
        courses = c;
    }

    void displayProfile() const {
        std::cout << "Name: " << name << "\nID: " << studentID << "\nCourses: ";
        for (const auto& course : courses) std::cout << course << " ";
        std::cout << "\nAvailability: ";
        for (const auto& time : availability) std::cout << time << " ";
        std::cout << "\n";
    }

    void addAvailability(const std::string& time) {
        availability.push_back(time);
    }

    void displayAvailability() const {
        std::cout << "Availability: ";
        for (const auto& time : availability) {
            std::cout << time << " ";
        }
        std::cout << std::endl;
    }

    bool hasOverlap(const std::vector<std::string>& otherAvailability) const {
        for (const auto& time : availability) {
            for (const auto& otherTime : otherAvailability) {
                if (time == otherTime) {
                    return true;
                }
            }
        }
        return false;
    }
};

bool saveData(const std::string& path);
bool loadData(const std::string& path);
void addAvailabilityToProfile(int profileIndex);
void searchByCourse(const std::string& course);
int findProfileIndexByID(const std::string& id);

extern std::vector<StudentProfile> profiles; // Declare the profiles vector
void addProfile(); // Declare function
void displayAllProfiles(); // Declare function

#endif // STUDENTPROFILE_H