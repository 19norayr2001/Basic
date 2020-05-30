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
	File(const std::string& filename, Directory* const root)
		:m_name(filename)
		,m_root(root)
	{}
	const std::string& GetName() const { return m_name; }
//	virtual void allocate(const File* const) = 0;
	virtual ~File() {}
protected:
	Directory* const GetRoot();
	const Directory* const GetRoot() const;
protected:
	std::string m_name;
	Directory* const m_root;
};


class Document :public File
{
public:
	Document(const std::string& name, Directory* const root)
		:File(name, root)
		, m_HardLinkCount(0)
	{}
	~Document() { Deallocate(); }
public:
	void AddHardLink() { ++m_HardLinkCount; }
	void RemoveHardLink() { --m_HardLinkCount; }
	void AddDynamicLink(Directory* parent) { m_DynamicLinks.push_back(parent); }
	void RemoveDynamicLink(Directory*);
	bool CheckHardLinkCount() const { return m_HardLinkCount == 0; }
	Directory* FindParentDynamicLink(const DynamicLink* const) const;
private:
	void Deallocate();
private:
	int m_HardLinkCount;
	std::vector<Directory*> m_DynamicLinks;
};

class Directory :public File
{
public:
	Directory(const std::string&, Directory* const = nullptr);
	~Directory();
private:
	void Deallocate();
public:
	void print(std::ostream&, int = 0) const;
public:
	bool empty() const { return m_Files.size() == 0; }
	void AddFolder(const std::string&);
	void AddFile(const std::string&);
	void AddHardLink(const std::string&, Document*, Directory*);
	void AddDynamicLink(const std::string&, Document*, Directory*);
	void RemoveFolder(const std::string&, const Directory*);
	void RemoveTree(const std::string&, const Directory*);
	void RemoveFile(const std::string&, Directory*);
	void RemoveDynamicLink(const Document*);
	void IncrementHardLinkCount(const std::string&);
	void DecrementHardLinkCount(const std::string&);
	void Copy(const File* const);
	Directory* SearchFolder(const std::string&);
	Document* SearchDocument(const std::string&);
	DynamicLink* SearchDynamicLink(const std::string&);
	const File* const SearchFile(const std::string&) const;
	bool SearchDynamicLink(const DynamicLink* const);
private:
	void DeleteObject(int);
	bool HasFileWithSameName(const std::string&) const;
	bool CheckTree(const Directory*, const Directory*);
	void IncrementHardLinkCount(const std::vector<std::string>&, int = 1);
	void DecrementHardLinkCount(const std::vector<std::string>&, int = 1);
	Directory* SearchFolder(const std::vector<std::string>&, int = 0);
private:
	std::vector<File*> m_Files;
	int m_CountOfHardLinks;
};

class Link : public File
{
public:
	Link(const std::string& name, Document* file, Directory* const root)
		:File(name, root)
		, m_file(file)
	{}
	const std::string GetPath() const
	{
		const std::string& name = this->GetName();
		int len = name.size();
		return name.substr(6, len - 7);
	}
	Document* GetFile() const { return m_file; }
private:
	Document* const m_file;
};

class DynamicLink :public Link 
{
public:
	DynamicLink(const std::string& path, Document* file, Directory* const root)
		:Link("dlink[" + path + "]", file, root)
	{}
	~DynamicLink() { Deallocate(); }
	void ChangePath(const std::string& path)
	{
		m_name = "dlink[" + path + "]";
	}
private:
	void Deallocate();
};

class HardLink :public Link
{
public:
	HardLink(const std::string& path, Document* file, Directory* const root)
		:Link("hlink[" + path + "]", file, root)
	{
		root->IncrementHardLinkCount(path);
	}
	~HardLink() { Deallocate(); }
private:
	void Deallocate();
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

	void LinkCase(const std::string&, const std::string&, Directory*&, Document*&);
	const std::string GetFullPath(const std::string&);
	Directory* GetParent(const std::string&, std::string&);
	Directory* GetParent(const std::string&);

private:

	Directory*const m_root;
	Directory* m_CurrentDirectory;
	std::string m_CurrentDirectoryPath;
};

