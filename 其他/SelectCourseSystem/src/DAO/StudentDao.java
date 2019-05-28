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

    public boolean login(String Id, String password, String password1) {    //学生登陆，返回学号（需要改为完整课程表信息）

        if (!password.equals(password1)) return false;
        Session session = sessionFactory.openSession();
        String hql = "from TStudent where sId = :Id";
        Query query = session.createQuery(hql);
        session.close();
        return true;
    }

    public SessionFactory getSessionFactory() {
        return sessionFactory;
    }

    public void setSessionFactory(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }
}
