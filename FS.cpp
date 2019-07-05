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
            cout<<"用户"+cmd[1]+"创建成功！\n";
        else  cout<<"用户"+cmd[1]+"创建失败！\n";
    } else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }
}

void su(string*cmd,int length){
    if(length == 2){
        int signal;
        if(cmd[1]=="root")
            signal=sys_suroot();
        else signal=sys_su(cmd[1]);
        if(signal==1)
            cout<<"用户切换成功！\n";
        else  cout<<"用户切换失败！\n";
    } else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }
}


/**************************************************/
//基于内核实现的目录管理；
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

//查看目录内容；
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
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }
}

//创建目录；
void mkdir(string*cmd, int length) {
    if (length == 2) {
        int signal;         //记录创建目录的情况，给用户提供信息；
        signal = sys_mkdir(cmd[1]);

        if (signal == 1)
        {
            cout << "创建目录成功！" << endl;
        }
        else if (signal == -1)
        {
            cout << "路径错误！" << endl;
        }
        else if(signal==0)
        {
            cout << "用户无该命令权限！" << endl;
        }
        else
        {
            cout << "目录已经存在！" << endl;
        }
    }
    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }
}

//删除目录;
void rmdir(string*cmd, int length) {
    if (length == 2) {

        int signal;         //记录创建目录的情况，给用户提供信息；
        signal = sys_rmdir(cmd[1]);

        if (signal == 1)
        {
            cout << "删除目录成功！" << endl;
        }
        else if (signal == -1)
        {
            cout << "路径错误！" << endl;
        }
        else if(signal==0)
        {
            cout << "用户无该命令权限！" << endl;
        }
        else
        {
            cout << "目录不存在！" << endl;
        }
    }
    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }
}

//创建文件；
void create_file(string*cmd, int length) {

    if (length == 2) {

        int signal;         //记录创建目录的情况，给用户提供信息；
        signal = sys_create_file(cmd[1]);

        if (signal == 1)
        {
            cout << "创建文件成功！" << endl;
        }
        else if (signal == -1)
        {
            cout << "路径错误！" << endl;
        }
        else if(signal==0)
        {
            cout << "用户无该命令权限！" << endl;
        }
        else
        {
            cout << "文件已经存在！" << endl;
        }
    }
    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }
}

//删除文件；
void delete_file(string*cmd, int length) {
    if (length == 2) {

        int signal;         //记录创建目录的情况，给用户提供信息；
        signal = sys_delete_file(cmd[1]);

        if (signal == 1)
        {
            cout << "删除文件成功！" << endl;
        }
        else if (signal == -1)
        {
            cout << "路径错误！" << endl;
        }
        else if(signal==0)
        {
            cout << "用户无该命令权限！" << endl;
        }
        else
        {
            cout << "文件不存在！" << endl;
        }
    }
    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }
}

//重命名文件；
void rename(string*cmd, int length) {
    if (length == 4) {
        int type = 0;
        if (cmd[2] == "1")
            type = 1;
        int signal;         //记录创建目录的情况，给用户提供信息；
        signal = sys_rename(cmd[1], type, cmd[3]);

        if (signal == 1)
        {
            cout << "重命名成功！" << endl;
        }
        else if (signal == -1)
        {
            cout << "存在同名同类型！" << endl;
        }
        else if (signal == -2)
        {
            cout << "路径错误！" <<endl;
        }
        else if(signal==0)
        {
            cout << "用户无该命令权限！" << endl;
        }
        else
        {
            cout << "重命名的文件不存在！" << endl;
        }
    }
    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }

}

