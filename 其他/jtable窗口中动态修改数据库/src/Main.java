import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Vector;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;


public class Main extends JFrame{

    Table_Model model = null;
    JScrollPane   s_pan   =   null;
    JButton add,del,exit,save;		// 各处理按钮
    JTable table;		// 表格
    JPanel panelUP;	    //增加信息的面板

    // 构造函数
    public Main() {
        this.setBounds(300, 200, 600, 450);		// 设置窗体大小
        this.setTitle("测试");		// 设置窗体名称
        this.setLayout(new BorderLayout());	// 设置窗体的布局方式

        // 新建各按钮组件
        add = new JButton("增加");
        del = new JButton("删除");
        save = new JButton("保存");
        exit = new JButton("退出");

        panelUP = new JPanel();		// 新建按钮组件面板
        panelUP.setLayout(new FlowLayout(FlowLayout.LEFT));	// 设置面板的布局方式

        // 将各按钮组件依次添加到面板中
        panelUP.add(add);
        panelUP.add(del);
        panelUP.add(save);
        panelUP.add(exit);

        // 取得haha数据库的aa表的各行数据
        Vector rowData = Storage.getRows();
        // 取得haha数据库的aa表的表头数据
        Vector columnNames = Storage.getHead();

        model = new Table_Model(20);

        DefaultTableModel tt = new DefaultTableModel(rowData, columnNames);
        int age;
        String sno, name;
        table = new JTable(tt);
        for(int i = 0; i < table.getRowCount(); i++) {
            sno = table.getValueAt(i, 0).toString();
            name = table.getValueAt(i, 1).toString();
            age = Integer.valueOf(table.getValueAt(i, 2).toString());
            model.addRow(sno, name, age);
        }

        table = new JTable(model);
        table.setBackground(Color.white);

        TableColumnModel tcm   =   table.getColumnModel();
        tcm.getColumn(0).setPreferredWidth(50);
        tcm.getColumn(1).setPreferredWidth(100);
        tcm.getColumn(2).setPreferredWidth(50);

        s_pan = new JScrollPane(table);

        // 将面板和表格分别添加到窗体中
        this.add(panelUP,BorderLayout.NORTH);
        this.add(s_pan);

        // 事件处理
        MyEvent();

        this.setVisible(true);		// 显示窗体
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);		 // 设置窗体可关闭
    }

    // 事件处理
    public void MyEvent(){

        // 增加
        add.addActionListener(new ActionListener(){

            @Override
            public void actionPerformed(ActionEvent arg0) {
                // 增加一行空白区域
                model.addRow("110", "小明", 13);
                table.updateUI();
            }

        });

        // 删除
        del.addActionListener(new ActionListener(){

            @Override
            public void actionPerformed(ActionEvent arg0) {
                // TODO Auto-generated method stub
                // 删除指定行
                int rowcount = table.getSelectedRow();
                if(rowcount >= 0){
                    model.removeRow(rowcount);
                }
            }

        });

        /**
         * 保存
         * 我的解决办法是直接将aa表中的全部数据删除，
         * 将表格中的所有内容获取到,
         * 然后将表格数据重新写入aa表
         */
        save.addActionListener(new ActionListener(){

            @Override
            public void actionPerformed(ActionEvent e) {
                table.updateUI();
                int column = table.getColumnCount();		// 表格列数
                int row = table.getRowCount();		// 表格行数

                // value数组存放表格中的所有数据
                String[][] value = new String[row][column];

                for(int i = 0; i < row; i++){
                    for(int j = 0; j < column; j++){
                        value[i][j] = table.getValueAt(i, j).toString();
                    }
                }

                // 以下均为对数据库的操作
                String sql_url = "jdbc:mysql://localhost:3306/_233?useUnicode=true&characterEncoding=GBK";	//数据库路径（一般都是这样写），haha是数据库名称
                String name = "root";		//用户名
                String password = "root";	//密码
                Connection conn;
                PreparedStatement preparedStatement = null;

                try {
                    Class.forName("com.mysql.jdbc.Driver");		//连接驱动
                    conn = DriverManager.getConnection(sql_url, name, password);	//连接数据库
                    if(!conn.isClosed())
                        System.out.println("成功连接数据库");

                    // 删除aa表中所有数据
                    preparedStatement = conn.prepareStatement("delete from student");
                    preparedStatement.executeUpdate();

                    // 将value数组中的数据依次存放到aa表中
                    for(int i = 0; i < row; i++){
//                        conn.prepareStatement("insert into student values(" + Integer.parseInt(value[i][0]) + ",'" + value[i][1] + "')");
                        preparedStatement = conn.prepareStatement("insert into student values('" + value[i][0] + "','" + value[i][1] + "'," + Integer.parseInt(value[i][2]) + ")");
                        preparedStatement.executeUpdate();
                    }

                } catch (ClassNotFoundException e1) {
                    // TODO Auto-generated catch block
                    System.out.println("未成功加载驱动。");
                    e1.printStackTrace();
                } catch (SQLException e1) {
                    // TODO Auto-generated catch block
                    System.out.println("未成功打开数据库。");
                    e1.printStackTrace();
                }

                // 保存后退出
                System.exit(0);
            }
        });

        // 退出
        exit.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent e) {
                // TODO Auto-generated method stub
                System.exit(0);
            }

        });
    }

    // 主函数
    public static void main(String[] args){

        new Main();
    }
}
