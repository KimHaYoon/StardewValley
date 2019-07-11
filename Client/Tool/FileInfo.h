#pragma once
class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();
public:
	static CString ConvertRelativePath(CString strFullPath);
	static void DirInfoExtraction(const wstring& wstrPath, list<IMGPATHINFO*>& rImgInfoLst);
	static int DirFileCount(const wstring& wstrPath);
};

