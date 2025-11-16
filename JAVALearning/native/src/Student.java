import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.Comparator;

public class Student {
    private String id; // 学号
    private int scoreA; // 成绩A
    private int scoreB; // 成绩B
    private int scoreC; // 成绩C

    public static Student[] readFromFile(String path, int num) {
        // 待完成
        Student[] stu = new Student[num];
        try {
            FileReader fr = new FileReader(path);
            BufferedReader br = new BufferedReader(fr);
            String line;
            int i = 0;
            while ((line = br.readLine()) != null) {
                String[] s = line.split(",");
                stu[i] = new Student(s[0], Integer.parseInt(s[1]), Integer.parseInt(s[2]), Integer.parseInt(s[3]));
                i++;
            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return stu;
    }

    public int totalScore() {
        // 待完成
        return scoreA + scoreB + scoreC;
    }

    public static void sortByTotalScore(Student[] s) {
        // 待完成
        class StudentComparator implements Comparator<Student> {
            @Override
            public int compare(Student o1, Student o2) {
                return o1.totalScore() - o2.totalScore();
            }
        }
        Arrays.sort(s, new StudentComparator());
    }

    public Student(String id, int scoreA, int scoreB, int scoreC) {
        // 待完成
        this.id = id;
        this.scoreA = scoreA;
        this.scoreB = scoreB;
        this.scoreC = scoreC;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public int getScoreA() {
        return scoreA;
    }

    public void setScoreA(int scoreA) {
        this.scoreA = scoreA;
    }

    public int getScoreB() {
        return scoreB;
    }

    public void setScoreB(int scoreB) {
        this.scoreB = scoreB;
    }

    public int getScoreC() {
        return scoreC;
    }

    public void setScoreC(int scoreC) {
        this.scoreC = scoreC;
    }

    public String toString() {
        return id + "," + scoreA + "," + scoreB + "," + scoreC + "," + totalScore();
    }
}