#include "SqlReader.h"
gtup::SqlReader::SqlReader()
{
	// Allocate environment handle
	m_retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);

	// Set the ODBC version
	m_retcode = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

	// Allocate connection handle
	m_retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc);

	// Connect to the database
	m_retcode = SQLConnect(m_hdbc, (SQLWCHAR*)szDSN, SQL_NTS, (SQLWCHAR*)szUID, SQL_NTS, (SQLWCHAR*)szPWD, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Connected to database." << std::endl;
	}
	else {
		std::cout << "Failed to connect to the database." << std::endl;
	}

}

gtup::SqlReader::~SqlReader()
{
	// Free resources
	SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
	SQLDisconnect(m_hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
}
void gtup::SqlReader::ReadAdm()
{

	// Allocate statement handle
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);

	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)admQuery, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Query executed." << std::endl;
	}

	// clear the data
	v_admin.clear();

	// Fetch the results
	while (SQLFetch(m_hstmt) == SQL_SUCCESS) {
		// Process the data
		char worker_id[11];
		wchar_t worker_name[21] = { 0 };
		bool worker_sex;
		int worker_age;
		wchar_t worker_position[21] = { 0 };
		wchar_t worker_address[201] = { 0 };
		char worker_phone[21];
		char worker_pid[21];
		float worker_salary;
		char worker_password[21];

		SQLGetData(m_hstmt, 1, SQL_C_CHAR, worker_id, sizeof(worker_id), NULL);
		SQLGetData(m_hstmt, 2, SQL_C_WCHAR, worker_name, sizeof(worker_name), NULL);
		SQLGetData(m_hstmt, 3, SQL_C_BIT, &worker_sex, 0, NULL);
		SQLGetData(m_hstmt, 4, SQL_C_LONG, &worker_age, 0, NULL);
		SQLGetData(m_hstmt, 5, SQL_C_WCHAR, worker_position, sizeof(worker_position), NULL);
		SQLGetData(m_hstmt, 6, SQL_C_WCHAR, worker_address, sizeof(worker_address), NULL);
		SQLGetData(m_hstmt, 7, SQL_C_CHAR, worker_phone, sizeof(worker_phone), NULL);
		SQLGetData(m_hstmt, 8, SQL_C_CHAR, worker_pid, sizeof(worker_pid), NULL);
		SQLGetData(m_hstmt, 9, SQL_C_FLOAT, &worker_salary, 0, NULL);
		SQLGetData(m_hstmt, 10, SQL_C_CHAR, worker_password, sizeof(worker_password), NULL);

		string worker_pid_str = trim_right(worker_pid, sizeof(worker_pid) / sizeof(worker_pid[0]) - 1);
		string worker_phone_str = trim_right(worker_phone, sizeof(worker_phone) / sizeof(worker_phone[0]) - 1);
		string worker_id_str = trim_right(worker_id, sizeof(worker_id) / sizeof(worker_id[0]) - 1);
		wstring worker_name_wstr = trim_right(worker_name, sizeof(worker_name) / sizeof(worker_name[0]) - 1);
		wstring worker_position_wstr = trim_right(worker_position, sizeof(worker_position) / sizeof(worker_position[0]) - 1);
		wstring worker_address_wstr = trim_right(worker_address, sizeof(worker_address) / sizeof(worker_address[0]) - 1);

		// Store the data
		v_admin.emplace_back(
			worker(
				worker_id_str,
				worker_name_wstr,
				wstring((worker_sex ? L"男" : L"女")),
				worker_age,
				worker_position_wstr,
				worker_address_wstr,
				worker_phone_str,
				worker_pid_str,
				worker_salary,
				string(worker_password),
				worker::worker_type::admin
			)
		);
	}
}
void gtup::SqlReader::ReadEmp()
{

	// Allocate statement handle
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);

	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)empQuery, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Query executed." << std::endl;
	}

	// clear the data
	v_employee.clear();

	// Fetch the results
	while (SQLFetch(m_hstmt) == SQL_SUCCESS) {
		// Process the data
		char worker_id[11];
		wchar_t worker_name[21] = { 0 };
		bool worker_sex;
		int worker_age;
		wchar_t worker_position[21] = { 0 };
		wchar_t worker_address[201] = { 0 };
		char worker_phone[21];
		char worker_pid[21];
		float worker_salary;
		char worker_password[21];

		SQLGetData(m_hstmt, 1, SQL_C_CHAR, worker_id, sizeof(worker_id), NULL);
		SQLGetData(m_hstmt, 2, SQL_C_WCHAR, worker_name, sizeof(worker_name), NULL);
		SQLGetData(m_hstmt, 3, SQL_C_BIT, &worker_sex, 0, NULL);
		SQLGetData(m_hstmt, 4, SQL_C_LONG, &worker_age, 0, NULL);
		SQLGetData(m_hstmt, 5, SQL_C_WCHAR, worker_position, sizeof(worker_position), NULL);
		SQLGetData(m_hstmt, 6, SQL_C_WCHAR, worker_address, sizeof(worker_address), NULL);
		SQLGetData(m_hstmt, 7, SQL_C_CHAR, worker_phone, sizeof(worker_phone), NULL);
		SQLGetData(m_hstmt, 8, SQL_C_CHAR, worker_pid, sizeof(worker_pid), NULL);
		SQLGetData(m_hstmt, 9, SQL_C_FLOAT, &worker_salary, 0, NULL);
		SQLGetData(m_hstmt, 10, SQL_C_CHAR, worker_password, sizeof(worker_password), NULL);

		string worker_pid_str = trim_right(worker_pid, sizeof(worker_pid) / sizeof(worker_pid[0]) - 1);
		string worker_phone_str = trim_right(worker_phone, sizeof(worker_phone) / sizeof(worker_phone[0]) - 1);
		string worker_id_str = trim_right(worker_id, sizeof(worker_id) / sizeof(worker_id[0]) - 1);
		wstring worker_name_wstr = trim_right(worker_name, sizeof(worker_name) / sizeof(worker_name[0]) - 1);
		wstring worker_position_wstr = trim_right(worker_position, sizeof(worker_position) / sizeof(worker_position[0]) - 1);
		wstring worker_address_wstr = trim_right(worker_address, sizeof(worker_address) / sizeof(worker_address[0]) - 1);

		// Store the data
		v_employee.emplace_back(
			worker(
				worker_id_str,
				worker_name_wstr,
				wstring((worker_sex ? L"男" : L"女")),
				worker_age,
				worker_position_wstr,
				worker_address_wstr,
				worker_phone_str,
				worker_pid_str,
				worker_salary,
				string(worker_password),
				worker::worker_type::employee
			)
		);
	}
}
void gtup::SqlReader::ReadDep()
{
	ReadEmp();
	ReadAdm();
	// Allocate statement handle
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);

	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)depQuery, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Query executed." << std::endl;
	}

	// clear the data
	v_depart.clear();

	// Fetch the results
	while (SQLFetch(m_hstmt) == SQL_SUCCESS) {
		// Process the data
		char dep_id[11];
		wchar_t dep_name[21] = { 0 };
		char adm_id[11];

		SQLGetData(m_hstmt, 1, SQL_C_CHAR, dep_id, sizeof(dep_id), NULL);
		SQLGetData(m_hstmt, 2, SQL_C_WCHAR, dep_name, sizeof(dep_name), NULL);
		SQLGetData(m_hstmt, 3, SQL_C_CHAR, adm_id, sizeof(adm_id), NULL);

		string depart_id_str = trim_right(dep_id, sizeof(dep_id) / sizeof(dep_id[0]) - 1);
		wstring dep_name_wstr = trim_right(dep_name, sizeof(dep_name) / sizeof(dep_name[0]) - 1);
		string adm_id_str = trim_right(adm_id, sizeof(adm_id) / sizeof(adm_id[0]) - 1);

		string adm_phone;
		for (auto w : v_admin)
		{
			if (w.m_id == adm_id_str)
			{
				adm_phone = w.m_phone;
			}
		}
		int cnt = 0;
		for (auto w : v_employee)
		{
			if (w.m_position == dep_name_wstr)
			{
				cnt++;
			}
		}

		// Store the data
		v_depart.emplace_back(
			department(
				depart_id_str,
				dep_name_wstr,
				adm_id_str,
				adm_phone,
				cnt
			)
		);
	}
}
void gtup::SqlReader::ReadInc()
{
	// Allocate statement handle
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);

	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)incQuery, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Query executed." << std::endl;
	}

	// clear the data
	v_incent.clear();

	// Fetch the results
	while (SQLFetch(m_hstmt) == SQL_SUCCESS) {
		// Process the data
		char incent_id[11];
		char incent_emp_id[11];
		char incent_time[11];
		float incent_meto;
		wchar_t incent_info[201] = { 0 };


		SQLGetData(m_hstmt, 1, SQL_C_CHAR, incent_time, sizeof(incent_time), NULL);
		SQLGetData(m_hstmt, 2, SQL_C_FLOAT, &incent_meto, 0, NULL);
		SQLGetData(m_hstmt, 3, SQL_C_WCHAR, incent_info, sizeof(incent_info), NULL);
		SQLGetData(m_hstmt, 4, SQL_C_CHAR, incent_id, sizeof(incent_id), NULL);
		SQLGetData(m_hstmt, 5, SQL_C_CHAR, incent_emp_id, sizeof(incent_emp_id), NULL);

		string incent_time_str = trim_right(incent_time, sizeof(incent_time) / sizeof(incent_time[0]) - 1);
		wstring incent_info_wstr = trim_right(incent_info, sizeof(incent_info) / sizeof(incent_info[0]) - 1);
		string incent_id_str = trim_right(incent_id, sizeof(incent_id) / sizeof(incent_id[0]) - 1);
		string incent_emp_id_str = trim_right(incent_emp_id, sizeof(incent_emp_id) / sizeof(incent_emp_id[0]) - 1);

		// Store the data
		v_incent.emplace_back(
			incentive(
				incent_id_str,
				incent_time_str,
				incent_meto,
				incent_info_wstr,
				incent_emp_id_str
			)
		);
	}
}

