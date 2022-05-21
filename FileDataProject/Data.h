#ifndef _DATA_H_
#define _DATA_H_

#include <vector>
#include <string>
#include <regex>

namespace Data {
	class Data {
		private:
			// dv = data vector
			std::vector<std::string> dv;
			const std::string& file_name{ "data.txt" };
			// fd = find data
			std::regex fd{ "(\\d+\.?\\s+?)?(.*)" };
			std::regex find_number{ "(\\d+)" };
			std::regex find_zero{ "0" };
		public:
			Data();
			std::vector<std::string> LoadDataIntoVector();
			void InsertDataIntoFile();
			void DisplayData();
			void AddData();
			void DeleteData();
			void Count();
			void Swap();
			void Edit();
			void Search();
	};
}

#endif