#include "descriptor_link.h"

void descriptor_link::show_info()
{
	string type_p = m_protokol == type_protokol::ftp ? "FTP" : "Http";
	cout << "��� ���������: " << type_p << ", ��� �������: " << m_server_name << endl;
}
