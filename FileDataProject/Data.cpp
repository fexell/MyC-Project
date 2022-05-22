/*
*
* ====================
* Made by Felix Cervin *
* ====================
*
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <regex>
#include <iomanip>
#include <utility>

#include "Data.h"

Data::Data::Data() {

	LoadDataIntoVector();

}

std::vector<std::string> Data::Data::LoadDataIntoVector() {

	std::string data;

	std::ifstream in_file;
	in_file.open(file_name);

	if (in_file.is_open()) {
		while (in_file.good()) {
			std::getline(in_file, data);

			if (!data.empty() && std::find(dv.begin(), dv.end(), data) == dv.end())
				dv.push_back(data);
		}
	} else {
		std::cout << std::setw(50) << std::setfill('-') << "\n";
		std::cerr << "Error opening the file...\n";
	}

	in_file.close();

	return dv;
	
}

void Data::Data::InsertDataIntoFile() {

	std::ofstream out_file;
	out_file.open(file_name);

	if (out_file.is_open()) {
		for (auto& d : dv) {
			out_file << d << "\n";
		}
	}

	out_file.close();

}

void Data::Data::DisplayData() {

	for (auto& d : dv) {
		std::cout << d << "\n";
	}

}

void Data::Data::AddData() {

	std::smatch match;

	int i{ 1 };
	std::string input;

	std::cout << "Enter data to add: ";
	std::getline(std::cin, input);

	if (dv.size() != 0 && std::regex_search(dv.back(), match, find_number))
		i = (stoi(match.str(0)) + 1);

	dv.push_back((std::to_string(i) + ". " + input));

	std::cout << std::setw(50) << std::setfill('-') << "\n";
	std::cout << i << ". " << input << ", has been added.\n";

	// Update data.txt file
	InsertDataIntoFile();
	
}

void Data::Data::DeleteData() {

	std::string input;

	if (dv.size() != 0) {
		std::cout << "Enter the number of the entry to delete: ";
		std::getline(std::cin, input);

		if (std::regex_search(input, find_number) && !std::regex_search(input, find_zero)) {
			int i = stoi(input);
			dv.erase(dv.begin() + (i - 1));

			// Update data.txt file
			InsertDataIntoFile();
		} else {
			std::cerr << "Input needs to be a number, and cannot be 0...\n";
		}
	} else {
		std::cout << std::setw(50) << std::setfill('-') << "\n";
		std::cerr << "There is no data...\n";
	}

	Count();

}

void Data::Data::Count() {

	std::smatch match;

	if (dv.size() != 0) {
		for (int i = 0; i < dv.size(); i++) {
			if (std::regex_search(dv[i], match, fd)) {
				std::replace(dv.begin(), dv.end(), match.str(0), (std::to_string(i + 1) + ". " + match.str(2)));
			}
		}
		// Update data.txt file
		InsertDataIntoFile();
	} else {
		std::cout << std::setw(50) << std::setfill('-') << "\n";
		std::cerr << "There is no data...\n";
	}

}

void Data::Data::Swap() {

	std::smatch match;

	std::string input, input2;

	if (dv.size() != 0) {
		std::cout << "Enter the first number to swap with: ";
		std::getline(std::cin, input);
		std::cout << "Enter the second number to swap with: ";
		std::getline(std::cin, input2);

		auto last_data_number = std::regex_search(dv.back(), match, find_number);

		if (std::regex_search(input, find_number) && std::regex_search(input2, find_number)
			&& !std::regex_search(input, find_zero) && !std::regex_search(input2, find_zero)) {
			int n = stoi(input);
			int n2 = stoi(input2);

			if (n <= stoi(match.str(0)) && n2 <= stoi(match.str(0))) {
				if (n != n2) {
					// Swap the vector elements
					std::swap(dv[(n - 1)], dv[(n2 - 1)]);

					// Update data.txt file
					InsertDataIntoFile();

					// Order the data
					Count();
				} else {
					std::cout << std::setw(50) << std::setfill('-') << "\n";
					std::cerr << "You cannot swap with the same number...\n";
				}
			} else {
				std::cout << std::setw(50) << std::setfill('-') << "\n";
				std::cerr << "Input number cannot be above: " << match.str(0) << "\n";
			}
		} else {
			std::cout << std::setw(50) << std::setfill('-') << "\n";
			std::cerr << "Input needs to be a number, and cannot be 0...\n";
		}
	} else {
		std::cout << std::setw(50) << std::setfill('-') << "\n";
		std::cerr << "There is no data...\n";
	}

}

void Data::Data::Edit() {

	std::smatch match;

	std::string input, input2;

	if (dv.size() != 0) {
		std::cout << "Enter the number of the entry to edit: ";
		std::getline(std::cin, input);
		if (std::regex_search(input, match, find_number) && !std::regex_search(input, find_zero)) {
			int n = stoi(input);
			std::cout << "Enter what entry number \"" << n << "\" will be replaced with: ";
			std::getline(std::cin, input2);
			std::cout << dv[(n - 1)] << ", will be replaced with: ";
			std::replace(dv.begin(), dv.end(), dv[(n - 1)], (std::to_string(n) + ". " + input2));
			std::cout << dv[(n - 1)] << "\n";

			// Update data.txt file
			InsertDataIntoFile();
		} else {
			std::cout << std::setw(50) << std::setfill('-') << "\n";
			std::cerr << "Input needs to be a number, and cannot be 0...\n";
		}
	} else {
		std::cout << std::setw(50) << std::setfill('-') << "\n";
		std::cerr << "There is no data...\n";
	}

}

void Data::Data::Search() {

	std::string input;

	if (dv.size() != 0) {
		std::cout << "Enter your search term: ";
		std::getline(std::cin, input);
		std::cout << std::setw(50) << std::setfill('-') << "\n";

		std::regex search{ input, std::regex_constants::icase };

		//std::cout << std::setw(50) << std::setfill('-') << "\n";
		//std::cout << "SEARCH RESULT:" << "\n";

		for (auto& d : dv) {
			if (std::regex_search(d, search)) {
				std::cout << d << "\n";
			}
		}
	} else {
		std::cout << std::setw(50) << std::setfill('-') << "\n";
		std::cerr << "There is no data...\n";
	}

}
