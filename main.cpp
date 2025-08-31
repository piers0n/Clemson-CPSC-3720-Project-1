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
                     "3) Add availability to first profile\n"
                     "4) Search by course\n"
                     "5) Save\n"
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
                std::cout << "Enter Student ID: ";
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                std::string id;
                std::getline(std::cin, id);

                int idx = findProfileIndexByID(id);
                if (idx < 0) {
                    std::cout << "No profile with that ID.\n";
                    break;
                }
                addAvailabilityToProfile(idx);
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