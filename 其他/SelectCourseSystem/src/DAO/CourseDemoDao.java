package DAO;

import Table.TCourse;
import Table.TCourseDemo;
import org.hibernate.Criteria;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.query.*;
import java.util.*;

public class CourseDemoDao {

    private SessionFactory sessionFactory;

    public boolean addCourseDemo(int cId, int sWeek, int eWeek, int day, String location, int sTime, int length) {

        Session session = sessionFactory.openSession();
        Transaction ts = session.beginTransaction();
        TCourseDemo courseDemo = new TCourseDemo();
        courseDemo.setcId(cId);
        courseDemo.setsWeek(sWeek);
        courseDemo.seteWeek(eWeek);
        courseDemo.setDay(day);
        courseDemo.setLocation(location);
        courseDemo.setsTime(sTime);
        courseDemo.setLength(length);

        ArrayList<TCourseDemo> now = showCourseDemo();
        for (TCourseDemo p : now) {
            if (p.getcId() == courseDemo.getcId() && p.getDay() == courseDemo.getDay()) {
                session.close();
                return false;
            }
        }
        session.save(courseDemo);   //保存新的课程demo对象
        ts.commit();
        session.close();
        return true;
    }

    public ArrayList<TCourseDemo> showCourseDemo() { //查询所有课程demo记录

        Session session = sessionFactory.openSession();
        String hql = "from TCourseDemo";
        Query query = session.createQuery(hql);
        ArrayList<TCourseDemo> res = (ArrayList<TCourseDemo>) query.list();
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
