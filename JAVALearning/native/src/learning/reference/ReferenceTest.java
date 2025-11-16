package learning.reference;

import java.sql.Ref;

public class ReferenceTest {
    public ReferenceTest() {
        int a = 5;
        modify(a);
        System.out.println(a);
        int b = 5;
        System.out.println("b is " + b);
        System.out.println("c is " + (double) b);
    }

    void modify(int a) {
        a = 10;
    }
}
