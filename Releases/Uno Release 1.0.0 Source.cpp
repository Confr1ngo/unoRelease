#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
bool colAvail=true,autoCard=true;
enum Color{black,blue,green,red,yellow,nullColor};
enum Content{num0,num1,num2,num3,num4,num5,num6,num7,num8,num9,rev,skip,add2,add4,colorchange,nullContent};
void SetFontColor(int ForgC,int BackC){
	WORD wColor=((BackC&0x0F)<<4)+(ForgC&0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
}
struct Card{
	enum Color color;
	enum Content content;
	void print(bool endline=false){
		switch (this->color){
			case black:if (colAvail) SetFontColor(0,15);cout<<"黑色 ";break;
			case green:if (colAvail) SetFontColor(2,15);cout<<"绿色 ";break;
			case blue:if (colAvail) SetFontColor(9,15);cout<<"蓝色 ";break;
			case red:if (colAvail) SetFontColor(12,15);cout<<"红色 ";break;
			case yellow:if (colAvail) SetFontColor(6,15);cout<<"黄色 ";break;
			case nullColor:if (colAvail) SetFontColor(0,15);cout<<"Null ";break;
			default:if (colAvail) SetFontColor(0,15);return;
		}
		switch (this->content){
			case num0:cout<<"0";break;
			case num1:cout<<"1";break;
			case num2:cout<<"2";break;
			case num3:cout<<"3";break;
			case num4:cout<<"4";break;
			case num5:cout<<"5";break;
			case num6:cout<<"6";break;
			case num7:cout<<"7";break;
			case num8:cout<<"8";break;
			case num9:cout<<"9";break;
			case rev:cout<<"反转";break;
			case skip:cout<<"跳过";break;
			case colorchange:cout<<"变色";break;
			case add2:cout<<"+2";break;
			case add4:cout<<"+4";break;
			case nullContent:if (colAvail) SetFontColor(0,15);cout<<"null";break;
			default:if (colAvail) SetFontColor(0,15);return;
		}
		if (colAvail) SetFontColor(0,15);
		if (endline) cout<<endl;
	}
	int getStrength(){
		if (this->content==add4) return 20;
		if (this->content==add2) return 10;
		if (this->content==skip) return 8;
		if (this->content==num0) return 3;
		if (this->content==colorchange) return 13;
		return 5;
	}
	Card(){
		color=nullColor;content=nullContent;
	}
	Card(enum Color a,enum Content b){
		color=a;content=b;
	}
	Card(const Card &card){
		this->color=card.color;this->content=card.content;
	}
	~Card(){}
};
bool cmp(Card a,Card b){
	if (int(a.color)>int(b.color)) return false;
	if (int(a.color)<int(b.color)) return true;
	if (int(a.content)>int(b.content)) return false;
	return true;
}
struct Pile{
	int cardCount;
	Card cards[1010];
	Card topCard(){
		if (cardCount==0) Init(),Swap();
		Card retval=cards[1];
		for (int i=2;i<=cardCount;i++){
			cards[i-1]=cards[i];
		}
		cardCount--;
		return retval;
	}
	void Init(){
		int cnt=0;
		cardCount=108;
		for (int i=13;i<=14;i++){
			for (int j=1;j<=4;j++){
				cnt++;
				cards[cnt].color=Color(0);
				cards[cnt].content=Content(i);
			}
		}
		for (int i=1;i<=4;i++){
			for (int j=0;j<=0;j++){
				for (int k=1;k<=1;k++){
					cnt++;
					cards[cnt].color=Color(i);
					cards[cnt].content=Content(j);
				}
			}
			for (int j=1;j<=12;j++){
				for (int k=1;k<=2;k++){
					cnt++;
					cards[cnt].color=Color(i);
					cards[cnt].content=Content(j);
				}
			}
		}
	}
	void Swap(){
		srand(int(time(0)));
		for (int i=1;i<=100000;i++){
			swap(cards[rand()%108+1],cards[rand()%108+1]);
		}
	}
	Pile(){Init();Swap();}
};
struct Player{
	int cardsTotal;
	Card cards[1010]; 
	void DrawCard(Pile &pile,int num){
		while (num--){
			cardsTotal++;
			cards[cardsTotal]=pile.topCard();
		}
	}
	Color strongestColor(){
		int result[5]={0,0,0,0,0};
		for (int i=1;i<=this->cardsTotal;i++){
			if (this->cards[i].color!=black) result[int(this->cards[i].color)]+=this->cards[i].getStrength();
		}
		int maxn=(result[1],max(result[2],max(result[3],result[4])));
		for (int i=1;i<=4;i++){
			if (result[i]==maxn) return Color(i);
		}
	}
	void sortCard(){
		sort(cards+1,cards+cardsTotal+1,cmp);
	}
	int getCardCount(){
		int ret=0;
		for (int i=1;i<=this->cardsTotal;i++){
			if (this->cards[i].content==colorchange) ret+=50;
			else if (this->cards[i].content==add4) ret+=50;
			else if (this->cards[i].content==skip) ret+=20;
			else if (this->cards[i].content==add2) ret+=20;
			else if (this->cards[i].content==rev) ret+=20;
			else ret+=int(this->cards[i].content);
		}
		return ret;
	} 
	Player(){cardsTotal=0;}
	~Player(){}
};
bool validOut(Card now,Card want){
	if (want.content==colorchange || want.content==add4){
		return true;
	}
	if (want.content==now.content || want.color==now.color){
		return true;
	}
	return false;
}
void game(){
	system("mode con lines=35 cols=57");
	srand(int(time(0)));
	Pile pile;
	Card now(Color(rand()%4+1),Content(rand()%13)),prev(nullColor,nullContent);
	Player players[5];
	int playernow=1,playerTurn=rand()%4+1,turn=1;
	cout<<"你是 "<<playerTurn<<" 号玩家\n请按任意键继续...\n";
	getch();
	for (int i=1;i<=4;i++){
		players[i].DrawCard(pile,7);
	}
	int jumped=0;
	while (true){
		system("cls");
		cout<<"上一张有效出牌: ";
		now.print(true);
		if (jumped==0){
			cout<<"当前是 "<<playernow<<" 号玩家\n";
			Sleep(1000);
		}
		else if (jumped==1){
			jumped=0;
			cout<<"当前是 "<<playernow<<" 号玩家\nta被跳过!该玩家现剩余 "<<players[playernow].cardsTotal<<" 张手牌!\n请按任意键继续...\n"; 
			getch();
			playernow+=turn;
			while (playernow>4) playernow-=4;
			while (playernow<1) playernow+=4;
			continue;
		}
		else if (jumped==2){
			jumped=0;
			if (now.content==add2){
				cout<<"当前是 "<<playernow<<" 号玩家(被罚2张,跳过)\n该玩家现剩余 "<<players[playernow].cardsTotal+2<<" 张手牌!\n请按任意键继续...\n";
				players[playernow].DrawCard(pile,2);
				playernow+=turn;
				while (playernow>4) playernow-=4;
				while (playernow<1) playernow+=4;
				getch();
				continue;
			}
			else if (now.content==add4){
				if (playerTurn==playernow){
					cout<<"当前是 "<<playernow<<" 号玩家(被+4中)\n";
					Sleep(500);
					cout<<"是否质疑(0/1):";
					bool zhiyi;cin>>zhiyi;
					if (zhiyi){
						int prevPerson=playernow-turn;
						while (prevPerson>4) prevPerson-=4;
						while (prevPerson<1) prevPerson+=4;
						bool flag=false;
						for (int i=1;i<=players[prevPerson].cardsTotal;i++){
							if (validOut(prev,players[prevPerson].cards[i]) && !players[prevPerson].cards[i].color==black){
								flag=true;break;
							}
						}
						if (flag){
							cout<<"质疑成功! "<<prevPerson<<" 号玩家被罚4张!\n被罚牌玩家现剩余 "<<players[prevPerson].cardsTotal+4<<" 张手牌!\n请按任意键继续...\n";
							players[prevPerson].DrawCard(pile,4);
							getch();
						}
						else{
							cout<<"质疑失败! "<<playernow<<" 号玩家被罚6张,跳过!\n该玩家现剩余 "<<players[playernow].cardsTotal+6<<" 张手牌!\n请按任意键继续...\n";
							players[playernow].DrawCard(pile,6);
							playernow+=turn;
							while (playernow>4) playernow-=4;
							while (playernow<1) playernow+=4;
							getch();
							continue;
						}
					}
					else{
						cout<<"当前是 "<<playernow<<" 号玩家(被罚4张,跳过,不质疑)\n请按任意键继续...\n";
						players[playernow].DrawCard(pile,4);
						playernow+=turn;
						while (playernow>4) playernow-=4;
						while (playernow<1) playernow+=4;
						getch();
						continue;
					}
				}
				else{
					srand(int(time(0)));
					bool zhiyi=rand()%2;
					if (zhiyi){
						int prevPerson=playernow-turn;
						while (prevPerson>4) prevPerson-=4;
						while (prevPerson<1) prevPerson+=4;
						bool flag=false;
						for (int i=1;i<=players[prevPerson].cardsTotal;i++){
							if (validOut(prev,players[prevPerson].cards[i]) && !players[prevPerson].cards[i].color==black){
								flag=true;break;
							}
						}
						if (flag){
							cout<<"质疑成功! "<<prevPerson<<" 号玩家被罚4张!\n请按任意键继续...\n";
							players[prevPerson].DrawCard(pile,4);
							getch();
						}
						else{
							cout<<"质疑失败! "<<playernow<<" 号玩家被罚6张,跳过!\n请按任意键继续...\n";
							players[playernow].DrawCard(pile,6);
							playernow+=turn;
							while (playernow>4) playernow-=4;
							while (playernow<1) playernow+=4;
							getch();
							continue;
						}
					}
					else{
						cout<<"当前是 "<<playernow<<" 号玩家(被罚4张,跳过,不质疑)\n请按任意键继续...\n";
						players[playernow].DrawCard(pile,4);
						playernow+=turn;
						while (playernow>4) playernow-=4;
						while (playernow<1) playernow+=4;
						getch();
						continue;
					}
				}
			}
			else{
				MessageBox(NULL,"错误代码:[ERR_JUMP2_CONTENT_ERROR]","错误",MB_ICONERROR | MB_OK);
				return; 
			}
		}
		bool winFlag=false;
		for (int i=1;i<=4;i++){
			if (players[i].cardsTotal==0){
				system("cls"); 
				cout<<"游戏结束, 玩家 "<<i<<" 胜利!\n\n";
				winFlag=true; 
				break;
			}
		}
		if (winFlag) break;
		if (playerTurn==playernow){
			bool validOperation=false,unoflag=false;
			while (true){
				system("cls");
				cout<<"上一张有效出牌: ";
				now.print(true);
				cout<<"+======= 您的回合 ======+\n";
				cout<<"|  请选择一项操作执行:  |\n";
				cout<<"|   1. 摸一张牌         |\n";
				cout<<"|   2. 查看牌库         |\n";
				cout<<"|   0. 结束回合         |\n";
				cout<<"+====== UNO进行时 ======+\n";
				int op;cin>>op;
				if (op==1){
					if (validOperation){
						cout<<"您已执行过操作!\n请按任意键继续...\n";
						getch();
					}
					else{
						jumped=0;
						validOperation=true;
						players[playernow].DrawCard(pile,1);
						cout<<"您摸到了 ";
						players[playernow].cards[players[playernow].cardsTotal].print(true);
						Sleep(1000);
						if (validOut(now,players[playernow].cards[players[playernow].cardsTotal])){
							cout<<"是否打出该牌(0/1):";
							int t;cin>>t;
							if (t==1){
								Card want=players[playernow].cards[players[playernow].cardsTotal];
								players[playernow].cardsTotal--;
								validOperation=true;
								if (want.content==add2){
									now=want;
									jumped=2;
								}
								else if (want.content==add4){
									cout<<"选择颜色(1=blue,2=green,3=red,4=yellow):\n";
									int t3;cin>>t3;
									if (t3>4 || t3<1) t3=rand()%4+1;
									want.color=Color(t3);
									jumped=2;
								}
								else if (want.content==rev){
									now=want;
									turn*=-1;
									jumped=0;
								}
								else if (want.content==skip){
									now=want;
									jumped=1;
								}
								else if (want.content==colorchange){
									cout<<"选择颜色(1=blue,2=green,3=red,4=yellow):\n";
									int t3;cin>>t3;
									if (t3>4 || t3<1) t3=rand()%4+1;
									want.color=Color(t3);
									jumped=0;
								}
								else{
									now=want;
									jumped=0;
								}
								prev=want;
								swap(prev,now);
							}
						}
					}
				}
				else if (op==2){
					while (true){
						system("cls");
						cout<<"上一张有效出牌: ";
						now.print(true);
						players[playernow].sortCard();
						cout<<"+===== 您的牌库 =====+\n";
						for (int i=1;i<=players[playernow].cardsTotal;i++){
							cout<<"#"<<setw(2)<<i<<": ";
							if (players[playernow].cards[i].content==add4){
								bool flag=true;
								for (int j=1;j<=players[playernow].cardsTotal;j++){
									if (players[playernow].cards[j].content!=add4 && players[playernow].cards[j].content!=colorchange && validOut(now,players[playernow].cards[j])){
										flag=false;
									}
								}
								if (!flag){
									if (colAvail){
										SetFontColor(6,15);
									}
									else{
										SetFontColor(0,15);
									}
									cout<<"(危险) ";
									SetFontColor(0,15);
								}
								else{
									if (colAvail){
										SetFontColor(2,15);
									}
									else{
										SetFontColor(0,15);
									}
									cout<<"(合法) ";
									SetFontColor(0,15);
								}
							}
							else if (colAvail && validOut(now,players[playernow].cards[i])){
								SetFontColor(2,15);
								cout<<"(合法) ";
								SetFontColor(0,15);
							}
							else if (colAvail){
								SetFontColor(12,15);
								cout<<"(无效) ";
								SetFontColor(0,15);
							}
							else if (validOut(now,players[playernow].cards[i])){
								SetFontColor(0,15);
								cout<<"(合法) ";
								SetFontColor(0,15);
							}
							else{
								SetFontColor(0,15);
								cout<<"(无效) ";
								SetFontColor(0,15);
							}
							players[playernow].cards[i].print(true);
						}
						cout<<"1.打出   2.UNO  0.退出\n";
						cout<<"提示: 没喊或错喊UNO罚2!\n";
						cout<<"+===== UNO进行时 ====+\n";
						int t;cin>>t;
						if (t==2){
							unoflag=true; 
						}
						else if (t==1){
							if (validOperation){
								cout<<"您已执行过操作!\n请按任意键继续...\n";
								getch();
								break; 
							}
							cout<<"请输入序号:";
							int t2;cin>>t2;
							Card want=players[playernow].cards[t2];
							if (validOut(now,want)){
								for (int i=t2+1;i<=players[playernow].cardsTotal;i++){
									players[playernow].cards[i-1]=players[playernow].cards[i];
								}
								players[playernow].cardsTotal--;
								validOperation=true;
								if (want.content==add2){
									now=want;
									jumped=2;
								}
								else if (want.content==add4){
									cout<<"选择颜色(1=blue,2=green,3=red,4=yellow):\n";
									int t3;cin>>t3;
									if (t3>4 || t3<1) t3=rand()%4+1;
									want.color=Color(t3);
									jumped=2;
								}
								else if (want.content==rev){
									now=want;
									turn*=-1;
									jumped=0;
								}
								else if (want.content==skip){
									now=want;
									jumped=1;
								}
								else if (want.content==colorchange){
									cout<<"选择颜色(1=blue,2=green,3=red,4=yellow):\n";
									int t3;cin>>t3;
									if (t3>4 || t3<1) t3=rand()%4+1;
									want.color=Color(t3);
									jumped=0;
								}
								else{
									now=want;
									jumped=0;
								}
								prev=want;
								swap(prev,now);
							}
							else{
								cout<<"该牌不合法!请按任意键继续...\n";
								getch();
							}
						}
						else if (t==0){
							break;
						}
					}
				}
				else if (op==0){
					if (validOperation){
						if (unoflag^(players[playernow].cardsTotal==1)){
							cout<<"错喊或未喊UNO! 罚2张!\n";
							players[playernow].DrawCard(pile,2);
						}
						break;
					}
					else{
						cout<<"您还未执行有效操作!请按任意键继续...\n";
						getch();
					}
				}
				else continue;
			}
		}
		else{
			cout<<"该玩家剩余手牌 "<<players[playernow].cardsTotal<<" 张。\n";
			cout<<"玩家正在思考出牌......";
			Sleep(2000);
			vector<int>can,priority;
			for (int i=1;i<=players[playernow].cardsTotal;i++){
				if (validOut(now,players[playernow].cards[i])) can.push_back(i);
			}
			if (can.size()==0){
				cout<<"玩家摸了一张牌...\n请按任意键继续...\n";
				getch();
				players[playernow].DrawCard(pile,1);
				if (!validOut(now,players[playernow].cards[players[playernow].cardsTotal])){
					cout<<"玩家无牌可出。请按任意键继续...\n";
					getch();
					playernow+=turn;
					while (playernow>4) playernow-=4;
					while (playernow<1) playernow+=4;
					continue;
				}
				else{
					can.push_back(players[playernow].cardsTotal);
				}
			}
			bool unoflag=false;
			if (players[playernow].cardsTotal==2){
				unoflag=1-(rand()%4/3);
			}
			for (int i=0;i<can.size();i++){
				Content cont=players[playernow].cards[can[i]].content;
				if (cont==rev || cont==add2 || cont==skip){
					priority.push_back(can[i]);
				}
			}
			for (int i=0;i<can.size();i++){
				Content cont=players[playernow].cards[can[i]].content;
				if (!(cont==rev || cont==add2 || cont==skip || cont==add4 || cont==colorchange)){
					priority.push_back(can[i]);
				}
			}
			for (int i=0;i<can.size();i++){
				Content cont=players[playernow].cards[can[i]].content;
				if (cont==add4 || cont==colorchange){
					priority.push_back(can[i]);
				}
			}
			cout<<"该玩家选择出牌: ";
			int wantInt=priority[0];
			Card want=players[playernow].cards[wantInt];
			want.print(true);
			for (int i=wantInt+1;i<=players[playernow].cardsTotal;i++){
				players[playernow].cards[i-1]=players[playernow].cards[i];
			}
			players[playernow].cardsTotal--;
			if (want.content==add2){
				now=want;
				jumped=2;
			}
			else if (want.content==add4){
				want.color=players[playernow].strongestColor();
				cout<<"颜色转为: ";
				if (want.color==1){
					if (colAvail) SetFontColor(9,15);
					cout<<"Blue\n";
					SetFontColor(0,15);
				}
				else if (want.color==2){
					if (colAvail) SetFontColor(2,15);
					cout<<"Green\n";
					SetFontColor(0,15);
				}
				else if (want.color==3){
					if (colAvail) SetFontColor(12,15);
					cout<<"Red\n";
					SetFontColor(0,15);
				}
				else if (want.color==4){
					if (colAvail) SetFontColor(6,15);
					cout<<"Yellow\n";
					SetFontColor(0,15);
				}
				jumped=2;
			}
			else if (want.content==rev){
				now=want;
				turn*=-1;
				jumped=0;
			}
			else if (want.content==skip){
				now=want;
				jumped=1;
			}
			else if (want.content==colorchange){
				want.color=players[playernow].strongestColor();
				cout<<"颜色转为: ";
				if (want.color==1){
					if (colAvail) SetFontColor(9,15);
					cout<<"Blue\n";
					SetFontColor(0,15);
				}
				else if (want.color==2){
					if (colAvail) SetFontColor(2,15);
					cout<<"Green\n";
					SetFontColor(0,15);
				}
				else if (want.color==3){
					if (colAvail) SetFontColor(12,15);
					cout<<"Red\n";
					SetFontColor(0,15);
				}
				else if (want.color==4){
					if (colAvail) SetFontColor(6,15);
					cout<<"Yellow\n";
					SetFontColor(0,15);
				}
				jumped=0;
			}
			else{
				now=want;
				jumped=0;
			}
			if (unoflag^(players[playernow].cardsTotal==1)){
				cout<<"\n未喊UNO! 罚2张!\n";
			}
			prev=want;
			swap(prev,now);
		}
		playernow+=turn;
		while (playernow>4) playernow-=4;
		while (playernow<1) playernow+=4;
		cout<<"请按任意键继续...\n";
		getch();
	}
	for (int i=1;i<=4;i++){
		cout<<"玩家 "<<i<<" 剩余 "<<players[i].cardsTotal<<" 张牌, ";
		cout<<"手牌分为: -"<<players[i].getCardCount()<<"\n\n";
	}
	for (int i=1;i<=4;i++){
		cout<<"\n玩家 "<<i<<" 剩余手牌: ";
		if (players[i].cardsTotal==0){
			cout<<"打完啦";
		}
		else{
			for (int j=1;j<=players[i].cardsTotal;j++){
				players[i].cards[j].print(false);
				cout<<"; ";
			}
		}
		cout<<"\n";
	} 
	cout<<"\n按下任意键继续...";
	getch();
	system("cls");
	return;
}
void settings(){
	system("mode con lines=6 cols=22");
	while (true){
		system("cls");
		cout<<"+====== 设置 =======+\n";
		cout<<"|   1.颜色增强:"<<(colAvail? "开":"关")<<"   |\n";
		cout<<"|   2.自动整理:"<<(autoCard? "开":"关")<<"   |\n";
		cout<<"|       0.退出      |\n";
		cout<<"+===================+\n";
		int t;cin>>t;
		if (t==0) break;
		else if (t==1) colAvail^=1;
		else if (t==2) autoCard^=1;
		else continue;
	}
}
void rules(){
	system("mode con lines=25 cols=80");
	system("cls");
	cout<<"每一段看完后请按任意键继续!\n\n\n";
	cout<<"UNO 牌分三类牌：数字牌（76 张）、功能牌（24 张）、万能牌（8 张），合计 108 张。\n";system("pause>nul");
	cout<<"\n数字牌\n数字牌由红黄蓝绿 4 色组成，每色都有数字牌 0~9。数字牌每色有 19 张，1~9 每色各 2 张，0 每色各 1 张。它们是 UNO 中最基础的卡牌。\n";system("pause>nul");
	cout<<"\n功能牌\n功能牌也由红黄蓝绿 4 色组成。它们的名称分别为\"跳过\"、\"反转\"、\"+2\"。功能牌每种 2 张，每色 6 张，它们有着特殊的功能。\n";system("pause>nul");
	cout<<"\n跳过：打出跳过后，你的下家不能出牌，轮到再下家出牌。\n反转：打出反转后，当前出牌时针顺序将反转，轮到下家（原来的上家）出牌。\n+2：打出+2后，下家将被罚摸2张牌，并且不能出牌，轮到再下家出牌。\n";system("pause>nul");
	cout<<"\n万能牌\n万能牌在UNO中有很重要的地位，具有很强的功能。它们的牌面是黑色的，且万能牌类没有颜色。名称分别为\"变色\"和\"+4\"，每种各 4 张。万能牌有许多别称，例如黑牌、王牌等。\n";system("pause>nul");
	cout<<"\n变色：打出变色牌后，你可以随意指定下家出牌的颜色（4 色中选 1），随后下家出牌。\n+4：打出+4后，你可以随意指定下家出牌的颜色，同时下家需从牌堆中罚摸 4 张牌，且不能出牌，轮到再下家出牌。\n";system("pause>nul");
	system("cls");cout<<"出牌规则：必须和上一张牌的颜色或图案相同，每次只可以出1张牌。\n";cout<<"\n例：假设参照牌为 红3，那你可以出：红色的所有牌(颜色相同)，所有颜色的3(数字相同)\n假设参照牌为 黄+2，那你可以出：黄色的所有牌(颜色相同)，其他颜色的+2(功能相同)\n当然，万能牌可以无视参照牌直接打出，并由你指定下一张牌的颜色。\n";system("pause>nul");
	cout<<"\n若玩家无牌可出，则从牌堆抽 1 张牌，若这张牌可出即可立即打出，也可以保留。否则就跳过，让下家出牌。\n";system("pause>nul");
	cout<<"\n若有玩家出完了手中所有的牌，游戏结束。\n当你在打剩1张牌的时候（即打出倒数第2张牌），喊出\"UNO\"。若玩家忘记喊\"UNO\"，要在牌堆罚抽2张牌。这是新手很易忘记的一个游戏特色，需多多注意。\n";system("pause>nul");
	cout<<"\n+4质疑：\n+4只有出牌者手中没有与参照牌同颜色(不包括同数字或功能，并且万能牌类没有颜色)才能合法出牌。\n下家有权利质疑你的出牌是否合法（可选），若你合法出牌，那么下家被罚抽6张牌。反之，你将因违规而罚抽4张牌，下家则无需抽牌。\n下家若检举成功，则仍然可以出牌；检举失败，则被跳过回合，不可以出牌。\n";system("pause>nul");
	cout<<"\n算分规则：+4 或变色计 -50 分，+2 或反转或计跳过 -20 分，数字牌按内容计分（9 计 -9 分，8 计 -8 分，以此类推，0 计 0 分），最后按照从大到小排序即为 1 至 4 名。\n";cout<<"\n---------------END---------------\n";system("pause>nul");
}
int main(){
	system("chcp 936");
	while (true){
		system("cls");
		system("color F0"); 
		system("mode con lines=7 cols=22");
		cout<<"+==== UNO 主菜单 ===+\n";
		cout<<"|     1.开始游戏    |\n";
		cout<<"|   2.设置  3.规则  |\n";
		cout<<"|       0.退出      |\n";
		cout<<"+====== GHJ制 ======+\n";
		int t;cin>>t;
		if (t==1) game();
		else if (t==2) settings();
		else if (t==3) rules();
		else if (t==0) break;
		else continue;
	}
	return 0;
}
