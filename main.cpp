#include "StudentProfile.h"
#include <limits>   

int main() {
    // Try to load previous data
    loadData("study_buddy_data.txt");

    // Minimal demo flow for Sprint 2
    // (Assumes addProfile() and displayAllProfiles() are provided in Sprint 1)
    std::cout << "Study Buddy - Sprint 2 (with persistence)\n";
    bool running = true;
    while (running) {
        std::cout << "\nMenu:\n"
                    "1) Add profile (Sprint 1)\n"
                    "2) Show all profiles (Sprint 1)\n"
                    "3) Add availability (choose profile)\n"
                    "4) Search by course\n"
                    "5) Save\n"
                    "6) Remove availability (choose profile)\n"
                    "7) Suggest random matches (choose profile)\n"
                    "8) Request study session\n"
                    "9) Respond to my requests\n"
                    "10) View my confirmed sessions\n"
                    "0) Exit\n"
                << "Choice: ";

        int choice = -1;
        if (!(std::cin >> choice)) break;

        switch (choice) {
            case 1: {
                extern void addProfile(); // from Sprint 1
                addProfile();
                break;
            }
            case 2: {
                extern void displayAllProfiles(); // from Sprint 1
                displayAllProfiles();
                break;
            }

            case 3: {
                if (profiles.empty()) {
                    std::cout << "No profiles yet.\n";
                    break;
                }

                std::cout << "Profiles:\n";
                for (size_t i = 0; i < profiles.size(); ++i) {
                    std::cout << "  [" << i << "] " << profiles[i].name
                            << " (" << profiles[i].studentID << ")\n";
                }

                std::cout << "Enter profile index: ";
                int pidx = -1;
                if (!(std::cin >> pidx)) {
                    std::cin.clear();
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    std::cout << "Invalid input.\n";
                    break;
                }

                if (pidx < 0 || pidx >= static_cast<int>(profiles.size())) {
                    std::cout << "Invalid index.\n";
                    break;
                }

                // clear newline before getline inside addAvailabilityToProfile
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                addAvailabilityToProfile(pidx);
                break;
            }

            case 4: {
                std::string course;
                std::cout << "Enter course to search: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, course);
                searchByCourse(course);
                break;
            }
            case 5: {
                if (saveData("study_buddy_data.txt")) std::cout << "Saved.\n";
                else std::cout << "Save failed.\n";
                break;
            }

            case 6: {
                if (profiles.empty()) {
                    std::cout << "No profiles yet.\n";
                    break;
                }

                // List profiles to choose from
                std::cout << "Profiles:\n";
                for (size_t i = 0; i < profiles.size(); ++i) {
                    std::cout << "  [" << i << "] " << profiles[i].name
                            << " (" << profiles[i].studentID << ")\n";
                }

                std::cout << "Enter profile index: ";
                int pidx = -1;
                if (!(std::cin >> pidx)) {
                    std::cin.clear();
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    std::cout << "Invalid input.\n";
                    break;
                }

                if (pidx < 0 || pidx >= static_cast<int>(profiles.size())) {
                    std::cout << "Invalid index.\n";
                    break;
                }

                removeAvailabilityFromProfile(pidx);
                break;
            }

        case 7: {
            if (profiles.empty()) { std::cout << "No profiles yet.\n"; break; }

            // List profiles to choose from
            std::cout << "Profiles:\n";
            for (size_t i = 0; i < profiles.size(); ++i) {
                std::cout << "  [" << i << "] " << profiles[i].name
                        << " (" << profiles[i].studentID << ")\n";
            }

            std::cout << "Enter profile index: ";
            int pidx = -1;
            if (!(std::cin >> pidx)) {
                std::cin.clear();
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                std::cout << "Invalid input.\n";
                break;
            }
            if (pidx < 0 || pidx >= static_cast<int>(profiles.size())) {
                std::cout << "Invalid index.\n";
                break;
            }

            std::cout << "How many suggestions? ";
            int k = 0;
            if (!(std::cin >> k)) {
                std::cin.clear();
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                std::cout << "Invalid input.\n";
                break;
            }

            suggestRandomMatches(pidx, k);

            // Optional: immediately show the updated profile (so you see the suggestions line)
            profiles[pidx].displayProfile();
            break;
        }
    case 8: { // Request study session
        std::string req, rec, course, time;
        std::cout << "Requester Student ID: ";
        std::cin >> req;
        std::cout << "Recipient Student ID: ";
        std::cin >> rec;

        std::cout << "Course: ";
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        std::getline(std::cin, course);

        std::cout << "Proposed time slot: ";
        std::getline(std::cin, time);

        requestStudySession(req, rec, course, time);
        break;
    }

    case 9: { // Respond (accept/decline)
        std::string me;
        std::cout << "Your Student ID: ";
        std::cin >> me;
        viewAndRespondToRequests(me);
        break;
    }

    case 10: { // View confirmed
        std::string me;
        std::cout << "Your Student ID: ";
        std::cin >> me;
        viewMyConfirmedSessions(me);
        break;
    }

            case 0: {
                // Auto-save on exit
                saveData("study_buddy_data.txt");
                running = false;
                break;
            }
            default:
                std::cout << "Invalid choice.\n";
        }
    }
    return 0;
}