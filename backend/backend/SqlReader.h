#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <windows.h>
#include "class.h"

#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

using std::vector;
using std::string;

namespace gtup
{
	class SqlReader
	{
	public:
		vector<worker>v_employee;
		vector<worker>v_admin;
		vector<department>v_depart;
		vector<incentive>v_incent;
		vector<overtime>v_overtm;

	public:
		SqlReader();
		~SqlReader();
		void ReadAdm();
		void ReadEmp();
		void ReadDep();
		void ReadInc();
		void ReadOvt();

		bool EditEmp(worker& worker_to_edit);
		bool AddEmp(worker& worker_to_add);
		bool DeleteEmp(std::wstring id_to_delete);

		bool EditAdm(worker& worker_to_edit);
		bool AddAdm(worker& worker_to_add);
		bool DeleteAdm(std::wstring id_to_delete);

		bool EditDep(department& dep_to_edit);
		bool AddDep(department& dep_to_edit);
		bool DeleteDep(std::wstring id_to_delete);

		bool EditInc(incentive& inc_to_edit);
		bool AddInc(incentive& inc_to_edit);
		bool DeleteInc(std::wstring id_to_delete);

		bool EditOvt(overtime& inc_to_edit);
		bool AddOvt(overtime& inc_to_edit);
		bool DeleteOvt(std::wstring id_to_delete);

		// delete the spaces from  back
		std::string trim_right(const char* str, size_t len)
		{
			if (str == nullptr || len == 0) {
				return "";
			}
			size_t endpos = len - 1;
			while (endpos > 0 && (isspace(str[endpos])) || str[endpos] == '\0') {
				endpos--;
			}
			return std::string(str, endpos + 1);
		}
		std::wstring trim_right(const wchar_t* str, size_t len)
		{
			if (str == nullptr || len == 0) {
				return L"";
			}
			size_t endpos = len - 1;
			while (endpos > 0 && (iswspace(str[endpos])) || str[endpos] == '\0') {
				endpos--;
			}
			return std::wstring(str, endpos + 1);
		}
		wstring string2wstring(string str)
		{
			wstring result;
			//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
			int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
			TCHAR* buffer = new TCHAR[len + 1];
			//多字节编码转换成宽字节编码  
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
			buffer[len] = '\0';             //添加字符串结尾  
			//删除缓冲区并返回值  
			result.append(buffer);
			delete[] buffer;
			return result;
		}

		//将wstring转换成string  
		string wstring2string(wstring wstr)
		{
			string result;
			//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
			int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
			char* buffer = new char[len + 1];
			//宽字节编码转换成多字节编码  
			WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
			buffer[len] = '\0';
			//删除缓冲区并返回值  
			result.append(buffer);
			delete[] buffer;
			return result;
		}

	private:
		// Declare variables

		SQLWCHAR szDSN[256] = L"EmpManagment";
		SQLWCHAR szUID[256] = L"";
		SQLWCHAR szPWD[256] = L"";
		SQLWCHAR empQuery[1024] = L"select * from employee";
		SQLWCHAR depQuery[1024] = L"select * from department";
		SQLWCHAR admQuery[1024] = L"select * from admin";
		SQLWCHAR incQuery[1024] = L"select * from incentive";
		SQLWCHAR ovtQuery[1024] = L"select * from overtime";

		SQLHENV m_henv;
		SQLHDBC m_hdbc;
		SQLHSTMT m_hstmt;
		SQLRETURN m_retcode;
	};


}