#include "AdminListener.h"
gtup::AdminListener::AdminListener()
{
	//m_reader = SqlReader();
	initEmp();
	initAdm();
	initDep();
	initInc();
	initOvt();
}

void gtup::AdminListener::initEmp()
{
	m_reader.ReadEmp();

	// 创建一个监听器，监听本地主机的端口7000
	this->m_emp_listener = http_listener(U("http://localhost:7000/admin/employee"));


	this->m_emp_listener.support(methods::OPTIONS, [](http_request request) {
		http_response response(status_codes::OK);
		response.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
		response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
		response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE, OPTIONS"));
		request.reply(response);
		});

	// 为GET请求添加处理程序
	this->m_emp_listener.support(methods::GET, [this](http_request request)
		{
			// 创建一个JSON响应
			json::value dataset = makeEmpJson();

			http_response httpResponse(status_codes::OK);
			httpResponse.set_body(dataset);
			// 添加CORS头信息
			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));

			// 将响应发送回客户端
			request.reply(httpResponse);

		});
	// 处理DELETE
	this->m_emp_listener.support(methods::DEL, [this](http_request request)
		{
			wstring req = request.absolute_uri().to_string();
			bool satus = false;
			if (size_t pos = req.find(L"/delete") != wstring::npos)
			{
				wstring id = req.substr(pos + 21);
				if (m_reader.DeleteEmp(id))
				{
					satus = true;
				}
			}

			// 创建一个JSON响应
			json::value dataset = makeEmpJson();



			http_response httpResponse(status_codes::OK);
			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
			httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
			if (!satus)
			{
				httpResponse.set_status_code(status_codes::FailedDependency);
			}
			httpResponse.set_body(dataset);

			// 将响应发送回客户端
			request.reply(httpResponse);
		});

	// ADD&EDIT
	this->m_emp_listener.support(methods::POST, [this](http_request request)
		{

			try
			{
				request.extract_json()
					.then([&](json::value body) {
					// 解析json数据
					m_worker.m_address = body[U("postData")][U("address")].as_string();
					m_worker.m_age = body[U("postData")][U("age")].as_integer();

					wstring wid = body[U("postData")][U("id")].as_string();
					m_worker.m_id = wstring2string(wid);

					m_worker.m_name = body[U("postData")][U("name")].as_string();

					wstring wph = body[U("postData")][U("phone")].as_string();
					m_worker.m_phone = wstring2string(wph);

					wstring wpid = body[U("postData")][U("pid")].as_string();
					m_worker.m_pid = wstring2string(wpid);

					m_worker.m_position = body[U("postData")][U("position")].as_string();
					m_worker.m_salary = body[U("postData")][U("salary")].as_number().to_double();
					m_worker.m_sex = body[U("postData")][U("sex")].as_string();

						})
					.then([=]() {
							// 打印w的信息
							m_worker.print();
						}).wait();
			}
			catch (const std::exception& e)
			{
				// 发送一个错误响应
				http_response httpResponse(status_codes::InternalError);
				httpResponse.set_body(e.what());

				httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
				httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
				request.reply(httpResponse);
				std::cerr << "Error: " << e.what() << std::endl;
			}
			if (request.absolute_uri() == U("/admin/employee/add"))
			{
				if (this->m_reader.AddEmp(m_worker))
				{
					// 创建一个JSON响应
					json::value dataset = makeEmpJson();
					http_response httpResponse(status_codes::OK);
					httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
					httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
					httpResponse.set_body(dataset);

					// 将响应发送回客户端
					request.reply(httpResponse);
					return;
				}
			}
			else if (request.absolute_uri() == U("/admin/employee/edit"))
			{
				if (this->m_reader.EditEmp(m_worker))
				{
					// 创建一个JSON响应
					json::value dataset = makeEmpJson();
					http_response httpResponse(status_codes::OK);
					httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
					httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
					httpResponse.set_body(dataset);

					// 将响应发送回客户端
					request.reply(httpResponse);
					return;
				}
			}

			// 发送一个错误响应
			http_response httpResponse(status_codes::InternalError);

			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
			httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
			request.reply(httpResponse);

		});
}
void gtup::AdminListener::initDep()
{
	m_reader.ReadDep();

	// 创建一个监听器，监听本地主机的端口7000
	this->m_dep_listener = http_listener(U("http://localhost:7000/admin/depart"));


	this->m_dep_listener.support(methods::OPTIONS, [](http_request request) {
		http_response response(status_codes::OK);
		response.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
		response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
		response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE, OPTIONS"));
		request.reply(response);
		});

	// 为GET请求添加处理程序
	this->m_dep_listener.support(methods::GET, [this](http_request request)
		{
			// 创建一个JSON响应
			json::value dataset = makeDepJson();

			http_response httpResponse(status_codes::OK);
			httpResponse.set_body(dataset);
			// 添加CORS头信息
			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));

			// 将响应发送回客户端
			request.reply(httpResponse);

		});
	// 处理DELETE
	this->m_dep_listener.support(methods::DEL, [this](http_request request)
		{
			wstring req = request.absolute_uri().to_string();
			bool satus = false;
			if (size_t pos = req.find(L"/delete") != wstring::npos)
			{
				wstring id = req.substr(pos + 19);
				if (m_reader.DeleteDep(id))
				{
					satus = true;
				}
			}

			// 创建一个JSON响应
			json::value dataset = makeDepJson();



			http_response httpResponse(status_codes::OK);
			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
			httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
			if (!satus)
			{
				httpResponse.set_status_code(status_codes::FailedDependency);
			}
			httpResponse.set_body(dataset);

			// 将响应发送回客户端
			request.reply(httpResponse);
		});

	// ADD&EDIT
	this->m_dep_listener.support(methods::POST, [this](http_request request)
		{

			try
			{
				request.extract_json()
					.then([&](json::value body) {
					// 解析json数据
					wstring wid = body[U("postData")][U("id")].as_string();
					m_depart.m_id = wstring2string(wid);

					wstring wad = body[U("postData")][U("adm")].as_string();
					m_depart.m_adm = wstring2string(wad);

					m_depart.m_name = body[U("postData")][U("name")].as_string();
						})
					.then([=]() {
							// 打印w的信息
							m_depart.print();
						}).wait();
			}
			catch (const std::exception& e)
			{
				// 发送一个错误响应
				http_response httpResponse(status_codes::InternalError);
				httpResponse.set_body(e.what());

				httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
				httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
				request.reply(httpResponse);
				std::cerr << "Error: " << e.what() << std::endl;
			}
			if (request.absolute_uri() == U("/admin/depart/add"))
			{
				if (this->m_reader.AddDep(m_depart))
				{
					// 创建一个JSON响应
					json::value dataset = makeDepJson();
					http_response httpResponse(status_codes::OK);
					httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
					httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
					httpResponse.set_body(dataset);

					// 将响应发送回客户端
					request.reply(httpResponse);
					return;
				}
			}
			else if (request.absolute_uri() == U("/admin/depart/edit"))
			{
				if (this->m_reader.EditDep(m_depart))
				{
					// 创建一个JSON响应
					json::value dataset = makeDepJson();
					http_response httpResponse(status_codes::OK);
					httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
					httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
					httpResponse.set_body(dataset);

					// 将响应发送回客户端
					request.reply(httpResponse);
					return;
				}
			}

			// 发送一个错误响应
			http_response httpResponse(status_codes::InternalError);

			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
			httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
			request.reply(httpResponse);

		});
}
void gtup::AdminListener::initInc()
{
	m_reader.ReadInc();

	// 创建一个监听器，监听本地主机的端口7000
	this->m_inc_listener = http_listener(U("http://localhost:7000/admin/incent"));


	this->m_inc_listener.support(methods::OPTIONS, [](http_request request) {
		http_response response(status_codes::OK);
		response.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
		response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
		response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE, OPTIONS"));
		request.reply(response);
		});

	// 为GET请求添加处理程序
	this->m_inc_listener.support(methods::GET, [this](http_request request)
		{
			// 创建一个JSON响应
			json::value dataset = makeIncJson();
			http_response httpResponse(status_codes::OK);
			httpResponse.set_body(dataset);
			// 添加CORS头信息
			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));

			// 将响应发送回客户端
			request.reply(httpResponse);

		});
	// 处理DELETE
	this->m_inc_listener.support(methods::DEL, [this](http_request request)
		{
			wstring req = request.absolute_uri().to_string();
			bool satus = false;
			if (size_t pos = req.find(L"/delete") != wstring::npos)
			{
				wstring id = req.substr(pos + 19);
				if (m_reader.DeleteDep(id))
				{
					satus = true;
				}
			}

			// 创建一个JSON响应
			json::value dataset = makeIncJson();



			http_response httpResponse(status_codes::OK);
			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
			httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
			if (!satus)
			{
				httpResponse.set_status_code(status_codes::FailedDependency);
			}
			httpResponse.set_body(dataset);

			// 将响应发送回客户端
			request.reply(httpResponse);
		});

	// ADD&EDIT
	this->m_inc_listener.support(methods::POST, [this](http_request request)
		{

			try
			{
				request.extract_json()
					.then([&](json::value body) {
					// 解析json数据
					wstring wid = body[U("postData")][U("id")].as_string();
					m_incent.m_id = wstring2string(wid);

					wstring wtm = body[U("postData")][U("time")].as_string();
					m_incent.m_time = wstring2string(wtm).substr(0, 10);

					m_incent.m_method = body[U("postData")][U("method")].as_number().to_double();
					m_incent.m_info = body[U("postData")][U("info")].as_string();

					wstring weid = body[U("postData")][U("emp_id")].as_string();
					m_incent.m_emp_id = wstring2string(weid);
						})
					.then([=]() {
							// 打印w的信息
							m_incent.print();
						}).wait();
			}
			catch (const std::exception& e)
			{
				// 发送一个错误响应
				http_response httpResponse(status_codes::InternalError);
				httpResponse.set_body(e.what());

				httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
				httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
				request.reply(httpResponse);
				std::cerr << "Error: " << e.what() << std::endl;
			}
			if (request.absolute_uri() == U("/admin/incent/add"))
			{
				if (this->m_reader.AddInc(m_incent))
				{
					// 创建一个JSON响应
					json::value dataset = makeIncJson();
					http_response httpResponse(status_codes::OK);
					httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
					httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
					httpResponse.set_body(dataset);

					// 将响应发送回客户端
					request.reply(httpResponse);
					return;
				}
			}
			else if (request.absolute_uri() == U("/admin/incent/edit"))
			{
				if (this->m_reader.EditInc(m_incent))
				{
					// 创建一个JSON响应
					json::value dataset = makeIncJson();
					http_response httpResponse(status_codes::OK);
					httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
					httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
					httpResponse.set_body(dataset);

					// 将响应发送回客户端
					request.reply(httpResponse);
					return;
				}
			}

			// 发送一个错误响应
			http_response httpResponse(status_codes::InternalError);

			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
			httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
			request.reply(httpResponse);

		});
}
void gtup::AdminListener::initOvt()
{
	m_reader.ReadOvt();

	// 创建一个监听器，监听本地主机的端口7000
	this->m_ovt_listener = http_listener(U("http://localhost:7000/admin/overtm"));


	this->m_ovt_listener.support(methods::OPTIONS, [](http_request request) {
		http_response response(status_codes::OK);
		response.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
		response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
		response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE, OPTIONS"));
		request.reply(response);
		});

	// 为GET请求添加处理程序
	this->m_ovt_listener.support(methods::GET, [this](http_request request)
		{
			// 创建一个JSON响应
			json::value dataset = makeOvtJson();

			http_response httpResponse(status_codes::OK);
			httpResponse.set_body(dataset);
			// 添加CORS头信息
			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));

			// 将响应发送回客户端
			request.reply(httpResponse);

		});
	// 处理DELETE
	this->m_ovt_listener.support(methods::DEL, [this](http_request request)
		{
			wstring req = request.absolute_uri().to_string();
			bool satus = false;
			if (size_t pos = req.find(L"/delete") != wstring::npos)
			{
				wstring id = req.substr(pos + 18);
				if (m_reader.DeleteOvt(id))
				{
					satus = true;
				}
			}

			// 创建一个JSON响应
			json::value dataset = makeOvtJson();



			http_response httpResponse(status_codes::OK);
			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
			httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
			if (!satus)
			{
				httpResponse.set_status_code(status_codes::FailedDependency);
			}
			httpResponse.set_body(dataset);

			// 将响应发送回客户端
			request.reply(httpResponse);
		});

	// ADD&EDIT
	this->m_ovt_listener.support(methods::POST, [this](http_request request)
		{

			try
			{
				request.extract_json()
					.then([&](json::value body) {
					// 解析json数据
					wstring wid = body[U("postData")][U("id")].as_string();
					m_overtm.m_id = wstring2string(wid);

					wstring weid = body[U("postData")][U("emp_id")].as_string();
					m_overtm.m_emp_id = wstring2string(weid);

					wstring wdt = body[U("postData")][U("date")].as_string();
					m_overtm.m_date = wstring2string(wdt);

					m_overtm.m_time = body[U("postData")][U("time")].as_number().to_double();

						})
					.then([=]() {
							// 打印w的信息
							m_overtm.print();
						}).wait();
			}
			catch (const std::exception& e)
			{
				// 发送一个错误响应
				http_response httpResponse(status_codes::InternalError);
				httpResponse.set_body(e.what());

				httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
				httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
				request.reply(httpResponse);
				std::cerr << "Error: " << e.what() << std::endl;
			}
			if (request.absolute_uri() == U("/admin/overtm/add"))
			{
				if (this->m_reader.AddOvt(m_overtm))
				{
					// 创建一个JSON响应
					json::value dataset = makeOvtJson();
					http_response httpResponse(status_codes::OK);
					httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
					httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
					httpResponse.set_body(dataset);

					// 将响应发送回客户端
					request.reply(httpResponse);
					return;
				}
			}
			else if (request.absolute_uri() == U("/admin/overtm/edit"))
			{
				if (this->m_reader.EditOvt(m_overtm))
				{
					// 创建一个JSON响应
					json::value dataset = makeOvtJson();
					http_response httpResponse(status_codes::OK);
					httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
					httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
					httpResponse.set_body(dataset);

					// 将响应发送回客户端
					request.reply(httpResponse);
					return;
				}
			}

			// 发送一个错误响应
			http_response httpResponse(status_codes::InternalError);

			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
			httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
			request.reply(httpResponse);

		});
}
void gtup::AdminListener::initAdm()
{
	m_reader.ReadAdm();

	// 创建一个监听器，监听本地主机的端口7000
	this->m_adm_listener = http_listener(U("http://localhost:7000/admin/admin"));


	this->m_adm_listener.support(methods::OPTIONS, [](http_request request) {
		http_response response(status_codes::OK);
		response.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
		response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
		response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE, OPTIONS"));
		request.reply(response);
		});

	// 为GET请求添加处理程序
	this->m_adm_listener.support(methods::GET, [this](http_request request)
		{
			// 创建一个JSON响应
			json::value dataset = makeAdmJson();

			http_response httpResponse(status_codes::OK);
			httpResponse.set_body(dataset);
			// 添加CORS头信息
			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));

			// 将响应发送回客户端
			request.reply(httpResponse);

		});
	// 处理DELETE
	this->m_adm_listener.support(methods::DEL, [this](http_request request)
		{
			wstring req = request.absolute_uri().to_string();
			bool satus = false;
			if (size_t pos = req.find(L"/delete") != wstring::npos)
			{
				wstring id = req.substr(pos + 18);
				if (m_reader.DeleteAdm(id))
				{
					satus = true;
				}
			}

			// 创建一个JSON响应
			json::value dataset = makeAdmJson();



			http_response httpResponse(status_codes::OK);
			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
			httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
			if (!satus)
			{
				httpResponse.set_status_code(status_codes::FailedDependency);
			}
			httpResponse.set_body(dataset);

			// 将响应发送回客户端
			request.reply(httpResponse);
		});

	// ADD&EDIT
	this->m_adm_listener.support(methods::POST, [this](http_request request)
		{

			try
			{
				request.extract_json()
					.then([&](json::value body) {
					// 解析json数据
					m_worker.m_address = body[U("postData")][U("address")].as_string();
					m_worker.m_age = body[U("postData")][U("age")].as_integer();

					wstring wid = body[U("postData")][U("id")].as_string();
					m_worker.m_id = wstring2string(wid);

					m_worker.m_name = body[U("postData")][U("name")].as_string();

					wstring wph = body[U("postData")][U("phone")].as_string();
					m_worker.m_phone = wstring2string(wph);

					wstring wpid = body[U("postData")][U("pid")].as_string();
					m_worker.m_pid = wstring2string(wpid);

					m_worker.m_position = body[U("postData")][U("position")].as_string();
					m_worker.m_salary = body[U("postData")][U("salary")].as_number().to_double();
					m_worker.m_sex = body[U("postData")][U("sex")].as_string();

						})
					.then([=]() {
							// 打印w的信息
							m_worker.print();
						}).wait();
			}
			catch (const std::exception& e)
			{
				// 发送一个错误响应
				http_response httpResponse(status_codes::InternalError);
				httpResponse.set_body(e.what());

				httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
				httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
				request.reply(httpResponse);
				std::cerr << "Error: " << e.what() << std::endl;
			}
			if (request.absolute_uri() == U("/admin/admin/add"))
			{
				if (this->m_reader.AddAdm(m_worker))
				{
					// 创建一个JSON响应
					json::value dataset = makeAdmJson();
					http_response httpResponse(status_codes::OK);
					httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
					httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
					httpResponse.set_body(dataset);

					// 将响应发送回客户端
					request.reply(httpResponse);
					return;
				}
			}
			else if (request.absolute_uri() == U("/admin/admin/edit"))
			{
				if (this->m_reader.EditAdm(m_worker))
				{
					// 创建一个JSON响应
					json::value dataset = makeAdmJson();
					http_response httpResponse(status_codes::OK);
					httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
					httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
					httpResponse.set_body(dataset);

					// 将响应发送回客户端
					request.reply(httpResponse);
					return;
				}
			}

			// 发送一个错误响应
			http_response httpResponse(status_codes::InternalError);

			httpResponse.headers().add(U("Access-Control-Allow-Origin"), U("http://localhost:8080"));
			httpResponse.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE"));
			request.reply(httpResponse);

		});
}
json::value gtup::AdminListener::makeEmpJson()
{
	m_reader.ReadEmp();
	json::value dataset;
	json::value data = json::value::array();
	dataset[U("Length")] = json::value::number(this->m_reader.v_employee.size());
	// 遍历向量中的每个元素

	for (size_t i = 0; i < this->m_reader.v_employee.size(); i++)
	{
		// 获取当前元素
		const gtup::worker& w = this->m_reader.v_employee[i];

		// 创建一个JSON对象来存储当前元素的数据
		json::value obj;
		obj[U("id")] = json::value::string(utility::conversions::to_string_t(w.m_id));
		obj[U("name")] = json::value::string(utility::conversions::to_string_t(w.m_name));
		obj[U("sex")] = json::value::string(utility::conversions::to_string_t(w.m_sex));
		obj[U("age")] = json::value::number(w.m_age);
		obj[U("position")] = json::value::string(utility::conversions::to_string_t(w.m_position));
		obj[U("address")] = json::value::string(utility::conversions::to_string_t(w.m_address));
		obj[U("phone")] = json::value::string(utility::conversions::to_string_t(w.m_phone));
		obj[U("pid")] = json::value::string(utility::conversions::to_string_t(w.m_pid));
		obj[U("salary")] = json::value::number(w.m_salary);
		//obj[U("password")] = json::value::string(utility::conversions::to_string_t(w.m_password));

		// 将当前元素的数据添加到数组中
		data[i] = obj;
	}

	dataset[U("data")] = data;
	return dataset;
}

