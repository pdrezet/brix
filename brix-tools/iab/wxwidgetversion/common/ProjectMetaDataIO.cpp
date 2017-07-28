#include <fstream>
#include <stdio.h>
#include <algorithm>
//#include <assert.h>
#include <cassert>
#include <cstdlib>
#include <cerrno>
#include <sys/stat.h>
#include <wx/msgdlg.h>

#include "libxml/xmlreader.h"



#include "ProjectMetaData.h"

#include "../LucidApplicationBuilder/ProjectDialog.h"

#include "Markup.h"
#include "LucidConstants.h"
#include "LucidEnums.h"
#include "FileOperations.h"
#include "ExtGuiFile.h"
#include "ExtBmpFile.h"
#include "ExtDataFile.h"
//#include "LabLgbBaseApp.h"
#include "LucidTypedefs.h"
#include "LccPmdXfers.h"
#include "GlobalFuncs_2.h"

#include "Porting_Classes/INXString.h"
#include "Porting_Classes/INXWidgets.h"




#define APPINFO_ROOT "root"
#define APPINFO_CANONICAL_NAME "Name"
#define APPINFO_COMMERCIAL_NAME "CommercialName"
#define APPINFO_VERSION "Version"
#define APPINFO_DESC "Description"
#define APPDEFAULT_VERSION "1.0"

//extern LucidErrEnum ProjectMetaData::checkProjectFile( CMarkup &xml );

LucidErrEnum ProjectMetaData::readProjectFile()
{
	//LucidErrEnum err;

	if(!projectIsSet()){

		return kErr_ProjectMetaDataNoProjectSet;

	}else{

		INXString dummyCs = "";
		getFullPathProjectFile(dummyCs);
		LucidErrEnum err = readProjectFile( dummyCs );

			// It's an old project, so set its revision to the coded-in labels (ie consistent with this rev of the code).
		m_cProjFolderMinder.setProjectFolder( m_csProjectDir );
//		m_cProjFolderMinder.setProjectRevision( m_iCodeMajorRev, m_iCodeMinorRev );

		assert( kErr_NoErr == err);

	}

	return kErr_NoErr;
}

#ifdef __INX_NOT_DEFINED_IN_ProjectMetaDataIO
void ProjectMetaData::initProjFolderMinder()
{
	m_cProjFolderMinder.setProjectFolder(m_csProjectDir);
	m_cProjFolderMinder.setProjectRevision( m_iCodeMajorRev, m_iCodeMinorRev );
}

INXString ProjectMetaData::getVersionString(void)
{
	return intToString(m_iCodeMajorRev) + "." + intToString(m_iCodeMinorRev);
}

void ProjectMetaData::getVersionInts(void)
{
	assert( m_csLucidVersion.GetLength() >=3 ); // 'i.j' min )

	int dotPos = m_csLucidVersion.Find(".");
	assert(dotPos > 0);

	m_iProjReadMajorRev = atoi( m_csLucidVersion.Left(dotPos) );
	m_iProjReadMinorRev = atoi( m_csLucidVersion.Right(m_csLucidVersion.GetLength() - dotPos -1 ) );
}

#endif

/*
 * Parse the XML file using libXML2 that holds the project description for the app uploader
*/

