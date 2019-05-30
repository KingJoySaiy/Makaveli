package Action;

import DAO.CourseDao;
import DAO.StudentDao;
import Table.TCourse;
import com.opensymphony.xwork2.ActionContext;

import java.util.ArrayList;
import java.util.Map;

public class loginStudentAction {

    private String sId;
    private String password;
    private StudentDao studentDao;

    public String execute() {
        String res = studentDao.login(sId, password);
        if (res == null) return "failure";
        Map session = ActionContext.getContext().getSession();
        session.put("studentId", res);
        return "success";
    }

    public String getsId() {
        return sId;
    }

    public void setsId(String sId) {
        this.sId = sId;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public StudentDao getStudentDao() {
        return studentDao;
    }

    public void setStudentDao(StudentDao studentDao) {
        this.studentDao = studentDao;
    }
}
