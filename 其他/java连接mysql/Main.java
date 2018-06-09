/*
Main.java   创建GUI界面并管理数据库
 */
import java.awt.*;
import java.awt.event.*;
import java.sql.*;
import java.util.Vector;
import javax.swing.*;
import javax.swing.table.*;


public class Main extends JFrame {

    private static Tablemodel model;
    private static JScrollPane s_pan;
    private static JButton add, qur, exit, save;   // 各处理按钮
    private static JTable table;                   // 表格
    private static JPanel panelUP;                 //增加信息的面板

    private Main() {
        this.setBounds(300, 200, 600, 400);        // 设置窗体大小
        this.setTitle("薛金强");                        // 设置窗体名称
        this.setLayout(new BorderLayout());           // 设置窗体的布局方式

        // 新建各按钮组件
        add = new JButton("增加");
        qur = new JButton("查询");
        save = new JButton("保存");
        exit = new JButton("退出");

        panelUP = new JPanel();        // 新建按钮组件面板
        panelUP.setLayout(new FlowLayout(FlowLayout.CENTER));    // 设置面板的布局方式

        // 将各按钮组件依次添加到面板中
        panelUP.add(add);
        panelUP.add(qur);
        panelUP.add(save);
        panelUP.add(exit);

        Vector rowData = JDBC.getRows(true);        //获取表中各行数据
        Vector columnNames = JDBC.getHead();    //获取表头数据

        model = new Tablemodel();

        //利用DefaultTablemodel的构造函数提取单元格信息
        DefaultTableModel tmp = new DefaultTableModel(rowData, columnNames);
        int sage;
        String sno, sname, ssex, sdept;
        table = new JTable(tmp);
        for (int i = 0; i < table.getRowCount(); i++) {
            sno = table.getValueAt(i, 0).toString();
            sname = table.getValueAt(i, 1).toString();
            ssex = table.getValueAt(i, 2).toString();
            sage = Integer.valueOf(table.getValueAt(i, 3).toString());
            sdept = table.getValueAt(i, 4).toString();
            model.addRow(sno, sname, ssex, sage, sdept);
        }

        table = new JTable(model);          //添加model
        table.setBackground(Color.gray);    //设置背景色为灰色
        s_pan = new JScrollPane(table);

        this.add(panelUP, BorderLayout.NORTH);  // 将面板和表格分别添加到窗体中
        this.add(s_pan);
        MyEvent();                              // 事件处理

        this.setVisible(true);                  // 显示窗体
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);         // 设置窗体可关闭
    }

    public void MyEvent() {             //事件处理

        add.addActionListener(new ActionListener() {        //增加
            @Override
            public void actionPerformed(ActionEvent arg0) {
                // 增加一行空白区域
                model.addRow("233", "小明", "男", 15, "计算机系");
                table.updateUI();
            }
        });
        qur.addActionListener(new ActionListener() {        //查询
            @Override
            public void actionPerformed(ActionEvent arg0) {
                // TODO Auto-generated method stub
                    Vector res = JDBC.getRows(false);
                    Vector tmp = new Vector(3);
                    tmp.add(0, "学号");
                    tmp.add(1, "姓名");
                    tmp.add(2, "出生年份");
                    System.out.println(tmp.toString());
                    for(int i = 0; i < res.size(); i++)
                        System.out.println(res.get(i).toString());
            }
        });
        save.addActionListener(new ActionListener() {       //保存
            @Override
            public void actionPerformed(ActionEvent e) {
                table.updateUI();
                int column = table.getColumnCount();        // 表格列数
                int row = table.getRowCount();              // 表格行数
                int has = JDBC.getRows(true).size();            //数据库中的行数

                // value数组记录下表格中的新增的数据
                String[][] value = new String[row][column];
                for (int i = has; i < row; i++) {
                    for (int j = 0; j < column; j++) {
                        value[i][j] = table.getValueAt(i, j).toString();
                    }
                }

                Connection conn = null;
                PreparedStatement preparedStatement = null;
                try {
                    conn = JDBC.GetConn();

                    // 再把刚刚记录的数据一依次存放到表中
                    for (int i = has; i < row; i++) {
                        preparedStatement = conn.prepareStatement(
                                "insert into student values('"
                                + value[i][0] + "','" + value[i][1] + "','"
                                + value[i][2] + "'," + Integer.parseInt(value[i][3]) + ",'"
                                + value[i][4] + "')"
                        );
                        preparedStatement.executeUpdate();
                    }

                } catch (Exception t) {
                    t.printStackTrace();
                }
            }
        });
        exit.addActionListener(new ActionListener() {       //退出
            @Override
            public void actionPerformed(ActionEvent e) {
                // TODO Auto-generated method stub
                System.exit(0);
            }

        });
    }

    public static void main(String[] args) {

        new Main();
    }
}
