#pragma once
#include <fstream>
#include <sstream>

class IOFile
{
public:
	// read whole file in text mode
	static std::string read(const std::string &fileName);

	// write the data to the file, old data from the file will be deleted.
	static void write(const std::string &fileName, const std::string &data);
	
private:
	IOFile() = delete;
	~IOFile() = delete;
};

