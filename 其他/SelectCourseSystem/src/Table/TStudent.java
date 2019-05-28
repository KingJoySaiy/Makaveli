package Table;

import javax.persistence.*;
import java.util.Objects;

@Entity
@Table(name = "student", schema = "selectCourse")
public class TStudent {
    private String sId;
    private String password;
    private String name;
    private String sClass;

    @Id
    @Column(name = "SID")
    public String getsId() {
        return sId;
    }

    public void setsId(String sId) {
        this.sId = sId;
    }

    @Basic
    @Column(name = "PASSWORD")
    public String getPassword() {
        return password;
    }
    public void setPassword(String password) {
        this.password = password;
    }

    @Basic
    @Column(name = "NAME")
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }

    @Basic
    @Column(name = "SCLASS")
    public String getsClass() {
        return sClass;
    }

    public void setsClass(String sClass) {
        this.sClass = sClass;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        TStudent tStudent = (TStudent) o;
        return Objects.equals(sId, tStudent.sId) &&
                Objects.equals(name, tStudent.name) &&
                Objects.equals(sClass, tStudent.sClass);
    }

    @Override
    public int hashCode() {
        return Objects.hash(sId, name, sClass);
    }
}
