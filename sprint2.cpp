#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include "StudentProfile.h"  // Declares StudentProfile and `extern std::vector<StudentProfile> profiles;`

void addAvailabilityToProfile(int profileIndex) {
    if (profileIndex < 0 || profileIndex >= static_cast<int>(profiles.size())) {
        std::cout << "Invalid profile index.\n";
        return;
    }
    std::string time;
    std::cout << "Enter availability time: ";

    std::getline(std::cin, time);
    profiles[profileIndex].addAvailability(time);
    std::cout << "Availability added!\n";
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

void removeAvailabilityFromProfile(int profileIndex) {
    if (profileIndex < 0 || profileIndex >= static_cast<int>(profiles.size())) {
        std::cout << "Invalid profile index.\n";
        return;
    }

    auto& av = profiles[profileIndex].availability;
    if (av.empty()) {
        std::cout << "This profile has no availability to remove.\n";
        return;
    }

    // List availability with indices
    std::cout << "Availability for " << profiles[profileIndex].name << ":\n";
    for (size_t i = 0; i < av.size(); ++i) {
        std::cout << "  [" << i << "] " << av[i] << "\n";
    }

    // Ask which one to remove
    std::cout << "Enter index to remove: ";
    int idxToRemove = -1;
    if (!(std::cin >> idxToRemove)) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        std::cout << "Invalid input.\n";
        return;
    }

    if (idxToRemove < 0 || idxToRemove >= static_cast<int>(av.size())) {
        std::cout << "Invalid index.\n";
        return;
    }

    // Remove it
    av.erase(av.begin() + idxToRemove);
    std::cout << "Availability removed.\n";
}

// Text format:
// PROFILES N
// NAME <line>
// ID <line>
// COURSES K
//   <line>*K
// AVAIL M
//   <line>*M
// sprint2.cpp
#include <fstream>
#include <string>
#include <limits>
#include <iostream>
#include "StudentProfile.h"

// ... your addAvailabilityToProfile / searchByCourse / removeAvailabilityFromProfile ...

bool saveData(const std::string& path) {
    std::ofstream out(path);
    if (!out) {
        std::cout << "Failed to open '" << path << "' for writing.\n";
        return false;
    }

    out << "PROFILES " << profiles.size() << "\n";
    for (const auto& p : profiles) {
        out << "NAME " << p.name << "\n";
        out << "ID " << p.studentID << "\n";
        out << "COURSES " << p.courses.size() << "\n";
        for (const auto& c : p.courses) out << c << "\n";
        out << "AVAIL " << p.availability.size() << "\n";
        for (const auto& a : p.availability) out << a << "\n";

        // (Optional) persist suggestions; skip for now to keep format stable
        // out << "SUG " << p.suggestedMatches.size() << "\n";
        // for (const auto& s : p.suggestedMatches) out << s << "\n";
    }

    // ---- NEW: sessions ----
    out << "SESSIONS " << sessions.size() << "\n";
    for (const auto& s : sessions) {
        out << "SID " << s.id << "\n";
        out << "REQ " << s.requesterID << "\n";
        out << "REC " << s.recipientID << "\n";
        out << "COURSE " << s.course << "\n";
        out << "TIME " << s.timeSlot << "\n";
        out << "STATUS " << s.status << "\n";
    }
    out << "NEXTID " << nextSessionId << "\n";
    return true;
}

bool loadData(const std::string& path) {
    std::ifstream in(path);
    if (!in) return false;

    profiles.clear();
    sessions.clear();
    nextSessionId = 1;

    std::string tag, line;
    size_t nProfiles = 0;
    if (!(in >> tag >> nProfiles) || tag != "PROFILES") return false;
    std::getline(in, line); // eat EOL

    for (size_t i = 0; i < nProfiles; ++i) {
        StudentProfile p;
        std::getline(in, line); if (line.rfind("NAME ", 0) != 0) return false; p.name = line.substr(5);
        std::getline(in, line); if (line.rfind("ID ",   0) != 0) return false; p.studentID = line.substr(3);

        size_t k = 0;
        in >> tag >> k; if (tag != "COURSES") return false; std::getline(in, line);
        p.courses.resize(k);
        for (size_t j = 0; j < k; ++j) std::getline(in, p.courses[j]);

        size_t m = 0;
        in >> tag >> m; if (tag != "AVAIL") return false; std::getline(in, line);
        p.availability.resize(m);
        for (size_t j = 0; j < m; ++j) std::getline(in, p.availability[j]);

        // (Optional) suggestions parsing if you later persist them:
        // size_t sCount = 0;
        // if (in >> tag && tag == "SUG") {
        //     in >> sCount; std::getline(in, line);
        //     p.suggestedMatches.resize(sCount);
        //     for (size_t j = 0; j < sCount; ++j) std::getline(in, p.suggestedMatches[j]);
        // } else { /* handle gracefully if absent */ }

        profiles.push_back(std::move(p));
    }

    size_t sessN = 0;
    if (!(in >> tag >> sessN) || tag != "SESSIONS") return false;
    std::getline(in, line); // EOL
    for (size_t i = 0; i < sessN; ++i) {
        StudySession s;
        std::getline(in, line); if (line.rfind("SID ",    0) != 0) return false; s.id         = std::stoi(line.substr(4));
        std::getline(in, line); if (line.rfind("REQ ",    0) != 0) return false; s.requesterID= line.substr(4);
        std::getline(in, line); if (line.rfind("REC ",    0) != 0) return false; s.recipientID= line.substr(4);
        std::getline(in, line); if (line.rfind("COURSE ", 0) != 0) return false; s.course     = line.substr(7);
        std::getline(in, line); if (line.rfind("TIME ",   0) != 0) return false; s.timeSlot   = line.substr(5);
        std::getline(in, line); if (line.rfind("STATUS ", 0) != 0) return false; s.status     = std::stoi(line.substr(7));
        sessions.push_back(std::move(s));
    }

    if (in >> tag >> nextSessionId) {
        if (tag != "NEXTID") { /* tolerate older files without NEXTID */ }
    }
    return true;
}
