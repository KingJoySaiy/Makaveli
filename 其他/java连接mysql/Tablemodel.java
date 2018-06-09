import javax.swing.table.AbstractTableModel;
import java.util.Vector;

class Tablemodel extends AbstractTableModel {  //�̳�AbstractTableModel��

    private static Vector content = null;
    private static final String[] title_name = {"ѧ��", "����", "�Ա�", "����", "����ϵ"};

    public Tablemodel() {
        content = new Vector();
    }

    public void addRow(String sno, String sname, String ssex, int sage, String sdept) {    //����һ�м�¼
        Vector v = new Vector(5);
        v.add(0, sno);
        v.add(1, sname);
        v.add(2, ssex);
        v.add(3, new Integer(sage));
        v.add(4, sdept);
        content.add(v);
    }

    public boolean isCellEditable(int rowIndex, int columnIndex) {  //�ñ���ĳЩֵ���޸�

        return 0 <= columnIndex && columnIndex < 5;
    }

    public void setValueAt(Object value, int row, int col) {        //ʹ�޸ĵ�������Ч
        ((Vector) content.get(row)).remove(col);
        ((Vector) content.get(row)).add(col, value);
        this.fireTableCellUpdated(row, col);
    }

    public String getColumnName(int col) {      //��ȡ����
        return title_name[col];
    }

    public int getColumnCount() {       //�������
        return title_name.length;
    }

    public int getRowCount() {          //�������
        return content.size();
    }

    public Object getValueAt(int row, int col) {    //��row��col�е�ֵ
        return ((Vector) content.get(row)).get(col);
    }
}
