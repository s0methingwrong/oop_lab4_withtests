#include <iostream>
#include "server.h"
#include <string>
#include "package_descriptor_mail.h"

descriptor_message* create_descriptor_message() {
	cout << "�������� ��������� ���������: ";
	unsigned int len_message;
	cout << "������� ����� ���������: ";
	cin >> len_message;
	
	cin.ignore();

	char* message = new char[len_message + 1];
	cout << "������� ���������: ";
	cin.getline(message, len_message);

	descriptor_message* d_mes = new descriptor_message(len_message, message);
	return d_mes;
}

void fill_descriptor_links(descriptor_link** descriptor_links, int n) {
	for (int i = 0; i < n; i++)
	{
		cout << "�������� ��� ��������� 1.ftp, 2.http ";
		int pr;
		cin >> pr;
		cin.ignore();

		type_protokol protok = (type_protokol)(pr - 1);
		string server_name;
		cout << "��� �������: ";
		getline(cin, server_name);

		descriptor_links[i] = new descriptor_link(protok, server_name);
	}
}

package_descriptor* create_package_descriptor() {
	cout << "1.�����" << endl;
	cout << "2.����" << endl;
	cout << "3.����������" << endl;

	int choice;
	cin >> choice;
	cin.ignore();

	string address_sender, address_recipient;

	cout << "������� ����� �����������: ";
	getline(cin, address_sender);

	cout << "������� ����� ����������: ";
	getline(cin, address_recipient);

	descriptor_message* d_mes = create_descriptor_message();

	if (choice == 1) {
		cout << "������� ��� ������������: ";
		string user_name;
		cin >> user_name;

		package_descriptor_mail* p = new package_descriptor_mail(address_sender, address_recipient, d_mes, user_name);
		return p;
	}
	else if (choice == 2) {
		cout << "�������� ��� ���� 1.ACII, 2.BIN" << endl;
		int type_c;
		cin >> type_c;

		type_code t = (type_code)(type_c - 1);

		cout << "�������� ��� ���������� 1.�����������, 2.������" << endl;
		int type_i;
		cin >> type_i;

		info_type ti = (info_type)(type_i - 1);
		package_descriptor_file* p = new package_descriptor_file(address_sender, address_recipient, d_mes, t, ti);
		return p;
	}
	else {
		int count_url;
		cout << "������� ���-�� ������: ";
		cin >> count_url;

		descriptor_link** links = new descriptor_link*[count_url];
		fill_descriptor_links(links, count_url);

		cout << "�������� ��� ���� 1.ACII, 2.BIN" << endl;
		int type_c;
		cin >> type_c;

		type_code t = (type_code)(type_c - 1);

		cout << "�������� ��� ���������� 1.�����������, 2.������" << endl;
		int type_i;
		cin >> type_i;

		info_type ti = (info_type)(type_i - 1);

		package_descriptor_hypertext* p = new package_descriptor_hypertext(address_sender, address_recipient, d_mes, t, ti, count_url, links);
		return p;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	string name;
	cout << "������� ��� �������: ";
	cin >> name;

	string address;
	cout << "������� ����� �������: ";
	cin >> address;

	auto ser = make_unique<server>(name, address);
	int action;

	do
	{
		cout << "1.�������� �����" << endl;
		cout << "2.����� ������" << endl;
		cout << "3.�������� ������� �������" << endl;
		cout << "4.������� �����" << endl;
		cout << "5.�������� ���������� ��� ���� ������������ �������" << endl;
		cout << "0.�����" << endl;

		cin >> action;
		cin.ignore();

		if (action == 1) {
			package_descriptor* p = create_package_descriptor();
			ser->add(p);
		}
		else if (action == 2) {
			string address;
			cout << "������� ����� ����������: ";
			getline(cin, address);

			cout << "�������� ��� ������ 1.mail, 2.file, 3.hypertext" << endl;
			int t;
			cin >> t;
			type_package type = (type_package)(t - 1);

			package_descriptor* package = ser->find_package(address, type);
			if (package != nullptr) {
				package->show_info();
			}
			else {
				cout << "����� �� ������" << endl;
			}
		}
		else if (action == 3) {
			ser->show();
		}
		else if (action == 4) {
			string address;
			cout << "������� ����� ����������: ";
			getline(cin, address);

			cout << "�������� ��� ������ 1.mail, 2.file, 3.hypertext" << endl;
			int t;
			cin >> t;
			type_package type = (type_package)(t - 1);

			if (ser->remove_package(address, type)) {
				cout << "�������� �������" << endl;
			}
			else {
				cout << "����� �� ������" << endl;
			}
		}
		else if (action == 5) {
			ser->show_senders();
		}
	} 
	while (action != 0);

}
