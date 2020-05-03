#include "FileManager.h"
#include <exception>
#include <cctype>



FileManager::FileManager()
	:m_root(new Directory("C:"))
	, current_directory(m_root)
{}

FileManager::FileManager(const FileManager& obj)
{}

FileManager& FileManager::operator=(const FileManager& obj)
{
	if (this != &obj)
	{

	}
	return *this;
}

FileManager::~FileManager()
{

}

void FileManager::Command(const std::string& command)
{
	StringVector args;
	GetArgs(args, command);

}

void FileManager::ChangeDirectory(const std::string& s) {}
void FileManager::MakeDirectory(const std::string& s) {}
void FileManager::RemoveDirectory(const std::string& s) {}
void FileManager::DeleteTree(const std::string& s) {}
void FileManager::MakeFile(const std::string& s) {}
void FileManager::MakeHardLink(const std::string& s, const std::string& t) {}
void FileManager::MakeDynamicLink(const std::string& s, const std::string& t) {}
void FileManager::Delete(const std::string& s) {}
void FileManager::Copy(const std::string& s, const std::string& t) {}
void FileManager::Move(const std::string& s, const std::string& t) {}



void FileManager::GetArgs(FileManager::StringVector& args, const std::string& command)
{
	std::string next_command;
	int len = command.size();
	for (int i = 0; i < len; ++i)
	{
		if (!isspace(command[i]))
		{
			next_command += tolower(command[i]);
		}
		else
		{
			if (!next_command.empty())
			{
				args.push_back(next_command);
				next_command = "";
			}
			while (i < len && isspace(command[i]))
			{
				i++;
			}
			i--;
		}
	}
	if (!next_command.empty())
	{
		args.push_back(next_command);
	}
}

FileManager::OneArgCommandFunction FileManager::CheckOneArgumentCommand(const std::string& command, int count)
{
	const static StringVector command_names{ "md", "cd", "rd", "deltree", "mf", "del",};
	const static std::vector<OneArgCommandFunction> Functions
	{
		&FileManager::MakeDirectory,
		&FileManager::ChangeDirectory,
		&FileManager::RemoveDirectory,
		&FileManager::DeleteTree,
		&FileManager::MakeFile,
		&FileManager::Delete,
	};
	int len = command_names.size();
	for (int i = 0; i < len; ++i)
	{
		if (command_names[i] == command)
		{
			if (count == 1)
				return Functions[i];
			else
				throw std::exception("Too many arguments");
		}
	}
	return nullptr;
}

FileManager::TwoArgCommandFunction FileManager::CheckTwoArgumentCommand(const std::string& command, int count)
{
	const static StringVector command_names{ "mhl", "mdl", "copy", "move" };
	const static std::vector<TwoArgCommandFunction> Functions
	{
		&FileManager::MakeHardLink,
		&FileManager::MakeDynamicLink,
		&FileManager::Copy,
		&FileManager::Move,
	};
	int len = command_names.size();
	for (int i = 0; i < len; ++i)
	{
		if (command_names[i] == command)
		{
			if (count == 2)
				return Functions[i];
			else
				throw std::exception("Too many arguments");
		}
	}
	return nullptr;
}