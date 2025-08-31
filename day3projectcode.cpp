#include <iostream>
#include <vector>
#include <string>

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

    bool hasOverlap(const std::vector<std::string>& otherAvailability) {
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

std::vector<StudentProfile> profiles;

void scheduleStudySession(int studentIndex1, int studentIndex2) {
    std::cout << profiles[studentIndex1].name << " and " << profiles[studentIndex2].name << " have scheduled a study session!" << std::endl;
}

void matchAndSchedule(int profileIndex) {
    std::cout << "Matching available students for " << profiles[profileIndex].name << ":\n";
    for (size_t i = 0; i < profiles.size(); ++i) {
        if (i != profileIndex && profiles[profileIndex].hasOverlap(profiles[i].availability)) {
            std::cout << profiles[i].name << " is available to study.\n";
            // Schedule session
            scheduleStudySession(profileIndex, i);
        }
    }
}

int main() {
    // Assume profiles have been populated and availability set
    matchAndSchedule(0); // Example: Match availability for the first profile
    return 0;
}