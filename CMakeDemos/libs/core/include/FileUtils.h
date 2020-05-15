/************************************************************ 
  Copyright (C), 2014-2016, SSIT Tech. Co., Ltd. 
  文件名: FileUtils.h
  作者: lyk
  版本: V1.0.0
  日期: 2016/09/23
  模块描述:获取路径接口
  主要函数及其功能:
  历史修改记录:
***********************************************************/
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>

////////////////////////////////////////////////
// 使用方式为在main函数的入口处，调用init,
// 所得目录即为根目录，之后获取的目录都以此为基目录
// FileUtils::ins()->init("D:/project/");
////////////////////////////////////////////////
class FileUtils
{
public:
	static FileUtils* ins();
	static void del();

	void init(const std::string& name);
	std::string getPath(const std::string& name);

private:
	FileUtils();
	~FileUtils();

private:
	static FileUtils* m_pIns;
	std::string m_strRoot;
};

#endif // FILEUTILS_H
