package Action;

import DAO.CourseDao;
import Table.TCourse;
import com.opensymphony.xwork2.ActionContext;

import java.util.ArrayList;
import java.util.Map;

public class addCourseAction {

    private int cId;
    private String cName;
    private String teacher;
    private CourseDao courseDao;

    public String execute() {
        boolean ok = courseDao.addCourse(cId, cName, teacher);
        return ok ? "success" : "failure";
    }

    public int getcId() {
        return cId;
    }

    public void setcId(int cId) {
        this.cId = cId;
    }

    public String getcName() {
        return cName;
    }

    public void setcName(String cName) {
        this.cName = cName;
    }

    public String getTeacher() {
        return teacher;
    }

    public void setTeacher(String teacher) {
        this.teacher = teacher;
    }

    public CourseDao getCourseDao() {
        return courseDao;
    }

    public void setCourseDao(CourseDao courseDao) {
        this.courseDao = courseDao;
    }
}