void gtup::SqlReader::ReadOvt()
{
	// Allocate statement handle
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);

	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)ovtQuery, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Query executed." << std::endl;
	}

	// clear the data
	v_overtm.clear();

	// Fetch the results
	while (SQLFetch(m_hstmt) == SQL_SUCCESS) {
		// Process the data
		char overtm_id[11];
		char overtm_emp_id[11];
		char overtm_date[11];
		float overtm_time;

		SQLGetData(m_hstmt, 1, SQL_C_CHAR, overtm_id, sizeof(overtm_id), NULL);
		SQLGetData(m_hstmt, 2, SQL_C_FLOAT, &overtm_time, 0, NULL);
		SQLGetData(m_hstmt, 3, SQL_C_CHAR, overtm_emp_id, sizeof(overtm_emp_id), NULL);
		SQLGetData(m_hstmt, 4, SQL_C_CHAR, overtm_date, sizeof(overtm_date), NULL);

		string overtm_id_str = trim_right(overtm_id, sizeof(overtm_id) / sizeof(overtm_id[0]) - 1);
		string overtm_emp_id_str = trim_right(overtm_emp_id, sizeof(overtm_emp_id) / sizeof(overtm_emp_id[0]) - 1);
		string overtm_date_str = trim_right(overtm_date, sizeof(overtm_date) / sizeof(overtm_date[0]) - 1);

		// Store the data
		v_overtm.emplace_back(
			overtime(
				overtm_id_str,
				overtm_emp_id_str,
				overtm_date_str,
				overtm_time
			)
		);
	}
}
bool gtup::SqlReader::EditEmp(worker& worker_to_edit)
{
	SQLWCHAR edit_query[1024];
	swprintf_s(edit_query,
		1024,
		L"UPDATE employee SET emp_name='%s', emp_age=%d, emp_position='%s', emp_address='%s', emp_phone='%s', emp_pid='%s', emp_salary=%f, emp_sex='%d' WHERE emp_id='%S'",
		worker_to_edit.m_name.c_str(),
		worker_to_edit.m_age,
		worker_to_edit.m_position.c_str(),
		worker_to_edit.m_address.c_str(),
		string2wstring(worker_to_edit.m_phone).c_str(),
		string2wstring(worker_to_edit.m_pid).c_str(),
		worker_to_edit.m_salary,
		worker_to_edit.m_sex == L"男",
		worker_to_edit.m_id.c_str());

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)edit_query, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Edit finished!" << std::endl;
		return true;
	}
	return false;
}
bool gtup::SqlReader::AddEmp(worker& worker_to_add)
{
	SQLWCHAR edit_query[1024];
	swprintf_s(edit_query,
		1024,
		L"INSERT INTO employee(emp_id, emp_name, emp_age, emp_position, emp_address, emp_phone, emp_pid, emp_salary, emp_sex)  VALUES ('%S', '%s', %d, '%s', '%s', '%s', '%s', %f, '%d')",
		worker_to_add.m_id.c_str(),
		worker_to_add.m_name.c_str(),
		worker_to_add.m_age,
		worker_to_add.m_position.c_str(),
		worker_to_add.m_address.c_str(),
		string2wstring(worker_to_add.m_phone).c_str(),
		string2wstring(worker_to_add.m_pid).c_str(),
		worker_to_add.m_salary,
		worker_to_add.m_sex == L"男"
	);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)edit_query, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Add finished!" << std::endl;
		return true;
	}
	return false;
}
bool gtup::SqlReader::DeleteEmp(std::wstring id_to_delete)
{
	std::wstring base = L"delete from employee where emp_id=";
	base += id_to_delete;
	const SQLWCHAR* delete_querty = base.c_str();
	// Allocate statement handle
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)delete_querty, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Delete finished!" << std::endl;
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool gtup::SqlReader::EditAdm(worker& worker_to_edit)
{
	SQLWCHAR edit_query[1024];
	swprintf_s(edit_query,
		1024,
		L"UPDATE admin SET adm_name='%s', adm_age=%d, adm_position='%s', adm_address='%s', adm_phone='%s', adm_pid='%s', adm_salary=%f, adm_sex='%d' WHERE adm_id='%S'",
		worker_to_edit.m_name.c_str(),
		worker_to_edit.m_age,
		worker_to_edit.m_position.c_str(),
		worker_to_edit.m_address.c_str(),
		string2wstring(worker_to_edit.m_phone).c_str(),
		string2wstring(worker_to_edit.m_pid).c_str(),
		worker_to_edit.m_salary,
		worker_to_edit.m_sex == L"男",
		worker_to_edit.m_id.c_str());

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)edit_query, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Edit finished!" << std::endl;
		return true;
	}
	return false;
}