//向文件写内容；
void write_file(string*cmd, int length) {
    if (length == 2) {
        string path_name = cmd[1];
        string name = "";
        FCB* parent = NULL;
        int B,F;
        FCB* file = sys_returnFCB(path_name, name, 0, parent,B,F);
        if (file != NULL)
        {
            //此时文件存在；
            cout << "请输入内容:";
            string content;
            //getchar();
            getline(cin, content);
            int signal;
            signal = sys_overwrite_file(file, content);
            if (signal ==1)
            {
                cout << "写文件成功" << endl;
            }
            else if(signal==0)
            {
                cout << "用户无该命令权限！" << endl;
            }
            else
            {
                cout << "系统资源不足，无法写入内容" << endl;
            }
        }
        else
        {
            //文件不存在；
            cout << "文件不存在，无法写入内容" << endl;
        }
    }
    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }
}

//读取文件内容；
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
                cout << "读取文件内容成功！" << endl;
                cout << "文件内容为：" << content << endl;
            }else cout << "用户无该命令权限！" << endl;
        }

        else
        {
            cout << "文件不存在！" << endl;
        }
    }
    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }
}

//进入子目录；
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
            cout << "用户无该命令权限！" << endl;
        }
        else
        {
            cout <<signal << endl;
        }
    }
    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }
}

//返回上一级目录；
void cdback() {
    sys_cdback();
}

//剪切；
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
            cout << "剪切粘贴成功！" << endl;
        }
        else if (signal == -1)
        {
            cout << "存在同名同类型，不允许剪切粘贴" << endl;
        }
        else if (signal == -2)
        {
            cout << "路径错误" << endl;
        }
        else if (signal == -3)
        {
            cout << "不存在，无法剪切" << endl;
        }
        else if (signal == -4)
        {
            cout << "目标目录不存在" << endl;
        }
        else if(signal==0)
        {
            cout << "用户无该命令权限！" << endl;
        }
    }
    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }
}

//复制；
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
            cout << "复制粘贴成功！" << endl;
        }
        else if (signal == -1)
        {
            cout << "系统资源不够，无法进行复制" << endl;
        }
        else if (signal == -2)
        {
            cout << "目标目录下存在同名同类型，不允许粘贴" << endl;
        }
        else if (signal == -3)
        {
            cout << "路径错误" << endl;
        }
        else if (signal == -4)
        {
            cout << "复制对象不存在" << endl;
        }
        else if (signal == -5)
        {
            cout << "目标目录不存在" << endl;
        }
        else if(signal==0)
        {
            cout << "用户无该命令权限！" << endl;
        }
    }
    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
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
            cout << "共享成功！" << endl;
        }
        else if (signal == -2)
        {
            cout << "共享的文件的路径不存在" << endl;
        }
        else if (signal == -3)
        {
            cout << "共享对象不存在" << endl;
        }
        else if (signal == -4)
        {
            cout << "本地路径不存在" << endl;
        }
        else if(signal==0)
        {
            cout << "该文件您无共享权限！" << endl;
        }
    }
    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }

}
/******************************************************/
//虚拟磁盘(内存管理)，实现恢复系统的服务；

//向磁盘写内容
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
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
        return;
    }
    if(result == -1){
        cout<<"打开虚拟磁盘失败！！！"<<endl;
    } else if(result == 1){
        cout << "写入磁盘，成功！" << endl;
    }
}

//读取磁盘内容
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
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
        return;
    }
    if (result == 1){
        cout<<"恢复成功！！！"<<endl;
    } else if (result == -1){
        cout<<"读取虚拟磁盘出错！"<<endl;
    }
}

//查看磁盘状态；
void viewDisk(string*cmd, int length) {
    if (length == 1) {
        //此时位示图个数和总容量有关；
        //cout << "虚拟磁盘总容量：" << _bitMapCount << "MB;" << endl;
        cout << "虚拟磁盘总容量：" <<  "8MB;" << endl;

        cout << "虚拟磁盘中系统占用的容量：" << _systemUsedBlock << "KB;" << endl;

        cout << "虚拟磁盘还剩余的容量：" << _emptyBLOCK_Count << "KB;" << endl;
    }
    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }

}

