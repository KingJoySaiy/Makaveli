import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

//信息安全小工具主窗体
public class Window extends JFrame {

    private JLabel welcome;
    private JLabel result;
    private JFileChooser jfc;
    private JButton encrypt;
    private JButton decode;
    private JComboBox mode;
    private fileWork work;

    public Window() {
        super("KingJoy");   //标题
        initWindow();   //初始化
        work = new fileWork();
    }

    private void initWindow() {
        //设置窗体大小、位置、窗体大小固定、关闭操作、可见性
        setSize(700, 500);
        setLocationRelativeTo(null);
        setResizable(false);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        //加入中间容器（自适应窗体大小），传入主体句柄便于数据修改
        MyJPanel panel = new MyJPanel(this);
        setContentPane(panel);

        //使窗体可见
        setVisible(true);
    }

    //该窗体的中间容器类
    class MyJPanel extends JPanel {

        private Window window;    //获得当前窗体的句柄

        public MyJPanel(Window window) {
            super();
            this.window = window; //保存传参句柄
            initMyJPanel();     //初始化
        }

        public void initMyJPanel() {

            //设置中间容器为流式布局
            setLayout(new FlowLayout(FlowLayout.CENTER, 30, 30));

            //欢迎语
            welcome = new JLabel("Encryption & Decryption program by RSA", JLabel.CENTER);
            welcome.setFont(new Font("Consoles", 1, 30));
            welcome.setForeground(Color.magenta);
            add(welcome, BorderLayout.NORTH);

            final String[] select = {"Mixed Mode", "ECB Mode", "CTR Mode"};
            mode = new JComboBox(select);
            mode.setFont(new Font("Consoles", 1, 16));
            add(mode, BorderLayout.CENTER);

            //加密
            encrypt = new JButton("Encrypt");
            encrypt.setFont(new Font("Consoles", 1, 20));
            encrypt.setForeground(Color.black);
            encrypt.addActionListener(e -> {
                jfc = new JFileChooser();
                jfc.setFileSelectionMode(JFileChooser.FILES_ONLY);
                jfc.showDialog(new Label(), "Select File!");
                work.encryptFile(jfc.getSelectedFile(), mode.getSelectedIndex());
                result.setText("Encrypt Successful!");
            });
            add(encrypt);

            //解密
            decode = new JButton("Decrypt");
            decode.setFont(new Font("Consoles", 1, 20));
            decode.setForeground(Color.black);
            decode.addActionListener(e -> {
                jfc = new JFileChooser();
                jfc.setFileSelectionMode(JFileChooser.FILES_ONLY);
                jfc.showDialog(new Label(), "Select File!");
                work.decryptFile(jfc.getSelectedFile(), mode.getSelectedIndex());
                result.setText("Decrypt Successful!");
            });
            add(decode);

            //结果
            result = new JLabel("", JLabel.CENTER);
            result.setFont(new Font("Consoles", 1, 30));
            result.setForeground(Color.ORANGE);
            add(result, BorderLayout.SOUTH);

            setVisible(true);
        }

        @Override
        protected void paintComponent(Graphics g) { //主体背景
            ImageIcon icon = new ImageIcon(Window.class.getResource("/Images/background.png"));
            Image image = icon.getImage();
            g.drawImage(image, 0, 0, this.getWidth(), this.getHeight(), this);
        }
    }

    public static void main(String[] args) {

        new Window();
    }
}
