//
// Created by zfy on 2019/6/26.
//
#include<string>
#include<iostream>
using namespace std;
/**************************************************/
//基于内核实现的目录管理；
void Menu();
void create_user(string*cmd,int length);
void su(string*cmd,int length);
void dir(string*cmd,int length);//查看目录内容；
void mkdir(string*cmd, int length);//创建目录；
void rmdir(string*cmd, int length);//删除目录;
void create_file(string*cmd, int length);//创建文件；
void rename(string*cmd, int length);//重命名文件；
void write_file(string*cmd, int length);//向文件写内容；
void read_file(string*cmd, int length);//读取文件内容；
void cd(string*cmd, int length);//进入子目录；
void cdback();//返回上一级目录；
void cut(string*cmd, int length);//剪切；
void copy(string*cmd, int length);//复制；
void share(string*cmd, int length);
/**************************************************/
//虚拟磁盘(内存管理)，实现恢复系统的服务；

void writeDisk(string*cmd, int length);//向磁盘写内容
void readDisk(string*cmd, int length);//读取磁盘内容
void viewDisk(string*cmd, int length);//查看磁盘状态；

void help_command(string*cmd, int length); //查询命令使用方式；
bool check_empty(char ch);
char delete_empty(char ch);
/***************************************************/
//开发者利用内核(文件系统部分)实现基于内存的文件系统，为用户提供服务；
void FileSystemOnMemory();
/*******************************************************************/
class Command {
private:
    string _cmd[100];
    int _cmd_len;

public:
    Command() {
        _cmd_len = 0;
    }
    void get_command();
    void exe_command();
    void rst_command();
};