LucidErrEnum ProjectMetaData::readProjectDescriptionFile()
{
	char *name = NULL, * value = NULL;
	xmlTextReaderPtr reader;
	int ret = 0;
	bool foundFile = false;

	INXString infoFilePath = m_csProjectDir + APP_DESC_DIR + APP_DESC_FILE;

	if (m_csProjectAppCanonicalName == "")
		m_csProjectAppCanonicalName = m_csProjectName;
	if (m_csProjectAppCommercialName == "")
		m_csProjectAppCommercialName = m_csProjectName;
	if (m_csProjectAppVersion == "")
		m_csProjectAppVersion = APPDEFAULT_VERSION;
	if (m_csProjectAppDescription == "")
		m_csProjectAppDescription = m_csProjectName;


	// load description if already exists, else create it with defaults
	struct stat xFileInfo;
	// stat returns -1 if fails, 0 otherwise
	if (stat(infoFilePath,&xFileInfo) > -1) {
		reader = xmlNewTextReaderFilename(infoFilePath);	
		if (reader != NULL) {
			foundFile = true;

			// read next node
			ret = xmlTextReaderRead(reader);

			while (ret == 1) {
				name = (char*) xmlTextReaderConstName(reader); // This is dealoocated with reader  -don't deallocate!
	//			INX_MessageBox(name);

				// if this is a node end type, then skip this node
				if (xmlTextReaderNodeType(reader) == NODE_TYPE_END_ELEMENT) {
					ret = xmlTextReaderRead(reader);
					continue;
				}
				// if this is a #text type in an unexpected place, then skip this node
				if ((xmlTextReaderNodeType(reader) == NODE_TYPE_STARTTEXT_ELEMENT) || (xmlTextReaderNodeType(reader) == NODE_TYPE_ENDTEXT_ELEMENT)) {
					ret = xmlTextReaderRead(reader);
					continue;
				}


				if (strcmp(APPINFO_CANONICAL_NAME, name) == 0) {
					ret = xmlTextReaderRead(reader);	// note - once find node, need to read again to access #text element
					value = (char*) xmlTextReaderConstValue(reader);
					m_csProjectAppCanonicalName = value;
				} else if (strcmp(APPINFO_COMMERCIAL_NAME, name) == 0) {
					ret = xmlTextReaderRead(reader);	// note - once find node, need to read again to access #text element
					value = (char*) xmlTextReaderConstValue(reader);
					m_csProjectAppCommercialName = value;
				} else if (strcmp(APPINFO_VERSION, name) == 0) {
					ret = xmlTextReaderRead(reader);	// note - once find node, need to read again to access #text element
					value = (char*) xmlTextReaderConstValue(reader);
					m_csProjectAppVersion = value;
				} else if (strcmp(APPINFO_DESC, name) == 0) {
					ret = xmlTextReaderRead(reader);	// note - once find node, need to read again to access #text element
					value = (char*) xmlTextReaderConstValue(reader);
					m_csProjectAppDescription = value;
				}

				// read next node
				ret = xmlTextReaderRead(reader);
			}
			xmlFreeTextReader(reader);
		}
	}

	if (!foundFile) {
		// write defaults to file
		writeProjectDescriptionFile();
	}

	return kErr_NoErr;
}

/**
 * Writes the current project meta data that decribes the app uploader info
 */
