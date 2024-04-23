#include "stdafx.h"
#include <iostream>
#include <iosfwd>
#include <afxdlgs.h>
#include <commdlg.h>
#include <fstream>
#include <string>
#include "MyStack.h"
using namespace std;
class TextEditor
{
public:
	TextEditor(MyString s) {
		this->strcurrent = s;
	}
	TextEditor() {
		previous = initStack();
		now = initStack();
	}
	void ShowMainMune();//���˵�
	void ShowEditorMune();//�༭�˵�
	void Run();//���к���
	void Exit();//�˳�
	void Open();//���ļ�
	void Save(char* path);//����ļ�
	void FileSave();//����
	void Clear();//����
	void Review();//���������ǰ���ַ���
	void OutputCharCount();//ͳ���ַ�
	void Input(string a, string b);//�ı��༭�����뺯��
	void Search();//�ı�����
	void Replace();//�ı��滻
	void Delete();//�ı�ɾ��
	void Insert();//�ı�����
	void  Copy(char*& temp);//�ı�����
	void  Cut(char*& temp);//�ı�����
	void Paste(char* temp);//�ı�ճ��
private:
	MyString strcurrent;//��ǰ���ַ���
	linkStack* previous;//�޸�ǰ��
	linkStack* now; //�޸ĺ��
	MyString filepath;//�ļ�����λ��
};
//�������λ��->����ԭ�ȵ��ַ���->����->��ʾ->����������ַ���
void TextEditor::Paste(char* temp) {
	int index;
	if (strlen(temp) != 0)
	{
		cout << "ճ�����ݣ�" << temp << endl;
		cout << "��������Ҫճ����λ�ã��ò��ҹ����ҵ�ճ��λ�ã�" << endl;
		cin >> index;
		previous = push(previous, strcurrent.data());
		strcurrent.insert(temp, index);
		Review();
		now = push(now, strcurrent.data());
	}
	else
	{
		cout << "��ǰû�п�ճ������" << endl;
	}
}
//���뿪ʼλ�úͽ�ȡ����->��ȡ�ַ���->��ʾ��ȡ����->�����ȡ����
void  TextEditor::Copy(char*& temp) {
	int start = 0;//����ճ���Ŀ�ʼλ��
	int length = 0;//����ճ���ĳ���
	MyString copy;//����,ճ��������
	cout << "��Ҫ���ĸ�λ�ÿ�ʼ����?�����Ƕ���?(Ӣ��ÿ����ĸ����Ϊ1������ÿ���ֳ���Ϊ2)" << endl;
	cin >> start >> length;
	length = (length / 2);
	length = length * 2;
	copy = strcurrent.substring(start + 1, length);
	if (copy.strlength() != 0)
	{
		cout << "���Ƴɹ�" << endl;
		cout << "����Ϊ��" << copy.data() << endl;
		cout << "����Ϊ��" << copy.strlength() << endl;
		temp = new char[strlen(copy.data())];
		for (int i = 0; i < strlen(copy.data()); i++)
		{
			temp[i] = copy.data()[i];
		}
		temp[strlen(copy.data())] = '\0';
	}
	else {
		cout << "����ʧ��" << endl;
		temp = "";
	}
}
//���뿪ʼ����λ�úͼ��г���->��ȡ�ַ���->����ԭ�ȵ��ַ���->�滻�ַ���->�����滻����ַ���->��ʾ�滻�������->��ʾ��ȡ����->�����ȡ����
void  TextEditor::Cut(char*& temp) {
	int start = 0;//����ճ���Ŀ�ʼλ��
	int length = 0;//����ճ���ĳ���
	MyString copy;//����,ճ��������
	cout << "��Ҫ���ĸ�λ�ÿ�ʼ����?�����Ƕ���?(Ӣ��ÿ����ĸ����Ϊ1������ÿ���ֳ���Ϊ2)" << endl;
	cin >> start >> length;
	length = (length / 2);
	length = length * 2;
	copy = strcurrent.substring(start + 1, length);
	MyString s = strcurrent.data();
	MyString d = strcurrent.data();
	if (copy.strlength() != 0)
	{
		previous = push(previous, strcurrent.data());
		strcurrent.replace(d, s, copy.data(), "", false);
		strcurrent.setchar(d.data());
		Review();
		cout << "��������Ϊ��" << copy.data() << endl;
		temp = new char[strlen(copy.data())];
		for (int i = 0; i < strlen(copy.data()); i++)
		{
			temp[i] = copy.data()[i];
		}
		temp[strlen(copy.data())] = '\0';
		now = push(now, strcurrent.data());
	}
	else {
		cout << "����ʧ��" << endl;
		temp = "";
	}
}
//�������λ��->����ԭ�ȵ��ַ���->����->��ʾ->����������ַ���
void TextEditor::Insert() {
	int index = 0;//����λ��
	previous = push(previous, strcurrent.data());
	char* buffer = new char[strcurrent.strlength() + 1];
	cout << "������Ҫ���������" << endl;
	cin >> buffer;
	cout << "���������λ��" << endl;
	cin >> index;
	strcurrent.insert(buffer, index - 1);
	Clear();
	Review();
	now = push(now, strcurrent.data());
	delete(buffer);
}
//����ԭ�����ַ���->�滻->����
void TextEditor::Delete() {
	int deleteflag, replaceflag;
	previous = push(previous, strcurrent.data());
	MyString s = strcurrent.data();//���滻��ķ��ص�����
	MyString d = strcurrent.data();//���滻������
	char* buffer = new char[strcurrent.strlength() + 1];
	cout << "������Ҫɾ��������" << endl;
	cin >> buffer;
	cout << "�Ƿ�ȫ��ɾ��������� 1.�� 0.��" << endl;
	cin >> replaceflag;
	strcurrent.replace(d, s, buffer, "", replaceflag);
	strcurrent.setchar(d.data());
	Clear();
	Review();
	now = push(now, strcurrent.data());
	delete(buffer);
}
//ͬ�ϣ�ɾ�����ǰ��滻����дΪ"",�滻�����û�����
void TextEditor::Replace() {
	previous = push(previous, strcurrent.data());
	MyString s = strcurrent.data();
	MyString d = strcurrent.data();
	int replaceflag;
	char* buffer = new char[strcurrent.strlength() + 1];
	char* p = new char[strcurrent.strlength() + 1];
	cout << "������Ҫ�滻������" << endl;
	cin >> buffer;
	cout << "������������" << endl;
	cin >> p;
	cout << "�Ƿ�ȫ���滻 1.�� 0.��" << endl;
	cin >> replaceflag;
	strcurrent.replace(d, s, buffer, p, replaceflag);
	strcurrent.setchar(d.data());
	Clear();
	Review();
	now = push(now, strcurrent.data());
	delete(p);
	delete(buffer);
}
//temp��ԭ�ĵĸ��ƣ���Ϊ���ǵ�Ҫ���ϵĽ�ȡ�ַ�����ȫ�Ĳ��ң������в���ԭ���޸ġ�
void TextEditor::Search() {
	int search;
	int searchlength = 0;
	MyString temp = strcurrent;
	char* buffer = new char[strcurrent.strlength() + 1];
	cout << "������Ҫ���ҵ�����" << endl;
	cin >> buffer;
	buffer[strcurrent.strlength()] = '\0';
	cout << "�Ƿ�ȫ�Ĳ��� 1.�� 0.��" << endl;
	cin >> search;
	if (search == 1) {
		while (temp.indexof(buffer)) {
			int start = temp.indexof(buffer);
			searchlength = searchlength + start;
			cout << "����λ���ǣ�" << searchlength << endl;
			temp = temp.substring(start, temp.strlength() - start);

		}
	}
	else {
		cout << "����λ���ǣ�" << strcurrent.indexof(buffer) << endl;
	}

	delete(buffer);
}
void TextEditor::FileSave() {
	char* buffer = new char[100];//����·��
	if (strcurrent.strlength() != 0)
	{
		cout << "�����뱣��·��" << endl;
		cin >> buffer;
		//filepath.setchar(buffer);
		Save(buffer);
	}
	else {
		cout << "��ǰû���ı�" << endl;
	}
}
void TextEditor::Input(string a, string b) {
	char* buffer;//Ҫ���ң��滻��ɾ���Ļ���
	cout << "�������ı�,������'#'����" << endl;
	a.clear();
	while (1) {
		getline(cin, b);
		if (b[0] != '#') {

			a = a + b + '\n';

		}
		else {
			break;
		}
	}
	buffer = new char[a.length() + 1];
	for (int i = 0; i < a.length(); i++) {
		buffer[i] = a.data()[i];
	}
	buffer[a.length() + 1] = '\0';
	strcurrent = buffer;
}
void TextEditor::OutputCharCount() {
	cout << "��д��ĸ����" << strcurrent.CharCount().bchar << endl;
	cout << "Сд��ĸ����" << strcurrent.CharCount().schar << endl;
	cout << "�ո�����" << strcurrent.CharCount().space << endl;
	cout << "�ַ�������" << strcurrent.CharCount().length << endl;
	cout << "����������" << strcurrent.CharCount().number << endl;
}
void TextEditor::Clear() {
	system("cls");
}
void TextEditor::Review() {
	cout << "*----------------------�༭����-----------------------*" << endl;
	cout << strcurrent.data() << endl;
	cout << "*----------------------����ѡ��-----------------------*" << endl;
	ShowEditorMune();
	cout << "*--------------------������������-------------------*" << endl;
}
void TextEditor::ShowMainMune() {
	cout << "*----------------------˳���ı��༭��-----------------------*" << endl;
	cout << "*------------------------1.���ļ�-------------------------*" << endl;
	cout << "*------------------------2.�½��ļ�-------------------------*" << endl;
	cout << "*------------------------3.�����ļ�-------------------------*" << endl;
	cout << "*------------------------4.�༭-----------------------------*" << endl;
	cout << "*------------------------5.�˳�-----------------------------*" << endl;
	cout << "*------------------------������������---------------------*" << endl;
}
void TextEditor::ShowEditorMune() {
	cout << "6.����" << endl;
	cout << "7.�滻" << endl;
	cout << "8.ɾ��" << endl;
	cout << "9.����" << endl;
	cout << "10.����" << endl;
	cout << "11.����" << endl;
	cout << "12.�ַ�ͳ��" << endl;
	cout << "13.����" << endl;
	cout << "14.����" << endl;
	cout << "15.ճ��" << endl;
	cout << "16.������һ��" << endl;
}
void TextEditor::Exit() {
	cout << "��лʹ��" << endl;

	exit(-1);
}
void TextEditor::Run() {
	ShowMainMune();
	int command;//ָ��
	//MyString temp;//���Ҳ����ǵ���ʱ���壬��ֱ���ڵ�ǰ�ַ��������������
	string a = "";//�û������ȫ���ַ���
	string b = "";//�û������ÿһ���ַ���
	char* temp;
	while (1)
	{
		cin >> command;
		cin.ignore(2, '\n');
		switch (toupper(command))
		{
		case 1:
			Open();
			Clear();
			Review();
			break;
		case 2:
			Input(a, b);
			Clear();
			Review();
			break;
		case 3:
			FileSave();
			break;
		case 4:
			ShowEditorMune();

			break;
		case 5:
			Exit();
		case 6:
			Search();
			cout << "*------------------------������������---------------------*" << endl;
			break;
		case 7:
			Replace();
			break;
		case 8:
			Delete();
			cout << "*------------------------������������---------------------*" << endl;
			break;
		case 9:
			Insert();

			break;
		case 10:
			if (previous != NULL)
			{
				now = push(now, strcurrent.data());
				strcurrent = previous->data;
				Clear();
				Review();
				previous = pop(previous);

			}
			else {
				cout << "�㵱ǰû�����κβ���" << endl;
			}

			break;
		case 11:
			if (now != NULL)
			{
				previous = push(previous, strcurrent.data());
				strcurrent = now->data;
				Clear();
				Review();
				now = pop(now);

			}
			else {
				cout << "�㵱ǰû�����κβ���" << endl;
			}

			break;
		case 12:
			Clear();
			Review();
			OutputCharCount();

			break;
		case 13:

			Copy(temp);
			cout << "*------------------------������������---------------------*" << endl;
			break;
		case 14:

			Cut(temp);
			cout << "*------------------------������������---------------------*" << endl;
			break;
		case 15:
			Paste(temp);
			cout << "*------------------------������������---------------------*" << endl;
			break;
		case 16:
			ShowMainMune();
			break;
		default:
			cout << "\n***Illegal command***\n";
			ShowMainMune();

		}

	}
}
void TextEditor::Save(char* buffer) {
	int i;
	ofstream outfile(buffer);
	if (!outfile) {
		cerr << "������󣬲�����ָ���ļ�" << endl;
		exit(1);
	}
	for (i = 0; i < strcurrent.strlength() - 1; i++)
	{
		outfile << strcurrent.data()[i];
	}
	cout << "����ɹ�" << endl;
	outfile.close();
}
void TextEditor::Open() {
	OPENFILENAME ofn;
	TCHAR szPath[MAX_PATH];
	ZeroMemory(szPath, sizeof(szPath));
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	TCHAR szBuffer[1024] = { 0 };
	ofn.lpstrFilter = TEXT("Ӧ�ó���\0*.*\0*.*\0\0");
	ofn.lpstrFile = szBuffer;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_DONTADDTORECENT | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST;
	if (GetOpenFileName(&ofn) == TRUE) {

		int iLength = WideCharToMultiByte(CP_ACP, 0, szBuffer, -1, NULL, 0, NULL, NULL); ;//CString,TCHAR������һ���ַ�����˲�����ͨ���㳤�� 
		char* _char = new char[iLength + 1];
		WideCharToMultiByte(CP_ACP, 0, szBuffer, -1, _char, iLength, NULL, NULL);
		filepath = _char;
		ifstream f(filepath.data(), ios::in | ios::binary);
		int length;
		f.seekg(0, ios::end);
		length = f.tellg();
		f.seekg(0, ios::beg);
		char* buffer = new char[length + 1];
		f.read(buffer, length);
		buffer[length] = '\0';
		this->strcurrent.setchar(buffer);
		delete(buffer);


	}
}