import Obj.Monster;
import Obj.Person;
import Obj.Package;
import Const.Const;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;
import java.util.Scanner;

class Run {

    Random rand = new Random(233);
    Scanner in = new Scanner(System.in);
    int choose;
    int level, at, guan = 1;
    int[] a = new int[500];

    void showPerson(Person player)        //展示玩家状态
    {
        System.out.printf("\n您现在的状态   职业:%s  体力:%4d  ", player.job, player.HP);
        System.out.printf("法力:%4d  攻击力:%4d  防御力:%4d\n", player.shu[0], player.shu[1], player.shu[2]);
    }

    void showPackage(Person player)        //展示玩家背包
    {
        Package x = player.xPackage;
        System.out.printf("\n您的背包里有   ");
        System.out.printf("武器:%s  红药品:%4d个  蓝药瓶:%4d个  \n", x.weapon, x.huihp, x.huifa);
    }

    void showMonster(Monster enemy, int num)    //num表示第num关的怪兽
    {
        System.out.printf("%d号怪物现在的状态         体力:%4d  ", num, enemy.HP);
        System.out.printf("法力:%4d  攻击力:%4d  防御力:%4d\n", enemy.shu[0], enemy.shu[1], enemy.shu[2]);
    }

    void showgo()        //展示作战经历 
    {
        if (at == 0) System.out.printf("您暂时还没有作战经历！加油！(-_-)\n");
        else {
            for (int i = 0; i < at; i++)
                System.out.printf("通过第%d关，累计%d个回合\n", i + 1, a[i]);
            System.out.println();
        }
    }

    int fight(Person player)        //返回值：0表示继续，1表示战死（lose），2表示通关（win）
    {

        //十个关卡，对应十个怪物。
        //每次格斗计算回合数。（第n关第m回合）每回合更新玩家属性，怪物属性
        int huihe = 0, gg;

        boolean flag = false, jinying = true;    //到了第8、9、10关，由于怪兽很强大，提示精英怪兽出现
        Monster enemy = new Monster(Const.rua(level, guan) + rand.nextInt() % 10, Const.rua(level, guan), Const.rua(level, guan), Const.rua(level, guan) - rand.nextInt() % 10);
        enemy.HP += rand.nextInt() % level + guan * rand.nextInt() % 5;

        while (true) {
//            system("cls");
            System.out.printf("******************** 第%d关 第%d回合 现在开始！********************\n", guan, ++huihe);
            showPerson(player);
            showMonster(enemy, guan);
            System.out.println();

            if (guan > 7 && jinying) {
                System.out.println("精英怪兽出现！");
                jinying = false;
            }


            while (Const.selectOperation()) {
                choose = (char) in.nextInt();
                if (choose < 1 || choose > 6) {        //不合法的选择全部去除，重新读取
                    Const.pError();
                    continue;
                } else if (choose == 4 && player.shu[0] < 20 || choose == 5 && player.shu[0] < 50 || choose == 6 && player.shu[0] < 80) {
                    Const.piError();
                    continue;
                } else if (choose == 2 && player.xPackage.huihp == 0 || choose == 3 && player.xPackage.huifa == 0) {
                    Const.pjError();
                    continue;
                }
                break;
            }

            gg = rand.nextInt() % 3 + 1;        //1,3攻击;2不操作
            if (choose == 1) {
                enemy.HP -= player.shu[1] / 10 - enemy.shu[2] / 20;
                System.out.printf("攻击成功，对怪兽造成%d点伤害！\n", player.shu[1] / 10 - enemy.shu[2] / 20);
            } else if (choose == 2) {
                player.HP += 50;
                player.xPackage.huihp--;
                System.out.printf("使用红药瓶成功，恢复50点体力！\n");
            } else if (choose == 3) {
                player.shu[0] += 50;
                player.xPackage.huifa--;
                System.out.printf("使用蓝药瓶成功，恢复50点法力！\n");
            } else if (choose == 6) {
                int tt = player.shu[1] + rand.nextInt() % 10 - enemy.shu[2] / 10;
                enemy.HP -= tt;
                player.shu[0] -= 80;
                System.out.printf("发挥无双大招，对怪兽造成%d点伤害！\n", tt);
            }

            if (gg % 2 == 1) {
                if (choose == 4) {
                    player.shu[0] -= 20;
                    System.out.printf("闪避成功，怪兽的攻击无效！\n");
                } else if (choose == 5) {
                    enemy.HP -= enemy.shu[1] / 10 - enemy.shu[2] / level;
                    player.shu[0] -= 50;
                    System.out.printf("反弹成功，怪兽对自己造成%d点伤害！\n", enemy.shu[1] / 10 - enemy.shu[2] / level);
                } else {
                    player.HP -= enemy.shu[1] / 10;
                    System.out.printf("怪兽对你造成%d点伤害\n", enemy.shu[1] / 10);
                }
            } else {
                if (choose == 4) {
                    player.shu[0] -= 20;
                    System.out.printf("怪兽没有选择进攻，技能无效，消耗20法力！\n");
                } else if (choose == 5) {
                    player.shu[0] -= 50;
                    System.out.printf("怪兽没有选择进攻，技能无效，消耗50法力！\n");
                } else System.out.println();
            }

            if (player.HP <= 0) {
                System.out.printf("\n勇士牺牲！！！\n\nGAME OVER\n");
                return 1;
            } else if (enemy.HP <= 0) {
                System.out.printf("第%d个怪兽已成功被击杀，能力获得提升，无谓的勇士继续前进吧！！！\n", guan);
                player.HP += Const.normal + rand.nextInt() % 10;        //每次击杀怪兽后各项能力获得提升 
                for (int i = 0; i < 3; i++) player.shu[i] += Const.normal + rand.nextInt() % 10;
                player.xPackage.huifa += guan + rand.nextInt() % 2;
                player.xPackage.huihp += guan + rand.nextInt() % 2;
                if (guan == 10) flag = true;            //当第10关也通过了，标记玩家胜利 
                break;
            }
            System.out.println();
            Const.pause();
        }
        a[at++] = huihe;
        guan++;
        if (flag) return 2;

        return 0;
    }