bool gtup::SqlReader::AddAdm(worker& worker_to_add)
{
	SQLWCHAR edit_query[1024];
	swprintf_s(edit_query,
		1024,
		L"INSERT INTO admin(adm_id, adm_name, adm_age, adm_position, adm_address, adm_phone, adm_pid, adm_salary, adm_sex)  VALUES ('%S', '%s', %d, '%s', '%s', '%s', '%s', %f, '%d')",
		worker_to_add.m_id.c_str(),
		worker_to_add.m_name.c_str(),
		worker_to_add.m_age,
		worker_to_add.m_position.c_str(),
		worker_to_add.m_address.c_str(),
		string2wstring(worker_to_add.m_phone).c_str(),
		string2wstring(worker_to_add.m_pid).c_str(),
		worker_to_add.m_salary,
		worker_to_add.m_sex == L"男"
	);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)edit_query, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Add finished!" << std::endl;
		return true;
	}
	return false;
}

bool gtup::SqlReader::DeleteAdm(std::wstring id_to_delete)
{
	std::wstring base = L"delete from admin where adm_id=";
	base += id_to_delete;
	const SQLWCHAR* delete_querty = base.c_str();
	// Allocate statement handle
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)delete_querty, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Delete finished!" << std::endl;
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool gtup::SqlReader::EditDep(department& dep_to_edit)
{
	SQLWCHAR edit_query[1024];
	swprintf_s(edit_query,
		1024,
		L"UPDATE department SET dep_name='%s',dep_admin='%S' WHERE dep_id='%S'",
		dep_to_edit.m_name.c_str(),
		dep_to_edit.m_adm.c_str(),
		dep_to_edit.m_id.c_str());

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)edit_query, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Edit finished!" << std::endl;
		return true;
	}
	return false;
}

