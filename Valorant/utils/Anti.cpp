#include <Windows.h>
#include <string>
#include <iostream>

#pragma section(".CRT$XLY", long, read)
    __declspec(thread) int var = 0xDEADBEEF;
    void NTAPI tls_callback(PVOID DllHandle, DWORD dwReason, PVOID)
    {
        var = 0xB15BADB0; // Required for TLS Callback call
        if (IsDebuggerPresent())
        {
            TerminateProcess(GetCurrentProcess(), 0xBABEFACE);
        }
    }
    __declspec(allocate(".CRT$XLY"))PIMAGE_TLS_CALLBACK g_tlsCallback = tls_callback;


    PVOID GetPEB()
    {
#ifdef _WIN64
        return (PVOID)__readgsqword(0x0C * sizeof(PVOID));
#else
        return (PVOID)__readfsdword(0x0C * sizeof(PVOID));
#endif
    }

#define FLG_HEAP_ENABLE_TAIL_CHECK   0x10
#define FLG_HEAP_ENABLE_FREE_CHECK   0x20
#define FLG_HEAP_VALIDATE_PARAMETERS 0x40
#define NT_GLOBAL_FLAG_DEBUGGED (FLG_HEAP_ENABLE_TAIL_CHECK | FLG_HEAP_ENABLE_FREE_CHECK | FLG_HEAP_VALIDATE_PARAMETERS)

    PIMAGE_NT_HEADERS GetImageNtHeaders(PBYTE pImageBase)
    {
        PIMAGE_DOS_HEADER pImageDosHeader = (PIMAGE_DOS_HEADER)pImageBase;
        return (PIMAGE_NT_HEADERS)(pImageBase + pImageDosHeader->e_lfanew);
    }
    PIMAGE_SECTION_HEADER FindRDataSection(PBYTE pImageBase)
    {
        static const std::string rdata = ".rdata";
        PIMAGE_NT_HEADERS pImageNtHeaders = GetImageNtHeaders(pImageBase);
        PIMAGE_SECTION_HEADER pImageSectionHeader = IMAGE_FIRST_SECTION(pImageNtHeaders);
        int n = 0;
        for (; n < pImageNtHeaders->FileHeader.NumberOfSections; ++n)
        {
            if (rdata == (char*)pImageSectionHeader[n].Name)
            {
                break;
            }
        }
        return &pImageSectionHeader[n];
    }

    int GetHeapFlagsOffset(bool x64)
    {
        return 0x70;
    }
    int GetHeapForceFlagsOffset(bool x64)
    {
        return 0x74;
    }


    void CheckNtGlobalFlag()
    {
        PVOID pPeb = GetPEB();
        DWORD offsetNtGlobalFlag = 0;

        offsetNtGlobalFlag = 0xBC;

        DWORD NtGlobalFlag = *(PDWORD)((PBYTE)pPeb + offsetNtGlobalFlag);
        if (NtGlobalFlag & NT_GLOBAL_FLAG_DEBUGGED)
        {
         //   std::cout << "CheckNtGlobalFlag" << std::endl;
            exit(0);
        }
    }
    void CheckGlobalFlagsClearInProcess()
    {
        PBYTE pImageBase = (PBYTE)GetModuleHandle(NULL);
        PIMAGE_NT_HEADERS pImageNtHeaders = GetImageNtHeaders(pImageBase);
        PIMAGE_LOAD_CONFIG_DIRECTORY pImageLoadConfigDirectory = (PIMAGE_LOAD_CONFIG_DIRECTORY)(pImageBase
            + pImageNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress);
        if (pImageLoadConfigDirectory->GlobalFlagsClear != 0)
        {
            // std::cout << "CheckGlobalFlagsClearInProcess" << std::endl;
            exit(-1);
        }
    }
    void CheckGlobalFlagsClearInFile()
    {
        HANDLE hExecutable = INVALID_HANDLE_VALUE;
        HANDLE hExecutableMapping = NULL;
        PBYTE pMappedImageBase = NULL;
        __try
        {
            PBYTE pImageBase = (PBYTE)GetModuleHandle(NULL);
            PIMAGE_SECTION_HEADER pImageSectionHeader = FindRDataSection(pImageBase);
            TCHAR pszExecutablePath[MAX_PATH];
            DWORD dwPathLength = GetModuleFileName(NULL, pszExecutablePath, MAX_PATH);
            if (0 == dwPathLength) __leave;
            hExecutable = CreateFile(pszExecutablePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
            if (INVALID_HANDLE_VALUE == hExecutable) __leave;
            hExecutableMapping = CreateFileMapping(hExecutable, NULL, PAGE_READONLY, 0, 0, NULL);
            if (NULL == hExecutableMapping) __leave;
            pMappedImageBase = (PBYTE)MapViewOfFile(hExecutableMapping, FILE_MAP_READ, 0, 0,
                pImageSectionHeader->PointerToRawData + pImageSectionHeader->SizeOfRawData);
            if (NULL == pMappedImageBase) __leave;
            PIMAGE_NT_HEADERS pImageNtHeaders = GetImageNtHeaders(pMappedImageBase);
            PIMAGE_LOAD_CONFIG_DIRECTORY pImageLoadConfigDirectory = (PIMAGE_LOAD_CONFIG_DIRECTORY)(pMappedImageBase
                + (pImageSectionHeader->PointerToRawData
                    + (pImageNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress - pImageSectionHeader->VirtualAddress)));
            if (pImageLoadConfigDirectory->GlobalFlagsClear != 0)
            {
                // std::cout << "CheckGlobalFlagsClearInFile" << std::endl;
                exit(-1);
            }
        }
        __finally
        {
            if (NULL != pMappedImageBase)
                UnmapViewOfFile(pMappedImageBase);
            if (NULL != hExecutableMapping)
                CloseHandle(hExecutableMapping);
            if (INVALID_HANDLE_VALUE != hExecutable)
                CloseHandle(hExecutable);
        }
    }
    void CheckHeap()
    {
        PVOID pPeb = GetPEB();
        PVOID heap = 0;
        DWORD offsetProcessHeap = 0;
        PDWORD heapFlagsPtr = 0, heapForceFlagsPtr = 0;
        BOOL x64 = TRUE;
        offsetProcessHeap = 0x30;

        heap = (PVOID) * (PDWORD_PTR)((PBYTE)pPeb + offsetProcessHeap);
        heapFlagsPtr = (PDWORD)((PBYTE)heap + GetHeapFlagsOffset(x64));
        heapForceFlagsPtr = (PDWORD)((PBYTE)heap + GetHeapForceFlagsOffset(x64));
        if (*heapFlagsPtr & ~HEAP_GROWABLE || *heapForceFlagsPtr != 0)
        {
            // std::cout << "CheckHeap" << std::endl;
            exit(-1);
        }
    }

    void CHECK()
    {
        int checks = 0;

        checks += IsDebuggerPresent();

        CheckNtGlobalFlag();
        CheckGlobalFlagsClearInFile();
        CheckGlobalFlagsClearInProcess();
        CheckHeap();

        BOOL c = FALSE;
        
        CheckRemoteDebuggerPresent(GetCurrentProcess(), &c);
        checks += c;

        if (checks > 0)
        {
            exit(0);
        }
    }