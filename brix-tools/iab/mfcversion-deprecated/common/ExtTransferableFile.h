#pragma once
#include "ExtFile.h"

class ExtTransferableFile :	public ExtFile
{
public:
	ExtTransferableFile(void);
	ExtTransferableFile(const ExtFile &file);
	~ExtTransferableFile(void);

	LucidErrEnum getTargetFileName(CString &csFileName) const;
	LucidErrEnum setTargetFileName(const int &FileStemNumber);
	LucidErrEnum setTargetFileName(const CString &cStr1);

protected:
	CString m_csTargetFileName;
};