bool gtup::SqlReader::AddDep(department& dep_to_add)
{
	SQLWCHAR edit_query[1024];
	swprintf_s(edit_query,
		1024,
		L"INSERT INTO department(dep_id, dep_name, dep_admin)  VALUES ('%S', '%s', '%S')",
		dep_to_add.m_id.c_str(),
		dep_to_add.m_name.c_str(),
		dep_to_add.m_adm.c_str()
	);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)edit_query, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Add finished!" << std::endl;
		return true;
	}
	return false;
}

bool gtup::SqlReader::DeleteDep(std::wstring id_to_delete)
{
	std::wstring base = L"delete from department where dep_id=";
	base += id_to_delete;
	const SQLWCHAR* delete_querty = base.c_str();
	// Allocate statement handle
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)delete_querty, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Delete finished!" << std::endl;
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool gtup::SqlReader::EditInc(incentive& inc_to_edit)
{
	SQLWCHAR edit_query[1024];
	swprintf_s(edit_query,
		1024,
		L"UPDATE incentive SET inc_time='%S',inc_meth='%f', emp_id='%S', inc_info='%s' WHERE inc_id='%S'",
		inc_to_edit.m_time.c_str(),
		inc_to_edit.m_method,
		inc_to_edit.m_emp_id.c_str(),
		inc_to_edit.m_info.c_str(),
		inc_to_edit.m_id.c_str()
	);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)edit_query, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Edit finished!" << std::endl;
		return true;
	}
	return false;
}

