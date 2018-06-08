import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.util.Vector;

class   Table_Model   extends AbstractTableModel {

    private Vector content   =   null;
    private   String[]   title_name   =   {"学号", "姓名", "年龄"};

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
    public   void   removeRow(int   row)   {    //删除第row行
        content.remove(row);
    }

    /**
     *   让表格中某些值可修改，但需要setValueAt(Object   value,   int   row,   int   col)方法配合才能使修改生效
     */
    public   boolean   isCellEditable(int   rowIndex,   int   columnIndex){
        if(columnIndex   ==   0){
            return   false;
        }
        return   true;
    }

    /**
     *   使修改的内容生效
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
     *   返回数据类型
     */
    public   Class   getColumnClass(int   col){
        return   getValueAt(0,   col).getClass();
    }

}
