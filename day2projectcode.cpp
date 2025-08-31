#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

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

    void addAvailability(const std::string& time) {
        availability.push_back(time);
    }

    void displayAvailability() {
        std::cout << "Availability: ";
        for (const auto& time : availability) {
            std::cout << time << " ";
        }
        std::cout << std::endl;
    }
};

std::vector<StudentProfile> profiles;

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
    // Assume profiles have already been added
    addAvailabilityToProfile(0); // Example: Adding availability to the first profile
    searchByCourse("CS101"); // Example: Search for students in CS101
    return 0;
}
