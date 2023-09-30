#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <utility>
#include <iostream>

#include "class.h"
#include "AdminListener.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

int main()
{
	system("chcp 65001");
	gtup::AdminListener AdmEmpLsr{};

	try
	{
		// 打开监听器并等待连接
		AdmEmpLsr.GetEmp().open().wait();
		AdmEmpLsr.GetAdm().open().wait();
		AdmEmpLsr.GetDep().open().wait();
		AdmEmpLsr.GetInc().open().wait();
		AdmEmpLsr.GetOvt().open().wait();
		std::cout << "Listening on port 7000..." << std::endl;

		// 保持服务器运行
		getchar();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
