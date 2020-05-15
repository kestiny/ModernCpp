/************************************************************ 
  Copyright (C), 2014-2016, SSIT Tech. Co., Ltd. 
  �ļ���: FileUtils.h
  ����: lyk
  �汾: V1.0.0
  ����: 2016/09/23
  ģ������:��ȡ·���ӿ�
  ��Ҫ�������书��:
  ��ʷ�޸ļ�¼:
***********************************************************/
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>

////////////////////////////////////////////////
// ʹ�÷�ʽΪ��main��������ڴ�������init,
// ����Ŀ¼��Ϊ��Ŀ¼��֮���ȡ��Ŀ¼���Դ�Ϊ��Ŀ¼
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
