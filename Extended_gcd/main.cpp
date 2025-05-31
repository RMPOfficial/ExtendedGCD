#include <iostream>
#include <string>
#include "Extended_gcd.h"
using namespace std;
using namespace boost::multiprecision;

static uint8_t ContinueChoice() {
    std::string Response;
    std::getline(std::cin, Response);
    if (Response[0] != 'y' && Response[0] != 'Y' && Response[0] != 'n' && Response[0] != 'N') {
        do {
            std::cout << "Enter a valid input: [y/N] or ENTER to exit the program: ";
            std::getline(std::cin, Response);
        } while (!Response.empty() && Response[0] != 'y' && Response[0] != 'Y' && Response[0] != 'n' && Response[0] != 'N');
    }

    if (Response.empty()) {
        return EXIT;
    }
    else if (Response[0] == 'y' || Response[0] == 'Y') {
        return YES;
    }
    else {
        return NO;
    }
}

int main() {
    bool firsttime = true;
    string InputNumber;
num0:
    cout << (firsttime ? "Welcome to a simple program made by @RMPOfficial to demonstrate how the alghorytm works\n\nPlease enter your number: " : "Please enter a valid number: ");
    firsttime = false;
    getline(cin, InputNumber);

    if (InputNumber.empty()) {
        goto num0;
    }
    for (char c : InputNumber) {
        if (NOTONLYNUMBERS) goto num0;
    }

    firsttime = true;
    string InputModulo;
num1:
    cout << (firsttime ? "Now, please enter your modulo number: " : "Please enter a valid modulo number: ");
    firsttime = false;
    getline(cin, InputModulo);

    if (InputModulo.empty()) {
        goto num1;
    }
    for (char c : InputModulo) {
        if (NOTONLYNUMBERS) goto num1;
    }

    firsttime = true;
    cout << "You chose " << InputNumber << " as your number and " << InputModulo << " as your modulo number.\nContinue? [y/n]: ";
    uint8_t choice = ContinueChoice();
    if (choice == EXIT) {
        cout << "\nPress ENTER to exit..";
        cin.get();
        return -1;
    }
    else if (choice == NO) {
        cout << "You cancelled, returning to the beggining of the program..\n\n";
        goto num0;
    }

    cpp_int y;
    cpp_int x;
    cpp_int number(InputNumber);
    cpp_int mod_number(InputModulo);

    cpp_int result = extended_gcd(number, mod_number, y, x);

    cout << "\nResult: (" << y << " * " << InputModulo << ") + (" << x << " * " << InputNumber << ") = " << result << endl;

    if (x < 0) x += mod_number; // Calculating the modular inverse if x is a negative number

    if (result == 1) {
        cout << "\nThe modular inverse of " << InputNumber << " modulo " << InputModulo << " is " << x << ".\n\nExit the program? [y/N]: ";
        choice = ContinueChoice();
        if (choice == EXIT || choice == YES) {
            cout << "\nPress ENTER to exit..";
            cin.get();
            return 0;
        }
        else {
            cout << "Returning to the beggining of the program..\n\n";
            goto num0;
        }
    }
    else {
        cout << "\nThere is no modular inverse of " << InputNumber << " modulo " << InputModulo << ".\n\nExit the program? [y/N]: ";
        choice = ContinueChoice();
        if (choice == EXIT || choice == YES) {
            cout << "\nPress ENTER to exit..";
            cin.get();
            return 0;
        }
        else {
            cout << "Returning to the beggining of the program..\n\n";
            goto num0;
        }
    }
}