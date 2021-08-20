#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clean_data(char* cmd);


//执行常量system
void system_call_const(char* cmd)
{
    system("ls");
}
//执行usr不可控的system
void system_call_safe1(char* cmd)
{
    char *command = "ls";
    system(command);
}
//执行usr不可控的system
void system_call_safe2(char* cmd)
{
    clean_data(cmd);   //校验
    system(cmd);
}
//执行危险的system
void system_call(char* cmd)
{
    char command[100];
    if(strlen("echo 1 ")+strlen(cmd)<50)
    {
        sprintf(command,"echo 1 %s",cmd);
        system(command);
    }
}

//假设这是清除污点的函数
void clean_data(char* cmd)
{   
    strcpy(cmd,cmd);
}

//假设这是用户可控的输入函数
int get_user_input(char *cmd)
{
    char* input = ";echo 'you are hacked'";  
    strcpy(cmd,input);
    return 1;
}

int main()
{
    char cmd[100],command[100];
    get_user_input(cmd);
    system_call_const(cmd);
    system_call_safe1(cmd);
    system_call_safe2(cmd);
    system_call(cmd);
    system(cmd);

    strcpy(command,cmd);
    system(command);
}
