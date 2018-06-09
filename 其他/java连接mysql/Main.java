/*
Main.java   ����GUI���沢�������ݿ�
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
    private static JButton add, qur, exit, save;   // ������ť
    private static JTable table;                   // ���
    private static JPanel panelUP;                 //������Ϣ�����

    private Main() {
        this.setBounds(300, 200, 600, 400);        // ���ô����С
        this.setTitle("Ѧ��ǿ");                        // ���ô�������
        this.setLayout(new BorderLayout());           // ���ô���Ĳ��ַ�ʽ

        // �½�����ť���
        add = new JButton("����");
        qur = new JButton("��ѯ");
        save = new JButton("����");
        exit = new JButton("�˳�");

        panelUP = new JPanel();        // �½���ť������
        panelUP.setLayout(new FlowLayout(FlowLayout.CENTER));    // �������Ĳ��ַ�ʽ

        // ������ť���������ӵ������
        panelUP.add(add);
        panelUP.add(qur);
        panelUP.add(save);
        panelUP.add(exit);

        Vector rowData = JDBC.getRows(true);        //��ȡ���и�������
        Vector columnNames = JDBC.getHead();    //��ȡ��ͷ����

        model = new Tablemodel();

        //����DefaultTablemodel�Ĺ��캯����ȡ��Ԫ����Ϣ
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

        table = new JTable(model);          //���model
        table.setBackground(Color.gray);    //���ñ���ɫΪ��ɫ
        s_pan = new JScrollPane(table);

        this.add(panelUP, BorderLayout.NORTH);  // �����ͱ��ֱ���ӵ�������
        this.add(s_pan);
        MyEvent();                              // �¼�����

        this.setVisible(true);                  // ��ʾ����
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);         // ���ô���ɹر�
    }

    public void MyEvent() {             //�¼�����

        add.addActionListener(new ActionListener() {        //����
            @Override
            public void actionPerformed(ActionEvent arg0) {
                // ����һ�пհ�����
                model.addRow("233", "С��", "��", 15, "�����ϵ");
                table.updateUI();
            }
        });
        qur.addActionListener(new ActionListener() {        //��ѯ
            @Override
            public void actionPerformed(ActionEvent arg0) {
                // TODO Auto-generated method stub
                    Vector res = JDBC.getRows(false);
                    Vector tmp = new Vector(3);
                    tmp.add(0, "ѧ��");
                    tmp.add(1, "����");
                    tmp.add(2, "�������");
                    System.out.println(tmp.toString());
                    for(int i = 0; i < res.size(); i++)
                        System.out.println(res.get(i).toString());
            }
        });
        save.addActionListener(new ActionListener() {       //����
            @Override
            public void actionPerformed(ActionEvent e) {
                table.updateUI();
                int column = table.getColumnCount();        // �������
                int row = table.getRowCount();              // �������
                int has = JDBC.getRows(true).size();            //���ݿ��е�����

                // value�����¼�±���е�����������
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

                    // �ٰѸոռ�¼������һ���δ�ŵ�����
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
        exit.addActionListener(new ActionListener() {       //�˳�
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
