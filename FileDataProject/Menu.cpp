/*
*
* ====================
* Made by Felix Cervin *
* ====================
*
*/

#include <iostream>
#include <regex>
#include <string>
#include <iomanip>
#include <Windows.h>

#include "Menu.h"
#include "Data.h"

Menu::Menu::Menu() {

	Data::Data data;

	std::regex find_zero{ "0" };
	std::regex find_number{ "[1-9]" };

	std::string input;

	do {

		std::cout << std::setw(50) << std::setfill('-') << "\n";
		std::cout << std::setw(25) << std::setfill('-') << "MENU" << std::setw(25) << std::setfill('-') << "\n";
		std::cout << std::setw(50) << std::setfill('-') << "\n";

		std::cout << "1. Display Data\n";
		std::cout << "2. Add Data\n";
		std::cout << "3. Delete Data\n";
		std::cout << "4. Swap Data\n";
		std::cout << "5. Edit\n";
		std::cout << "6. Search\n";
		std::cout << "0. Exit Program\n";

		std::cout << std::setw(50) << std::setfill('-') << "\n";

		std::cout << "Enter Menu Option: ";
		std::getline(std::cin, input);

		std::cout << std::setw(50) << std::setfill('-') << "\n";

		if (std::regex_search(input, find_number)) {
			int i = stoi(input);

			switch (i) {
				case 1:
					data.DisplayData();
					break;
				case 2:
					data.AddData();
					break;
				case 3:
					data.DeleteData();
					break;
				case 4:
					data.Swap();
					break;
				case 5:
					data.Edit();
					break;
				case 6:
					data.Search();
					break;
			}
		}


	} while (!std::regex_match(input, find_zero));

}