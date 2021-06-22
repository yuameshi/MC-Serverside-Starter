// MC-Server-Starter.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <string>

using namespace std;
#pragma warning(disable:4996)
int main() {
	cout << "==Reading and Parsing Configuration File==" << endl;
	ifstream fin(".\\serverBasicConfig.cfg");
	string configData = "",temp;
	if (fin.eof()){
		cout << "No CFG File!" << endl;
		return 0;
	}
	while (fin >> temp) {
		configData = configData + temp;
	}
	cout << configData.find("File=") << endl << configData.find(";", configData.find("File=")) << endl;
	string server = configData.substr(configData.find("File=") + 5, configData.find(";", configData.find("File=")) - configData.find("File=") - 5);
	string memory = configData.substr(configData.find("Memory=") + 7, configData.find(';', configData.find("Memory=")) - configData.find("Memory=") - 7);
	string PrcPPT = configData.substr(configData.find("Prop=") + 5, 1);
	cout << "Config data: " << configData << endl;
	cout << "Server file name :" << server << endl;
	cout << "Memory :" << memory << endl;
	cout << "Process Property : " << PrcPPT << endl;
	string prop = "Normal";
	if (PrcPPT == "1") {
		prop = "Idle";
	}
	if (PrcPPT == "2") {
		prop = "Below Normal";
	}
	if (PrcPPT == "3") {
		prop = "Normal";
	}
	if (PrcPPT == "4") {
		prop = "Above Normal";
	}
	if (PrcPPT == "5") {
		prop = "High Priority";
	}
	if (PrcPPT == "6") {
		prop = "Real Time";
	}
	prop = "wmic process where name='java.exe' call SetPriority \"" + prop + "\"";
	string cmd = "start cmd /k \"java -Xmx" + memory + " -jar " + server + " && pause\"";
	cout << "==============Read Complete==============" << endl;
	cout << "================Starting=================" << endl;
	cout << "COMMAND:" + cmd << endl;
	system(cmd.data());
	cout << "==============Awaiting Java==============" << endl;
	Sleep(2000);
	cout << "==============Setting  Prop==============" << endl;
	cout << "COMMAND:" << prop << endl;
	system(prop.data());
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
