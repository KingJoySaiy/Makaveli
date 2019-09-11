#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

#define perror printf("\n（输入有误，请重新输入）\n")
#define pierror printf("\n（您的法力不足，请重新选择）\n")
#define pjerror printf("\n（您的药瓶数不足，请重新选择）\n")
#define theend {printf("\n您放弃了您的使命\n\nGAME OVER...\n");Sleep(3000);return 0;}
#define rua(level) (level)*guan+rand()%10
#define easy 20			//根据难度的不同赋予不同的参数 
#define normal 50
#define hard 80

typedef struct	
{
	const char *weapon;	//不同职业对应不同武器
	int huihp;				//红药瓶，体力+50
	int huifa;				//蓝药瓶，法力+50
	//两个药瓶初始2个，游戏中随机掉落
}bao;
typedef struct
{
	const char *job;	//共有“战士”，“魔法师”，“神枪手”，“盾卫”四个职业
	int HP;				//玩家体力，降到0则玩家lose，游戏结束
	int shu[3];			//法力，攻击力，防御力，不同职业对应基础属性不同
	bao xbao;			//玩家配有背包
}ren;
typedef struct
{
	int HP;
	int shu[3];			//怪兽有体力，法力，攻击力，防御力四项属性
	//关卡越靠后怪兽各项能力值越高
}guai;

//四个职业初始的能力值不同 
const ren zhanshi={"战士",180,90,130,100,"破碎大斧"};
const ren fashi={"魔法师",130,170,90,110,"雷光羽扇"};
const ren qiangshou={"神枪手",120,110,180,90,"龙牙刚枪"};
const ren dunwei={"盾卫",110,120,100,170,"骑盾醒剑"};
char choose;
int level;
int a[500],at;
//vector<pair<int,int> > go;

void showren(const ren &player)		//展示玩家状态
{
	printf("\n您现在的状态   职业:%s  体力:%4d  ",player.job,player.HP);
	printf("法力:%4d  攻击力:%4d  防御力:%4d\n",player.shu[0],player.shu[1],player.shu[2]);
}
void showbao(const ren &player)		//展示玩家背包
{
	bao x=player.xbao;
	printf("\n您的背包里有   ");
	printf("武器:%s  红药品:%4d个  蓝药瓶:%4d个  \n",x.weapon,x.huihp,x.huifa);
}
void showguai(const guai &enemy,const int &num)	//num表示第num关的怪兽
{
	printf("%d号怪物现在的状态         体力:%4d  ",num,enemy.HP);
	printf("法力:%4d  攻击力:%4d  防御力:%4d\n",enemy.shu[0],enemy.shu[1],enemy.shu[2]);
}
void showgo()		//展示作战经历 
{
	if(!at) printf("您暂时还没有作战经历！加油！(-_-)\n");
	else{
		for(int i=0;i<at;i++)
			printf("通过第%d关，累计%d个回合\n",i+1,a[i]);
		puts("");
	}
}

int fight(ren &player)		//返回值：0表示继续，1表示战死（lose），2表示通关（win）
{
	//十个关卡，对应十个怪物。
	//每次格斗计算回合数。（第n关第m回合）每回合更新玩家属性，怪物属性
	static int guan=1;
	int huihe=0,gg;
	int flag=0,jinying=1;	//到了第8、9、10关，由于怪兽很强大，提示精英怪兽出现 
	guai enemy={rua(level)+rand()%10,rua(level),rua(level),rua(level)-rand()%10};
	enemy.HP+=rand()%level+guan*rand()%5;

	while(1){
		system("cls");
		printf("******************** 第%d关 第%d回合 现在开始！********************\n",guan,++huihe);
		showren(player);
		showguai(enemy,guan);
		puts("");
		
		if(guan>7&&jinying) puts("精英怪兽出现！"),jinying=0; 
		reccc:
		printf("您接下来的操作是：\n");
		printf("  1:普通攻击\n");
		printf("  2:使用红药瓶回体力（体力+50）\n");
		printf("  3:使用蓝药瓶回法力（法力+50）\n");
		printf("  4:迅速闪避（将消耗20法力）\n");
		printf("  5:反弹伤害（将消耗50法力）\n");
		printf("  6:无双大招（将消耗80法力）\n");
		scanf("%c",&choose);
		getchar();
		if(choose<'1'||choose>'6'){		//不合法的选择全部去除，重新读取
			perror;
			goto reccc;
		}
		else if(choose=='4'&&player.shu[0]<20||choose=='5'&&player.shu[0]<50||choose=='6'&&player.shu[0]<80){
			pierror;
			goto reccc;
		}
		else if(choose=='2'&&!player.xbao.huihp||choose=='3'&&!player.xbao.huifa){
			pjerror;
			goto reccc;
		}
		gg=rand()%3+1;		//1,3攻击;2不操作
		if(choose=='1'){
			enemy.HP-=player.shu[1]/10-enemy.shu[2]/20;
			printf("攻击成功，对怪兽造成%d点伤害！\n",player.shu[1]/10-enemy.shu[2]/20);
		}
		else if(choose=='2'){
			player.HP+=50;
			player.xbao.huihp--;
			printf("使用红药瓶成功，恢复50点体力！\n");
		}
		else if(choose=='3'){
			player.shu[0]+=50;
			player.xbao.huifa--;
			printf("使用蓝药瓶成功，恢复50点法力！\n");
		}
		else if(choose=='6'){
			int tt=player.shu[1]+rand()%10-enemy.shu[2]/10;
			enemy.HP-=tt;
			player.shu[0]-=80;
			printf("发挥无双大招，对怪兽造成%d点伤害！\n",tt);
		}

		if(gg%2){
			if(choose=='4'){
				player.shu[0]-=20;
				printf("闪避成功，怪兽的攻击无效！\n");
			}
			else if(choose=='5'){
				enemy.HP-=enemy.shu[1]/10-enemy.shu[2]/level;
				player.shu[0]-=50;
				printf("反弹成功，怪兽对自己造成%d点伤害！\n",enemy.shu[1]/10-enemy.shu[2]/level);
			}
			else{
				player.HP-=enemy.shu[1]/10;
				printf("怪兽对你造成%d点伤害\n",enemy.shu[1]/10);
			}
		}
		else{
			if(choose=='4'){
				player.shu[0]-=20;
				printf("怪兽没有选择进攻，技能无效，消耗20法力！\n");
			}
			else if(choose=='5'){
				player.shu[0]-=50;
				printf("怪兽没有选择进攻，技能无效，消耗50法力！\n");
			}
			else puts("");
		}

		if(player.HP<=0){
			printf("\n勇士牺牲！！！\n\nGAME OVER\n");
			return 1;
		}
		else if(enemy.HP<=0){
			printf("第%d个怪兽已成功被击杀，能力获得提升，无谓的勇士继续前进吧！！！\n",guan);
			player.HP+=normal+rand()%10;		//每次击杀怪兽后各项能力获得提升 
			for(int i=0;i<3;i++) player.shu[i]+=normal+rand()%10;
			player.xbao.huifa+=guan+rand()%2;
			player.xbao.huihp+=guan+rand()%2;
			if(guan==10) flag=1;			//当第10关也通过了，标记玩家胜利 
			break;
		}
    puts("");
	system("pause");
	}
	a[at++]=huihe;
	guan++;
	if(flag) return 2;

return 0;
}

