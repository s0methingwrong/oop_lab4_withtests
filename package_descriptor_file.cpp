#include "package_descriptor_file.h"

void package_descriptor_file::show_info()
{
	package_descriptor::show_info();
	string type_c = m_code == type_code::ACII ? "ASCII" : "BIN";
	string type_i = m_info_type == info_type::control ? "�����������" : "������";
	cout << "��� ����: " << type_c << endl;
	cout << "��� ����������: " << type_i << endl;

}

package_descriptor_hypertext* package_descriptor_file::convert(int count_links, descriptor_link** links)
{
	return new package_descriptor_hypertext(get_address_sender(), get_address_recipient(), get_descriptor_message(), 
		get_type_code(), get_info_type(), count_links, links);
}
