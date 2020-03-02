package database;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.sql.*;

public class LoginFrame extends Frame implements ActionListener {
    // JDBC 驱动名及数据库 URL
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost:3306/lyc_login_test";

    // 数据库的用户名与密码
    final static String user_database = "root";
    final static String pass_database = "0017";

    // GUI内容
    Label nameL, pinL;
    TextField nameT, pinT;
    Button b;

    ResultSet rs;
    Connection conn = null;
    Statement stmt = null;
    String sql;
    LoginFrame(String s) {
        super(s);
        setLayout(new FlowLayout());
        nameL = new Label("输入用户名：",Label.LEFT);
        nameT = new TextField(10);
        pinL = new Label("   输入密码：",Label.LEFT);
        pinT = new TextField(10);
        pinT.setEchoChar('*');
        b = new Button("确认");
        b.addActionListener(this);
        add(nameL);
        add(nameT);
        add(pinL);
        add(pinT);
        add(b);
        setBounds(200,200,200,160);
        setVisible(true);
        validate();

//        Connection conn = null;
//        Statement stmt = null;
        try{
            // 注册 JDBC 驱动
            Class.forName("com.mysql.jdbc.Driver");

            // 打开链接
            conn = DriverManager.getConnection(DB_URL,user_database,pass_database);

            // 执行查询
            stmt = conn.createStatement();

            sql = "SELECT user, pass FROM user_pass";
            rs = stmt.executeQuery(sql);

            // 展开结果集数据库
            while(rs.next()){
                // 通过字段检索
                String user = rs.getString("user");
                String pass = rs.getString("pass");

                // 输出数据
                System.out.print("user:" + user);
                System.out.println(" pass:" + pass);
            }
            // 完成后关闭
            rs.close();
        }catch(SQLException secpt){
            // 处理 JDBC 错误
            secpt.printStackTrace();
        }catch(Exception ecpt){
            // 处理 Class.forName 错误
            ecpt.printStackTrace();
        }finally{
            // 关闭资源
            try{
                if(stmt!=null) stmt.close();
            }catch(SQLException se2){
            }// 什么都不做
            try{
                if(conn!=null) conn.close();
            }catch(SQLException se){
                se.printStackTrace();
            }
        }
    }
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == b) {
            String user_in = nameT.getText();
            String pass_in = pinT.getText();
            try{
                // 注册 JDBC 驱动
                Class.forName("com.mysql.jdbc.Driver");

                // 打开链接
                conn = DriverManager.getConnection(DB_URL,user_database,pass_database);

                // 执行查询
                stmt = conn.createStatement();

                sql = "SELECT user, pass FROM user_pass";
                rs = stmt.executeQuery(sql);

                // 展开结果集数据库
                boolean is_find = false;
                while (rs.next()) {
                    // 通过字段检索
                    String user = rs.getString("user");
                    String pass = rs.getString("pass");

                    if (user_in.equals(user)) {
                        is_find = true;
                        if (pass_in.equals(pass)) {
                            // 用户名密码都匹配
                            JOptionPane.showMessageDialog(this, "成功", "information", JOptionPane.OK_OPTION);
                        } else {
                            // 密码不对
                            JOptionPane.showMessageDialog(this, "密码错误", "information", JOptionPane.OK_OPTION);
                        }
                    }
                }
                rs.close();
                if (is_find == false) {
                    // 无用户名
                    JOptionPane.showMessageDialog(this, "无此用户名", "information", JOptionPane.OK_OPTION);
                }
                // 完成后关闭
                rs.close();
            }catch(SQLException secpt){
                // 处理 JDBC 错误
                secpt.printStackTrace();
            }catch(Exception ecpt){
                // 处理 Class.forName 错误
                ecpt.printStackTrace();
            }finally{
                // 关闭资源
                try{
                    if(stmt!=null) stmt.close();
                }catch(SQLException se2){
                }// 什么都不做
                try{
                    if(conn!=null) conn.close();
                }catch(SQLException se){
                    se.printStackTrace();
                }
            }
        }
    }
    public static void main(String[] args) {

        LoginFrame login = new LoginFrame("登录");
    }
}