//查询命令使用方式；
void help_command(string*cmd, int length) {
    //对用户申请的服务帮助，提供指南；
    if (length == 1) {
        cout << "请使用help command查询某条指令的用法" << endl;
    }
    else if(length==2){
        map <string, int> help_menu;
        help_menu["dir"] = 1, help_menu["mkdir"] = 2, help_menu["rmdir"] = 3;
        help_menu["create"] = 4, help_menu["delete"] = 5; help_menu["rename"] = 6;
        help_menu["write"] = 7, help_menu["read"] = 8;
        help_menu["cd"] = 9, help_menu["cd.."] = 10;
        help_menu["cut"] = 11, help_menu["copy"] = 12;
        help_menu["writeDisk"] = 13, help_menu["readDisk"] = 14, help_menu["viewDisk"] = 15;


        //cout << "请输入需要查询的命令(如：help dir);" << endl;

        string help_command = cmd[1];
        int choice;

        //用户输入需要帮助的命令；
        //cin >> help_command;
        choice = help_menu[help_command];
        switch (choice)
        {
            case 1://help dir
                cout << "Eg:dir" << endl;
                cout << "只输入dir,则‘请问是查看当前目录的内容吗？’" << endl;
                cout << "Y,显示当前的目录；N，请输入要查看的目录路径(支持绝对路径(/)和相对路径)。" << endl;
                cout << "Eg:dir /test" << endl;
                cout << "查看的是根目录(/)下的test目录中的内容。" << endl;
                cout << "Eg:dir test" << endl;
                cout << "查看的是当前目录下的test目录中的内容。" << endl;
                break;

            case 2://help mkdir
                cout << "支持绝对路径(/)和相对路径。" << endl;
                cout << "Eg:mkdir /test" << endl;
                cout << "在根目录(/)下，创建test目录。" << endl;
                cout << "Eg:mkdir test" << endl;
                cout << "在当前目录下，创建test目录。" << endl;
                break;

            case 3://help rmdir
                cout << "支持绝对路径(/)和相对路径。" << endl;
                cout << "Eg:rmdir /test" << endl;
                cout << "在根目录(/)下，删除test目录。" << endl;
                cout << "Eg:mkdir test" << endl;
                cout << "在当前目录下，删除test目录。" << endl;
                break;

            case 4://help create
                cout << "支持绝对路径(/)和相对路径。" << endl;
                cout << "Eg:create /test" << endl;
                cout << "在根目录(/)下，创建test文件。" << endl;
                cout << "Eg:create test" << endl;
                cout << "在当前目录下，创建test文件。" << endl;
                break;

            case 5://help delete
                cout << "支持绝对路径(/)和相对路径。" << endl;
                cout << "Eg:delete /test" << endl;
                cout << "在根目录(/)下，删除test文件。" << endl;
                cout << "Eg:delete test" << endl;
                cout << "在当前目录下，删除test文件。" << endl;
                break;

            case 6://help rename
                cout << "支持绝对路径(/)和相对路径。" << endl;
                cout << "指定文件类型：1表示目录，0表示文件。" << endl;
                cout << "Eg:rename /test 1 test1" << endl;
                cout << "在根目录(/)下，把目录test重命名为test1" << endl;
                cout << "Eg:rename test 0 test1" << endl;
                cout << "在当前目录下，把文件test重命名为test1" << endl;
                break;

            case 7://help write
                cout << "支持绝对路径(/)和相对路径。" << endl;
                cout << "Eg:write /test" << endl;
                cout << "在根目录(/)下,向文件test写内容；若文件存在，则请输入内容。" << endl;
                cout << "Eg:write test" << endl;
                cout << "在当前目录下,向文件test写内容；若文件存在，则请输入内容。" << endl;
                break;

            case 8://help read
                cout << "支持绝对路径(/)和相对路径。" << endl;
                cout << "Eg:read /test" << endl;
                cout << "在根目录(/)下,读取文件test的内容；若文件存在，则请显示内容。" << endl;
                cout << "Eg:read test" << endl;
                cout << "在当前目录下,读取文件test的内容；若文件存在，则请显示内容。" << endl;
                break;

            case 9://helo cd
                cout << "支持绝对路径(/)和相对路径。" << endl;
                cout << "Eg:cd /test" << endl;
                cout << "进入根目录(/)下的test目录。" << endl;
                cout << "Eg:cd test" << endl;
                cout << "进入当前目录的test目录。" << endl;
                break;

            case 10://help cd..
                cout << "Eg:cd.." << endl;
                cout << "返回上一级目录；" << endl;
                break;

            case 11://help cut
                cout << "支持绝对路径(/)和相对路径。" << endl;
                cout << "指定文件类型：1表示目录，0表示文件。" << endl;
                cout << "Eg:cut /test 1 /test1" << endl;
                cout << "把根目录(/)下的目录test剪切到根目录下的目录test1中" << endl;
                cout << "Eg:cut test 0 /test1" << endl;
                cout << "把当前目录下的文件test剪切到根目录下的目录test1中" << endl;
                break;

            case 12://help copy
                cout << "支持绝对路径(/)和相对路径。" << endl;
                cout << "指定文件类型：1表示目录，0表示文件。" << endl;
                cout << "Eg:copy /test 1 /test1" << endl;
                cout << "把根目录(/)下的目录test复制到根目录下的目录test1中" << endl;
                cout << "Eg:cut test 0 /test1" << endl;
                cout << "把当前目录下的文件test复制到根目录下的目录test1中" << endl;
                break;

            case 13://help writeDisk
                cout << "Eg: writeDisk" << endl;
                cout << "把内存中的目录树存储到虚拟磁盘中，以便下次恢复系统。" << endl;
                break;

            case 14://help readDisk
                cout << "Eg: readDisk" << endl;
                cout << "把虚拟磁盘中的目录树读到内存中，恢复系统。" << endl;
                break;

            case 15://help viewDisk
                cout << "Eg:viewDisk" << endl;
                cout << "显示虚拟磁盘情况。" << endl;
                break;

            default:
                cout << "您输入的指令有误！！！" << endl;
                break;
        }

    }

    else {
        cout << cmd[0] << " 语法不正确，请输入正确命令" << endl;
    }
}
void Menu()
{

    cout<< "  欢迎使用文件系统 "     << endl;
    cout<< "  命令提示:        "  << endl;
    cout<< "  help 命令使用方示"<<endl;
    cout<< "  createUser 创建用户"<<endl;
    cout<< "  su 切换用户"<<endl;
    cout<< "  dir 查看目录的内容   "   <<endl;
    cout<< "  mkdir 创建目录      " << endl;
    cout<< "  rmdir 删除目录      " <<endl;
    cout<< "  create  创建文件    " << endl;
    cout<< "  delete  删除文件    "<<endl;
    cout<< "  rename 重命名命令   "<<endl;
    cout<< "  read 读取文件内容   "<<endl;
    cout<< "  write 向文件写内容  " << endl;
    cout<< "  cd 进入子目录 " << endl;
    cout<< "  cd .. 返回上一级目录  "<<endl;
    cout<< "  cut 剪切 " << endl;
    cout<< "  copy 复制 "<<endl;
    cout<< "  writeDisk 向磁盘写内容 " << endl;
    cout<< "  readDisk 读取磁盘内容"<<endl;
    cout<< "  viewDisk 查看磁盘状态" << endl;

}

/*********************************************************************/
//开发者利用内核(文件系统部分)实现基于内存的文件系统，为用户提供服务；

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
*获取第一个非空字符
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
    *初始化参数数组，将其值置为空字符串
    */
    scanf("%c", &ch);
    //过滤掉输入参数中的前几个空格字符
    ch = delete_empty(ch);
    if (ch == '\n')
        _cmd[0] = "\n";
    while (ch != '\n') {
        _cmd[_cmd_len] += ch;
        scanf("%c", &ch);
        //如果遇到空格且后面一个字符不是换行符，那么_cmd_len_++；
        if (check_empty(ch)) {
            ch = delete_empty(ch);//获取空格符后的第一个非空格字符
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
