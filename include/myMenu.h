#ifndef _MY_MENU_H_
#define _MY_MENU_H_
#include <Arduino.h>

enum  MenuEvent {
	EVENT_CLICK,
};

enum MenuObjectType {
	ROOT,
	SUBMENU,
	ITEM,
};

class MenuObj {
public:
	// MenuObj(void) : ObjName(""), type(SUBMENU) {};
	MenuObj(String _id, String _name, MenuObjectType _type) : id(_id), type(_type), ObjName(_name), parent(NULL) {};
	void setType(MenuObjectType _type) { type = _type; };
	void setName(String _name) { ObjName = _name; };
	MenuObjectType getType() { return type; };
	String getName() { return ObjName; };
	String getId() { return id; };
	void setLevel(uint8_t _level) { level = _level; };
	uint8_t getLevel() { return level; };
	void setParent(MenuObj * _parent) { parent = _parent; };
	virtual MenuObj *getParent() { return parent; };
	void printObj() {
		String str = "";
		for (int i = 0; i < level; i++) {
			str += "    ";
		}
		
		str += "[" + id + "] " + (type == SUBMENU ? ">>" : "  ");
		str += " " + ObjName + "";
		Serial.println(str);
	};
private:
	String id;
	MenuObjectType type;
	String ObjName;
	uint8_t level;
	MenuObj *parent;
};

class MenuItem : public MenuObj {
public:
	MenuItem(String _id, String _name, void(*_eventFunc)(String)) : MenuObj(_id, _name, ITEM), EventFunction(_eventFunc) {};
	void(*EventFunction)(String);
private:
	String param;
};

class SubMenu : public MenuObj {
public:
	SubMenu(String _id, String _name, MenuObj ** _itemlist, uint8_t _length)
		: MenuObj(_id, _name, SUBMENU), length(_length) {
		setItemList(_itemlist, _length);
	};
	void setItemList(MenuObj ** _itemlist, uint8_t _length) {
		itemList = _itemlist;
		length = _length;
		for (int i = 0; i < length; i++) {
			itemList[i]->setParent(this);
			itemList[i]->setLevel(getLevel() + 1);
		}
	};
	MenuObj ** getItemList() { return itemList; };
	uint8_t getLength() { return length; };
	void printSubMenuTree() {
		for (int i = 0; i < length; i++) {
			itemList[i]->setLevel(this->getLevel() + 1);
			itemList[i]->printObj();
			if (itemList[i]->getType() == SUBMENU) {
				((SubMenu*)itemList[i])->printSubMenuTree();
			}
		}
	};
	void printMenu() {
		if (getParent() != NULL) {
			Serial.println("上一级菜单[" + getParent()->getName() + "]  输入[bk]或[back]可返回上一级目录");
		}
		Serial.println("当前菜单[" + getName() + "]");

		for (int i = 0; i < length; i++) {
			itemList[i]->printObj();
		}
	};
	SubMenu * getParent() { return (SubMenu*)MenuObj::getParent(); };
	MenuObj * doMenuEvent(String _id, bool doSub = false) {
		String cmd = _id.substring(0, _id.indexOf(' '));
		for(int i = 0; i < length; i++) {
			if(cmd.equalsIgnoreCase(itemList[i]->getId())) {
				if(itemList[i]->getType() == ITEM) {
					MenuItem *item = (MenuItem*)itemList[i];
					String param = "";
					if(_id.indexOf(' ') != -1) {
						param = _id.substring(_id.indexOf(' ') + 1);
					}
					item->EventFunction(param);
					return itemList[i];
				}
				else if(itemList[i]->getType() == SUBMENU) {
					if(doSub) {
						return ((SubMenu*)itemList[i])->doMenuEvent(_id);
					}
					else {
						return itemList[i];
					}
				}
			}
		}
		return NULL;
	};
private:
	MenuObj ** itemList;
	uint8_t length;
};

#endif
