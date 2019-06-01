package Action;

import DAO.CourseDao;
import DAO.StudentDao;
import Table.TCourse;
import Table.realTable;
import com.opensymphony.xwork2.ActionContext;

import java.util.ArrayList;
import java.util.Map;

public class showTableAction {

    private String sId;
    private StudentDao studentDao;

    public String execute() {

        ArrayList<realTable> list = (ArrayList<realTable>) studentDao.showTable(sId);

        ArrayList<ArrayList<String>> res = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            res.add(new ArrayList<>(7));
        }
        for (int i = 0; i < list.size(); i++) {
            realTable data = (realTable) list.get(i);
            int day = data.getDay() - 1;
            String value = data.getcName() + "," + data.getLocation() + ","
                    + data.getsWeek() + "-" + data.geteWeek();

            for (int t = data.getsTime(); t < data.getsTime() + data.getLength(); t++) {
                res.get(t).set(day, value);
            }
        }

        Map session = ActionContext.getContext().getSession();
        session.put("table", res);
        return "success";
    }

    public String getsId() {
        return sId;
    }

    public void setsId(String sId) {
        this.sId = sId;
    }

    public StudentDao getStudentDao() {
        return studentDao;
    }

    public void setStudentDao(StudentDao studentDao) {
        this.studentDao = studentDao;
    }
}
