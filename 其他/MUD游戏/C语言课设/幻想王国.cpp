#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

#define perror printf("\n�������������������룩\n")
#define pierror printf("\n�����ķ������㣬������ѡ��\n")
#define pjerror printf("\n������ҩƿ�����㣬������ѡ��\n")
#define theend {printf("\n������������ʹ��\n\nGAME OVER...\n");Sleep(3000);return 0;}
#define rua(level) (level)*guan+rand()%10
#define easy 20			//�����ѶȵĲ�ͬ���費ͬ�Ĳ��� 
#define normal 50
#define hard 80

typedef struct	
{
	const char *weapon;	//��ְͬҵ��Ӧ��ͬ����
	int huihp;				//��ҩƿ������+50
	int huifa;				//��ҩƿ������+50
	//����ҩƿ��ʼ2������Ϸ���������
}bao;
typedef struct
{
	const char *job;	//���С�սʿ������ħ��ʦ��������ǹ�֡������������ĸ�ְҵ
	int HP;				//�������������0�����lose����Ϸ����
	int shu[3];			//������������������������ְͬҵ��Ӧ�������Բ�ͬ
	bao xbao;			//������б���
}ren;
typedef struct
{
	int HP;
	int shu[3];			//����������������������������������������
	//�ؿ�Խ������޸�������ֵԽ��
}guai;

//�ĸ�ְҵ��ʼ������ֵ��ͬ 
const ren zhanshi={"սʿ",180,90,130,100,"�����"};
const ren fashi={"ħ��ʦ",130,170,90,110,"�׹�����"};
const ren qiangshou={"��ǹ��",120,110,180,90,"������ǹ"};
const ren dunwei={"����",110,120,100,170,"����ѽ�"};
char choose;
int level;
int a[500],at;
//vector<pair<int,int> > go;

void showren(const ren &player)		//չʾ���״̬
{
	printf("\n�����ڵ�״̬   ְҵ:%s  ����:%4d  ",player.job,player.HP);
	printf("����:%4d  ������:%4d  ������:%4d\n",player.shu[0],player.shu[1],player.shu[2]);
}
void showbao(const ren &player)		//չʾ��ұ���
{
	bao x=player.xbao;
	printf("\n���ı�������   ");
	printf("����:%s  ��ҩƷ:%4d��  ��ҩƿ:%4d��  \n",x.weapon,x.huihp,x.huifa);
}
void showguai(const guai &enemy,const int &num)	//num��ʾ��num�صĹ���
{
	printf("%d�Ź������ڵ�״̬         ����:%4d  ",num,enemy.HP);
	printf("����:%4d  ������:%4d  ������:%4d\n",enemy.shu[0],enemy.shu[1],enemy.shu[2]);
}
void showgo()		//չʾ��ս���� 
{
	if(!at) printf("����ʱ��û����ս���������ͣ�(-_-)\n");
	else{
		for(int i=0;i<at;i++)
			printf("ͨ����%d�أ��ۼ�%d���غ�\n",i+1,a[i]);
		puts("");
	}
}

