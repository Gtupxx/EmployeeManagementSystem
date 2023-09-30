#pragma once
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <utility>
#include <iostream>

#include "class.h"
#include "SqlReader.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

namespace gtup
{
	class AdminListener
	{
	public:
		AdminListener();
		void initEmp();
		void initAdm();
		void initDep();
		void initInc();
		void initOvt();

		json::value makeEmpJson();
		json::value makeAdmJson();
		json::value makeDepJson();
		json::value makeIncJson();
		json::value makeOvtJson();

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

		http_listener& GetEmp()
		{
			return this->m_emp_listener;
		}
		http_listener& GetDep()
		{
			return this->m_dep_listener;
		}
		http_listener& GetAdm()
		{
			return this->m_adm_listener;
		}
		http_listener& GetInc()
		{
			return this->m_inc_listener;
		}
		http_listener& GetOvt()
		{
			return this->m_ovt_listener;
		}
	public:
		gtup::SqlReader m_reader;

		http_listener m_emp_listener;
		http_listener m_adm_listener;
		http_listener m_dep_listener;
		http_listener m_inc_listener;
		http_listener m_ovt_listener;

		worker m_worker{};
		department m_depart{};
		incentive m_incent{};
		overtime m_overtm{};

	};
}