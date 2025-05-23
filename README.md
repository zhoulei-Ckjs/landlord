# 创建项目
【欢迎】 -> 【创建项目】-> 【Application(Qt)】 -> 【Qt Widgets Application】 -> 点击【确认】进入下一步
* location: 输入项目名字和路径
* 构建系统: CMake
* Details:
  * Class name: game_pannel 主窗口名称
  * Base class: QMainWindow 或者 QWidget 都行
  * 其他: 默认
* 构建套件: Desktop Qt 6.8.2 MSVC2022 64bit
* 汇总:
  * 添加到版本控制系统: Git
# 分数面板
## 创建面板
项目右键 -> 【添加新文件】 -> 【Qt】 -> 【Qt Widgets Designer Form Class】-> 点击【选择】进入下一步
* 界面模板: Widget
* 类详情：
  * 类名: ScorePanel
  * 其他: 默认...
* 汇总：...
## 设计面板
    [me](label)             [](label)   [分](label)
    [left robot](label)     [](label)   [分](label)
    [right player](label)   [](label)   [分](label)
## 添加到主窗口game_panel
    |-------------------------------------------game_panel----------------------------------------|
    |                                                                                             |
    |    |-------------------------------------add new widget1-------------------------------|    |
    |    |                                                                                   |    |
    |    |                                                          |--add new widget2--|    |    |
    |    |          |--------Horizontal Spacer-----|                |                   |    |    |
    |    |                                                          |-------------------|    |    |
    |    |                                                                                   |    |
    |    |-----------------------------------------------------------------------------------|    |
    |                                           ——                                                |
    |                                           |                                                 |
    |                                           | Vertical Spacer                                 |
    |                                           |                                                 |
    |                                           ——                                                |
    |                                                                                             |
    |---------------------------------------------------------------------------------------------|
选择widget2 -> 【右键】 -> 【提升为】 ->
* 基类名称: QWidget
* 提升的类名称: ScorePanel
* 头文件: score_panel.h
  点击【添加】 -> 【提升】

提升后：

    |-------------------------------------------game_panel----------------------------------------|
    |                                                                                             |
    |    |-------------------------------------add new widget1-------------------------------|    |
    |    |                                                                                   |    |
    |    |                                                          |----ScorePanel-----|    |    |
    |    |          |--------Horizontal Spacer-----|                |                   |    |    |
    |    |                                                          |-------------------|    |    |
    |    |                                                                                   |    |
    |    |-----------------------------------------------------------------------------------|    |
    |                                           ——                                                |
    |                                           |                                                 |
    |                                           | Vertical Spacer                                 |
    |                                           |                                                 |
    |                                           ——                                                |
    |                                                                                             |
    |---------------------------------------------------------------------------------------------|
# 自定义按钮类
## 创建按钮类
【添加新文件】 -> 【C/C++】 -> 【C++ Class】 -> 【选择】 ->
* Details:
  * Class Name: MyButton
  * Base Class: QWidget
  * Header file: my_button.h
  * Source file: my_button.cpp
* 汇总: ...

【完成】
## 修改按钮类
将基类修改为QPushButton
# 按钮组窗口
## 创建按钮组窗口
项目右键 -> 【添加新文件】 -> 【Qt】 -> 【Qt Widgets Designer Form Class】-> 点击【选择】进入下一步
* 界面模板: Widget
* 类详情：
  * 类名: ButtonGroup
  * 其他: 默认...
* 汇总：...
## 集成到主窗口
在主窗口界面添加一个widget

    |-------------------------------------------game_panel----------------------------------------|
    |                                                                                             |
    |    |-------------------------------------widget(QWidget)-------------------------------|    |
    |    |                                                                                   |    |
    |    |                                   |--------score_panel_(ScorePanel)----------|    |    |
    |    |   |-----Horizontal Spacer-----|   |                                          |    |    |
    |    |                                   |------------------------------------------|    |    |
    |    |                                                                                   |    |
    |    |-----------------------------------------------------------------------------------|    |
    |                                           ——                                                |
    |                                           | Vertical Spacer                                 |
    |                                           ——                                                |
    |    |-------------------------------------button_group_(QWidget)------------------------|    |
    |    |                                                                                   |    |
    |    |-----------------------------------------------------------------------------------|    |
    |                                           ——                                                |
    |                                           |                                                 |
    |                                           ——                                                |
    |---------------------------------------------------------------------------------------------|
提升widget为ButtonGroup类型：

-> 选择widget【右键】 -> 【提升为】 ->
* 基类名称: QWidget
* 提升的类名称: ButtonGroup
* 头文件: button_group.h

-> 点击【添加】-> 【提升】

提升后:

    |-------------------------------------------game_panel----------------------------------------|
    |                                                                                             |
    |    |-------------------------------------widget(QWidget)-------------------------------|    |
    |    |                                                                                   |    |
    |    |                                   |--------score_panel_(ScorePanel)----------|    |    |
    |    |   |-----Horizontal Spacer-----|   |                                          |    |    |
    |    |                                   |------------------------------------------|    |    |
    |    |                                                                                   |    |
    |    |-----------------------------------------------------------------------------------|    |
    |                                           ——                                                |
    |                                           | Vertical Spacer                                 |
    |                                           ——                                                |
    |    |-------------------------------------button_group_(ButtonGroup)--------------------|    |
    |    |                                                                                   |    |
    |    |-----------------------------------------------------------------------------------|    |
    |                                           ——                                                |
    |                                           |                                                 |
    |                                           ——                                                |
    |---------------------------------------------------------------------------------------------|
## 按钮组窗口布局
双击 button_group.ui，添加 Stacked Widget 到窗口
### 开始按钮
#### 创建按钮
添加 Stacked Widget 到窗口 page1，并添加一个按钮。

    |----------------------------button_group_(ButtonGroup)--------------------------|
    |                                                                                |
    |    |-----------------------Stacked Widget----------start_page_, index=1---|    |
    |    |                                                                      |    |
    |    |         |---|       |== start_(QPushButton) ==|      |---|           |    |
    |    |                                                                      |    |
    |    |----------------------------------------------------------------------|    |
    |                                                                                |
    |--------------------------------------------------------------------------------|
#### 提升按钮
-> 选择 start_【右键】 -> 【提升为】 ->
* 基类名称: QPushButton
* 提升的类名称: MyButton
* 头文件: my_button.h

-> 点击【添加】-> 【提升】
#### 添加资源文件
-> 【添加新文件】 -> 选择【Qt】 -> 选择【Qt Resource File】-> 点击【选择】进入下一步
* location:
  * 文件名: res
  * ...
* ...

-> 点击【完成】。

-> 点击【添加前缀】:
* Prefix: /
* ...
-> 点击【添加文件】 -> 选择新添加的 start.png 图片。
