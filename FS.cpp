//
// Created by zfy on 2019/6/26.
//
#include "FS.h"
#include "System.h"
#include<Map>
#include<fstream>
#include<iostream>
using namespace std;

void create_user(string*cmd,int length){
    if(length == 2){
        int signal;
        signal=sys_createuser(cmd[1]);
        if(signal==1)
            cout<<"�û�"+cmd[1]+"�����ɹ���\n";
        else  cout<<"�û�"+cmd[1]+"����ʧ�ܣ�\n";
    } else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}

void su(string*cmd,int length){
    if(length == 2){
        int signal;
        if(cmd[1]=="root")
            signal=sys_suroot();
        else signal=sys_su(cmd[1]);
        if(signal==1)
            cout<<"�û��л��ɹ���\n";
        else  cout<<"�û��л�ʧ�ܣ�\n";
    } else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}


/**************************************************/
//�����ں�ʵ�ֵ�Ŀ¼����
string get_current() {
    string cur = "";
    int j = 0;
    cur += current_path[0];
    for (int i = 1; i < current_path.length(); i++) {
        if (current_path[i] == '/'&&cur[j] == '/') {
            continue;
        }
        else {
            cur += current_path[i];
            j++;
        }
    }
    return cur;
}

//�鿴Ŀ¼���ݣ�
void dir(string*cmd,int length) {
    StringList* display;
    if (length == 1) {
        display=sys_dir("");
        while (display != NULL)
        {
            cout << display->content;
            display = display->next;
        }
    }
    else if (length == 2) {
        display = sys_dir(cmd[1]);
        while (display != NULL)
        {
            cout << display->content;
            display = display->next;
        }
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}

//����Ŀ¼��
void mkdir(string*cmd, int length) {
    if (length == 2) {
        int signal;         //��¼����Ŀ¼����������û��ṩ��Ϣ��
        signal = sys_mkdir(cmd[1]);

        if (signal == 1)
        {
            cout << "����Ŀ¼�ɹ���" << endl;
        }
        else if (signal == -1)
        {
            cout << "·������" << endl;
        }
        else if(signal==0)
        {
            cout << "�û��޸�����Ȩ�ޣ�" << endl;
        }
        else
        {
            cout << "Ŀ¼�Ѿ����ڣ�" << endl;
        }
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}

//ɾ��Ŀ¼;
void rmdir(string*cmd, int length) {
    if (length == 2) {

        int signal;         //��¼����Ŀ¼����������û��ṩ��Ϣ��
        signal = sys_rmdir(cmd[1]);

        if (signal == 1)
        {
            cout << "ɾ��Ŀ¼�ɹ���" << endl;
        }
        else if (signal == -1)
        {
            cout << "·������" << endl;
        }
        else if(signal==0)
        {
            cout << "�û��޸�����Ȩ�ޣ�" << endl;
        }
        else
        {
            cout << "Ŀ¼�����ڣ�" << endl;
        }
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}

//�����ļ���
void create_file(string*cmd, int length) {

    if (length == 2) {

        int signal;         //��¼����Ŀ¼����������û��ṩ��Ϣ��
        signal = sys_create_file(cmd[1]);

        if (signal == 1)
        {
            cout << "�����ļ��ɹ���" << endl;
        }
        else if (signal == -1)
        {
            cout << "·������" << endl;
        }
        else if(signal==0)
        {
            cout << "�û��޸�����Ȩ�ޣ�" << endl;
        }
        else
        {
            cout << "�ļ��Ѿ����ڣ�" << endl;
        }
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}

//ɾ���ļ���
void delete_file(string*cmd, int length) {
    if (length == 2) {

        int signal;         //��¼����Ŀ¼����������û��ṩ��Ϣ��
        signal = sys_delete_file(cmd[1]);

        if (signal == 1)
        {
            cout << "ɾ���ļ��ɹ���" << endl;
        }
        else if (signal == -1)
        {
            cout << "·������" << endl;
        }
        else if(signal==0)
        {
            cout << "�û��޸�����Ȩ�ޣ�" << endl;
        }
        else
        {
            cout << "�ļ������ڣ�" << endl;
        }
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}

//�������ļ���
void rename(string*cmd, int length) {
    if (length == 4) {
        int type = 0;
        if (cmd[2] == "1")
            type = 1;
        int signal;         //��¼����Ŀ¼����������û��ṩ��Ϣ��
        signal = sys_rename(cmd[1], type, cmd[3]);

        if (signal == 1)
        {
            cout << "�������ɹ���" << endl;
        }
        else if (signal == -1)
        {
            cout << "����ͬ��ͬ���ͣ�" << endl;
        }
        else if (signal == -2)
        {
            cout << "·������" <<endl;
        }
        else if(signal==0)
        {
            cout << "�û��޸�����Ȩ�ޣ�" << endl;
        }
        else
        {
            cout << "���������ļ������ڣ�" << endl;
        }
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }

}

//���ļ�д���ݣ�
void write_file(string*cmd, int length) {
    if (length == 2) {
        string path_name = cmd[1];
        string name = "";
        FCB* parent = NULL;
        int B,F;
        FCB* file = sys_returnFCB(path_name, name, 0, parent,B,F);
        if (file != NULL)
        {
            //��ʱ�ļ����ڣ�
            cout << "����������:";
            string content;
            //getchar();
            getline(cin, content);
            int signal;
            signal = sys_overwrite_file(file, content);
            if (signal ==1)
            {
                cout << "д�ļ��ɹ�" << endl;
            }
            else if(signal==0)
            {
                cout << "�û��޸�����Ȩ�ޣ�" << endl;
            }
            else
            {
                cout << "ϵͳ��Դ���㣬�޷�д������" << endl;
            }
        }
        else
        {
            //�ļ������ڣ�
            cout << "�ļ������ڣ��޷�д������" << endl;
        }
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}

//��ȡ�ļ����ݣ�
void read_file(string*cmd, int length) {
    if (length == 2) {
        string path_name = cmd[1];
        string name = "";
        FCB* parent = NULL;
        int B,F;
        FCB* file = sys_returnFCB(path_name, name, 0, parent,B,F);
        if (file != NULL) {
            string content;
            bool flag;
            content = sys_read_file(file,flag);
            if(flag) {
                cout << "��ȡ�ļ����ݳɹ���" << endl;
                cout << "�ļ�����Ϊ��" << content << endl;
            }else cout << "�û��޸�����Ȩ�ޣ�" << endl;
        }

        else
        {
            cout << "�ļ������ڣ�" << endl;
        }
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}

//������Ŀ¼��
void cd(string*cmd, int length) {
    if (length == 2) {
        string path=cmd[1];
        string name = "";
        if (path == "..") {
            cdback();
            return;
        }
        int signal;
        signal = sys_cd(path, name);

        if (signal == 1)
        {
            cout <<"11111" << endl;
        }
        else if(signal==0)
        {
            cout << "�û��޸�����Ȩ�ޣ�" << endl;
        }
        else
        {
            cout <<signal << endl;
        }
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}

//������һ��Ŀ¼��
void cdback() {
    sys_cdback();
}

//���У�
void cut(string*cmd, int length) {
    if (length == 4) {
        string oldPath;
        int type=0;
        string newPath;
        oldPath = cmd[1];
        newPath = cmd[3];
        if (cmd[2] == "1")
            type = 1;
        int signal;
        signal = sys_cut(oldPath, type, newPath);

        if (signal == 1)
        {
            cout << "����ճ���ɹ���" << endl;
        }
        else if (signal == -1)
        {
            cout << "����ͬ��ͬ���ͣ����������ճ��" << endl;
        }
        else if (signal == -2)
        {
            cout << "·������" << endl;
        }
        else if (signal == -3)
        {
            cout << "�����ڣ��޷�����" << endl;
        }
        else if (signal == -4)
        {
            cout << "Ŀ��Ŀ¼������" << endl;
        }
        else if(signal==0)
        {
            cout << "�û��޸�����Ȩ�ޣ�" << endl;
        }
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}

//���ƣ�
void copy(string*cmd, int length) {
    if (length == 4) {
        string oldPath;
        int type=0;
        string newPath;
        oldPath = cmd[1];
        newPath = cmd[3];
        if (cmd[2] == "1")
            type = 1;

        int signal;
        signal = sys_copy(oldPath, type, newPath);

        if (signal == 1)
        {
            cout << "����ճ���ɹ���" << endl;
        }
        else if (signal == -1)
        {
            cout << "ϵͳ��Դ�������޷����и���" << endl;
        }
        else if (signal == -2)
        {
            cout << "Ŀ��Ŀ¼�´���ͬ��ͬ���ͣ�������ճ��" << endl;
        }
        else if (signal == -3)
        {
            cout << "·������" << endl;
        }
        else if (signal == -4)
        {
            cout << "���ƶ��󲻴���" << endl;
        }
        else if (signal == -5)
        {
            cout << "Ŀ��Ŀ¼������" << endl;
        }
        else if(signal==0)
        {
            cout << "�û��޸�����Ȩ�ޣ�" << endl;
        }
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}
void share(string*cmd, int length){
    if(length==4){
        int type =0;
        if(cmd[2]=="1") type=1;
        int signal;
        signal=sys_share(cmd[1],type,cmd[3]);
        if (signal == 1)
        {
            cout << "����ɹ���" << endl;
        }
        else if (signal == -2)
        {
            cout << "������ļ���·��������" << endl;
        }
        else if (signal == -3)
        {
            cout << "������󲻴���" << endl;
        }
        else if (signal == -4)
        {
            cout << "����·��������" << endl;
        }
        else if(signal==0)
        {
            cout << "���ļ����޹���Ȩ�ޣ�" << endl;
        }
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }

}
/******************************************************/
//�������(�ڴ����)��ʵ�ָֻ�ϵͳ�ķ���

//�����д����
void writeDisk(string*cmd, int length) {
    string diskpath;
    int result = 0;
    if (length == 1) {
        result = sys_write_disk(diskpath);
    }
    else if (length == 2) {
        result = sys_write_disk(cmd[1]);
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
        return;
    }
    if(result == -1){
        cout<<"���������ʧ�ܣ�����"<<endl;
    } else if(result == 1){
        cout << "д����̣��ɹ���" << endl;
    }
}

//��ȡ��������
void readDisk(string*cmd, int length) {
    ifstream read_disk;
    string diskpath;
    int result = 0;
    if (length == 1) {
        result = sys_read_disk(diskpath);
    }
    else if (length == 2) {
        result = sys_read_disk(cmd[1]);
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
        return;
    }
    if (result == 1){
        cout<<"�ָ��ɹ�������"<<endl;
    } else if (result == -1){
        cout<<"��ȡ������̳���"<<endl;
    }
}

//�鿴����״̬��
void viewDisk(string*cmd, int length) {
    if (length == 1) {
        //��ʱλʾͼ�������������йأ�
        //cout << "���������������" << _bitMapCount << "MB;" << endl;
        cout << "���������������" <<  "8MB;" << endl;

        cout << "���������ϵͳռ�õ�������" << _systemUsedBlock << "KB;" << endl;

        cout << "������̻�ʣ���������" << _emptyBLOCK_Count << "KB;" << endl;
    }
    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }

}

//��ѯ����ʹ�÷�ʽ��
void help_command(string*cmd, int length) {
    //���û�����ķ���������ṩָ�ϣ�
    if (length == 1) {
        cout << "��ʹ��help command��ѯĳ��ָ����÷�" << endl;
    }
    else if(length==2){
        map <string, int> help_menu;
        help_menu["dir"] = 1, help_menu["mkdir"] = 2, help_menu["rmdir"] = 3;
        help_menu["create"] = 4, help_menu["delete"] = 5; help_menu["rename"] = 6;
        help_menu["write"] = 7, help_menu["read"] = 8;
        help_menu["cd"] = 9, help_menu["cd.."] = 10;
        help_menu["cut"] = 11, help_menu["copy"] = 12;
        help_menu["writeDisk"] = 13, help_menu["readDisk"] = 14, help_menu["viewDisk"] = 15;


        //cout << "��������Ҫ��ѯ������(�磺help dir);" << endl;

        string help_command = cmd[1];
        int choice;

        //�û�������Ҫ���������
        //cin >> help_command;
        choice = help_menu[help_command];
        switch (choice)
        {
            case 1://help dir
                cout << "Eg:dir" << endl;
                cout << "ֻ����dir,�������ǲ鿴��ǰĿ¼�������𣿡�" << endl;
                cout << "Y,��ʾ��ǰ��Ŀ¼��N��������Ҫ�鿴��Ŀ¼·��(֧�־���·��(/)�����·��)��" << endl;
                cout << "Eg:dir /test" << endl;
                cout << "�鿴���Ǹ�Ŀ¼(/)�µ�testĿ¼�е����ݡ�" << endl;
                cout << "Eg:dir test" << endl;
                cout << "�鿴���ǵ�ǰĿ¼�µ�testĿ¼�е����ݡ�" << endl;
                break;

            case 2://help mkdir
                cout << "֧�־���·��(/)�����·����" << endl;
                cout << "Eg:mkdir /test" << endl;
                cout << "�ڸ�Ŀ¼(/)�£�����testĿ¼��" << endl;
                cout << "Eg:mkdir test" << endl;
                cout << "�ڵ�ǰĿ¼�£�����testĿ¼��" << endl;
                break;

            case 3://help rmdir
                cout << "֧�־���·��(/)�����·����" << endl;
                cout << "Eg:rmdir /test" << endl;
                cout << "�ڸ�Ŀ¼(/)�£�ɾ��testĿ¼��" << endl;
                cout << "Eg:mkdir test" << endl;
                cout << "�ڵ�ǰĿ¼�£�ɾ��testĿ¼��" << endl;
                break;

            case 4://help create
                cout << "֧�־���·��(/)�����·����" << endl;
                cout << "Eg:create /test" << endl;
                cout << "�ڸ�Ŀ¼(/)�£�����test�ļ���" << endl;
                cout << "Eg:create test" << endl;
                cout << "�ڵ�ǰĿ¼�£�����test�ļ���" << endl;
                break;

            case 5://help delete
                cout << "֧�־���·��(/)�����·����" << endl;
                cout << "Eg:delete /test" << endl;
                cout << "�ڸ�Ŀ¼(/)�£�ɾ��test�ļ���" << endl;
                cout << "Eg:delete test" << endl;
                cout << "�ڵ�ǰĿ¼�£�ɾ��test�ļ���" << endl;
                break;

            case 6://help rename
                cout << "֧�־���·��(/)�����·����" << endl;
                cout << "ָ���ļ����ͣ�1��ʾĿ¼��0��ʾ�ļ���" << endl;
                cout << "Eg:rename /test 1 test1" << endl;
                cout << "�ڸ�Ŀ¼(/)�£���Ŀ¼test������Ϊtest1" << endl;
                cout << "Eg:rename test 0 test1" << endl;
                cout << "�ڵ�ǰĿ¼�£����ļ�test������Ϊtest1" << endl;
                break;

            case 7://help write
                cout << "֧�־���·��(/)�����·����" << endl;
                cout << "Eg:write /test" << endl;
                cout << "�ڸ�Ŀ¼(/)��,���ļ�testд���ݣ����ļ����ڣ������������ݡ�" << endl;
                cout << "Eg:write test" << endl;
                cout << "�ڵ�ǰĿ¼��,���ļ�testд���ݣ����ļ����ڣ������������ݡ�" << endl;
                break;

            case 8://help read
                cout << "֧�־���·��(/)�����·����" << endl;
                cout << "Eg:read /test" << endl;
                cout << "�ڸ�Ŀ¼(/)��,��ȡ�ļ�test�����ݣ����ļ����ڣ�������ʾ���ݡ�" << endl;
                cout << "Eg:read test" << endl;
                cout << "�ڵ�ǰĿ¼��,��ȡ�ļ�test�����ݣ����ļ����ڣ�������ʾ���ݡ�" << endl;
                break;

            case 9://helo cd
                cout << "֧�־���·��(/)�����·����" << endl;
                cout << "Eg:cd /test" << endl;
                cout << "�����Ŀ¼(/)�µ�testĿ¼��" << endl;
                cout << "Eg:cd test" << endl;
                cout << "���뵱ǰĿ¼��testĿ¼��" << endl;
                break;

            case 10://help cd..
                cout << "Eg:cd.." << endl;
                cout << "������һ��Ŀ¼��" << endl;
                break;

            case 11://help cut
                cout << "֧�־���·��(/)�����·����" << endl;
                cout << "ָ���ļ����ͣ�1��ʾĿ¼��0��ʾ�ļ���" << endl;
                cout << "Eg:cut /test 1 /test1" << endl;
                cout << "�Ѹ�Ŀ¼(/)�µ�Ŀ¼test���е���Ŀ¼�µ�Ŀ¼test1��" << endl;
                cout << "Eg:cut test 0 /test1" << endl;
                cout << "�ѵ�ǰĿ¼�µ��ļ�test���е���Ŀ¼�µ�Ŀ¼test1��" << endl;
                break;

            case 12://help copy
                cout << "֧�־���·��(/)�����·����" << endl;
                cout << "ָ���ļ����ͣ�1��ʾĿ¼��0��ʾ�ļ���" << endl;
                cout << "Eg:copy /test 1 /test1" << endl;
                cout << "�Ѹ�Ŀ¼(/)�µ�Ŀ¼test���Ƶ���Ŀ¼�µ�Ŀ¼test1��" << endl;
                cout << "Eg:cut test 0 /test1" << endl;
                cout << "�ѵ�ǰĿ¼�µ��ļ�test���Ƶ���Ŀ¼�µ�Ŀ¼test1��" << endl;
                break;

            case 13://help writeDisk
                cout << "Eg: writeDisk" << endl;
                cout << "���ڴ��е�Ŀ¼���洢����������У��Ա��´λָ�ϵͳ��" << endl;
                break;

            case 14://help readDisk
                cout << "Eg: readDisk" << endl;
                cout << "����������е�Ŀ¼�������ڴ��У��ָ�ϵͳ��" << endl;
                break;

            case 15://help viewDisk
                cout << "Eg:viewDisk" << endl;
                cout << "��ʾ������������" << endl;
                break;

            default:
                cout << "�������ָ�����󣡣���" << endl;
                break;
        }

    }

    else {
        cout << cmd[0] << " �﷨����ȷ����������ȷ����" << endl;
    }
}
void Menu()
{

    cout<< "  ��ӭʹ���ļ�ϵͳ "     << endl;
    cout<< "  ������ʾ:        "  << endl;
    cout<< "  help ����ʹ�÷�ʾ"<<endl;
    cout<< "  createUser �����û�"<<endl;
    cout<< "  su �л��û�"<<endl;
    cout<< "  dir �鿴Ŀ¼������   "   <<endl;
    cout<< "  mkdir ����Ŀ¼      " << endl;
    cout<< "  rmdir ɾ��Ŀ¼      " <<endl;
    cout<< "  create  �����ļ�    " << endl;
    cout<< "  delete  ɾ���ļ�    "<<endl;
    cout<< "  rename ����������   "<<endl;
    cout<< "  read ��ȡ�ļ�����   "<<endl;
    cout<< "  write ���ļ�д����  " << endl;
    cout<< "  cd ������Ŀ¼ " << endl;
    cout<< "  cd .. ������һ��Ŀ¼  "<<endl;
    cout<< "  cut ���� " << endl;
    cout<< "  copy ���� "<<endl;
    cout<< "  writeDisk �����д���� " << endl;
    cout<< "  readDisk ��ȡ��������"<<endl;
    cout<< "  viewDisk �鿴����״̬" << endl;

}

/*********************************************************************/
//�����������ں�(�ļ�ϵͳ����)ʵ�ֻ����ڴ���ļ�ϵͳ��Ϊ�û��ṩ����

void FileSystemOnMemory() {
    sys_initDisk();
    Menu();
    Command command;
    while (true) {
        cout << "[user@jj-zfy:" << current_user->_name << "]	" << get_current() << ">";
        command.get_command();
        command.exe_command();
        command.rst_command();
        cout << endl;
    }
}
/*****************************/
bool check_empty(char ch) {
    if (ch == ' ' || ch == '	')
        return true;
    return false;
}
/*
*��ȡ��һ���ǿ��ַ�
*/
char delete_empty(char ch) {
    while (check_empty(ch)) {
        scanf("%c", &ch);
    }
    return ch;
}

void Command::get_command() {
    char ch;
    /*
    *��ʼ���������飬����ֵ��Ϊ���ַ���
    */
    scanf("%c", &ch);
    //���˵���������е�ǰ�����ո��ַ�
    ch = delete_empty(ch);
    if (ch == '\n')
        _cmd[0] = "\n";
    while (ch != '\n') {
        _cmd[_cmd_len] += ch;
        scanf("%c", &ch);
        //��������ո��Һ���һ���ַ����ǻ��з�����ô_cmd_len_++��
        if (check_empty(ch)) {
            ch = delete_empty(ch);//��ȡ�ո����ĵ�һ���ǿո��ַ�
            if (ch != '\n')
                _cmd_len++;
        }
    }
    _cmd_len++;
};

void Command::exe_command() {
    string *p = new string[_cmd_len];
    int q = _cmd_len;
    for (int i = 0; i<q; i++)
        p[i] = _cmd[i];
    if (p[0] == "dir") {
        dir(p, q);
    }
    else if (p[0] == "mkdir") {
        mkdir(p, q);
    }
    else if (p[0] == "rmdir") {
        rmdir(p, q);
    }
    else if (p[0] == "createFile") {
        create_file(p, q);
    }
    else if (p[0] == "delete") {
        delete_file(p, q);
    }
    else if (p[0] == "rename") {
        rename(p, q);
    }
    else if (p[0] == "write") {
        write_file(p, q);
    }
    else if (p[0] == "read") {
        read_file(p, q);
    }
    else if (p[0] == "cd") {
        cd(p, q);
    }
    else if (p[0] == "\n") {

    }
    else if (p[0] == "cut") {
        cut(p, q);
    }
    else if (p[0] == "copy") {
        copy(p, q);
    }
    else if (p[0] == "writeDisk") {
        writeDisk(p, q);
    }
    else if (p[0] == "readDisk") {
        readDisk(p, q);
    }
    else if (p[0] == "viewDisk") {
        viewDisk(p, q);
    }
    else if (p[0] == "Menu") {
        Menu();
    }
    else if (p[0] == "exit") {
        system("exit");
    }
    else if (p[0] == "help") {
        help_command(p, q);
    }
    else if (p[0] == "createUser") {
        create_user(p,q);
    }
    else if (p[0] == "su") {
        su(p, q);
    }
    else if (p[0] == "share") {
        su(p, q);
    }
    else {
        cout << _cmd[0] << "  doesn't exist, Use menu to check the command!" << endl;
    }
};

void Command::rst_command() {
    for (int i = 0; i<_cmd_len; i++) {
        _cmd[i] = "";
    }
    _cmd_len = 0;
}
int main(){
    FileSystemOnMemory();
    return 0;
}
