### $\textbf{Uno RC4 Build 0210}$ 说明文档

#### 请严格按照程序要求的输入操作，否则造成的后果作者概不负责！

---

#### $\sect 0$   $\text{What's New}$

##### $\sect 0.1$  修复的 $\text{Feature}$

**本次更新总计修复了 $2$ 个 $\text{Feature}$。**

**RC 阶段发现的 $\text{Feature}$ （$2$）**

###### $\text{UNO-0003}$  最后一位玩家打出的 +2/+4 不会被判定。

###### $\text{UNO-0004}$  黑色变色牌在屏幕上显示不下。

##### $\sect 0.2$  优化的特性

###### $\text{OPT-0002}$  将卡牌汉化。

###### $\text{OPT-0003}$  自动整理手牌功能（设置中可调整）。

###### $\text{OPT-0004}$  游戏结束后展示所有人的手牌。

---

#### $\sect 1$   下载和运行

##### $\sect 1.1$ 下载

请从 [https://www.luogu.com.cn/problem/U203031](https://www.luogu.com.cn/problem/U203031) 或 [https://www.github.com/gonghengjie/unoRelease/releases](https://www.github.com/gonghengjie/unoRelease/releases) 下载最新的 $\textbf{RC4}$ 版本文件，包含 $\textbf{x86}$ 和 $\textbf{x64}$ 两个版本。

- 如果您的电脑为 $16\ \text{bit}$，那么你可以试试买一块新的主板。
- 如果您的电脑为 $32\ \text{bit}$，那么你可以下载 $\textbf{x86}$ 版本。 
- 如果您的电脑为 $64\ \text{bit}$，那么可以下载 $\textbf{x86}$ 或 $\textbf{x64}$ 两个版本。（建议使用 $\textbf{x64}$）
- 如果您的电脑为 $128\ \text{bit}$，那么目前没有适合你的版本。你可以试试用兼容模式运行。

##### $\sect 1.2$ 运行

1. 双击打开程序，不需要以管理员权限运行；
2. 开始玩；
3. ~~注意你身旁的监护人或者老师。~~

---

#### $\sect 2$   UNO 简介（以下摘自百度百科）

##### $\sect 2.1$ 卡牌

UNO牌分三类牌：数字牌（76张）、功能牌（24张）、万能牌（8张），合计108张。

###### $\sect 2.1.1$ 数字牌

数字牌由红黄蓝绿4色组成，每色都有数字牌0~9。数字牌每色有19张，1~9每色各2张，0每色各1张。它们是UNO中最基础的卡牌。

###### $\sect 2.1.2$ 功能牌

功能牌也由红黄蓝绿4色组成。它们的名称分别为"跳过"、"反转"、"+2/+4"。功能牌每种8张，每色2张，它们有着特殊的功能。

跳过：打出跳过后，你的下家不能出牌，轮到再下家出牌。

反转：打出反转后，当前出牌时针顺序将反转，轮到下家（原来的上家）出牌。

+2：打出+2后，下家将被罚摸2张牌，并且不能出牌，轮到再下家出牌。

###### $\sect 2.1.3$ 万能牌

万能牌在UNO中有很重要的地位，具有很强的功能。它们的牌面是黑色的，且万能牌类没有颜色。名称分别为“变色”和“+4”，每种各4张。万能牌有许多别称，例如黑牌、王牌等。

变色：打出变色牌后，你可以随意指定下家出牌的颜色（4色中选1），随后下家出牌**。**

+4：打出+4后，你可以随意指定下家出牌的颜色，同时下家需从牌堆中罚摸4张牌，且不能出牌，轮到再下家出牌。

注：+4的质疑规则下面会补充。

##### $\sect 2.2$ 玩法

UNO的获胜条件是：出完自己手中所有的牌。

每人取牌7张，其余作为牌堆。从牌堆中取出首张数字牌并依据此牌出牌，游戏开始。

**出牌规则：必须和弃牌堆上一张牌（参照牌）的颜色或图案相同，每次只可以出1张牌。**

举例：假设参照牌为”红3“，那你可以出：红色的所有牌(颜色相同)，所有颜色的3(数字相同)；假设参照牌为”黄+2“，那你可以出：黄色的所有牌(颜色相同)，其他颜色的+2(功能相同)。当然，万能牌可以无视参照牌直接打出，并由你指定下一张牌的颜色。

若玩家无牌可出，则从牌堆抽1张牌，若这张牌可出即可立即打出，也可以保留。否则就跳过，让下家出牌。

当你在打剩1张牌的时候（即打出倒数第2张牌），**喊出"UNO"（读作“乌诺”，类似于斗地主的”报单“）**。若玩家忘记喊"UNO"，要在牌堆罚抽2张牌。

若有玩家出完了手中所有的牌，游戏结束。

##### $\sect 2.3$ 拓展规则

**1. +4质疑**

+4只有出牌者手中没有与参照牌同颜色(不包括同数字或功能，并且万能牌类没有颜色)才能合法出牌。下家有权利质疑你的出牌是否合法，这时你得把手中的牌给他看。若你合法出牌，那么下家被罚抽 $6$ 张牌。反之，你将因违规而罚抽 $4$ 张牌，下家则无需抽牌。

下家若检举成功，则仍然可以出牌；检举失败，则被跳过回合，不可以出牌。

**2. 计分规则**

在有人获胜后，玩家各自展示自己的手牌，依照如下表格进行计算。

|     牌型     |                  分数                   |
| :----------: | :-------------------------------------: |
|    数字牌    | 数字从 $0$ 至 $9$ 对应分值 $0$  至 $-9$ |
| 跳过/反转/+2 |                  $-20$                  |
|   变色/+4    |                  $-50$                  |

##### $\sect 2.4$ 本程序采用的拓展和备注

1. +4 质疑时万能牌不计入范围。
2. （强调第二遍）请严格按照程序要求的输入操作，否则造成的后果作者概不负责！。

---

#### $\sect 3$   程序除了进行游戏以外的基本操作

##### $\sect 3.1$  规则界面

在主菜单按下 $3$ 并回车即可进入规则界面。在规则界面你可以看到 $\sect 2$ 的这段话。

每次停顿后，请按下任意键查看下一部分。

##### $\sect 3.2$  设置界面

在主菜单按下 $2$ 并回车即可进入设置界面。

当前只有一个设置选项：颜色增强。

###### $\sect 3.2.1$ 颜色增强

颜色增强功能可以让游戏画面具有丰富的颜色。

##### $\sect 3.3$  退出

在主菜单按下 $0$ 并回车即可退出程序。

---

#### $\sect 4$   进行游戏

在主菜单按下 $1$ 并回车即可开始游戏。

首先，您会看到您是几号玩家。通常，游戏是从 $1$ 号玩家开始，到 $4$ 号玩家完成一轮，接下来继续从 $1$ 号玩家开始。但是反转牌可以改变这个顺序，敬请注意。

##### $\sect 4.1$  非您的回合

在非您的回合，您可以看到：当前玩家编号、当前出牌玩家出的牌、当前出牌玩家牌的数量和上一张有效出牌；您不能进行操作，除非您被 +4 时可选择是否质疑。

##### $\sect 4.2$  您的回合

在您的回合，您有 $3$ 种选项。

输入 $0$：结束回合。当且仅当进行有效操作后才可以执行。当您错喊或未喊UNO时，会在这个阶段被罚摸 $2$ 张牌。

输入 $1$：摸一张牌。当且仅当您没有进行有效操作时才可以执行。摸到的牌可以被打出，但仅可以打出摸到的牌。另外，摸到牌后您不能进入牌库出这张牌。该操作视为进行有效操作。

输入 $2$：查看牌库。

- 在牌库中输入 $0$：退出牌库，进入菜单界面。
- 在牌库中输入 $2$：喊UNO。注意：该操作不可撤销，不视为进行有效操作。
- 在牌库中输入 $1$：打出一张牌库中的牌，该操作视为进行有效操作，当且仅当打出合法或危险牌时。注意：非法牌不可打出，标注了危险的 +4 牌（表示有其他合法的非黑色牌）可以被质疑导致您 +4。
