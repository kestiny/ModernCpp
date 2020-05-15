#include "FileUtils.h"

FileUtils* FileUtils::m_pIns = NULL;

FileUtils::FileUtils()
{
	m_strRoot = "";
}

FileUtils::~FileUtils()
{

}

FileUtils* FileUtils::ins()
{
	if (m_pIns == NULL)
	{
		m_pIns = new FileUtils;
	}

	return m_pIns;
}

void FileUtils::del()
{
	delete m_pIns;
}

void FileUtils::init(const std::string& name)
{
	m_strRoot = name;
}

std::string FileUtils::getPath(const std::string& name)
{
	return m_strRoot + name;
}
