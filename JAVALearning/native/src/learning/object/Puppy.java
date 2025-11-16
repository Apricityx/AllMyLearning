package learning.object;

import java.util.Comparator;
import java.util.Date;// 构造方法：

abstract class Puppy {
    static void get_time() { // 静态方法，可以直接通过类名调用
        System.out.println("The time is " + new Date());
    }

    protected String name;
    private final int age; // final关键字修饰代表常量

    public void test() {
        System.out.println("test");
    }

    public Puppy(String arg_name, int arg_age) { //puppy的构造方法，构造方法中可以直接访问类的私有属性
        name = arg_name;
        System.out.println("A new puppy named " + this.name + " is born!");
        age = arg_age;
        System.out.println("The puppy is " + this.age + " years old.");
    }

    abstract void eat(); // 抽象方法，没有方法体，只有方法声明，子类必须实现

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }


}

class PuppyComparator implements Comparator<Puppy> {
    @Override
    public int compare(Puppy o1, Puppy o2) {
        if (o1 == null || o2 == null) {
            throw new IllegalArgumentException("Cannot compare null objects");
        }
        return o1.getAge() - o2.getAge();
    }
}


