// sprint3.cpp
#include <algorithm>
#include <random>
#include <iostream>
#include <string>
#include "StudentProfile.h"

// --------- sessions storage ---------
std::vector<StudySession> sessions;
int nextSessionId = 1;

// Helper to find profile by ID (declared in header)
int findProfileIndexByID(const std::string& id) {
    for (size_t i = 0; i < profiles.size(); ++i)
        if (profiles[i].studentID == id) return static_cast<int>(i);
    return -1;
}

// --------- Request a study session ----------
void requestStudySession(const std::string& requesterID,
                         const std::string& recipientID,
                         const std::string& course,
                         const std::string& timeSlot) {
    int rIdx = findProfileIndexByID(requesterID);
    int cIdx = findProfileIndexByID(recipientID);
    if (rIdx < 0 || cIdx < 0) {
        std::cout << "Requester or recipient not found.\n";
        return;
    }

    StudySession s;
    s.id = nextSessionId++;
    s.requesterID = requesterID;
    s.recipientID = recipientID;
    s.course = course;
    s.timeSlot = timeSlot;
    s.status = 0; // pending
    sessions.push_back(std::move(s));

    std::cout << "Request sent from " << profiles[rIdx].name
              << " to " << profiles[cIdx].name
              << " [Session ID " << (nextSessionId - 1) << "]\n";
}

// --------- View & respond (accept/decline) ----------
static int findSessionIndexById(int sid) {
    for (size_t i = 0; i < sessions.size(); ++i)
        if (sessions[i].id == sid) return static_cast<int>(i);
    return -1;
}

void viewAndRespondToRequests(const std::string& recipientID) {
    int cIdx = findProfileIndexByID(recipientID);
    if (cIdx < 0) { std::cout << "Profile not found.\n"; return; }

    // list pending for this recipient
    bool any = false;
    std::cout << "Pending requests for " << profiles[cIdx].name << ":\n";
    for (const auto& s : sessions) {
        if (s.recipientID == recipientID && s.status == 0) {
            any = true;
            std::cout << "  [ID " << s.id << "] From: " << s.requesterID
                      << " | Course: " << s.course
                      << " | Time: " << s.timeSlot << " | Status: Pending\n";
        }
    }
    if (!any) { std::cout << "(none)\n"; return; }

    std::cout << "Enter Session ID to respond (0 to cancel): ";
    int sid = -1;
    if (!(std::cin >> sid) || sid == 0) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return;
    }

    int si = findSessionIndexById(sid);
    if (si < 0 || sessions[si].recipientID != recipientID) {
        std::cout << "Invalid session id.\n"; return;
    }

    std::cout << "1=Accept, 2=Decline: ";
    int action = 0;
    if (!(std::cin >> action)) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        std::cout << "Cancelled.\n"; return;
    }
    if (action == 1) {
        sessions[si].status = 1;
        std::cout << "Session confirmed.\n";
    } else if (action == 2) {
        sessions[si].status = 2;
        std::cout << "Session declined.\n";
    } else {
        std::cout << "Cancelled.\n";
    }
}

// --------- View my confirmed sessions ----------
void viewMyConfirmedSessions(const std::string& userID) {
    int idx = findProfileIndexByID(userID);
    if (idx < 0) { std::cout << "Profile not found.\n"; return; }

    bool any = false;
    std::cout << "Confirmed sessions for " << profiles[idx].name << ":\n";
    for (const auto& s : sessions) {
        if (s.status == 1 && (s.requesterID == userID || s.recipientID == userID)) {
            any = true;
            std::cout << "  [ID " << s.id << "] "
                      << s.requesterID << " & " << s.recipientID
                      << " | " << s.course << " @ " << s.timeSlot << "\n";
        }
    }
    if (!any) std::cout << "(none)\n";
}

// --------- (Existing) random suggestions ----------
void suggestRandomMatches(int profileIndex, int howMany) {
    if (profileIndex < 0 || profileIndex >= static_cast<int>(profiles.size())) {
        std::cout << "Invalid profile index.\n";
        return;
    }
    if (profiles.size() <= 1) {
        std::cout << "Not enough profiles to suggest matches.\n";
        profiles[profileIndex].suggestedMatches.clear();
        return;
    }

    std::vector<int> candidates;
    for (int i = 0; i < static_cast<int>(profiles.size()); ++i)
        if (i != profileIndex) candidates.push_back(i);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(candidates.begin(), candidates.end(), gen);

    if (howMany < 0) howMany = 0;
    if (howMany > static_cast<int>(candidates.size()))
        howMany = static_cast<int>(candidates.size());
    candidates.resize(howMany);

    auto& out = profiles[profileIndex].suggestedMatches;
    out.clear();
    for (int idx : candidates)
        out.push_back(profiles[idx].name + " (" + profiles[idx].studentID + ")");

    std::cout << "Suggested " << out.size() << " random match(es) for "
              << profiles[profileIndex].name << ".\n";
}
