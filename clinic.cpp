#include <iostream>
#include <string>
using namespace std;

// --- Data Storage -----------------------------------------------
const int MAX = 50;

string patientNames[MAX];
int    patientAges[MAX];
string patientDoctors[MAX];
string appointmentTimes[MAX];
int    appointmentCount = 0;

string doctors[3] = {"Dr. Santos", "Dr. Reyes", "Dr. Cruz"};
string timeSlots[4] = {"9:00 AM", "11:00 AM", "2:00 PM", "4:00 PM"};

// --- Display Available Doctors ----------------------------------
void showDoctors() {
    cout << "\n  Available Doctors:\n";
    for (int i = 0; i < 3; i++) {
        cout << "  [" << (i + 1) << "] " << doctors[i] << "\n";
    }
}

// --- Display Available Time Slots -------------------------------
void showTimeSlots() {
    cout << "\n  Available Time Slots:\n";
    for (int i = 0; i < 4; i++) {
        cout << "  [" << (i + 1) << "] " << timeSlots[i] << "\n";
    }
}

// --- Book Appointment -------------------------------------------
void bookAppointment() {
    if (appointmentCount >= MAX) {
        cout << "\n  [!] Appointment list is full.\n";
        return;
    }

    string name;
    int age;
    int docChoice, timeChoice;

    cout << "\n  Enter patient name: ";
    cin.ignore();
    getline(cin, name);

    cout << "  Enter patient age: ";
    cin >> age;

    // Nested if-else: validate age
    if (age <= 0) {
        cout << "\n  [!] Invalid age entered.\n";
        return;
    } else {
        if (age < 18) {
            cout << "  [i] Patient is a minor. Guardian required during visit.\n";
        } else if (age >= 60) {
            cout << "  [i] Senior patient. Priority slot recommended.\n";
        } else {
            cout << "  [i] Adult patient registered.\n";
        }
    }

    showDoctors();
    cout << "\n  Choose doctor (1-3): ";
    cin >> docChoice;

    if (docChoice < 1 || docChoice > 3) {
        cout << "\n  [!] Invalid doctor selection.\n";
        return;
    } else {
        cout << "  Doctor selected: " << doctors[docChoice - 1] << "\n";
    }

    showTimeSlots();
    cout << "\n  Choose time slot (1-4): ";
    cin >> timeChoice;

    if (timeChoice < 1 || timeChoice > 4) {
        cout << "\n  [!] Invalid time slot selection.\n";
        return;
    } else {
        cout << "  Time slot selected: " << timeSlots[timeChoice - 1] << "\n";
    }

    patientNames[appointmentCount]    = name;
    patientAges[appointmentCount]     = age;
    patientDoctors[appointmentCount]  = doctors[docChoice - 1];
    appointmentTimes[appointmentCount] = timeSlots[timeChoice - 1];
    appointmentCount++;

    cout << "\n  [?] Appointment booked successfully!\n";
}

// view appt
void viewAppointments() {
    if (appointmentCount == 0) {
        cout << "\n  No appointments booked yet.\n";
    } else {
        cout << "\n  ------------------------------------------\n";
        cout << "   All Appointments (" << appointmentCount << ")\n";
        cout << "  ------------------------------------------\n";

        for (int i = 0; i < appointmentCount; i++) {
            cout << "\n  #" << (i + 1) << "\n";
            cout << "  Name   : " << patientNames[i] << "\n";
            cout << "  Age    : " << patientAges[i] << "\n";
            cout << "  Doctor : " << patientDoctors[i] << "\n";
            cout << "  Time   : " << appointmentTimes[i] << "\n";
        }
        cout << "\n  ------------------------------------------\n";
    }
}

// cancel appt
void cancelAppointment() {
    if (appointmentCount == 0) {
        cout << "\n  No appointments to cancel.\n";
        return;
    }

    viewAppointments();
    cout << "\n  Enter appointment # to cancel: ";
    int num;
    cin >> num;

    if (num < 1 || num > appointmentCount) {
        cout << "\n  [!] Invalid appointment number.\n";
    } else {
        string removedName = patientNames[num - 1];
        for (int i = num - 1; i < appointmentCount - 1; i++) {
            patientNames[i]    = patientNames[i + 1];
            patientAges[i]     = patientAges[i + 1];
            patientDoctors[i]  = patientDoctors[i + 1];
            appointmentTimes[i] = appointmentTimes[i + 1];
        }
        appointmentCount--;
        cout << "\n  [?] Appointment for " << removedName << " has been cancelled.\n";
    }
}

// search shts
void searchAppointment() {
    if (appointmentCount == 0) {
        cout << "\n  No appointments to search.\n";
        return;
    }

    cout << "\n  Enter patient name to search: ";
    cin.ignore();
    string keyword;
    getline(cin, keyword);

    bool found = false;
    for (int i = 0; i < appointmentCount; i++) {
        if (patientNames[i] == keyword) {
            cout << "\n  -- Found ------------------------------\n";
            cout << "  Name   : " << patientNames[i] << "\n";
            cout << "  Age    : " << patientAges[i] << "\n";
            cout << "  Doctor : " << patientDoctors[i] << "\n";
            cout << "  Time   : " << appointmentTimes[i] << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "\n  [!] No appointment found for \"" << keyword << "\".\n";
    }
}

// main 
int main() {
    int choice;
    bool running = true;

    cout << "\n  +--------------------------------------+\n";
    cout << "  ¦   SimpleClinic Appointment System    ¦\n";
    cout << "  +--------------------------------------+\n";

    while (running) {
        cout << "\n  +--------------------------------------+\n";
        cout << "  ¦  MAIN MENU                           ¦\n";
        cout << "  ¦  [1] Book Appointment                ¦\n";
        cout << "  ¦  [2] View All Appointments           ¦\n";
        cout << "  ¦  [3] Cancel Appointment              ¦\n";
        cout << "  ¦  [4] Search Appointment              ¦\n";
        cout << "  ¦  [5] Exit                            ¦\n";
        cout << "  +--------------------------------------+\n";
        cout << "  Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookAppointment();
                break;
            case 2:
                viewAppointments();
                break;
            case 3:
                cancelAppointment();
                break;
            case 4:
                searchAppointment();
                break;
            case 5:
                running = false;
                cout << "\n  Goodbye! Stay healthy.\n\n";
                break;
            default:
                cout << "\n  [!] Invalid choice. Try again.\n";
        }
    }

    return 0;
}