LucidErrEnum ProjectMetaData::writeProjectDescriptionFile()
{
	FILE* pFile;
	int error;
	CFileOperation fo;

	INXString infoFilePath = m_csProjectDir + APP_DESC_DIR + APP_DESC_FILE;

	// Create a new 'description' folder in the right place, if necessary
	if( PATH_NOT_FOUND == fo.CheckPath( m_csProjectDir + APP_DESC_DIR )){
		if (mkdir(m_csProjectDir + APP_DESC_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ) != 0 ) {
			return kErr_CouldNotCreateFolder;
		}
	}

	pFile=fopen(infoFilePath,"w");
	if (pFile != NULL) {
		fprintf(pFile,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		fprintf(pFile,"<%s>\n", APPINFO_ROOT);
		fprintf(pFile,"  <%s>%s</%s>\n",APPINFO_CANONICAL_NAME, m_csProjectAppCanonicalName.c_str(), APPINFO_CANONICAL_NAME);
		fprintf(pFile,"  <%s>%s</%s>\n",APPINFO_COMMERCIAL_NAME, m_csProjectAppCommercialName.c_str(), APPINFO_COMMERCIAL_NAME);
		fprintf(pFile,"  <%s>%s</%s>\n",APPINFO_VERSION, m_csProjectAppVersion.c_str(), APPINFO_VERSION);
		fprintf(pFile,"  <%s>%s</%s>\n",APPINFO_DESC, m_csProjectAppDescription.c_str(), APPINFO_DESC);
		fprintf(pFile,"</%s>\n", APPINFO_ROOT);
		fclose(pFile);
		return kErr_NoErr;
	}
	return kErr_NoErr;
}

LucidErrEnum ProjectMetaData::readProjectFile( INXString csProjectPathName )
{

	//@todo - this is called twice when a project is opened!!

	// With this overload of readProjectFile, we are normally reading NOT the present
	// project, but another one - which is probably in the process of being created.  
	// Therefore it is best not to lock the proj file.
	// assert( m_bLocked );
	// assert(  isUpToDate() );


	ifstream projectfile(csProjectPathName);
	char type[WORK_DIR_SIZE] = {'\0'};
	CMarkup xml;
	INXString csXML, csWidgetTag, csScreenTag, csTmpProjectDir;
	Group groupObj;

	if (projectfile.fail()) {
		INXString dummy = "Unable to open project file.";
		dummy += csProjectPathName;
		INX_MessageBox(dummy);
		return kErr_ProjectFileNotRead;
	}
	
	// Before setting the project to null take a copy of the
	// project dir, so can set it again for the case
	// when reading undo files.
	csTmpProjectDir = m_csProjectDir;

	// This is required for the case when reading a project file,
	// and the class has already been set up.
	setProjectToNull();


	// load xml project file
	while ((!projectfile.eof()) && (!projectfile.bad())) {
		projectfile.getline(type,4095);
		csXML = (INXString)(csXML + type);
	}

	projectfile.close();

	m_bProjectIsSet = true;
	isDirtySODL = false;


	// Extract project data
	xml.SetDoc(csXML );

	xml.FindElem((char*)"LucidProject");
	xml.IntoElem();

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// NB. We are now 'inside the Lucidproject tag.

	xml.FindElem((char*)"Version");
	m_csLucidVersion = xml.GetData();


	
	xml.FindElem((char*)"ProjectName");
	m_csProjectName = xml.GetData();

	xml.FindElem((char*)"LastTransferToTarget");
	INXString dummyTS = xml.GetData();

	// handle case where ts isn't present
	if( dummyTS == m_csProjectName)
		m_cLastTransferTime.setAncient();
	else
		m_cLastTransferTime.csParse( dummyTS );


	// Get group data
	xml.FindElem((char*)"GroupSet");
	xml.IntoElem();
	while (xml.FindElem((char*)"Group")) {
		xml.FindChildElem((char*)"ID");
		groupObj.ID = atoi(xml.GetChildData());
		xml.FindChildElem((char*)"Name");
		groupObj.Name = xml.GetChildData();
		xml.FindChildElem((char*)"Period");
		groupObj.Period = atoi(xml.GetChildData());
		xml.FindChildElem((char*)"Allocation");
		groupObj.Alloc = atoi(xml.GetChildData());
		m_vGroups.push_back(groupObj);
	}
	xml.OutOfElem();

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// External Files.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	xml.FindElem((char*)"ExternalFiles");
	xml.IntoElem();

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Get GUI files.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if( xml.FindElem((char*)"GuiFileSet") ){


		xml.IntoElem();

		ExtGuiFile egf;
		while (xml.FindElem((char*)"GuiFile")) {

			xml.FindChildElem((char*)"HostFileName");
			egf.setHostFileName(xml.GetChildData());

			xml.FindChildElem((char*)"Description");
			egf.setDescription(xml.GetChildData());

			xml.FindChildElem((char*)"Screen");
			egf.setScreenTag(xml.GetChildData());

			m_vGuiFiles.push_back(egf);
		}
		xml.OutOfElem(); // GuiFileSet

	}else{

	}



	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// get PNG files

	if( xml.FindElem((char*)"PngFileSet") ){

		xml.IntoElem();

		ExtPngFile epf;
		while (xml.FindElem((char*)"PngFile")) {

			xml.FindChildElem((char*)"HostFileName");
			epf.setHostFileName(xml.GetChildData());

			xml.FindChildElem((char*)"Description");
			epf.setDescription(xml.GetChildData());

			xml.FindChildElem((char*)"TargetFileName");
			epf.setTargetFileName(xml.GetChildData());

			m_vPngFiles.push_back(epf);
		}
		xml.OutOfElem(); // PngFileSet

	} 

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// get BMP files

	xml.FindElem((char*)"BmpFileSet");
	xml.IntoElem();

	ExtBmpFile ebf;
	while (xml.FindElem((char*)"BmpFile")) {

		xml.FindChildElem((char*)"HostFileName");
		ebf.setHostFileName(xml.GetChildData());

		xml.FindChildElem((char*)"Description");
		ebf.setDescription(xml.GetChildData());

		xml.FindChildElem((char*)"TargetFileName");
		ebf.setTargetFileName(xml.GetChildData());

		m_vBmpFiles.push_back(ebf);
	}
	xml.OutOfElem(); // BmpFileSet

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// get Data files.

	xml.FindElem((char*)"DataFileSet");
	xml.IntoElem();

	ExtDataFile edf;
	while (xml.FindElem((char*)"DataFile")) {

		xml.FindChildElem((char*)"HostFileName");
		edf.setHostFileName(xml.GetChildData());

		xml.FindChildElem((char*)"Description");
		edf.setDescription(xml.GetChildData());

		xml.FindChildElem((char*)"TargetFileName");
		edf.setTargetFileName(xml.GetChildData());

		m_vDataFiles.push_back(edf);
	}

	xml.OutOfElem(); // DataFileSet

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// get BDF files

	xml.FindElem((char*)"BdfFileSet");
	xml.IntoElem();

	ExtBdfFile eff;
	while (xml.FindElem((char*)"BdfFile")) {

		xml.FindChildElem((char*)"HostFileName");
		eff.setHostFileName(xml.GetChildData());

		xml.FindChildElem((char*)"Description");
		eff.setDescription(xml.GetChildData());

		xml.FindChildElem((char*)"TargetFileName");
		eff.setTargetFileName(xml.GetChildData());

		m_vBdfFiles.push_back(eff);
	}
	xml.OutOfElem(); // BdfFileSet

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// get Resource files.

	xml.FindElem((char*)"ResourceFileSet");
	xml.IntoElem();

	ExtResourceFile erf;
	while (xml.FindElem((char*)"ResourceFile")) {

		xml.FindChildElem((char*)"HostFileName");
		erf.setHostFileName(xml.GetChildData());

		xml.FindChildElem((char*)"Description");
		erf.setDescription(xml.GetChildData());

		xml.FindChildElem((char*)"TargetFileName");
		erf.setTargetFileName(xml.GetChildData());

		m_vResourceFiles.push_back(erf);
	}

	xml.OutOfElem(); // ResourceFileSet

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// get nls.csv file
	
	ExtNlsFile enf;

	if (xml.FindElem((char*)"NlsFile")) {
		xml.FindChildElem((char*)"HostFileName");
		enf.setHostFileName(xml.GetChildData());

		xml.FindChildElem((char*)"Description");
		enf.setDescription(xml.GetChildData());

		xml.FindChildElem((char*)"TargetFileName");
		enf.setTargetFileName(xml.GetChildData());

		m_vNlsFiles.push_back(enf);
	}

	xml.OutOfElem(); // External Files


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Get Screen Tags
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	TagProjMetaSupportData_t suppData;

	xml.FindElem((char*)"ScreenSet");
	xml.IntoElem();
	while (xml.FindElem((char*)"Screen")) {

		xml.FindChildElem((char*)"Tag");
		csScreenTag = xml.GetChildData();

		xml.FindChildElem((char*)"Description");
		suppData.tagDescr = xml.GetChildData();

		xml.FindChildElem((char*)"TargetFileName");
		suppData.tgtFilename = xml.GetChildData();

		if(xml.FindChildElem((char*)"ActiveHostLayout") ){

			INXString dummy = xml.GetChildData();	
			suppData.activeHostFilename = dummy;

		}else{
			suppData.activeHostFilename = "";
		}

		addScreenTag(csScreenTag, suppData);

	}

	xml.OutOfElem(); // ScreenSet


// Get Widgets
	xml.FindElem((char*)"WidgetSet");
	xml.IntoElem();

	while (xml.FindElem((char*)"Widget")) {
		xml.FindChildElem((char*)"WidgetTag");
		csWidgetTag = xml.GetChildData();
		xml.FindChildElem((char*)"ScreenTag");
		csScreenTag = xml.GetChildData();

		GuiWidget widget(csWidgetTag, csScreenTag);
		addGuiWidget(widget);
	}

	xml.OutOfElem(); // WidgetSet


// get external file name-counts.

	xml.FindElem((char*)"ExternalDataFileMetas");
	xml.IntoElem();

	xml.FindElem((char*)"NumberOfHighestGuiFile");
	INXString dum = xml.GetData();
	m_iLastGuiFileAddedKey = atoi(dum);

	 m_iLastGuiFileAddedKey = 10;
	xml.FindElem((char*)"NumberOfHighestPngFile");
	m_iLastPngFileAddedKey= atoi(xml.GetData());

	xml.FindElem((char*)"NumberOfHighestBmpFile");
	m_iLastBmpFileAddedKey= atoi(xml.GetData());

	xml.FindElem((char*)"NumberOfHighestDatFile");
	m_iLastDataFileAddedKey= atoi(xml.GetData());

	xml.FindElem((char*)"NumberOfHighestBdfFile");
	m_iLastBdfFileAddedKey= atoi(xml.GetData());

	xml.OutOfElem(); // ExternalDataFileMetas


// Get Transferrables

	// 1st clear out previous contents
	m_cTransferables.clear();

	xml.FindElem((char*)"Transferrables");
	xml.IntoElem();

	LccPmdXfers::TypesEnum dummy = LccPmdXfers::kData; // LccPmdXfers::kData;

	INXString csHostFileName;
	INXString csTargetFileName;

	xml.FindElem((char*)"DataFileSet");
	while ( xml.FindChildElem((char*)"Location") )
	{
		csHostFileName = xml.GetChildData();
		m_cTransferables.addItem( dummy, csHostFileName );
	}

	xml.FindElem((char*)"ImageFileSet");
	while ( xml.FindChildElem((char*)"Location") )
	{
		csHostFileName = xml.GetChildData();
		//getTargetFileNameForPngHostFileName( csHostFileName, csTargetFileName );
		m_cTransferables.addItem( dummy, csHostFileName );
	}

	xml.FindElem((char*)"LayoutFileSet");
	while ( xml.FindChildElem((char*)"Location") )
	{
		csHostFileName = xml.GetChildData();
		//getTargetFileNameForGuiHostFileName( csHostFileName, csTargetFileName );
		m_cTransferables.addItem( dummy, csHostFileName );
	}

	xml.FindElem((char*)"MiscFileSet");
	while ( xml.FindChildElem((char*)"Location") )
	{
		csHostFileName = xml.GetChildData();
		//getTargetFileNameForDataHostFileName( csHostFileName, csTargetFileName );
		m_cTransferables.addItem( dummy, csHostFileName );
	}
	
	//@todo - add info xml to project xml?

	xml.FindElem((char*)"FontFileSet");
	while ( xml.FindChildElem((char*)"Location") )
	{
		csHostFileName = xml.GetChildData();
		m_cTransferables.addItem( dummy, csHostFileName );
	}

	xml.OutOfElem(); // Transferrables
	
	// project root dir is no longer stored in project file so
	// if project file is an undo file the project dir is the project dir stored before
	// setting the project to null
	if (csProjectPathName.Find((char*)"temp\\lpj_undo") != -1) {
		m_csProjectDir = csTmpProjectDir;
	}
	// extract the project dir from the pathname and projectname
	// subtract 5 for .lpj and the '/' between the project dir and project file name
	else {
		int iLen = csProjectPathName.GetLength() - m_csProjectName.GetLength() - 5;
		m_csProjectDir = (INXString)(csProjectPathName.Left(iLen));
	}

	m_cProjFolderMinder.setProjectFolder( m_csProjectDir );
	getVersionInts();
	//m_cProjFolderMinder.setProjectRevision( m_iCodeMajorRev, m_iCodeMinorRev );
#ifdef _UNUSED_FUNCTIONS_TO_LOAD_THE_FILE
	if( checkProjectFileData() )
		wxMessageBox("Corrections / updates made to project meta data");
#endif
	updateTransferrables(false);

	// load the project description file
#ifdef _UNUSED_FUNCTIONS_TO_LOAD_THE_FILE
	readProjectDescriptionFile(); 
#endif

	// store the build num for later use
	populateBuildNumFromFile();

	return kErr_NoErr;

}


// writes the project file to the project directory
LucidErrEnum ProjectMetaData::writeProjectFile()
{
    assert(m_bLocked == false);
	INXString csProjectPathName = m_csProjectDir + "\\" + m_csProjectName + PROJECTEXT;
	return writeProjectFileAs(csProjectPathName);
}

// writes the project file to a specific path name
LucidErrEnum ProjectMetaData::writeProjectFileAs(INXString csProjectPathName)
{

	// don't assert m_bLocked, as this api is called mainly for writing the 'undo' versions.

		CMarkup xml;
		Group groupObj;
		char csID[8] = {'\0'};
		char csPeriod[8] = {'\0'};
		char csAlloc[8] ={'\0'};
		INXString csExtFileName, csWidgetTag, csScreenTag;
		ofstream projectfile(csProjectPathName);

		// put an error trap
		if (!projectfile.good()) {
			INX_MessageBox("Project file could not be written");
			return kErr_ProjectFileNotWritten;
		}

		xml.AddElem((char*)"LucidProject");
		xml.AddChildElem((char*)"Version", getVersionString() );
		xml.AddChildElem((char*)"ProjectName", m_csProjectName);
		xml.AddChildElem((char*)"LastTransferToTarget", m_cLastTransferTime.csPrint() );
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// GroupSet.

		xml.AddChildElem((char*)"GroupSet");
		xml.IntoElem();
		for (unsigned int i=0; i<m_vGroups.size(); i++) {
			groupObj = m_vGroups.at(i);
			xml.AddChildElem((char*)"Group");
			xml.IntoElem();
			sprintf(csID, "%d", groupObj.ID);
			xml.AddChildElem((char*)"ID", csID);
			xml.AddChildElem((char*)"Name", groupObj.Name);
			sprintf(csPeriod,"%d",groupObj.Period);
			xml.AddChildElem((char*)"Period", csPeriod);
			sprintf( csAlloc,"%d", groupObj.Alloc);
			xml.AddChildElem((char*)"Allocation", csAlloc);
			xml.OutOfElem();
		}
		xml.OutOfElem(); // GroupSet


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// ExternalFiles.

		xml.AddChildElem((char*) "ExternalFiles");
		xml.IntoElem();

	//-----------------------------------
	// Add gui files
	//-----------------------------------

		INXString cstr;

		xml.AddChildElem((char*)"GuiFileSet");
		xml.IntoElem();

		for (unsigned int i=0; i < m_vGuiFiles.size(); i++) {
			xml.AddChildElem((char*)"GuiFile");
			xml.IntoElem();

			m_vGuiFiles.at(i).getHostFileName(cstr);
			xml.AddChildElem((char*)"HostFileName", cstr);

			m_vGuiFiles.at(i).getDescription(cstr);
			xml.AddChildElem((char*)"Description", cstr);

			m_vGuiFiles.at(i).getScreenTag(cstr);
			xml.AddChildElem((char*)"Screen", cstr);

			xml.OutOfElem(); // GuiFile
		}

		xml.OutOfElem(); // GuiFileSet

	//-----------------------------------
	// Add png files
	//-----------------------------------

		xml.AddChildElem((char*)"PngFileSet");
		xml.IntoElem();

		for (unsigned int i=0; i < m_vPngFiles.size(); i++) {

			xml.AddChildElem((char*)"PngFile");
			xml.IntoElem();

			m_vPngFiles.at(i).getHostFileName(cstr);
			xml.AddChildElem((char*)"HostFileName", cstr);

			m_vPngFiles.at(i).getDescription(cstr);
			xml.AddChildElem((char*)"Description", cstr);

			m_vPngFiles.at(i).getTargetFileName(cstr);
			xml.AddChildElem((char*)"TargetFileName", cstr);

			xml.OutOfElem(); // PngFile

		}

		xml.OutOfElem(); // PngFileSet
	//-----------------------------------
	// Add bmp files
	//-----------------------------------

		xml.AddChildElem((char*)"BmpFileSet");
		xml.IntoElem();

		for (unsigned int i=0; i < m_vBmpFiles.size(); i++) {

			xml.AddChildElem((char*)"BmpFile");
			xml.IntoElem();

			m_vBmpFiles.at(i).getHostFileName(cstr);
			xml.AddChildElem((char*)"HostFileName", cstr);

			m_vBmpFiles.at(i).getDescription(cstr);
			xml.AddChildElem((char*)"Description", cstr);

			m_vBmpFiles.at(i).getTargetFileName(cstr);
			xml.AddChildElem((char*)"TargetFileName", cstr);

			xml.OutOfElem(); // BmpFile

		}

		xml.OutOfElem(); // BmpFileSet

	//-----------------------------------
	// Add data files
	//-----------------------------------

		xml.AddChildElem((char*)"DataFileSet");
		xml.IntoElem();

		for (unsigned int i=0; i < m_vDataFiles.size(); i++) {

			xml.AddChildElem((char*)"DataFile");
			xml.IntoElem();

			m_vDataFiles.at(i).getHostFileName(cstr);
			xml.AddChildElem((char*)"HostFileName", cstr);

			m_vDataFiles.at(i).getDescription(cstr);
			xml.AddChildElem((char*)"Description", cstr);

			m_vDataFiles.at(i).getTargetFileName(cstr);
			xml.AddChildElem((char*)"TargetFileName", cstr);

			xml.OutOfElem(); // DataFile

		}

		xml.OutOfElem(); // DataFileSet

	//-----------------------------------
	// Add bdf files
	//-----------------------------------

		xml.AddChildElem((char*)"BdfFileSet");
		xml.IntoElem();

		for (unsigned int i=0; i < m_vBdfFiles.size(); i++) {

			xml.AddChildElem((char*)"BdfFile");
			xml.IntoElem();

			m_vBdfFiles.at(i).getHostFileName(cstr);
			xml.AddChildElem((char*)"HostFileName", cstr);

			m_vBdfFiles.at(i).getDescription(cstr);
			xml.AddChildElem((char*)"Description", cstr);

			m_vBdfFiles.at(i).getTargetFileName(cstr);
			xml.AddChildElem((char*)"TargetFileName", cstr);

			xml.OutOfElem(); // BdfFile

		}

		xml.OutOfElem(); // BdfFileSet

	//-----------------------------------
	// Add resource files
	//-----------------------------------

		xml.AddChildElem((char*)"ResourceFileSet");
		xml.IntoElem();

		for (unsigned int i=0; i < m_vResourceFiles.size(); i++) {

			xml.AddChildElem((char*)"ResourceFile");
			xml.IntoElem();

			m_vResourceFiles.at(i).getHostFileName(cstr);
			xml.AddChildElem((char*)"HostFileName", cstr);

			m_vResourceFiles.at(i).getDescription(cstr);
			xml.AddChildElem((char*)"Description", cstr);

			m_vResourceFiles.at(i).getTargetFileName(cstr);
			xml.AddChildElem((char*)"TargetFileName", cstr);

			xml.OutOfElem(); // ResourceFile

		}

		xml.OutOfElem(); // ResourceFileSet

	//-----------------------------------
	// Add nls.csv file if it exists
	//-----------------------------------

		for (unsigned int i=0; i < m_vNlsFiles.size(); i++) {

			xml.AddChildElem((char*)"NlsFile");
			xml.IntoElem();

			m_vNlsFiles.at(i).getHostFileName(cstr);
			xml.AddChildElem((char*)"HostFileName", cstr);

			m_vNlsFiles.at(i).getDescription(cstr);
			xml.AddChildElem((char*)"Description", cstr);

			m_vNlsFiles.at(i).getTargetFileName(cstr);
			xml.AddChildElem((char*)"TargetFileName", cstr);

			xml.OutOfElem(); // NlsFile

		}

		xml.OutOfElem(); // ExternalFiles


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// ScreenSet

		xml.AddChildElem((char*)"ScreenSet");
		xml.IntoElem();

		if(m_mapScreenTagProjMetas.size() > 0){

			pair<INXString, TagProjMetaSupportData_t> *pPair = NULL;

			ScreenProjMetaMapIt_t it = m_mapScreenTagProjMetas.begin();

			while (it != m_mapScreenTagProjMetas.end()){

				pPair = (pair<INXString, TagProjMetaSupportData_t> *) &(*it);

				xml.AddChildElem((char*)"Screen");
					xml.IntoElem();
					xml.AddChildElem((char*)"Tag", pPair->first);
					xml.AddChildElem((char*)"Description", pPair->second.tagDescr);
					xml.AddChildElem((char*)"TargetFileName", pPair->second.tgtFilename);
					xml.AddChildElem((char*)"ActiveHostLayout", pPair->second.activeHostFilename);
					xml.OutOfElem();
				it++;
			} // while (it != m_mapScreenTagProjMetas.end())


		} // if(m_mapScreenTagProjMetas.size() > 0)

		xml.OutOfElem(); // ScreenSet


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// WidgetSet


		xml.AddChildElem("WidgetSet");
		// Add widgets
		xml.IntoElem();
		for (unsigned int i=0; i<m_vGuiWidgets.size(); i++) {
			xml.AddChildElem("Widget");
			xml.IntoElem();

				m_vGuiWidgets.at(i).getWidgetTag(csWidgetTag);
				m_vGuiWidgets.at(i).getScreenTag(csScreenTag);
				xml.AddChildElem("WidgetTag", csWidgetTag);
				xml.AddChildElem("ScreenTag", csScreenTag);

			xml.OutOfElem();
		}
		xml.OutOfElem(); // WidgetSet

		xml.AddChildElem("ExternalDataFileMetas");
		xml.IntoElem();

		int iDum = -1;

		//int err =  _itoa_s(m_iLastGuiFileAddedKey, dumBuf, STD_FIELD_LENGTH, RADIX_TEN );
		//assert(err==0);
		xml.AddChildElem("NumberOfHighestGuiFile", intToString( m_iLastGuiFileAddedKey ) );

		//err = _itoa_s(m_iLastPngFileAddedKey, dumBuf, STD_FIELD_LENGTH, RADIX_TEN );
		//assert(err==0);
		xml.AddChildElem("NumberOfHighestPngFile", intToString( m_iLastPngFileAddedKey ) );

		//err = _itoa_s(m_iLastBmpFileAddedKey, dumBuf, STD_FIELD_LENGTH, RADIX_TEN );
		//assert(err==0);
		xml.AddChildElem("NumberOfHighestBmpFile", intToString( m_iLastBmpFileAddedKey ) );

		//err = _itoa_s(m_iLastDataFileAddedKey, dumBuf, STD_FIELD_LENGTH, RADIX_TEN );
		//assert(err==0);
		xml.AddChildElem("NumberOfHighestDatFile", intToString( m_iLastDataFileAddedKey ) );

		xml.AddChildElem("NumberOfHighestBdfFile", intToString( m_iLastBdfFileAddedKey ) );

		xml.OutOfElem(); // ExternalDataFileMetas


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Transferrables

		vector<LccPmdXfers::DataPair_t> vDummy;

		xml.AddChildElem("Transferrables");
		xml.IntoElem();

	//-----------------------------------
	// Add Data Files
	//-----------------------------------

		xml.AddChildElem("DataFileSet");
		xml.IntoElem();

		iDum = m_cTransferables.getItems( LccPmdXfers::kData, vDummy );
		for (unsigned int i=0; i < vDummy.size(); i++)
			xml.AddChildElem("Location", vDummy[i].hostFileName);

		xml.OutOfElem(); // DataFileSet

	//-----------------------------------
	// Add Image Files
	//-----------------------------------

		xml.AddChildElem("ImageFileSet");
		xml.IntoElem();

		iDum = m_cTransferables.getItems( LccPmdXfers::kImages, vDummy );
		for (unsigned int i=0; i < vDummy.size(); i++)
			xml.AddChildElem("Location", vDummy[i].hostFileName);

		xml.OutOfElem(); // ImageFileSet

	//-----------------------------------
	// Add Layout Files
	//-----------------------------------

		xml.AddChildElem("LayoutFileSet");
		xml.IntoElem();

		iDum = m_cTransferables.getItems( LccPmdXfers::kLayouts, vDummy );
		for (unsigned int i=0; i < vDummy.size(); i++)
			xml.AddChildElem("Location", vDummy[i].hostFileName);

		xml.OutOfElem(); // LayoutFileSet

	//-----------------------------------
	// Add Resource Files
	//-----------------------------------

		xml.AddChildElem("ResourceFileSet");
		xml.IntoElem();

		iDum = m_cTransferables.getItems( LccPmdXfers::kResource, vDummy );
		for (unsigned int i=0; i < vDummy.size(); i++)
			xml.AddChildElem("Location", vDummy[i].hostFileName);

		xml.OutOfElem(); // ResourceFileSet

	//-----------------------------------
	// Add Miscellaneous ( ie sodl! ) File
	//-----------------------------------

		xml.AddChildElem("MiscFileSet");
		xml.IntoElem();

		iDum = m_cTransferables.getItems( LccPmdXfers::kMisc, vDummy );
		for (unsigned int i=0; i < vDummy.size(); i++)
			xml.AddChildElem("Location", vDummy[i].hostFileName);

		xml.OutOfElem(); // MiscFileSet

	//-----------------------------------
	// Add Descrition ( ie info.xml ) File
	//-----------------------------------
/* @todo - add info xml to project xml?
		xml.AddChildElem("DescritionFileSet");
		xml.IntoElem();

		iDum = m_cTransferables.getItems( LccPmdXfers::kDescription, vDummy );
		for (unsigned int i=0; i < vDummy.size(); i++)
			xml.AddChildElem("Location", vDummy[i].hostFileName);

		xml.OutOfElem(); // DescritionFileSet
*/
	//-----------------------------------
	// Add Font Files
	//-----------------------------------

		xml.AddChildElem("FontFileSet");
		xml.IntoElem();

		iDum = m_cTransferables.getItems( LccPmdXfers::kFonts, vDummy );
		for (unsigned int i=0; i < vDummy.size(); i++)
			xml.AddChildElem("Location", vDummy[i].hostFileName);

		xml.OutOfElem(); // FontFileSet

		xml.OutOfElem(); // Transferrables

		xml.OutOfElem(); // LucidProject

		INXString csXML = xml.GetDoc();
		projectfile << (INXString)csXML;
		projectfile.close();

		//releaseLock();

		return kErr_NoErr;

	//} //if(!getLock() )

}

