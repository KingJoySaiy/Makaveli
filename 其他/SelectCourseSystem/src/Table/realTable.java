package Table;

import java.util.Objects;

public class realTable {

    private int sWeek, eWeek, day;  //起始周，结束周，星期几
    private String cName, location; //课程名，上课地点
    private int sTime, length;      //上课时间，连上几节

    public int getsWeek() {
        return sWeek;
    }

    @Override
    public String toString() {
        return "realTable{" +
                "sWeek=" + sWeek +
                ", eWeek=" + eWeek +
                ", day=" + day +
                ", cName='" + cName + '\'' +
                ", location='" + location + '\'' +
                ", sTime=" + sTime +
                ", length=" + length +
                '}';
    }

    public void setsWeek(int sWeek) {
        this.sWeek = sWeek;
    }

    public int geteWeek() {
        return eWeek;
    }

    public void seteWeek(int eWeek) {
        this.eWeek = eWeek;
    }

    public int getDay() {
        return day;
    }

    public void setDay(int day) {
        this.day = day;
    }

    public String getcName() {
        return cName;
    }

    public void setcName(String cName) {
        this.cName = cName;
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public int getsTime() {
        return sTime;
    }

    public void setsTime(int sTime) {
        this.sTime = sTime;
    }

    public int getLength() {
        return length;
    }

    public void setLength(int length) {
        this.length = length;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        realTable realTable = (realTable) o;
        return sWeek == realTable.sWeek &&
                eWeek == realTable.eWeek &&
                day == realTable.day &&
                sTime == realTable.sTime &&
                length == realTable.length &&
                Objects.equals(cName, realTable.cName) &&
                Objects.equals(location, realTable.location);
    }

    @Override
    public int hashCode() {
        return Objects.hash(sWeek, eWeek, day, cName, location, sTime, length);
    }
}
