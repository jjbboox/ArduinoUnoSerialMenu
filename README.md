# ArduinoUnoSerialMenu

Simple serial menu example

Customizable menu items, support submenus

Each menu item is called by a callback function


简单的适用于Arduino的串口菜单实例

可自定义菜单项，子菜单

每个菜单项通过回调函数调用

开发环境：VS Code, Arduino, Platform



Arduino重新启动后显示整个菜单树

![image](https://github.com/jjbboox/ArduinoUnoSerialMenu/blob/master/img/ShowMenuTree.png)

通过串口发送[menu]命令，可以显示当前菜单列表

菜单列表左侧[]内的是菜单ID，可在串口发送菜单ID给UNO执行相应的菜单项

[]右侧带有>>的项目为子菜单

![image](https://github.com/jjbboox/ArduinoUnoSerialMenu/blob/master/img/ShowCurrentMenuList.png)

输入菜单项ID就可以执行该菜单项的回调函数，完成菜单动作

![image](https://github.com/jjbboox/ArduinoUnoSerialMenu/blob/master/img/DoMenuItemAction.png)

输入子菜单的ID便可以进入到子菜单

![image](https://github.com/jjbboox/ArduinoUnoSerialMenu/blob/master/img/EnterSubMenu.png)

输入菜单ID后加一个空格可以自定义参数，系统会将菜单ID后空格以后的字符串传递给回调函数

如下例中 031 50

031是菜单项，代表调整全彩LED的红色亮度，50代表亮度值

后方参数字符串的解析由每个菜单项的回调函数自行定义

![image](https://github.com/jjbboox/ArduinoUnoSerialMenu/blob/master/img/ItemActionParam.png)

输入bk或back可以回到上一级菜单

![image](https://github.com/jjbboox/ArduinoUnoSerialMenu/blob/master/img/BackToParentMenu.png)

我修改了readme