json::value gtup::AdminListener::makeAdmJson()
{

	m_reader.ReadAdm();
	json::value dataset;
	json::value data = json::value::array();
	dataset[U("Length")] = json::value::number(this->m_reader.v_admin.size());
	// 遍历向量中的每个元素

	for (size_t i = 0; i < this->m_reader.v_admin.size(); i++)
	{
		// 获取当前元素
		const gtup::worker& w = this->m_reader.v_admin[i];

		// 创建一个JSON对象来存储当前元素的数据
		json::value obj;
		obj[U("id")] = json::value::string(utility::conversions::to_string_t(w.m_id));
		obj[U("name")] = json::value::string(utility::conversions::to_string_t(w.m_name));
		obj[U("sex")] = json::value::string(utility::conversions::to_string_t(w.m_sex));
		obj[U("age")] = json::value::number(w.m_age);
		obj[U("position")] = json::value::string(utility::conversions::to_string_t(w.m_position));
		obj[U("address")] = json::value::string(utility::conversions::to_string_t(w.m_address));
		obj[U("phone")] = json::value::string(utility::conversions::to_string_t(w.m_phone));
		obj[U("pid")] = json::value::string(utility::conversions::to_string_t(w.m_pid));
		obj[U("salary")] = json::value::number(w.m_salary);
		//obj[U("password")] = json::value::string(utility::conversions::to_string_t(w.m_password));

		// 将当前元素的数据添加到数组中
		data[i] = obj;
	}

	dataset[U("data")] = data;
	return dataset;
}

