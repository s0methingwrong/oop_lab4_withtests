#include "package_descriptor.h"

void package_descriptor::show_info()
{
	cout << "����� �����������: " << m_address_sender << endl;
	cout << "����� ����������: " << m_address_recipient << endl;
	cout << "��������� ���������: ";
	m_descriptor_message->show_info();
}