    void realRun() {
        Person player = null;
        Const.showWelcome();

        Const.pause();
//        system("cls");

        while (Const.selectDifficulty()) {
            choose = in.nextInt();
            if (choose == 1) level = Const.easy;
            else if (choose == 2) level = Const.normal;
            else if (choose == 3) level = Const.hard;
            else {
                Const.pError();
                continue;
            }
            break;
        }

        while (Const.selectProfession()) {
            choose = in.nextInt();
            switch (choose) {
                case 1:
                    player = Const.zhanshi;
                    break;
                case 2:
                    player = Const.fashi;
                    break;
                case 3:
                    player = Const.qiangshou;
                    break;
                case 4:
                    player = Const.dunwei;
                    break;
                default: {
                    Const.pError();
                    continue;
                }
            }
            break;
        }


        player.xPackage.huihp = player.xPackage.huifa = 2;        //两个药瓶数量初始化

        System.out.printf("\n请按任意键进入游戏...");
//        Const.pause();
        try {
            new BufferedReader(new InputStreamReader(System.in)).readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }

//        system("cls");
        System.out.printf("                        游戏开始！\n\n");

        while (true) {
            int flag = 0;
            System.out.printf("请选择您的操作：1:查询背包  2:查询状态  3：查询经历  4:修养法力  5:作战  0:退出游戏\n");
            choose = (char) in.nextInt();
            switch (choose) {
                case 1:
                    showPackage(player);
                    break;
                case 2:
                    showPerson(player);
                    break;
                case 3:
                    showgo();
                    break;
                case 4: {
                    int tt = player.shu[1] - player.shu[1] % 10 + 20;
                    if (player.shu[0] > tt) player.shu[0] += 50;
                    else player.shu[0] = tt;
                    System.out.printf("\n修养成功！法力恢复至%d！", player.shu[0]);
                    break;
                }
                case 5:
                    flag = fight(player);
                    break;
                case 0:
                    Const.theEnd();
                default:
                    Const.pError();
            }
            if (flag == 1) return;
            if (flag == 2) break;
            //flag为0则继续游戏，flag为1则玩家失败，flag为2时玩家胜利

//            System.out.printf("\n3秒后进行下一操作");
//            Sleep(3000);
//            system("cls");
        }

        System.out.print("\n恭喜勇士凯旋归来！！！\n\nYOU WIN...");
    }
}
