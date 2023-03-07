#include <fstream>
#include <iostream>

using namespace std;

// Different OSs use different CLI commands to run Python
#ifdef _WIN32
// TODO: If your Windows machine runs Python in CLI with "python" instead of "py", update this line.
const string python = "python";
#else
// TODO: If your Mac/Linux machine runs Python in CLI with "python3" instead of "python", update this line.
const string python = "python";
#endif

/*
 * Prompts the user for a filename.
 * Allows the user to enter nothing to use the default pic (autumn.jpg).
 * If the file has extension jpg, jpeg, jpe, or png
 * and it exists in the project folder, return it.
 * Otherwise, return the default pic filename.
 */
string get_filename();

/*
 * Prints the main menu of options:
 * (a) flip, (b) mirror, (c) invert, or (d) exit
 */
void print_menu();

/*
 * Prompts the user for one of the options from the menu.
 * Validates input: makes sure the user enters exactly one character
 * and that it is one of the four valid options.
 * If it isn't valid, keep prompting for input until a valid option
 * is entered.
 */
char get_manip_choice();

int main() {
    cout << "Welcome to the image manipulator!" << endl;
    string filename = get_filename();
    cout << "Using file " << filename << "." << endl;
    print_menu();
    char choice = get_manip_choice();
    cout << "Processing. Go to Python program when it opens. May take a few seconds." << endl;
    string command;
    switch (choice) {
        // Use command-line arguments to pass the filename and manip to the Python file
        case 'a':
            command = python + " ../render.py " + filename + " flip";
            break;
        case 'b':
            command = python + " ../render.py " + filename + " mirror";
            break;
        case 'c':
            command = python + " ../render.py " + filename + " invert";
            break;
    }
    system(command.c_str());
    return 0;
}

string get_filename() {
    string path = "autumn.jpg";
    cout << "Enter image path: ../";
    string input;
    getline(cin, input);

    // Keep path as default if no input is entered
    if (input.empty()) {
        cout << "No input detected! Using default: autumn.jpg" << endl;
    } else if (input.find(".jpg") != string::npos || input.find(".jpeg") != string::npos ||
               input.find(".jpe") != string::npos || input.find(".png") != string::npos) {
        // Check that the file exist within project folder
        input = "../" + input;
        ifstream file;
        file.open(input);
        if (file) {
            cout << "Success!" << endl;
            path = input;
        } else {
            cout << "File not found. Using default: autumn.jpg" << endl;
        }
        file.close();
    } else {
        cout << "Invalid file extension. Using default: autumn.jpg" << endl;
    }
    return path;
}

void print_menu() {
    cout << "Options: (a) flip, (b) mirror, (c) invert, or (d) exit" << endl;
}

char get_manip_choice() {
    string input;
    string prompt = "Enter a single character from the above options: ";
    cout << prompt;
    getline(cin, input);

    // Re-prompts user for input if more or less than 1 character is entered
    while (input.length() != 1 || (input != "a" && input != "b" && input != "c" && input != "d")) {
        if (input.length() < 1) {
            cout << "No input. ";
        } else if (input.length() > 1) {
            cout << "Invalid input length. ";
        } else {
            cout << "Invalid option. ";
        }
        cout << prompt;
        getline(cin, input);
    }
    return input[0];
}
