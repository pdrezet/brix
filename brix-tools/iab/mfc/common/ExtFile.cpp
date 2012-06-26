#include "stdafx.h"
#include "ExtFile.h"

ExtFile::ExtFile(void): m_csFilePrefix("NOT_INITIALISED"), m_csFileExtension("NOT_INITIALISED")
{
}

ExtFile::ExtFile(const ExtFile &file)
{
	file.getDescription(m_csDescription);
}

ExtFile::~ExtFile(void)
{
}

bool ExtFile::operator==(const ExtFile &file)const
{

	if( file.m_csHostFileName == m_csHostFileName){
		return true;
	}
	else{
		return false;
	}
}

LucidErrEnum ExtFile::getHostFileName(CString &csFileName) const
{
	csFileName = m_csHostFileName;
	return kErr_NoErr;
}

LucidErrEnum ExtFile::setHostFileName(const CString &csFileName)
{
	m_csHostFileName = csFileName;
	return kErr_NoErr;
}

LucidErrEnum ExtFile::getDescription(CString &csDescr) const
{
	csDescr = m_csDescription;
	return kErr_NoErr;
}



LucidErrEnum ExtFile::setDescription(const CString &csDescr)
{
	m_csDescription = csDescr;
	return kErr_NoErr;
}