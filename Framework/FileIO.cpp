//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
//----------------------------------------------------------------------------- 
// FILE_IO  
//    v.2.1.0
//    v.2.8   - warning 5039 windows.h
//    v.2.9   - fence
//    v.2.10  - msc_ver 1914, win 10.0.17
//    v.2.11  - warning fixes 
//    v.2.12  - mutex on all trace::out
//    v.2.13  - fixed warnings on mutex and default copy const / assignment
//    v.2.14  - FileIO remove new... so you can overload new/delete
//    v.2.15  - number tests pass reformat
//    v.2.16  - fixing static analysis issues
//    v.2.17  - missing deleted copy constructor and assignment operator in macro
//    v.2.18  - teardown issue
//----------------------------------------------------------------------------- 

#include <stdio.h>
#include <assert.h>
#include <string.h>

// locals
#include "FileIO.h"


constexpr FileIO::FileIO() noexcept
	:pFileHandle(nullptr)
{

};

FileIO::~FileIO()
{
	if (nullptr != this->pFileHandle)
	{
		this->privClose();
	}
};

void FileIO::Open(const char * const pFirstName, const char * const pLastName) noexcept
{
	assert(pFirstName);
	assert(pLastName);
	privGetInstance()->privOpen(pFirstName, pLastName);
}

void FileIO::Close() noexcept
{
	privGetInstance()->privClose();
}

FILE *FileIO::GetHandle() noexcept
{
	return privGetInstance()->privGetHandle();
}

FileIO *FileIO::privGetInstance() noexcept
{
	static FileIO instance;
	return &instance;
}

void FileIO::privClose() noexcept
{
	errno_t fileError(0);
	assert(pFileHandle);

	fileError = fflush(this->pFileHandle);
	assert(!fileError);

	fileError = fclose(this->pFileHandle);
	this->pFileHandle = nullptr;
	assert(!fileError);
}

void FileIO::privOpen(const char * const pFirstName, const char * const pLastName) noexcept
{
	const int length = 256;

	char pFileName[length] = { 0 };
	assert(pFileName);

	errno_t fileError(0);

	// wash the name to 0
	memset(&pFileName[0], 0, length);
	assert(strlen(pFirstName) < length / 4);
	assert(strlen(pLastName) < length / 4);

	strcat_s(&pFileName[0], length, pFirstName);
	strcat_s(&pFileName[0], length, pLastName);
	strcat_s(&pFileName[0], length, "_");

#ifdef _DEBUG
	const char *debug_string = "Debug.txt";
	strcat_s(&pFileName[0], length, debug_string);
	const char *mode = "DEBUG";
#endif

#ifdef NDEBUG
	const char *debug_string = "Release.txt";
	strcat_s(pFileName, length, debug_string);
	const char *mode = "RELEASE";
#endif

	fileError = fopen_s(&pFileHandle, &pFileName[0], "wt");
	assert(pFileHandle);

	fprintf(this->pFileHandle, "Program Assignment \n");
	fprintf(this->pFileHandle, "Name: %s%s\n", pFirstName, pLastName);
	fprintf(this->pFileHandle, "Mode: %s\n", mode);
	fprintf(this->pFileHandle, "\n");
	fprintf(this->pFileHandle, "-------------------------------------------------\n");
	fprintf(this->pFileHandle, "\n");

}

FILE *FileIO::privGetHandle() noexcept
{
	assert(pFileHandle);
	return this->pFileHandle;
}

// ---  End of File ---------------

