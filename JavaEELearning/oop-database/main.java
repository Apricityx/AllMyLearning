import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class main {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/mydb"; // 替换为你的数据库名
        String user = "apricityx";
        String password = "520520Linux";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT VERSION()")) {
            if (rs.next()) {
                System.out.println("MySQL 版本: " + rs.getString(1));
            }

            /// 查询数据库中的表
            ResultSet rs2 = stmt.executeQuery("SHOW TABLES");
            System.out.println("数据库中的表有:");
            while (rs2.next()) {
                System.out.println(rs2.getString(1));
            }
            stmt.execute("CREATE TABLE IF NOT EXISTS students (id INT PRIMARY KEY, name VARCHAR(255))");

        } catch (SQLException e) {
            e.printStackTrace();
        }

    }
}
