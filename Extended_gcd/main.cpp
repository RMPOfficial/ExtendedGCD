#include <iostream>
#include <string>
#include "Extended_gcd.h"
using namespace std;
using namespace boost::multiprecision;

enum Flag : uint16_t {
	NEEDNUM0 = 1,
	NUM0SUBMITTED = 2,
	NEEDNUM1 = 4,
	NUM1SUBMITTED = 8,
	ONLYINVERSE = 16,
	ONLYGCD = 32,
	ONLYRESULT = 64,
	NOINPUT = 128,
	SHOWUSAGEINFO = 256,
	ONLYFLAG = 512,
	ARGSPRESENT = 1024
};

static string CharArrToStringCheckNum(char* strold, bool modulo) {
	bool badnumber = false;
	string str = string(strold);
	size_t str_len = str.size();

	if (str.empty() || str_len > 19) badnumber = true;

	if (!badnumber) {
		for (size_t i = 0; i < str_len; i++) {
			char c = str[i];
			if (c < '0' || c > '9') {
				badnumber = true;
			}
		}
	}

	while (badnumber) {
		cout << "Please enter a valid " << (modulo ? "modulo " : "") << "number: ";
		getline(cin, str);
		str_len = str.size();

		if (str.empty() || str_len > 19) {
			continue;
		}
		for (size_t i = 0; i < str_len; i++) {
			char c = str[i];
			if (c < '0' || c > '9') {
				continue;
			}
		} badnumber = false;
	} return str;
}

static uint8_t ArgsManagement(int argc, char* argv[], string& InputNumber, string& InputModulo, uint16_t& flags) {
	for (int i = 1; i < argc; i++) {
		if (flags & NEEDNUM0) {
			InputNumber = stoull(CharArrToStringCheckNum(argv[i], false));
			flags &= ~NEEDNUM0; flags |= NUM0SUBMITTED;
			continue;
		}
		if (flags & NEEDNUM1) {
			InputModulo = stoull(CharArrToStringCheckNum(argv[i], true));
			flags &= ~NEEDNUM1; flags |= NUM1SUBMITTED;
			continue;
		}
		if ((strcmp(argv[i], "-a") == 0) || (strcmp(argv[i], "-A") == 0) && !(flags & NUM0SUBMITTED)) {
			flags |= NEEDNUM0;
			if (!((i + 1) < argc)) goto errorcheck;
			continue;
		}
		if ((strcmp(argv[i], "-m") == 0) || (strcmp(argv[i], "-M") == 0) && !(flags & NUM1SUBMITTED)) {
			flags |= NEEDNUM1;
			if (!((i + 1) < argc)) goto errorcheck;
			continue;
		}
		if (argv[i][0] == '-') {
			for (int j = 1; argv[i][j] != '\0'; j++) {
				switch (argv[i][j]) {
				case 'h':
				case 'H':
					flags |= SHOWUSAGEINFO;
					break;
				case 'n':
				case 'N':
					flags |= NOINPUT;
					break;
				case 'i':
				case 'I':
					flags |= ONLYINVERSE;
					flags |= ONLYFLAG;
					break;
				case 'g':
				case 'G':
					flags |= ONLYGCD;
					flags |= ONLYFLAG;
					break;
				case 'r':
				case 'R':
					flags |= ONLYRESULT;
					flags |= ONLYFLAG;
					break;
				default:
					break;
				}
			}
		}

	}
errorcheck:
	if (flags & NEEDNUM0) {
		cout << "Bad usage of arguments! Valid usage: -a [Your Number]. Add -h / -H while starting the program to see the usage info.\n\n";
		cout << "Press ENTER to exit..";
		cin.get();
		return 15;
	}
	if (flags & NEEDNUM1) {
		cout << "Bad usage of arguments! Valid usage: -m [Your Modulo Number]. Add -h / -H while starting the program to see the usage info.\n\n";
		cout << "Press ENTER to exit..";
		cin.get();
		return 16;
	}

	if (flags & SHOWUSAGEINFO) {
		cout << "Usage: " << argv[0] << " -a [Your Number] -m [Your Modulo Number] [flags] or no arguments.\n\n";
		cout << "Flags:\n-n / -N: No input. If you dont have any of the numbers and this flag it will output nothing and exit.\n";
		cout << "-i / -I: Outputs only the modular inverse, if there is no modular inverse it outputs 0. Can mix with -g and -r.\n";
		cout << "-g / -G: Outputs only the GCD. Can mix with -i and -r.\n";
		cout << "-r / -R: Outputs only the result: (x * a) + (y * m). Can mix with -g and -i.\n";
		cout << "Output order: Result (-r), GCD (-g), Modular Inverse (-i).\n\n";
		cout << "Example usage: " << argv[0] << " -a 111 -m 991 -gi\n\n";
		cout << "Press ENTER to exit..";
		cin.get();
		return 1;
	}
	return 0;
}

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

int main(int argc, char* argv[]) {

	string InputNumber;
	string InputModulo;

	uint16_t flags = 0;
	if (argc != 1) {
		flags |= ARGSPRESENT;
		uint8_t result = ArgsManagement(argc, argv, InputNumber, InputModulo, flags);
		if (result != 0) {
			return 5;
		}

	}
	if (!(flags & ARGSPRESENT)) cout << "Welcome to a simple program made by @RMPOfficial to compute the GCD and the modular inverse.\n\n";
	bool firsttime = true;
num0:
	if (!(flags & NUM0SUBMITTED)) {
		if (flags & NOINPUT) return 3;
		cout << (firsttime ? "Please enter your number : " : "Please enter a valid number : ");
		firsttime = false;
		getline(cin, InputNumber);

		if (InputNumber.empty()) {
			goto num0;
		}
		for (char c : InputNumber) {
			if (NOTONLYNUMBERS) goto num0;
		}

		firsttime = true;
	}
num1:
	if (!(flags & NUM1SUBMITTED)) {
		if (flags & NOINPUT) return 4;
		cout << (firsttime ? "Now, please enter your modulo number: " : "Please enter a valid modulo number: ");
		firsttime = false;
		getline(cin, InputModulo);

		if (InputModulo.empty()) {
			goto num1;
		}
		for (char c : InputModulo) {
			if (NOTONLYNUMBERS) goto num1;
		}
	}

	if (!(flags & ARGSPRESENT)) {
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
	}

	cpp_int y;
	cpp_int x;
	cpp_int number(InputNumber);
	cpp_int mod_number(InputModulo);

	cpp_int result = extended_gcd(number, mod_number, y, x);
	if (flags & ONLYFLAG) {
		if (flags & ONLYRESULT) cout << "(" << y << " * " << InputModulo << ") + (" << x << " * " << InputNumber << ")\n";
		if (flags & ONLYGCD) cout << result << "\n";
		if (flags & ONLYINVERSE) {
			if (result != 1) cout << "0";
			else {
				if (x < 0) x += mod_number;
				cout << x << "\n";
			}
		}
	}
	else {
		cout << "\nResult: (" << y << " * " << InputModulo << ") + (" << x << " * " << InputNumber << ") = " << result << endl;

		if (x < 0) x += mod_number; // Calculating the modular inverse if x is a negative number

		if (result == 1) cout << "\nThe modular inverse of " << InputNumber << " modulo " << InputModulo << " is " << x;
		else cout << "\nThere is no modular inverse of " << InputNumber << " modulo " << InputModulo;
		if (!(flags & NOINPUT)) {
			cout << ".\n\nExit the program? [y/N]: ";
			uint8_t choice = ContinueChoice();
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
	return 0;
}