int fight(ren &player)		//����ֵ��0��ʾ������1��ʾս����lose����2��ʾͨ�أ�win��
{
	//ʮ���ؿ�����Ӧʮ�����
	//ÿ�θ񶷼���غ���������n�ص�m�غϣ�ÿ�غϸ���������ԣ���������
	static int guan=1;
	int huihe=0,gg;
	int flag=0,jinying=1;	//���˵�8��9��10�أ����ڹ��޺�ǿ����ʾ��Ӣ���޳��� 
	guai enemy={rua(level)+rand()%10,rua(level),rua(level),rua(level)-rand()%10};
	enemy.HP+=rand()%level+guan*rand()%5;

	while(1){
		system("cls");
		printf("******************** ��%d�� ��%d�غ� ���ڿ�ʼ��********************\n",guan,++huihe);
		showren(player);
		showguai(enemy,guan);
		puts("");
		
		if(guan>7&&jinying) puts("��Ӣ���޳��֣�"),jinying=0; 
		reccc:
		printf("���������Ĳ����ǣ�\n");
		printf("  1:��ͨ����\n");
		printf("  2:ʹ�ú�ҩƿ������������+50��\n");
		printf("  3:ʹ����ҩƿ�ط���������+50��\n");
		printf("  4:Ѹ�����ܣ�������20������\n");
		printf("  5:�����˺���������50������\n");
		printf("  6:��˫���У�������80������\n");
		scanf("%c",&choose);
		getchar();
		if(choose<'1'||choose>'6'){		//���Ϸ���ѡ��ȫ��ȥ�������¶�ȡ
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
		gg=rand()%3+1;		//1,3����;2������
		if(choose=='1'){
			enemy.HP-=player.shu[1]/10-enemy.shu[2]/20;
			printf("�����ɹ����Թ������%d���˺���\n",player.shu[1]/10-enemy.shu[2]/20);
		}
		else if(choose=='2'){
			player.HP+=50;
			player.xbao.huihp--;
			printf("ʹ�ú�ҩƿ�ɹ����ָ�50��������\n");
		}
		else if(choose=='3'){
			player.shu[0]+=50;
			player.xbao.huifa--;
			printf("ʹ����ҩƿ�ɹ����ָ�50�㷨����\n");
		}
		else if(choose=='6'){
			int tt=player.shu[1]+rand()%10-enemy.shu[2]/10;
			enemy.HP-=tt;
			player.shu[0]-=80;
			printf("������˫���У��Թ������%d���˺���\n",tt);
		}

		if(gg%2){
			if(choose=='4'){
				player.shu[0]-=20;
				printf("���ܳɹ������޵Ĺ�����Ч��\n");
			}
			else if(choose=='5'){
				enemy.HP-=enemy.shu[1]/10-enemy.shu[2]/level;
				player.shu[0]-=50;
				printf("�����ɹ������޶��Լ����%d���˺���\n",enemy.shu[1]/10-enemy.shu[2]/level);
			}
			else{
				player.HP-=enemy.shu[1]/10;
				printf("���޶������%d���˺�\n",enemy.shu[1]/10);
			}
		}
		else{
			if(choose=='4'){
				player.shu[0]-=20;
				printf("����û��ѡ�������������Ч������20������\n");
			}
			else if(choose=='5'){
				player.shu[0]-=50;
				printf("����û��ѡ�������������Ч������50������\n");
			}
			else puts("");
		}

		if(player.HP<=0){
			printf("\n��ʿ����������\n\nGAME OVER\n");
			return 1;
		}
		else if(enemy.HP<=0){
			printf("��%d�������ѳɹ�����ɱ�����������������ν����ʿ����ǰ���ɣ�����\n",guan);
			player.HP+=normal+rand()%10;		//ÿ�λ�ɱ���޺��������������� 
			for(int i=0;i<3;i++) player.shu[i]+=normal+rand()%10;
			player.xbao.huifa+=guan+rand()%2;
			player.xbao.huihp+=guan+rand()%2;
			if(guan==10) flag=1;			//����10��Ҳͨ���ˣ�������ʤ�� 
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
	printf("*************************��ӭ��������������************************* \n");
	printf("Ӣ����η����ʿ�����б�����԰���������޵Ĺ���ʹ�����������й��ްɣ�������Ҫ�㣡\n\n");

	printf("���ǵļ�԰����ʮ�����޵����ţ����ǵ�ʵ���᲻����������ʿ��Ҫ���������������λ�������\n");
	printf("������ѡ���ְҵ��������ò�ͬ�����Ժ�������ͬʱ��������2����ҩƿ������+50����2����ҩƿ������+50����");
	printf("ÿ�λ��ƹ��޺������Ѷ��������ҩƿ�����ĸ�������Ҳ��������ÿ���غϹ��޿��Թ����򲻹�����������ѡ������7�ֲ�����\n\n");
	printf("  1:��ͨ����\n");
	printf("  2:ʹ�ú�ҩƿ������������+50��\n");
	printf("  3:ʹ����ҩƿ�ط���������+50��\n");
	printf("  4:Ѹ�����ܣ����ڹ��޹���ʱ�����˺���	����20����\n");
	printf("  5:�����˺������ڹ��޹���ʱ�����˺���	����50����\n");
	printf("  6:��˫���У��Ծ޴�������������ޣ�    ����80����\n");
	printf("\n����ܰ��ʾ������Ϸ�У��밴����ʾ������Ӧ�����֣�����������Ч��\n\n");

	system("pause");
	system("cls");

	rechoose1:
	printf("��ѡ���Ѷ�:\n 1:���� 2:��ͨ 3:����\n\n");
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
	printf("��ѡ������ְҵ:\n 1:սʿ  2:ħ��ʦ  3:��ǹ��  4:����\n\n");
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
	player.xbao.huihp=player.xbao.huifa=2;		//����ҩƿ������ʼ��

	printf("\n�밴�����������Ϸ...");
	getch();		//system("pause");ͬ��ʵ��
	system("cls");
	printf("                        ��Ϸ��ʼ��\n\n");

	while(1){
		int flag=0;
		printf("��ѡ�����Ĳ�����1:��ѯ����  2:��ѯ״̬  3����ѯ����  4:��������  5:��ս  0:�˳���Ϸ\n");
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
				printf("\n�����ɹ��������ָ���%d��",player.shu[0]);
				break;
			}
			case '5': flag=fight(player);break;
			case '0': theend
			default: perror;
		}
		if(flag==1) return 0; 
		if(flag==2) break;
		//flagΪ0�������Ϸ��flagΪ1�����ʧ�ܣ�flagΪ2ʱ���ʤ�� 
		
		printf("\n3��������һ����");
		Sleep(3000);
		system("cls");
	}

	printf("\n��ϲ��ʿ��������������\n\nYOU WIN...");

return 0;
}




