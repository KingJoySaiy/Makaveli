package Table;

import javax.persistence.*;
import java.util.Objects;

@Entity
@Table(name = "courseDemo", schema = "selectCourse")
public class TCourseDemo {
    private int cId, sWeek, eWeek, day;
    private String location;
    private int sTime, length;

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "CID")
    public int getcId() {
        return cId;
    }

    public void setcId(int cId) {
        this.cId = cId;
    }

    @Basic
    @Column(name = "SWEEK")
    public int getsWeek() {
        return sWeek;
    }

    public void setsWeek(int sWeek) {
        this.sWeek = sWeek;
    }

    @Basic
    @Column(name = "EWEEK")
    public int geteWeek() {
        return eWeek;
    }

    public void seteWeek(int eWeek) {
        this.eWeek = eWeek;
    }

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "DAY")
    public int getDay() {
        return day;
    }

    public void setDay(int day) {
        this.day = day;
    }

    @Basic
    @Column(name = "LOCATION")
    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    @Basic
    @Column(name = "STIME")
    public int getsTime() {
        return sTime;
    }

    public void setsTime(int sTime) {
        this.sTime = sTime;
    }

    @Basic
    @Column(name = "LENGTH")
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
        TCourseDemo tCourseDemo = (TCourseDemo) o;
        return Objects.equals(cId, tCourseDemo.cId) &&
                Objects.equals(sWeek, tCourseDemo.sWeek) &&
                Objects.equals(eWeek, tCourseDemo.eWeek) &&
                Objects.equals(day, tCourseDemo.day) &&
                Objects.equals(location, tCourseDemo.location) &&
                Objects.equals(sTime, tCourseDemo.sTime) &&
                Objects.equals(length, tCourseDemo.length);
    }

    @Override
    public int hashCode() {
        return Objects.hash(cId, sWeek, eWeek, day, location, sTime, length);
    }
}