import javax.swing.table.AbstractTableModel;
import java.util.Vector;

class Tablemodel extends AbstractTableModel {  //继承AbstractTableModel类

    private static Vector content = null;
    private static final String[] title_name = {"学号", "姓名", "性别", "年龄", "所在系"};

    public Tablemodel() {
        content = new Vector();
    }

    public void addRow(String sno, String sname, String ssex, int sage, String sdept) {    //新增一行记录
        Vector v = new Vector(5);
        v.add(0, sno);
        v.add(1, sname);
        v.add(2, ssex);
        v.add(3, new Integer(sage));
        v.add(4, sdept);
        content.add(v);
    }

    public boolean isCellEditable(int rowIndex, int columnIndex) {  //让表中某些值可修改

        return 0 <= columnIndex && columnIndex < 5;
    }

    public void setValueAt(Object value, int row, int col) {        //使修改的内容生效
        ((Vector) content.get(row)).remove(col);
        ((Vector) content.get(row)).add(col, value);
        this.fireTableCellUpdated(row, col);
    }

    public String getColumnName(int col) {      //获取列名
        return title_name[col];
    }

    public int getColumnCount() {       //表格列数
        return title_name.length;
    }

    public int getRowCount() {          //表格行数
        return content.size();
    }

    public Object getValueAt(int row, int col) {    //第row行col列的值
        return ((Vector) content.get(row)).get(col);
    }
}