int main()
{
	ren player;
	srand((size_t)time(NULL));
	printf("*************************欢迎来到幻想王国！************************* \n");
	printf("英勇无畏的勇士！您有保卫家园，驱除怪兽的光荣使命，驱除所有怪兽吧，我们需要你！\n\n");

	printf("我们的家园遭受十个怪兽的侵扰，他们的实力会不断提升，勇士需要在生存的情况下依次击破他们\n");
	printf("根据您选择的职业，您将获得不同的属性和武器，同时背包里有2个红药瓶（生命+50）和2个蓝药瓶（法力+50），");
	printf("每次击破怪兽后会根据难度随机掉落药瓶，您的各项属性也会提升。每个回合怪兽可以攻击或不攻击，您可以选择以下7种操作：\n\n");
	printf("  1:普通攻击\n");
	printf("  2:使用红药瓶回体力（体力+50）\n");
	printf("  3:使用蓝药瓶回法力（法力+50）\n");
	printf("  4:迅速闪避（可在怪兽攻击时不收伤害）	消耗20法力\n");
	printf("  5:反弹伤害（可在怪兽攻击时反弹伤害）	消耗50法力\n");
	printf("  6:无双大招（以巨大的威力攻击怪兽）    消耗80法力\n");
	printf("\n（温馨提示：在游戏中，请按照提示输入相应的数字，否则输入无效）\n\n");

	system("pause");
	system("cls");

	rechoose1:
	printf("请选择难度:\n 1:容易 2:普通 3:困难\n\n");
	scanf("%c",&choose);
	getchar();
	if(choose=='1') level=easy;
	else if(choose=='2') level=normal;
	else if(choose=='3') level=hard;
	else{
		perror;
		goto rechoose1;
	}
	rechoose2:
	printf("请选择您的职业:\n 1:战士  2:魔法师  3:神枪手  4:盾卫\n\n");
	scanf("%c",&choose);
	getchar();
	switch(choose){
		case '1': player=zhanshi;break;
		case '2': player=fashi;break;
		case '3': player=qiangshou;break;
		case '4': player=dunwei;break;
		default:{
			perror;
			goto rechoose2;
		}
	}
	player.xbao.huihp=player.xbao.huifa=2;		//两个药瓶数量初始化

	printf("\n请按任意键进入游戏...");
	getch();		//system("pause");同样实现
	system("cls");
	printf("                        游戏开始！\n\n");

	while(1){
		int flag=0;
		printf("请选择您的操作：1:查询背包  2:查询状态  3：查询经历  4:修养法力  5:作战  0:退出游戏\n");
		scanf("%c",&choose);
		getchar();
		switch(choose){
			case '1': showbao(player);break;
			case '2': showren(player);break;
			case '3': showgo();break;
			case '4': {
				int tt=player.shu[1]-player.shu[1]%10+20;
				if(player.shu[0]>tt) player.shu[0]+=50;
				else player.shu[0]=tt;
				printf("\n修养成功！法力恢复至%d！",player.shu[0]);
				break;
			}
			case '5': flag=fight(player);break;
			case '0': theend
			default: perror;
		}
		if(flag==1) return 0; 
		if(flag==2) break;
		//flag为0则继续游戏，flag为1则玩家失败，flag为2时玩家胜利 
		
		printf("\n3秒后进行下一操作");
		Sleep(3000);
		system("cls");
	}

	printf("\n恭喜勇士凯旋归来！！！\n\nYOU WIN...");

return 0;
}




