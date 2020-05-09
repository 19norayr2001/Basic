#pragma once
#include <iostream>
#include <vector>
#include <string>

class File;
class Document;
class Link;
class DynamicLink;
class HardLink;
class Directory;

class File
{
public:
	File(const std::string& filename)
		:m_name(filename)
	{}
	const std::string& GetName() const { return m_name; }
	virtual ~File() {}
protected:
	std::string m_name;
};


class Document :public File
{
public:
	Document(const std::string& name)
		:File(name)
		, m_HardLinkCount(0)
	{}
	~Document() { Deallocate(); }
public:
	void AddHardLink() { ++m_HardLinkCount; }
	void RemoveHardLink() { --m_HardLinkCount; }
	void AddDynamicLink(Directory* link) { m_DynamicLinks.push_back(link); }
	void RemoveDynamicLink(Directory*);
	bool CheckHardLinkCount() const { return m_HardLinkCount == 0; }

private:
	void Deallocate();
private:
	int m_HardLinkCount;
	std::vector<Directory*> m_DynamicLinks;
};

class Directory :public File
{
public:
	Directory(const std::string&);
	~Directory();
private:
	void Deallocate();
public:
	void print(std::ostream&, int = 0) const;
public:
	bool empty() const { return m_Files.size() == 0; }
	void AddFolder(const std::string&);
	void AddFile(const std::string&);
	void AddHardLink(const std::string&, const Document*);
	void AddDynamicLink(const std::string&, const Document*);
	void RemoveFolder(const std::string&, const Directory*);
	void RemoveTree(const std::string&, const Directory*);
	void RemoveFile(const std::string&, Directory*);
	void RemoveDynamicLink(const Document*);
	void IncrementHardLinkCount(const std::string& path);
	void DecrementHardLinkCount(const std::vector<std::string>&, int = 1);
	Directory* SearchFolder(const std::string& path);
	Document* SearchDocument(const std::string&);
	DynamicLink* SearchDynamicLink(const std::string&);
private:
	bool CheckTree(const Directory*, const Directory*);
	void IncrementHardLinkCount(const std::vector<std::string>&, int = 1);
	Directory* SearchFolder(const std::vector<std::string>&, int = 0);
private:
	std::vector<File*> m_Files;
	int m_CountOfHardLinks;
};

class Link : public File
{
public:
	Link(const std::string& name, const Document* file)
		:File(name)
		, m_file(file)
	{}
	const std::string GetPath() const
	{
		const std::string& name = this->GetName();
		int len = name.size();
		return name.substr(6, len - 7);
	}
	const Document* GetFile() const { return m_file; }
private:
	const Document* m_file;
};

class DynamicLink :public Link 
{
public:
	DynamicLink(const std::string& path, const Document* file)
		:Link("dlink[" + path + "]", file)
	{}
	void ChangePath(const std::string& path)
	{
		m_name = "dlink[" + path + "]";
	}
};

class HardLink :public Link
{
public:
	HardLink(const std::string& path, const Document* file)
		:Link("hlink[" + path + "]", file)
	{}
};

class FileManager
{
	typedef std::vector<std::string> StringVector;
	typedef void(FileManager::* OneArgCommandFunction)(const std::string&);
	typedef void(FileManager::* TwoArgCommandFunction)(const std::string&, const std::string&);

	friend std::ostream& operator<<(std::ostream&, const FileManager&);

public:

	FileManager();
	FileManager(const FileManager&) = delete;
	FileManager& operator=(const FileManager&) = delete;
	~FileManager();

public:

	void Command(const std::string&);
	static OneArgCommandFunction CheckOneArgumentCommand(const std::string&, int);
	static TwoArgCommandFunction CheckTwoArgumentCommand(const std::string&, int);

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

	void LinkCase(const std::string&, const std::string&, Directory*&, Document*&, Directory*&);
	const std::string GetFullPath(const std::string&);
	Directory* GetParent(const std::string&, std::string&);
	Directory* GetParent(const std::string&);

private:

	Directory* m_root;
	Directory* m_CurrentDirectory;
	std::string m_CurrentDirectoryPath;
};