bool gtup::SqlReader::AddInc(incentive& inc_to_edit)
{
	SQLWCHAR edit_query[1024];
	swprintf_s(edit_query,
		1024,
		L"INSERT INTO incentive(inc_id, emp_id, inc_info, inc_meth, inc_time)  VALUES ('%S', '%S', '%s', '%f', '%S)",
		inc_to_edit.m_id.c_str(),
		inc_to_edit.m_emp_id.c_str(),
		inc_to_edit.m_info.c_str(),
		inc_to_edit.m_method,
		inc_to_edit.m_time.c_str()
	);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)edit_query, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Add finished!" << std::endl;
		return true;
	}
	return false;
}

bool gtup::SqlReader::DeleteInc(std::wstring id_to_delete)
{
	std::wstring base = L"delete from incentive where inc_id=";
	base += id_to_delete;
	const SQLWCHAR* delete_querty = base.c_str();
	// Allocate statement handle
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)delete_querty, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Delete finished!" << std::endl;
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool gtup::SqlReader::EditOvt(overtime& ovt_to_edit)
{
	SQLWCHAR edit_query[1024];
	swprintf_s(edit_query,
		1024,
		L"UPDATE overtime SET ovt_time='%f',emp_id='%S', ovt_date='%S' WHERE ovt_id='%S'",
		ovt_to_edit.m_time,
		ovt_to_edit.m_emp_id.c_str(),
		ovt_to_edit.m_date.c_str(),
		ovt_to_edit.m_id.c_str()
	);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)edit_query, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Edit finished!" << std::endl;
		return true;
	}
	return false;
}

bool gtup::SqlReader::AddOvt(overtime& ovt_to_edit)
{
	SQLWCHAR edit_query[1024];
	swprintf_s(edit_query,
		1024,
		L"INSERT INTO overtime(ovt_id, ovt_time, emp_id, ovt_date)  VALUES ('%S', '%f', '%S', '%S')",
		ovt_to_edit.m_id.c_str(),
		ovt_to_edit.m_time,
		ovt_to_edit.m_emp_id.c_str(),
		ovt_to_edit.m_date.c_str()
	);

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)edit_query, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Add finished!" << std::endl;
		return true;
	}
	return false;
}

bool gtup::SqlReader::DeleteOvt(std::wstring id_to_delete)
{
	std::wstring base = L"delete from overtime where inc_id=";
	base += id_to_delete;
	const SQLWCHAR* delete_querty = base.c_str();
	// Allocate statement handle
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	// Execute the query
	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)delete_querty, SQL_NTS);

	if (SQL_SUCCEEDED(m_retcode)) {
		std::cout << "Delete finished!" << std::endl;
		return true;
	}
	else {
		return false;
	}
	return false;
}
