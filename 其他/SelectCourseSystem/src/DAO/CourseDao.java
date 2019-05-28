package DAO;

import Table.TCourse;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.query.Query;

import java.util.ArrayList;

public class CourseDao {

    private SessionFactory sessionFactory;

    public ArrayList<TCourse> queryCourseByWord(String courseName) {    //课程查询（支持模糊查询）

        Session session = sessionFactory.openSession();
        String hql = "from TCourse where cName like :name";
        Query query = session.createQuery(hql);
        query.setParameter("name", "%" + courseName + "%");
        ArrayList<TCourse> res = (ArrayList<TCourse>) query.list();
        session.close();
        return res;
    }

    public ArrayList<TCourse> addCourse(int cId, String cName, String teacher) {    //课程信息录入

        Session session = sessionFactory.openSession();
        Transaction ts = session.beginTransaction();
        TCourse course = new TCourse();
        course.setcId(cId);
        course.setcName(cName);
        course.setTeacher(teacher);
        session.save(course);   //保存新的课程对象
        ts.commit();

        String hql = "from TCourse";    //查询新的课程记录
        Query query = session.createQuery(hql);
        ArrayList<TCourse> res = (ArrayList<TCourse>) query.list();
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
