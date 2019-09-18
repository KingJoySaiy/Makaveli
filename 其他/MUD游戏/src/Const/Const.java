package Const;

import Obj.Person;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;

public class Const {

    private static Random rand = new Random(233);
    public static final int easy = 20, normal = 50, hard = 80;
    //四个职业初始的能力值不同 
    public static final Person zhanshi = new Person("战士", 180, 90, 130, 100, "破碎大斧");
    public static final Person fashi = new Person("魔法师", 130, 170, 90, 110, "雷光羽扇");
    public static final Person qiangshou = new Person("神枪手", 120, 110, 180, 90, "龙牙刚枪");
    public static final Person dunwei = new Person("盾卫", 110, 120, 100, 170, "骑盾醒剑");

    public static void pause() {
        try {
            System.out.println("按任意键继续...");
            new BufferedReader(new InputStreamReader(System.in)).read();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void showWelcome() {
        System.out.print("*************************欢迎来到幻想王国！************************* \n");
        System.out.print("英勇无畏的勇士！您有保卫家园，驱除怪兽的光荣使命，驱除所有怪兽吧，我们需要你！\n\n");

        System.out.print("我们的家园遭受十个怪兽的侵扰，他们的实力会不断提升，勇士需要在生存的情况下依次击破他们\n");
        System.out.print("根据您选择的职业，您将获得不同的属性和武器，同时背包里有2个红药瓶（生命+50）和2个蓝药瓶（法力+50），");
        System.out.print("每次击破怪兽后会根据难度随机掉落药瓶，您的各项属性也会提升。每个回合怪兽可以攻击或不攻击，您可以选择以下7种操作：\n\n");
        System.out.print("  1:普通攻击\n");
        System.out.print("  2:使用红药瓶回体力（体力+50）\n");
        System.out.print("  3:使用蓝药瓶回法力（法力+50）\n");
        System.out.print("  4:迅速闪避（可在怪兽攻击时不收伤害）	消耗20法力\n");
        System.out.print("  5:反弹伤害（可在怪兽攻击时反弹伤害）	消耗50法力\n");
        System.out.print("  6:无双大招（以巨大的威力攻击怪兽）    消耗80法力\n");
        System.out.print("\n（温馨提示：在游戏中，请按照提示输入相应的数字，否则输入无效）\n\n");
    }

    public static boolean selectOperation() {
        System.out.print("您接下来的操作是：\n");
        System.out.print("  1:普通攻击\n");
        System.out.print("  2:使用红药瓶回体力（体力+50）\n");
        System.out.print("  3:使用蓝药瓶回法力（法力+50）\n");
        System.out.print("  4:迅速闪避（将消耗20法力）\n");
        System.out.print("  5:反弹伤害（将消耗50法力）\n");
        System.out.print("  6:无双大招（将消耗80法力）\n");
        return true;
    }

    public static boolean selectDifficulty() {
        System.out.print("请选择难度:\n 1:容易 2:普通 3:困难\n\n");
        return true;
    }

    public static boolean selectProfession() {
        System.out.print("请选择您的职业:\n 1:战士  2:魔法师  3:神枪手  4:盾卫\n\n");
        return true;
    }

    public static void pError() {
        System.out.print("\n（输入有误，请重新输入）\n");
    }

    public static void piError() {
        System.out.print("\n（您的法力不足，请重新选择）\n");
    }

    public static void pjError() {
        System.out.print("\n（您的药瓶数不足，请重新选择）\n");
    }

    public static void theEnd() {
        System.out.print("\n您放弃了您的使命\n\nGAME OVER...\n");
    }

    public static int rua(int level, int guan) {
        return (level) * guan + rand.nextInt() % 10;
    }
}
