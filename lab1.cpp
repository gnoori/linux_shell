/*Guzel Noori
Lab1 - CS 470*/
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
using namespace std;

void manual();
void sysinfo_manual();
void exit_manual();
void meminfo_manual();

#define KEY_UP 72
#define KEY_DOWN 80

void mem_info(char *switches){
    string switch_type = switches;
    if(switch_type == "-h"){
        meminfo_manual();
    }
    else if (switch_type == "-s"){
        cout << "Total swap space in bytes: " << endl;
        system("vmstat -s | grep \"total swap\"");
    }
    else if(switch_type == "-S"){
        cout << "Total shared memory in bytes available in the system: "<<endl;
        system("cat /proc/sys/kernel/shmall");
    }
    else if(switch_type == "-u"){
        cout << "Total memory in bytes: "<<endl;
        system("vmstat -s | grep \"total memory\"");
    }
    else{
        cout << "Incorrect switch entry"<<endl;
        cout << "Type 'memoryinformation -h' to see the list of available switches"<<endl;
    }
}

void system_info(char *switches){
    string switch_type = switches;

    //prompts to systeminformation manual
    if(switch_type=="-h"){
        sysinfo_manual();
    }
    else{
        if(switch_type == "-p"){
            cout << "Number of processors available in the system: "<<endl;
            system("grep -c processor /proc/cpuinfo");
        }
        else if(switch_type == "-m"){
            cout << "The maximum number of open files per processor: "<<endl;
            system("ulimit -n");
        }
        else if(switch_type == "-o"){
            cout << "Processor type: "<<endl;
            system("cat /proc/cpuinfo | grep 'model' | uniq");
        }
        else {
            cout << "Incorrect switch entry." << endl;
            cout << "Type 'systeminformation -h' to see the list of available switches"<<endl;
            
        }
    }
}

string exit_Command(char* entry){
    //empty string
    string user_Input="";

    //holds the temporary switch
    string switch_type = entry;

    //prompts to exit manual
    if (switch_type == "-h"){
        user_Input = "exit_manual";
    }
    else{
        string old_entry = entry;

        //tokenize the input
        entry = strtok(NULL, " ");

        //if the value is entered exit [n]
        if(entry != NULL){
            user_Input = "multiple";
        }
        //if the value is not entered exit [n]
        else{
            for (int i=0; i<old_entry.length(); i++){
                if(isdigit(old_entry[i])==false){
                    user_Input = "empty";
                    cout<< switch_type <<endl;
                    break;
                }
            }
            if(user_Input==""){
                user_Input=old_entry;
            }
        }
    }
    return user_Input;
}


void sysinfo_manual()
{
    cout << "----------------------------------------------------------------------"<< endl;
    cout << "systeminformation -switch has the following list of switches:" << endl;
    cout << "----------------------------------------------------------------------"<<endl;
    cout<< "-p  --> prints the number of processors available in the system"<< endl;
    cout<< "-m  --> prints the maximum number of open files per processor"<< endl;
    cout<< "-o  --> prints the processor type"<< endl;

}

void meminfo_manual(){
    cout << "-------------------------------------------------------------" << endl;
    cout<< "memoryinformation -switch has the following list of switches:" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout<< "-s  --> prints the total swap space in bytes"<<endl;
    cout<< "-u  --> prints the total memory in bytes"<< endl;
    cout<< "-S --> prints the total shared memory in nytes available in the system"<<endl;
}

void exit_manual(){
    cout<< "exit [n] terminates the shell." << endl;
    cout<< "If [n] argument is given, it will be the exit value of the shell's execution. "<<endl;
    cout<< "Otherwise, the exit value will be the value returned by the last executed commmand (or 0 if no commands were executed" << endl;
}

void manual(){
    cout << "-----------------------------------------------------------"<<endl;
    cout<< "List of available commands:" << endl;
    cout << "-----------------------------------------------------------"<<endl;
    cout<< "systeminformation -switch ----> Information about the system" << endl;
    cout<< "memoryinformation -switch ----> Information about memory" << endl;
    cout<< "exit [n] -----> Exits from the shell" << endl;
    cout<< "ls ------> list of available files" << endl;
    cout<< "cat ------>" << endl;
    cout<< "pwd ------> shows current directory" << endl;
    cout<< "----------------------------------------------"<< endl;
    cout<< "To see list of available switches, type 'command -h'"<< endl;
    cout<< "-----------------------------------------------------"<<endl;
}

int main(){
    string commands[5] = {"systeminformation", "memoryinformation","exit", "manual", "-h"};
    string prompt = "cwushell";
    int i = 0;
    while(i==0){
        cout << prompt << ">";
        char cmdl[200];
        cin.getline(cmdl, 200);
        string command = cmdl;
        char *command_input;
        command_input = strtok(cmdl, " ");
        //if statement for systeminformation command
        if (command_input == commands[0]){
            command_input = strtok(NULL, " ");
            if (command_input == NULL){
                sysinfo_manual();
            }
            else{
                system_info(command_input);
            }

        }
        //if statement for memoryinformation command
        else if (command_input == commands[1]){
            command_input = strtok(NULL, " ");
            if (command_input == NULL){
                meminfo_manual();
            }
            else{
                mem_info(command_input);
            }
        }
        //if statement for exit command
        else if(command_input == commands[2]){
            command_input = strtok(NULL, " ");
            if (command_input == NULL){
                cout << "Exit 0"<<endl;
                return 0;
            }
            else{
                string user_Input = exit_Command(command_input);
                if(user_Input == "multiple"){
                    cout << user_Input<<endl;
                }
                else if (user_Input == "empty"){
                    cout << "Exit 0"<<endl;
                    return 0;
                }
                else if (user_Input == "exit_manual"){
                    exit_manual();
                }
                else {
                    cout << "Exit " << stoi(user_Input)<<endl;
                    return stoi(user_Input);
                }
            }
        }
        //if statement for manual
        else if ((command_input == commands[3]) || (command_input == commands[4])){
            manual();
        }
        //error handling for incorrect commands
        else {
            const char *c = command.c_str();
            cout<< "Incorrect command. Type -h to get the list of commands available" << endl;
            system(c);
        }
    }
    return 0;
}