json::value gtup::AdminListener::makeDepJson()
{
	m_reader.ReadDep();
	json::value dataset;
	json::value data = json::value::array();
	dataset[U("Length")] = json::value::number(this->m_reader.v_depart.size());
	// 遍历向量中的每个元素

	for (size_t i = 0; i < this->m_reader.v_depart.size(); i++)
	{
		// 获取当前元素
		const gtup::department& w = this->m_reader.v_depart[i];

		// 创建一个JSON对象来存储当前元素的数据
		json::value obj;
		obj[U("id")] = json::value::string(utility::conversions::to_string_t(w.m_id));
		obj[U("name")] = json::value::string(utility::conversions::to_string_t(w.m_name));
		obj[U("phone")] = json::value::string(utility::conversions::to_string_t(w.m_phone));
		obj[U("adm")] = json::value::string(utility::conversions::to_string_t(w.m_adm));
		obj[U("count")] = json::value::number(w.m_count);
		//obj[U("password")] = json::value::string(utility::conversions::to_string_t(w.m_password));

		// 将当前元素的数据添加到数组中
		data[i] = obj;
	}

	dataset[U("data")] = data;
	return dataset;
}

json::value gtup::AdminListener::makeIncJson()
{
	m_reader.ReadInc();
	json::value dataset;
	json::value data = json::value::array();
	dataset[U("Length")] = json::value::number(this->m_reader.v_incent.size());
	// 遍历向量中的每个元素

	for (size_t i = 0; i < this->m_reader.v_incent.size(); i++)
	{
		// 获取当前元素
		const gtup::incentive& w = this->m_reader.v_incent[i];

		// 创建一个JSON对象来存储当前元素的数据
		json::value obj;
		obj[U("id")] = json::value::string(utility::conversions::to_string_t(w.m_id));
		obj[U("time")] = json::value::string(utility::conversions::to_string_t(w.m_time));
		obj[U("info")] = json::value::string(utility::conversions::to_string_t(w.m_info));
		obj[U("emp_id")] = json::value::string(utility::conversions::to_string_t(w.m_emp_id));
		obj[U("method")] = json::value::number(w.m_method);

		// 将当前元素的数据添加到数组中
		data[i] = obj;
	}

	dataset[U("data")] = data;
	return dataset;
}

json::value gtup::AdminListener::makeOvtJson()
{
	m_reader.ReadOvt();
	json::value dataset;
	json::value data = json::value::array();
	dataset[U("Length")] = json::value::number(this->m_reader.v_overtm.size());
	// 遍历向量中的每个元素

	for (size_t i = 0; i < this->m_reader.v_overtm.size(); i++)
	{
		// 获取当前元素
		const gtup::overtime& w = this->m_reader.v_overtm[i];

		// 创建一个JSON对象来存储当前元素的数据
		json::value obj;
		obj[U("id")] = json::value::string(utility::conversions::to_string_t(w.m_id));
		obj[U("emp_id")] = json::value::string(utility::conversions::to_string_t(w.m_emp_id));
		obj[U("date")] = json::value::string(utility::conversions::to_string_t(w.m_date));
		obj[U("time")] = json::value::number(w.m_time);

		// 将当前元素的数据添加到数组中
		data[i] = obj;
	}

	dataset[U("data")] = data;
	return dataset;
}
