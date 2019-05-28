package Action;

import DAO.CourseDao;
import Table.TCourse;
import com.opensymphony.xwork2.ActionContext;

import java.util.ArrayList;
import java.util.Map;

public class queryCourseByWordAction {

    private String Word;
    private CourseDao courseDao;

    public String execute() {
        ArrayList<TCourse> list = courseDao.queryCourseByWord(Word);
        Map session = ActionContext.getContext().getSession();
        session.put("list",list);
        return "success";
    }

    public String getWord() {
        return Word;
    }

    public void setWord(String Word) {
        this.Word = Word;
    }

    public CourseDao getCourseDao() {
        return courseDao;
    }

    public void setCourseDao(CourseDao courseDao) {
        this.courseDao = courseDao;
    }
}
