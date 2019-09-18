package Obj;

public class Monster {
    public int HP;
    public int[] shu = new int[3];			//怪兽有体力，法力，攻击力，防御力四项属性
    //关卡越靠后怪兽各项能力值越高
    public Monster(int hp, int _0, int _1, int _2) {
        HP = hp;
        shu[0] = _0;
        shu[1] = _1;
        shu[2] = _2;
    }
}
