#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

CString CFileInfo::ConvertRelativePath(CString strFullPath)
{
	TCHAR szRelativePath[MAX_STR] = L"";
	TCHAR szCurDirectory[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szCurDirectory);
	PathRelativePathTo(szRelativePath, szCurDirectory, FILE_ATTRIBUTE_DIRECTORY,
		strFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelativePath);
}

void CFileInfo::DirInfoExtraction(const wstring& wstrPath, list<IMGPATHINFO*>& rImgInfoLst)
{
	CFileFind find;
	wstring wstrFilePath = wstrPath + L"\\*.*";

	find.FindFile(wstrFilePath.c_str());

	int iContinue = 1;

	while (iContinue)
	{
		iContinue = find.FindNextFile();

		if (find.IsDots())	
			continue;
		else if (find.IsDirectory()) 
		{
			DirInfoExtraction(wstring(find.GetFilePath()), rImgInfoLst);
		}
		else 
		{
			if (find.IsSystem())
				continue;
			IMGPATHINFO* pImgPathInfo = new IMGPATHINFO;

			TCHAR szPathInfo[MAX_STR] = L"";
			lstrcpy(szPathInfo, find.GetFilePath().GetString());
			PathRemoveFileSpec(szPathInfo);

			pImgPathInfo->iCount = CFileInfo::DirFileCount(szPathInfo);

			wstring wstrFileName = find.GetFileTitle();

			wstrFileName = wstrFileName.substr(0, wstrFileName.length() - 1) + L"%d.png";

			TCHAR szRelativeFullPath[MAX_STR] = L"";

			PathCombine(szRelativeFullPath, szPathInfo, wstrFileName.c_str());

			pImgPathInfo->wstrPath = CFileInfo::ConvertRelativePath(szRelativeFullPath);
			pImgPathInfo->wstrStateKey = PathFindFileName(szPathInfo);

			PathRemoveFileSpec(szPathInfo);

			pImgPathInfo->wstrObjKey = PathFindFileName(szPathInfo);

			rImgInfoLst.push_back(pImgPathInfo);
			break;
		}
	}

}

int CFileInfo::DirFileCount(const wstring & wstrPath)
{
	CFileFind find;
	wstring wstrCurPath = wstrPath + L"\\*.*";

	find.FindFile(wstrCurPath.c_str());

	int iCount = 0;
	int iContinue = 1;

	while (iContinue)
	{
		iContinue = find.FindNextFile();

		if (find.IsDots())
			continue;
		else if (find.IsDirectory())
			continue;
		else
		{
			if (find.IsSystem())
				continue;

			++iCount;
		}
	}

	return iCount;
}
