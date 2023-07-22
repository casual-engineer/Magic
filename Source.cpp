#include <iostream>
#include <string>
#include <windows.h>

void searchFiles(const std::string& searchPhrase, const std::string& directory) {
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile((directory + "\\*").c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		// Failed to open directory, but let's just return without an error message.
		// It might be a system directory or inaccessible folder.
		FindClose(hFind);
		return;
	}

	do {
		std::string fileName = findFileData.cFileName;
		if (fileName != "." && fileName != "..") {
			std::string fullPath = directory + "\\" + fileName;
			if (fileName.find(searchPhrase) != std::string::npos) {
				std::cout << fullPath << std::endl;
			}

			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				try {
					searchFiles(searchPhrase, fullPath);
				}
				catch (...) {
					// Catch any exceptions that might occur during the recursive search.
					// We're just going to ignore them and continue the search.
				}
			}
		}
	} while (FindNextFile(hFind, &findFileData) != 0);

	FindClose(hFind);
}

int main() {
	std::string searchPhrase;

	std::cout << "Enter the search phrase: ";
	std::getline(std::cin, searchPhrase);

	std::string cDrivePath = "C:\\"; // Change this path if you want to search in a different directory

	searchFiles(searchPhrase, cDrivePath);

	system("pause");
	return 0;
}
