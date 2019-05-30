package DAO;

import Table.TCourse;
import Table.TStudent;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
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

    public SessionFactory getSessionFactory() {
        return sessionFactory;
    }

    public void setSessionFactory(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }
}
