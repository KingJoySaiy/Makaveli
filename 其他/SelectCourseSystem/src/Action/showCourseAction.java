package Action;

import DAO.CourseDao;
import Table.TCourse;
import com.opensymphony.xwork2.ActionContext;

import java.util.ArrayList;
import java.util.Map;

public class showCourseAction {

    private CourseDao courseDao;

    public String execute() {
        ArrayList<TCourse> list = courseDao.showCourse();
        Map session = ActionContext.getContext().getSession();
        session.put("list",list);
        return "success";
    }

    public CourseDao getCourseDao() {
        return courseDao;
    }

    public void setCourseDao(CourseDao courseDao) {
        this.courseDao = courseDao;
    }
}
