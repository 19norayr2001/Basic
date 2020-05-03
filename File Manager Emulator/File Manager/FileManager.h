#pragma once
#include <iostream>
#include <vector>
#include <string>
class File
{
public:
	File(const std::string& filename)
		:name(filename)
	{}
	std::string name;
};

class Directory :public File
{
public:
	Directory(const std::string& filename)
		:File(filename)
	{}
	std::vector<File*> Files;
	void AddFile(File* file)
	{
		Files.push_back(file);
	}
	void DeallocateFileTree(File* file)
	{
		for (File* mfile : Files)
		{
			DeallocateFileTree(mfile);
		}
		delete file;
	}
};

class DynamicLink :public File 
{
public:
	DynamicLink(const std::string& path)
		:File(path)
	{}
};

class HardLink :public File
{
public:
	HardLink(const std::string& path)
		:File(path)
	{}
};

class Document :public File
{
public:
	Document(const std::string& name)
		:File(name)
	{}
};
class FileManager
{
	typedef std::vector<std::string> StringVector;
	typedef void(FileManager::* OneArgCommandFunction)(const std::string&);
	typedef void(FileManager::* TwoArgCommandFunction)(const std::string&, const std::string&);
public:
	FileManager();
	FileManager(const FileManager&);
	FileManager& operator=(const FileManager&);
	~FileManager();
	void Command(const std::string&);
private:

	void ChangeDirectory(const std::string&);
	void MakeDirectory(const std::string&);
	void RemoveDirectory(const std::string&);
	void DeleteTree(const std::string&);
	void MakeFile(const std::string&);
	void MakeHardLink(const std::string&, const std::string&);
	void MakeDynamicLink(const std::string&, const std::string&);
	void Delete(const std::string&);
	void Copy(const std::string&, const std::string&);
	void Move(const std::string&, const std::string&);

private:
	void GetArgs(StringVector&, const std::string&);
	OneArgCommandFunction CheckOneArgumentCommand(const std::string&, int);
	TwoArgCommandFunction CheckTwoArgumentCommand(const std::string&, int);
private:
	File* m_root;
	File* current_directory;

};

