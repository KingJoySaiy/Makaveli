package Table;

import javax.persistence.*;
import java.util.Objects;

@Entity
@Table(name = "course", schema = "selectCourse")
public class TCourse {
    private int cId;
    private String cName;
    private String teacher;
    
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "CID")
    public int getcId() {
        return cId;
    }

    public void setcId(int cId) {
        this.cId = cId;
    }

    @Basic
    @Column(name = "CNAME")
    public String getcName() {
        return cName;
    }
    public void setcName(String cName) {
        this.cName = cName;
    }

    @Basic
    @Column(name = "TEACHER")
    public String getTeacher() {
        return teacher;
    }

    public void setTeacher(String teacher) {
        this.teacher = teacher;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        TCourse tCourse = (TCourse) o;
        return Objects.equals(cId, tCourse.cId) &&
                Objects.equals(cName, tCourse.cName) &&
                Objects.equals(teacher, tCourse.teacher);
    }

    @Override
    public int hashCode() {
        return Objects.hash(cId, cName, teacher);
    }
}
