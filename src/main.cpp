// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <Arduino.h>
#include <stdio.h>
#include "myMenu.h"

using namespace std;

extern SubMenu root;
SubMenu * currentMenu = &root;
MenuObj * doMenuById(SubMenu* &submenu, String _id);

void setup()
{
	String strline;
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("自定义菜单类测试程序");
  Serial.println("打印全部菜单项");

	root.printSubMenuTree();
}

void menu_loop();

void loop() {
	menu_loop();
}

void menu_loop() {
	static String inputItem;
  if(Serial.available() > 0) {
		char ch = Serial.read();
		if(ch != '\n' && ch != '\r') {
			inputItem += ch;
		}
		else if(ch == '\n') {
			Serial.println("执行用户输入指令：" + inputItem);
			if(inputItem.equalsIgnoreCase("menu")) {
				currentMenu->printMenu();
			}
			else {
				Serial.println(inputItem);
				doMenuById(currentMenu, inputItem);
				Serial.println();
			}
			inputItem = "";
		}
  }
}

MenuObj * doMenuById(SubMenu* &submenu, String _id) {
	// MenuObj **obj_list = submenu->getItemList();
	// uint8_t objs = submenu->getLength();

	if (_id == "bk" || _id == "back") {
		if (submenu->getParent() != NULL) {
			submenu = submenu->getParent();
      Serial.println("返回上层菜单：<" + submenu->getName() + ">");

			submenu->printMenu();
			return submenu;
		}
	}

	MenuObj * rtn = submenu->doMenuEvent(_id);
	if(rtn == NULL) {
		Serial.println("Err:<未找到菜单项>");
	}
	else if(rtn->getType() == SUBMENU) {
		submenu = (SubMenu*)rtn;
		Serial.println("选中子菜单：<" + submenu->getName() + ">");
		submenu->printMenu();
	}
	return rtn;
}
