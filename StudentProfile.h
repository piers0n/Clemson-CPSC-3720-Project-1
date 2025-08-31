// StudentProfile.h
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

    // Optional: random suggestions storage (from earlier feature)
    std::vector<std::string> suggestedMatches;

    void createProfile(const std::string& n, const std::string& id, const std::vector<std::string>& c) {
        name = n; studentID = id; courses = c;
    }

    void displayProfile() const {
        std::cout << "Name: " << name
                  << "\nID: " << studentID
                  << "\nCourses: ";
        for (const auto& course : courses) std::cout << course << " ";
        std::cout << "\nAvailability: ";
        if (availability.empty()) std::cout << "(none)";
        else for (const auto& time : availability) std::cout << time << " ";

        std::cout << "\nSuggested matches: ";
        if (suggestedMatches.empty()) std::cout << "(none)";
        else {
            for (size_t i = 0; i < suggestedMatches.size(); ++i) {
                if (i) std::cout << ", ";
                std::cout << suggestedMatches[i];
            }
        }
        std::cout << "\n";
    }

    void addAvailability(const std::string& time) { availability.push_back(time); }

    void displayAvailability() const {
        std::cout << "Availability: ";
        for (const auto& time : availability) std::cout << time << " ";
        std::cout << std::endl;
    }

    bool hasOverlap(const std::vector<std::string>& otherAvailability) const {
        for (const auto& time : availability)
            for (const auto& otherTime : otherAvailability)
                if (time == otherTime) return true;
        return false;
    }
};

// -------- NEW: study session model & API declarations --------
struct StudySession {
    int id = -1;
    std::string requesterID;  // who requested
    std::string recipientID;  // who received
    std::string course;
    std::string timeSlot;
    // 0=pending, 1=confirmed, 2=declined
    int status = 0;
};

// Global session store (defined in sprint3.cpp)
extern std::vector<StudySession> sessions;
extern int nextSessionId;

// Schedule/confirm APIs (defined in sprint3.cpp)
void requestStudySession(const std::string& requesterID,
                         const std::string& recipientID,
                         const std::string& course,
                         const std::string& timeSlot);

void viewAndRespondToRequests(const std::string& recipientID); // prompts accept/decline
void viewMyConfirmedSessions(const std::string& userID);

// Random suggestion (from your previous step)
void suggestRandomMatches(int profileIndex, int howMany);

// Persistence + app APIs you already use (implemented in sprint2.cpp)
bool saveData(const std::string& path);
bool loadData(const std::string& path);
void addAvailabilityToProfile(int profileIndex);
void removeAvailabilityFromProfile(int profileIndex);
void searchByCourse(const std::string& course);
int  findProfileIndexByID(const std::string& id);

extern std::vector<StudentProfile> profiles;
void addProfile();
void displayAllProfiles();

#endif // STUDENTPROFILE_H
