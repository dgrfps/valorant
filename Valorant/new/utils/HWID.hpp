#pragma once

#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <intrin.h>
#include <filesystem>

class HWID {
	private:
		static std::string GetHWID()
		{
			std::string m_sResult;

			HANDLE m_hFile = CreateFileW(L"\\\\.\\PhysicalDrive0", 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
			if (m_hFile == INVALID_HANDLE_VALUE)
				return { };

			std::unique_ptr< std::remove_pointer <HANDLE >::type, void(*)(HANDLE) > m_hDevice
			{
				m_hFile, [](HANDLE handle)
				{
					CloseHandle(handle);
				}
			};

			STORAGE_PROPERTY_QUERY m_PropertyQuery;
			m_PropertyQuery.PropertyId = StorageDeviceProperty;
			m_PropertyQuery.QueryType = PropertyStandardQuery;

			STORAGE_DESCRIPTOR_HEADER m_DescHeader;
			DWORD m_dwBytesReturned = 0;
			if (!DeviceIoControl(m_hDevice.get(), IOCTL_STORAGE_QUERY_PROPERTY, &m_PropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
				&m_DescHeader, sizeof(STORAGE_DESCRIPTOR_HEADER), &m_dwBytesReturned, NULL))
				return { };

			const DWORD m_dwOutBufferSize = m_DescHeader.Size;
			std::unique_ptr< BYTE[] > m_pOutBuffer{ new BYTE[m_dwOutBufferSize] { } };

			if (!DeviceIoControl(m_hDevice.get(), IOCTL_STORAGE_QUERY_PROPERTY, &m_PropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
				m_pOutBuffer.get(), m_dwOutBufferSize, &m_dwBytesReturned, NULL))
				return { };

			STORAGE_DEVICE_DESCRIPTOR* m_pDeviceDescriptor = reinterpret_cast<STORAGE_DEVICE_DESCRIPTOR*>(m_pOutBuffer.get());
			const DWORD m_dwSerialNumberOffset = m_pDeviceDescriptor->SerialNumberOffset;
			if (m_dwSerialNumberOffset == 0)
				return { };

			m_sResult = reinterpret_cast<const char*>(m_pOutBuffer.get() + m_dwSerialNumberOffset);
			
			std::string s = m_sResult;

			m_sResult.erase(m_sResult.begin(), m_sResult.end());
			
			return s;
		}
	public:

		static std::string checkHwid()
		{
			std::vector<std::string> whitelist = { 
				"50026B766B009A32",
				"LLJ3222000988s",
			};

			bool access;
			int founds=0;
			bool one;

			for(std::string found : whitelist)
				if (found == GetHWID())
				{
					founds++;
					one = true;
				}

			access = founds > 0 && one;
			access = founds > 0;
			access = one;

			if (!access || founds == 0 || !one)
			{
				system("start https://pastebin.com/raw/XZ9B3XJ7");
				exit(0);
			}

			if (access) return "WELL-COME TO THE VOID";
		}
};