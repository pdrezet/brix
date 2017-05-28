// SODL.h: interface for the SODL class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _SODL_H__
#define _SODL_H__



#include "Condat.h"
#include "TypeConversion.h"
#include "Project.h"
#include "Porting_Classes/INXString.h"
class SODL  
{
public:
	// Constructor
	SODL();
	SODL(Project* _pProject);
	virtual ~SODL();
	
	// Attributes
	INXObjList* flattened; // a list to point to flattened ConDat objects
	Project* pProject;
	TypeConversion convert;

	// Methods
	void WriteSODL(INXString sodlfile);
	void Copy2Flattened();
	void Flatten();
	void ReassignIconIDs(INXObjList* encapsulated);
	long CheckNewID(INXObjList* encapsulated, long int id);
	void AssignLineIDNum();
	void InitLineID();
	long GetOtherPortLineID(ConData *blob, int portType, int portNum);
	ConData* GetFlatIconFromID(long id);
	void AssignLineID2OtherPort(ConData *blob, int portType, int portNum, long lineID);
	// Writes version information into the SODL header 
	void WriteVersionInformation(ofstream *datafile);
	// reads/incrementsstores the build number to persistant storage. 
	int UpdateBuildNum(void);
};

#endif // !defined(AFX_SODL_H__4E55B460_F6E9_4EE3_9468_6A12F20F0B7E__INCLUDED_)
