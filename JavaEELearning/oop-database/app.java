import java.sql.*;

public class app {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/mydb"; // 替换为你的数据库名
        String user = "apricityx";
        String password = "520520Linux";
        boolean isDebugMode = args.length > 0 && args[0].equals("--debug");
        System.out.println("调试模式" + isDebugMode);
        try (Connection conn = DriverManager.getConnection(url, user, password); Statement stmt = conn.createStatement(); ResultSet rs = stmt.executeQuery("SELECT VERSION()")) {
            if (rs.next()) {
                System.out.println("MySQL 版本: " + rs.getString(1));
            }
            rs.close();

            if (isDebugMode) stmt.execute("DROP TABLE IF EXISTS students");
            /// 查询数据库中的表
            ResultSet rs2 = stmt.executeQuery("SHOW TABLES");
            System.out.println("数据库中的表有:");
            while (rs2.next()) {
                System.out.println(rs2.getString(1));
            }
            /// 判断表是否存在
            ResultSet isTableExistObject = stmt.executeQuery("SHOW TABLES LIKE 'students'");
            boolean isTableExist = !isTableExistObject.next();
            if (isTableExist) {
                final String sql = "CREATE TABLE IF NOT EXISTS students (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255))";
                stmt.execute(sql);
                System.out.println("创建表格成功: ");
                PreparedStatement ps = conn.prepareStatement("INSERT INTO students (name) VALUES (?)");
                for (int i = 0; i < 10; i++) {
                    ps.setString(1, "Student_" + i);
                    ps.execute();
                }
                ResultSet rs3 = stmt.executeQuery("SELECT * FROM students");
                ;
                System.out.println("students 表中的数据有:");
                while (rs3.next()) {
                    System.out.println(rs3.getInt(1) + ", " + rs3.getString(2));
                }
                stmt.close();
                ps.close();
            } else {
                System.out.println("表格已存在，不再初始化");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
