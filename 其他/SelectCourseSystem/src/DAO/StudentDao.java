package DAO;

import Table.TCourse;
import Table.realTable;
import org.hibernate.Criteria;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.cache.spi.QueryResultsCache;
import org.hibernate.query.Query;

import java.util.ArrayList;

public class StudentDao {

    private SessionFactory sessionFactory;

    public String login(String Id, String password) {    //学生登陆，返回学号（需要改为完整课程表信息）

        Session session = sessionFactory.openSession();
        Query query = session.createSQLQuery("select * from student where sid = '" + Id + "\' and password = \'" + password + "\'");
        if (query.list() == null) {
            session.close();
            return null;
        }
        session.close();
        return Id;
    }

    public ArrayList<realTable> showTable(String Id) {    //查询学生完整课表

        Session session = sessionFactory.openSession();
        String sql = "select sweek, eweek, day, cname, location, stime, length" +
                " from course,coursedemo, selected where " +
                "course.cid = coursedemo.cid and course.cid = selected.cid " +
//                "and selected.sid = \'" + Id + "\'";
                "and selected.sid = '1'";

        Query<realTable> query = session.createQuery(sql, realTable.class);
        ArrayList<realTable> res = (ArrayList<realTable>) query.list();

        session.close();
        return res;
    }

    public SessionFactory getSessionFactory() {
        return sessionFactory;
    }

    public void setSessionFactory(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }
}
