package Action;

import DAO.CourseDemoDao;
import Table.TCourse;
import com.opensymphony.xwork2.ActionContext;

import java.util.ArrayList;
import java.util.Map;

public class addCourseDemoAction {

    private int cId, sWeek, eWeek, day;
    private String location;
    private int sTime, length;
    private CourseDemoDao courseDemoDao;

    public String execute() {
        boolean ok = courseDemoDao.addCourseDemo(cId, sWeek, eWeek, day, location, sTime, length);
        return ok ? "success" : "failure";
    }

    public int getcId() {
        return cId;
    }

    public void setcId(int cId) {
        this.cId = cId;
    }

    public int getsWeek() {
        return sWeek;
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

    public CourseDemoDao getCourseDemoDao() {
        return courseDemoDao;
    }

    public void setCourseDemoDao(CourseDemoDao courseDemoDao) {
        this.courseDemoDao = courseDemoDao;
    }
}
