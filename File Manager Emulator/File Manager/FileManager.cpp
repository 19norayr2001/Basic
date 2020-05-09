#include "FileManager.h"
#include <exception>
#include <cctype>

namespace
{
	typedef std::vector<std::string> VectorString;

	void ToLower(std::string& s)
	{
		for (char& elem : s)
		{
			elem = tolower(elem);
		}
	}

	int Drop(int x)
	{
		return x == '/';
	}

	void Concatenate(std::vector<std::string>& vec1, const std::vector<std::string>& vec2)
	{
		for (const std::string& s: vec2)
		{
			vec1.push_back(s);
		}
	}

	bool IsFullPath(const std::string& path)
	{
		return path.size() >= 2 && path[0] == 'C' && path[1] == ':';
	}

	const std::string GetLastComponent(const std::string& path)
	{
		int len = path.size();
		std::string ret;
		int i = len - 1;
		for (; i >= 0; --i)
		{
			if (path[i] == '/')
				break;
		}
		for (i = i + 1; i < len; ++i)
			ret += path[i];
		return ret;
	}

	const std::string SubString(const std::string& str, int left, int right)
	{
		return str.substr(left, str.size() - left - right);
	}

	void ParsingCommands(VectorString& args, const std::string& str, int(*predicat)(int))
	{
		std::string next_command;
		int len = str.size();
		for (int i = 0; i < len; ++i)
		{
			if (!predicat(str[i]))
			{
				next_command += str[i];
			}
			else
			{
				if (!next_command.empty())
				{
					args.push_back(next_command);
					next_command = "";
				}
				while (i < len && predicat(str[i]))
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

	void GetArgs(VectorString& args, const std::string& command)
	{
		ParsingCommands(args, command, isspace);
		if (!args.empty())
		{
			ToLower(args[0]);
		}
	}

	void GetPathArgs(VectorString& files, const std::string& path)
	{
		ParsingCommands(files, path, Drop);
	}

	void PrintNode(const File* file, std::ostream& out, int layer = 0)
	{
		if (layer != 0)
			out << '|';
		for (int i = 0; i < layer - 1; ++i)
			out << "\t|";
		if (layer != 0)
			out << '_';
		out << file->GetName();
		const Directory* folder = dynamic_cast<const Directory*>(file);
		if (folder == nullptr)
		{
			out << std::endl;
			return;
		}
		out << std::endl;
		folder->print(out, layer + 1);
	}
}

std::ostream& operator<<(std::ostream& out, const FileManager& filemanager)
{
	const Directory* root = filemanager.m_root;
	PrintNode(root, out);
	return out;
}


FileManager::FileManager()
	:m_root(new Directory("C:"))
	, m_CurrentDirectory(m_root)
	, m_CurrentDirectoryPath("C:")
{}

FileManager::~FileManager()
{
	delete m_root;
}

void FileManager::Command(const std::string& command)
{
	StringVector args;
	GetArgs(args, command);
	if (args.empty())
		return;
	const std::string& first = args[0];
	int count = args.size() - 1;
	OneArgCommandFunction func1 = CheckOneArgumentCommand(first, count);
	if (func1 != nullptr)
	{
		(this->*func1)(args[1]);
		return;
	}
	TwoArgCommandFunction func2 = CheckTwoArgumentCommand(first, count);
	if (func2 != nullptr)
	{
		(this->*func2)(args[1], args[2]);
		return;
	}
	throw std::exception("Command not found");
}

FileManager::OneArgCommandFunction FileManager::CheckOneArgumentCommand(const std::string& command, int count)
{
	const static StringVector command_names{ "md", "cd", "rd", "deltree", "mf", "del", };
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
			else if (count > 1)
				throw std::exception("Too many arguments");
			else
				throw std::exception("Mising argument");
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
			else if (count > 2)
				throw std::exception("Too many arguments");
			else
				throw std::exception("Mising argument");
		}
	}
	return nullptr;
}

void FileManager::ChangeDirectory(const std::string& path)
{
	bool pathflag = IsFullPath(path);
	const std::string& my_path = (pathflag ? SubString(path, 2, 0) : path);
	Directory* cur = (pathflag ? m_root : m_CurrentDirectory);
	m_CurrentDirectory = cur->SearchFolder(my_path);
	if (pathflag)
		m_CurrentDirectoryPath = path;
	else
		m_CurrentDirectoryPath += path;
}

void FileManager::MakeDirectory(const std::string& path)
{
	std::string FileName;
	Directory* parent = GetParent(path, FileName);
	parent->AddFolder(FileName);
}

void FileManager::RemoveDirectory(const std::string& path)
{
	if (path == "C:")
		throw std::exception("Not allowed remove root");
	std::string FileName;
	Directory* parent = GetParent(path, FileName);
	parent->RemoveFolder(FileName, m_CurrentDirectory);
}

void FileManager::DeleteTree(const std::string& path)
{
	if (path == "C:")
		throw std::exception("Not allowed remove root");
	std::string FileName;
	Directory* parent = GetParent(path, FileName);
	parent->RemoveTree(FileName, m_CurrentDirectory);
}

void FileManager::MakeFile(const std::string& path)
{
	std::string FileName;
	Directory* parent = GetParent(path, FileName);
	parent->AddFile(FileName);
}

void FileManager::MakeHardLink(const std::string& document_path, const std::string& link_path)
{
	Document* document{};
	Directory* link_location{};
	Directory* parent{};
	const std::string& full_path = GetFullPath(document_path);
	LinkCase(document_path, link_path, link_location, document, parent);
	link_location->AddHardLink(full_path, document);
	document->AddHardLink();
	m_root->IncrementHardLinkCount(full_path);
}

void FileManager::MakeDynamicLink(const std::string& document_path, const std::string& link_path)
{
	Document* document{};
	Directory* link_location{};
	Directory* parent{};
	const std::string& full_path = GetFullPath(document_path);
	LinkCase(document_path, link_path, link_location, document, parent);
	link_location->AddDynamicLink(full_path, document);
	document->AddDynamicLink(parent);
}

void FileManager::Delete(const std::string& path)
{
	if (path == "C:")
		throw std::exception("Is a directory");
	std::string FileName;
	Directory* parent = GetParent(path, FileName);
	parent->RemoveFile(FileName, m_root);
}

void FileManager::Copy(const std::string& file_path, const std::string& loc_path){} //TODO
void FileManager::Move(const std::string& file_path, const std::string& loc_path){} //TODO

void FileManager::LinkCase(
	const std::string& document_path,
	const std::string& link_path,
	Directory*& link_location,
	Document*& document,
	Directory*& parent)
{
	std::string FileName;
	parent = GetParent(document_path, FileName);
	document = parent->SearchDocument(FileName);

	link_location = GetParent(link_path);
}

const std::string FileManager::GetFullPath(const std::string& path)
{
	return (IsFullPath(path) ? "" : m_CurrentDirectoryPath) + path;
}

Directory* FileManager::GetParent(const std::string& path, std::string& FileName)
{
	bool pathflag = IsFullPath(path);
	Directory* cur = (pathflag ? m_root : m_CurrentDirectory);
	FileName = GetLastComponent(path);
	return cur->SearchFolder(SubString(path, 2 * pathflag, FileName.size()));
}

Directory* FileManager::GetParent(const std::string& path)
{
	bool pathflag = IsFullPath(path);
	Directory* cur = (pathflag ? m_root : m_CurrentDirectory);
	return cur->SearchFolder(SubString(path, 2 * pathflag, 0));
}
















Directory::Directory(const std::string& filename)
	:File(filename)
	, m_CountOfHardLinks(0)
{}

Directory::~Directory()
{
	Deallocate();
}

void Directory::Deallocate()
{
	int len = m_Files.size();
	for (int i = 0; i < len; ++i)
	{
		delete m_Files[i];
	}
}

void Directory::print(std::ostream& out, int layer) const
{
	int len = m_Files.size();
	for (int i = 0; i < len; ++i)
	{
		PrintNode(m_Files[i], out, layer);
	}
}

void Directory::AddFolder(const std::string& name)
{
	for (File* file : m_Files)
	{
		if (file->GetName() == name)
		{
			if (dynamic_cast<Directory*>(file) == nullptr)
				throw std::exception("File exists");
			else
				return;
		}
	}
	m_Files.push_back(new Directory(name));
}

void Directory::AddFile(const std::string& name)
{
	for (File* file : m_Files)
	{
		if (file->GetName() == name)
		{
			return;
		}
	}
	m_Files.push_back(new Document(name));
}

void Directory::AddHardLink(const std::string& path, const Document* file)
{
	m_Files.push_back(new HardLink(path, file));
}

void Directory::AddDynamicLink(const std::string& path, const Document* file)
{
	m_Files.push_back(new DynamicLink(path, file));
}

void Directory::RemoveFolder(const std::string& name, const Directory* cur)
{
	int len = m_Files.size();
	for (int i = 0; i < len; ++i)
	{
		File* file = m_Files[i];
		if (file->GetName() == name)
		{
			Directory* myfolder = dynamic_cast<Directory*>(file);
			if (myfolder == nullptr)
				throw std::exception("Not a directory");
			else if (!myfolder->empty())
				throw std::exception("Directory not empty");
			else if (myfolder == cur)
				throw std::exception("Not allowed remove current directory");
			else
			{
				delete myfolder;
				m_Files.erase(m_Files.begin() + i);
			}
			return;
		}
	}
	throw std::exception("No such file or directory");
}

void Directory::RemoveTree(const std::string& name, const Directory* cur)
{
	int len = m_Files.size();
	for (int i = 0; i < len; ++i)
	{
		File* file = m_Files[i];
		if (file->GetName() == name)
		{
			Directory* myfolder = dynamic_cast<Directory*>(file);
			if (myfolder == nullptr)
				throw std::exception("Not a directory");
			else if (!CheckTree(myfolder, cur))
				throw std::exception("Not allowed remove current directory");
			else if (m_CountOfHardLinks > 0)
				throw std::exception("Not allowed remove folder containing hard links");
			else
			{
				delete myfolder;
				m_Files.erase(m_Files.begin() + i);
			}
			return;
		}
	}
	throw std::exception("No such file or directory");
}

void Directory::RemoveFile(const std::string& name, Directory* root)
{
	int len = m_Files.size();
	for (int i = 0; i < len; ++i)
	{
		if (m_Files[i]->GetName() == name)
		{
			Directory* folderptr = dynamic_cast<Directory*>(m_Files[i]);
			if (folderptr != nullptr)
				throw std::exception("Is a directory");
			HardLink* hlink = dynamic_cast<HardLink*>(m_Files[i]);
			if (hlink != nullptr)
			{
				const std::string& path = hlink->GetPath();
				std::vector<std::string> path_vector;
				GetPathArgs(path_vector, path);
				root->DecrementHardLinkCount(path_vector);
				delete m_Files[i];
				m_Files.erase(m_Files.begin() + i);
				return;
			}
			DynamicLink* dlink = dynamic_cast<DynamicLink*>(m_Files[i]);
			if (dlink != nullptr)
			{
				const std::string& path = dlink->GetPath();
				std::vector<std::string> path_vector;
				GetPathArgs(path_vector, path);
				const std::string& filename = path_vector.back();
				path_vector.pop_back();
				Directory* parent = root->SearchFolder(path_vector, 1);
				Document* doc = parent->SearchDocument(filename);
				doc->RemoveDynamicLink(this);
				delete m_Files[i];
				m_Files.erase(m_Files.begin() + i);
			}
			Document* doc = dynamic_cast<Document*>(m_Files[i]);
			if (doc != nullptr)
			{
				if (doc->CheckHardLinkCount())
				{
					delete m_Files[i];
					m_Files.erase(m_Files.begin() + i);
					return;
				}
				throw std::exception("File contains hard links");
			}
		}
	}
}

void Directory::RemoveDynamicLink(const Document* file)
{
	int len = m_Files.size();
	for (int i = 0; i < len; ++i)
	{
		DynamicLink* dlink = dynamic_cast<DynamicLink*>(m_Files[i]);
		if (dlink != nullptr && dlink->GetFile() == file)
		{
			delete dlink;
			m_Files.erase(m_Files.begin() + i);
			return;
		}
	}
}

void Directory::IncrementHardLinkCount(const std::string& path)
{
	VectorString pathvector;
	GetPathArgs(pathvector, path);
	IncrementHardLinkCount(pathvector);
}

void Directory::IncrementHardLinkCount(const std::vector<std::string>& pathvector, int ind)
{
	m_CountOfHardLinks++;
	if (ind == pathvector.size() - 1)
	{
		return;
	}
	for (File* file : m_Files)
	{
		Directory* folder = dynamic_cast<Directory*>(file);
		if (folder != nullptr)
		{
			folder->IncrementHardLinkCount(pathvector, ind + 1);
			return;
		}
	}
}

void Directory::DecrementHardLinkCount(const std::vector<std::string>& pathvector, int ind)
{
	m_CountOfHardLinks--;
	if (ind == pathvector.size() - 1)
	{
		Document* doc = this->SearchDocument(pathvector.back());
		doc->RemoveHardLink();
		return;
	}
	for (File* file : m_Files)
	{
		Directory* folder = dynamic_cast<Directory*>(file);
		if (folder != nullptr)
		{
			folder->IncrementHardLinkCount(pathvector, ind + 1);
			return;
		}
	}
}

Directory* Directory::SearchFolder(const std::string& path)
{
	VectorString path_vector;
	GetPathArgs(path_vector, path);
	return SearchFolder(path_vector);
}

bool Directory::CheckTree(const Directory* folder, const Directory* cur)
{
	if (folder == cur)
		return false;
	int len = folder->m_Files.size();
	for (int i = 0; i < len; ++i)
	{
		Directory* folderptr = dynamic_cast<Directory*>(folder->m_Files[i]);
		if (folderptr != nullptr)
		{
			bool flag = CheckTree(folderptr, cur);
			if (!flag)
				return false;
		}
	}
	return true;
}

Directory* Directory::SearchFolder(const std::vector<std::string>& pathvector, int ind)
{
	if (ind == pathvector.size())
		return this;
	for (File* file : m_Files)
	{
		if (file->GetName() == pathvector[ind])
		{
			Directory* folder = dynamic_cast<Directory*>(file);
			if (folder == nullptr)
				throw std::exception("Not a directory");
			else
				return folder->SearchFolder(pathvector, ind + 1);
		}
	}
	throw std::exception("No such file or directory");
}

Document* Directory::SearchDocument(const std::string& name)
{
	for (File* file : m_Files)
	{
		if (file->GetName() == name)
		{
			Document* ptr = dynamic_cast<Document*>(file);
			if (ptr == nullptr)
				throw std::exception("Operation not permitted");
			return ptr;
		}
	}
	throw std::exception("No such file or directory");
}

DynamicLink* Directory::SearchDynamicLink(const std::string& path)
{
	for (File* file : m_Files)
	{
		DynamicLink* link = dynamic_cast<DynamicLink*>(file);
		if (link != nullptr && link->GetPath() == path)
		{
			return link;
		}
	}
	throw std::exception("No such file or directory");
}


void Document::RemoveDynamicLink(Directory* parent)
{
	int len = m_DynamicLinks.size();
	for (int i = 0; i < len; ++i)
	{
		if (m_DynamicLinks[i] == parent)
		{
			m_DynamicLinks.erase(m_DynamicLinks.begin() + i);
			return;
		}
	}
}

void Document::Deallocate()
{
	int len = m_DynamicLinks.size();
	for (int i = 0; i < len; ++i)
	{
		Directory* parent = m_DynamicLinks[i];
		parent->RemoveDynamicLink(this);
	}
}