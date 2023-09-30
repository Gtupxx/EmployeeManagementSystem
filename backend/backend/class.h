#pragma once
#include <string>
#include <vector>
#include <iostream>

using std::wstring;
using std::string;
using std::vector;
namespace gtup
{

	class worker
	{
	public:
		enum class worker_type
		{
			employee,
			admin,
			hr
		}m_type;

	public:
		worker(string id = "001",
			wstring name = L"LiHua",
			wstring sex = L"男",
			int age = 24,
			wstring position = L"打螺丝的",
			wstring address = L"威海",
			string phone = "10086",
			string pid = "371000000000000000",
			float salary = 0.0f,
			string password = "",
			worker_type type = worker_type::employee)
			: m_id(id), m_name(name), m_sex(sex), m_age(age), m_position(position),
			m_address(address), m_phone(phone), m_pid(pid),
			m_salary(salary), m_password(password), m_type(type) {};

		~worker() {};

	public:
		string m_id;
		wstring m_name;
		wstring m_sex;
		int m_age;
		wstring m_position;
		wstring m_address;
		string m_phone;
		string m_pid;
		float m_salary;
		string m_password;

	public:
		void print()
		{
			std::cout << "Worker ID: " << m_id << std::endl;
			std::wcout << "Worker Name: " << m_name << std::endl;
			std::wcout << "Worker Sex: " << m_sex << std::endl;
			std::cout << "Worker Age: " << m_age << std::endl;
			std::wcout << "Worker Position: " << m_position << std::endl;
			std::wcout << "Worker Address: " << m_address << std::endl;
			std::cout << "Worker Phone: " << m_phone << std::endl;
			std::cout << "Worker PID: " << m_pid << std::endl;
			std::cout << "Worker Salary: " << m_salary << std::endl;
			std::cout << "Worker Password: " << m_password << std::endl;
			std::cout << std::endl;
		}
	};
	class department
	{
	public:
		department(string _m_id = "001", wstring _m_name = L"宣传", string _m_adm = "10001", string _m_phone = "16325631253", int _m_count = 0)
			:m_id(_m_id), m_name(_m_name), m_adm(_m_adm), m_phone(_m_phone), m_count(_m_count) {}
	public:
		string m_id;
		wstring m_name;
		string m_adm;
		string m_phone;// 从admin获取
		int m_count = 0;

	public:
		void print()
		{
			std::cout << "id:" << m_id << std::endl;
			std::wcout << L"name:" << m_name << std::endl;
			std::cout << "phone" << m_phone << std::endl;
			std::cout << "admid:" << m_adm << std::endl;
			std::cout << "count:" << m_count << std::endl;
		}
	};

	class incentive
	{
	public:
		incentive(string _m_id = "40001", string _m_time = "", float _m_method = 0.0f, wstring _m_info = L"玩原神玩的", string _m_emp_id = "20001")
			:m_id(_m_id), m_time(_m_time), m_method(_m_method), m_info(_m_info), m_emp_id(_m_emp_id) {}

	public:
		string m_id;
		string m_time;
		float m_method;
		wstring m_info;
		string m_emp_id;

		void print()
		{
			std::cout << "id:" << m_id << std::endl;
			std::cout << "empid:" << m_emp_id << std::endl;
			std::cout << "time:" << m_time << std::endl;
			std::cout << "method:" << m_method << std::endl;
			std::wcout << L"info:" << m_info << std::endl;
		}
	};

	class overtime
	{
	public:
		overtime(string _m_id = "50001", string _m_emp_id = "20001", string _m_date = "2023-06-15", float _m_time = 0.0f)
			:m_id(_m_id), m_emp_id(_m_emp_id), m_date(_m_date), m_time(_m_time) {}

	public:
		string m_id;
		string m_emp_id;
		string m_date;
		float m_time;

	public:
		void print()
		{
			std::cout << "id: " << m_id << std::endl;
			std::cout << "emp id: " << m_emp_id << std::endl;
			std::cout << "date: " << m_date << std::endl;
			std::cout << "time" << m_time << std::endl;
		}
	};
}
