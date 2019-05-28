package Action;

import DAO.CourseDao;
import DAO.StudentDao;
import Table.TCourse;
import com.opensymphony.xwork2.ActionContext;

import java.util.ArrayList;
import java.util.Map;

public class loginStudentAction {

    private String Id;
    private String password;
    private String password1;
    private StudentDao studentDao;

    public String execute() {
        boolean ok = studentDao.login(Id, password, password1);
        return "success";
    }

    public String getId() {
        return Id;
    }

    public void setId(String Id) {
        this.Id = Id;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getPassword1(String password1) {
        return password1;
    }

    public void setPassword1(String password1) {
        this.password1 = password1;
    }

    public StudentDao getStudentDao() {
        return studentDao;
    }

    public void setStudentDao(StudentDao studentDao) {
        this.studentDao = studentDao;
    }
}
