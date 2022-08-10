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
			case black:if (colAvail) SetFontColor(0,15);cout<<"��ɫ ";break;
			case green:if (colAvail) SetFontColor(2,15);cout<<"��ɫ ";break;
			case blue:if (colAvail) SetFontColor(9,15);cout<<"��ɫ ";break;
			case red:if (colAvail) SetFontColor(12,15);cout<<"��ɫ ";break;
			case yellow:if (colAvail) SetFontColor(6,15);cout<<"��ɫ ";break;
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
			case rev:cout<<"��ת";break;
			case skip:cout<<"����";break;
			case colorchange:cout<<"��ɫ";break;
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
	cout<<"���� "<<playerTurn<<" �����\n�밴���������...\n";
	getch();
	for (int i=1;i<=4;i++){
		players[i].DrawCard(pile,7);
	}
	int jumped=0;
	while (true){
		system("cls");
		cout<<"��һ����Ч����: ";
		now.print(true);
		if (jumped==0){
			cout<<"��ǰ�� "<<playernow<<" �����\n";
			Sleep(1000);
		}
		else if (jumped==1){
			jumped=0;
			cout<<"��ǰ�� "<<playernow<<" �����\nta������!�������ʣ�� "<<players[playernow].cardsTotal<<" ������!\n�밴���������...\n"; 
			getch();
			playernow+=turn;
			while (playernow>4) playernow-=4;
			while (playernow<1) playernow+=4;
			continue;
		}
		else if (jumped==2){
			jumped=0;
			if (now.content==add2){
				cout<<"��ǰ�� "<<playernow<<" �����(����2��,����)\n�������ʣ�� "<<players[playernow].cardsTotal+2<<" ������!\n�밴���������...\n";
				players[playernow].DrawCard(pile,2);
				playernow+=turn;
				while (playernow>4) playernow-=4;
				while (playernow<1) playernow+=4;
				getch();
				continue;
			}
			else if (now.content==add4){
				if (playerTurn==playernow){
					cout<<"��ǰ�� "<<playernow<<" �����(��+4��)\n";
					Sleep(500);
					cout<<"�Ƿ�����(0/1):";
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
							cout<<"���ɳɹ�! "<<prevPerson<<" ����ұ���4��!\n�����������ʣ�� "<<players[prevPerson].cardsTotal+4<<" ������!\n�밴���������...\n";
							players[prevPerson].DrawCard(pile,4);
							getch();
						}
						else{
							cout<<"����ʧ��! "<<playernow<<" ����ұ���6��,����!\n�������ʣ�� "<<players[playernow].cardsTotal+6<<" ������!\n�밴���������...\n";
							players[playernow].DrawCard(pile,6);
							playernow+=turn;
							while (playernow>4) playernow-=4;
							while (playernow<1) playernow+=4;
							getch();
							continue;
						}
					}
					else{
						cout<<"��ǰ�� "<<playernow<<" �����(����4��,����,������)\n�밴���������...\n";
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
							cout<<"���ɳɹ�! "<<prevPerson<<" ����ұ���4��!\n�밴���������...\n";
							players[prevPerson].DrawCard(pile,4);
							getch();
						}
						else{
							cout<<"����ʧ��! "<<playernow<<" ����ұ���6��,����!\n�밴���������...\n";
							players[playernow].DrawCard(pile,6);
							playernow+=turn;
							while (playernow>4) playernow-=4;
							while (playernow<1) playernow+=4;
							getch();
							continue;
						}
					}
					else{
						cout<<"��ǰ�� "<<playernow<<" �����(����4��,����,������)\n�밴���������...\n";
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
				MessageBox(NULL,"�������:[ERR_JUMP2_CONTENT_ERROR]","����",MB_ICONERROR | MB_OK);
				return; 
			}
		}
		bool winFlag=false;
		for (int i=1;i<=4;i++){
			if (players[i].cardsTotal==0){
				system("cls"); 
				cout<<"��Ϸ����, ��� "<<i<<" ʤ��!\n\n";
				winFlag=true; 
				break;
			}
		}
		if (winFlag) break;
		if (playerTurn==playernow){
			bool validOperation=false,unoflag=false;
			while (true){
				system("cls");
				cout<<"��һ����Ч����: ";
				now.print(true);
				cout<<"+======= ���Ļغ� ======+\n";
				cout<<"|  ��ѡ��һ�����ִ��:  |\n";
				cout<<"|   1. ��һ����         |\n";
				cout<<"|   2. �鿴�ƿ�         |\n";
				cout<<"|   0. �����غ�         |\n";
				cout<<"+====== UNO����ʱ ======+\n";
				int op;cin>>op;
				if (op==1){
					if (validOperation){
						cout<<"����ִ�й�����!\n�밴���������...\n";
						getch();
					}
					else{
						jumped=0;
						validOperation=true;
						players[playernow].DrawCard(pile,1);
						cout<<"�������� ";
						players[playernow].cards[players[playernow].cardsTotal].print(true);
						Sleep(1000);
						if (validOut(now,players[playernow].cards[players[playernow].cardsTotal])){
							cout<<"�Ƿ�������(0/1):";
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
									cout<<"ѡ����ɫ(1=blue,2=green,3=red,4=yellow):\n";
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
									cout<<"ѡ����ɫ(1=blue,2=green,3=red,4=yellow):\n";
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
						cout<<"��һ����Ч����: ";
						now.print(true);
						players[playernow].sortCard();
						cout<<"+===== �����ƿ� =====+\n";
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
									cout<<"(Σ��) ";
									SetFontColor(0,15);
								}
								else{
									if (colAvail){
										SetFontColor(2,15);
									}
									else{
										SetFontColor(0,15);
									}
									cout<<"(�Ϸ�) ";
									SetFontColor(0,15);
								}
							}
							else if (colAvail && validOut(now,players[playernow].cards[i])){
								SetFontColor(2,15);
								cout<<"(�Ϸ�) ";
								SetFontColor(0,15);
							}
							else if (colAvail){
								SetFontColor(12,15);
								cout<<"(��Ч) ";
								SetFontColor(0,15);
							}
							else if (validOut(now,players[playernow].cards[i])){
								SetFontColor(0,15);
								cout<<"(�Ϸ�) ";
								SetFontColor(0,15);
							}
							else{
								SetFontColor(0,15);
								cout<<"(��Ч) ";
								SetFontColor(0,15);
							}
							players[playernow].cards[i].print(true);
						}
						cout<<"1.���   2.UNO  0.�˳�\n";
						cout<<"��ʾ: û�����UNO��2!\n";
						cout<<"+===== UNO����ʱ ====+\n";
						int t;cin>>t;
						if (t==2){
							unoflag=true; 
						}
						else if (t==1){
							if (validOperation){
								cout<<"����ִ�й�����!\n�밴���������...\n";
								getch();
								break; 
							}
							cout<<"���������:";
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
									cout<<"ѡ����ɫ(1=blue,2=green,3=red,4=yellow):\n";
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
									cout<<"ѡ����ɫ(1=blue,2=green,3=red,4=yellow):\n";
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
								cout<<"���Ʋ��Ϸ�!�밴���������...\n";
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
							cout<<"����δ��UNO! ��2��!\n";
							players[playernow].DrawCard(pile,2);
						}
						break;
					}
					else{
						cout<<"����δִ����Ч����!�밴���������...\n";
						getch();
					}
				}
				else continue;
			}
		}
		else{
			cout<<"�����ʣ������ "<<players[playernow].cardsTotal<<" �š�\n";
			cout<<"�������˼������......";
			Sleep(2000);
			vector<int>can,priority;
			for (int i=1;i<=players[playernow].cardsTotal;i++){
				if (validOut(now,players[playernow].cards[i])) can.push_back(i);
			}
			if (can.size()==0){
				cout<<"�������һ����...\n�밴���������...\n";
				getch();
				players[playernow].DrawCard(pile,1);
				if (!validOut(now,players[playernow].cards[players[playernow].cardsTotal])){
					cout<<"������ƿɳ����밴���������...\n";
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
			cout<<"�����ѡ�����: ";
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
				cout<<"��ɫתΪ: ";
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
				cout<<"��ɫתΪ: ";
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
				cout<<"\nδ��UNO! ��2��!\n";
			}
			prev=want;
			swap(prev,now);
		}
		playernow+=turn;
		while (playernow>4) playernow-=4;
		while (playernow<1) playernow+=4;
		cout<<"�밴���������...\n";
		getch();
	}
	for (int i=1;i<=4;i++){
		cout<<"��� "<<i<<" ʣ�� "<<players[i].cardsTotal<<" ����, ";
		cout<<"���Ʒ�Ϊ: -"<<players[i].getCardCount()<<"\n\n";
	}
	for (int i=1;i<=4;i++){
		cout<<"\n��� "<<i<<" ʣ������: ";
		if (players[i].cardsTotal==0){
			cout<<"������";
		}
		else{
			for (int j=1;j<=players[i].cardsTotal;j++){
				players[i].cards[j].print(false);
				cout<<"; ";
			}
		}
		cout<<"\n";
	} 
	cout<<"\n�������������...";
	getch();
	system("cls");
	return;
}
void settings(){
	system("mode con lines=6 cols=22");
	while (true){
		system("cls");
		cout<<"+====== ���� =======+\n";
		cout<<"|   1.��ɫ��ǿ:"<<(colAvail? "��":"��")<<"   |\n";
		cout<<"|   2.�Զ�����:"<<(autoCard? "��":"��")<<"   |\n";
		cout<<"|       0.�˳�      |\n";
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
	cout<<"ÿһ�ο�����밴���������!\n\n\n";
	cout<<"UNO �Ʒ������ƣ������ƣ�76 �ţ��������ƣ�24 �ţ��������ƣ�8 �ţ����ϼ� 108 �š�\n";system("pause>nul");
	cout<<"\n������\n�������ɺ������ 4 ɫ��ɣ�ÿɫ���������� 0~9��������ÿɫ�� 19 �ţ�1~9 ÿɫ�� 2 �ţ�0 ÿɫ�� 1 �š������� UNO ��������Ŀ��ơ�\n";system("pause>nul");
	cout<<"\n������\n������Ҳ�ɺ������ 4 ɫ��ɡ����ǵ����Ʒֱ�Ϊ\"����\"��\"��ת\"��\"+2\"��������ÿ�� 2 �ţ�ÿɫ 6 �ţ�������������Ĺ��ܡ�\n";system("pause>nul");
	cout<<"\n�������������������¼Ҳ��ܳ��ƣ��ֵ����¼ҳ��ơ�\n��ת�������ת�󣬵�ǰ����ʱ��˳�򽫷�ת���ֵ��¼ң�ԭ�����ϼң����ơ�\n+2�����+2���¼ҽ�������2���ƣ����Ҳ��ܳ��ƣ��ֵ����¼ҳ��ơ�\n";system("pause>nul");
	cout<<"\n������\n��������UNO���к���Ҫ�ĵ�λ�����к�ǿ�Ĺ��ܡ����ǵ������Ǻ�ɫ�ģ�����������û����ɫ�����Ʒֱ�Ϊ\"��ɫ\"��\"+4\"��ÿ�ָ� 4 �š�������������ƣ�������ơ����Ƶȡ�\n";system("pause>nul");
	cout<<"\n��ɫ�������ɫ�ƺ����������ָ���¼ҳ��Ƶ���ɫ��4 ɫ��ѡ 1��������¼ҳ��ơ�\n+4�����+4�����������ָ���¼ҳ��Ƶ���ɫ��ͬʱ�¼�����ƶ��з��� 4 ���ƣ��Ҳ��ܳ��ƣ��ֵ����¼ҳ��ơ�\n";system("pause>nul");
	system("cls");cout<<"���ƹ��򣺱������һ���Ƶ���ɫ��ͼ����ͬ��ÿ��ֻ���Գ�1���ơ�\n";cout<<"\n�������������Ϊ ��3��������Գ�����ɫ��������(��ɫ��ͬ)��������ɫ��3(������ͬ)\n���������Ϊ ��+2��������Գ�����ɫ��������(��ɫ��ͬ)��������ɫ��+2(������ͬ)\n��Ȼ�������ƿ������Ӳ�����ֱ�Ӵ����������ָ����һ���Ƶ���ɫ��\n";system("pause>nul");
	cout<<"\n��������ƿɳ�������ƶѳ� 1 ���ƣ��������ƿɳ��������������Ҳ���Ա�������������������¼ҳ��ơ�\n";system("pause>nul");
	cout<<"\n������ҳ������������е��ƣ���Ϸ������\n�����ڴ�ʣ1���Ƶ�ʱ�򣨼����������2���ƣ�������\"UNO\"����������Ǻ�\"UNO\"��Ҫ���ƶѷ���2���ơ��������ֺ������ǵ�һ����Ϸ��ɫ������ע�⡣\n";system("pause>nul");
	cout<<"\n+4���ɣ�\n+4ֻ�г���������û���������ͬ��ɫ(������ͬ���ֻ��ܣ�������������û����ɫ)���ܺϷ����ơ�\n�¼���Ȩ��������ĳ����Ƿ�Ϸ�����ѡ��������Ϸ����ƣ���ô�¼ұ�����6���ơ���֮���㽫��Υ�������4���ƣ��¼���������ơ�\n�¼�����ٳɹ�������Ȼ���Գ��ƣ����ʧ�ܣ��������غϣ������Գ��ơ�\n";system("pause>nul");
	cout<<"\n��ֹ���+4 ���ɫ�� -50 �֣�+2 ��ת������� -20 �֣������ư����ݼƷ֣�9 �� -9 �֣�8 �� -8 �֣��Դ����ƣ�0 �� 0 �֣�������մӴ�С����Ϊ 1 �� 4 ����\n";cout<<"\n---------------END---------------\n";system("pause>nul");
}
int main(){
	system("chcp 936");
	while (true){
		system("cls");
		system("color F0"); 
		system("mode con lines=7 cols=22");
		cout<<"+==== UNO ���˵� ===+\n";
		cout<<"|     1.��ʼ��Ϸ    |\n";
		cout<<"|   2.����  3.����  |\n";
		cout<<"|       0.�˳�      |\n";
		cout<<"+====== GHJ�� ======+\n";
		int t;cin>>t;
		if (t==1) game();
		else if (t==2) settings();
		else if (t==3) rules();
		else if (t==0) break;
		else continue;
	}
	return 0;
}
