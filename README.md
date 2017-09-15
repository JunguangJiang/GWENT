# GWENT

## 各个模块的逻辑关系
用户直接打开的是一个Dialog类。
Dialog主要用到了两个类，游戏类Game和卡组类Deck。

游戏类Game执行昆特牌的游戏逻辑，同时生成对应的图形界面。
游戏类主要调用了玩家类Player。

玩家类Player主要调用了卡牌类Card、战排类BattleField、手牌类HandCard、墓地类BattleField、牌库类Library。
卡牌类Card是各种牌的基类，在Card的基础上派生出了CardDerived（头文件在carddatabase.h中），在CardDerived的基础上派生出了各种牌类，这些牌类统一都在carddatabase.h中声明。
Card、BattleField、HandCard、Library都继承了图形类GraphicsItem，以实现绘图功能。

卡组类Deck，用于修改用户的卡组，同时在文件夹中生成对应的存储文件（Deck1.dat和Deck2.dat）。卡组类中也调用了卡牌Card。

为了便于界面的绘制，文本框text、按钮类Button、图形类GraphicsItem被以上各个类调用。
绝大多数的常数、文件路径都存储在parameter.h中。


## 程序运行的主要流程

在用户账号输入0后可以发起一场游戏，用户账号输入1后可以接受一场游戏。
用户0先洗牌、抽牌、调度，结束后，用户1再洗牌、抽牌、调度，然后由用户1进行掷筛（game.h中的函数decideOderByRandom）,然后游戏正式开始。

两个用户是通过文件“Game0.dat”进行通信的。
当用户0进行操作时（比如调度、出牌、发动牌效果等），用户1会每隔1s查询一次当前文件的状态。
如果文件中Game包的开头写着用户1，则用户1读取这个包，并开始操作，同时停止查询；
如果Game包开头不是用户1，则继续查询。
当用户1执行完操作之后，将当前游戏状态更新到文件中，然后失去当前回合，重新开始对文件的查询。

每次用户失去回合之前，都要判断当前游戏是否结束，如果当前一轮游戏结束，则向另外一个用户发送一个Game包，通知对方当前一轮结束，然后由对方用户判断接下来的出牌次序。

如果整场游戏结束，则界面会输出结果，然后通知另外一个用户游戏结束。

## 各个功能的演示方法

### 程序的开始界面
输入账号为0，可以开始一场游戏。
输入账号为1，可以接受一场游戏。
从开始界面可以进入游戏界面和修改卡组界面（建议先进入游戏，再修改卡组以节省时间）。
程序可以随意调整界面大小，图片会自动适应，但是文字不会适应，建议在全屏模式下显示。
![image](https://github.com/JunguangJiang/GWENT/blob/master/res/readmePicture/Begin.png)


### 选择牌组界面
点击各个牌，即可改变其在牌组中的数量。
金卡和银卡只可能取0、1，铜卡可以取0~3中任意一数。
当卡牌改变时，会自动改变总数的显示。
点击Leader时，卡牌上会有显示，并且只能点选一个Leader。
只有当卡牌构成满足规则时，按Save按钮才能保存且回到初始界面。
按退出键也可以回到初始界面。
![image](https://github.com/JunguangJiang/GWENT/blob/master/res/readmePicture/ModifyCard.png)

### 主游戏界面
首先是调度环节，屏幕上显示着Dispatching，双击卡牌即可调度该卡。
当调度到3张卡，或者调度时间到达30s或者用户点击左方的Pass按钮，即可结束调度。
![image](https://github.com/JunguangJiang/GWENT/blob/master/res/readmePicture/Game.png)
进入正式的游戏后，Pass按钮下方会显示当前出牌玩家，如果是己方出牌，会显示剩余的时间。

出牌的方式有两种，
对于任意站位的牌，需要将其拖动到相应的战排，同时战排的边框会变亮；
对于确定站位的牌或者没有站位的特殊牌，只需要鼠标双击即可。
![image](https://github.com/JunguangJiang/GWENT/blob/master/res/readmePicture/Game2.png)
当发动的卡牌具有特殊效果，需要点击其他卡牌或者战排时，会显示蓝色的目标指示线。

战排上会更新当前的总战斗力。
墓地和卡库会显示其中的卡的数量。

当将鼠标在卡牌上悬浮时，会在屏幕右方显示这张卡的大图和文字描述，敌方的手牌则不能显示。

当一方选择让过后，会显示其让过信息。

### 游戏结束后显示比分
![image](https://github.com/JunguangJiang/GWENT/blob/master/res/readmePicture/End.png)
