import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.util.Vector;

class   Table_Model   extends AbstractTableModel {

    private Vector content   =   null;
    private   String[]   title_name   =   {"ѧ��", "����", "����"};

    public   Table_Model()   {
        content   =   new   Vector();
    }
    public   Table_Model(int   count)   {
        content   =   new   Vector(count);
    }

    public   void   addRow(String sno, String name, int age)   {
        Vector   v   =   new   Vector(3);
        v.add(0, sno);
        v.add(1,   name);
        v.add(2, new Integer(age));
        content.add(v);
    }
    public   void   removeRow(int   row)   {    //ɾ����row��
        content.remove(row);
    }

    /**
     *   �ñ����ĳЩֵ���޸ģ�����ҪsetValueAt(Object   value,   int   row,   int   col)������ϲ���ʹ�޸���Ч
     */
    public   boolean   isCellEditable(int   rowIndex,   int   columnIndex){
        if(columnIndex   ==   0){
            return   false;
        }
        return   true;
    }

    /**
     *   ʹ�޸ĵ�������Ч
     */
    public   void   setValueAt(Object   value,   int   row,   int   col){
        ((Vector)   content.get(row)).remove(col);
        ((Vector)   content.get(row)).add(col,   value);
        this.fireTableCellUpdated(row,   col);
    }

    public   String   getColumnName(int   col)   {
        return   title_name[col];
    }

    public   int   getColumnCount()   {
        return   title_name.length;
    }

    public   int   getRowCount()   {
        return   content.size();
    }

    public   Object   getValueAt(int   row,   int   col)   {
        return   ((Vector)   content.get(row)).get(col);
    }

    /**
     *   ������������
     */
    public   Class   getColumnClass(int   col){
        return   getValueAt(0,   col).getClass();
    }

}
