package Obj;

public class Person {
    public String job;	//共有“战士”，“魔法师”，“神枪手”，“盾卫”四个职业
    public int HP;				//玩家体力，降到0则玩家lose，游戏结束
    public int[] shu = new int[3];			//法力，攻击力，防御力，不同职业对应基础属性不同
    public Package xPackage = new Package();			//玩家配有背包
    public Person(String j, int hp, int _0, int _1, int _2, String p) {
        job = j;
        HP = hp;
        shu[0] = _0;
        shu[1] = _1;
        shu[2] = _2;
        xPackage.weapon = p;
    }
}
