package learning.object;

public class Cat extends Puppy {
    public Cat(String arg_name, int arg_age) {
        super(arg_name, arg_age); // 使用super关键字调用父类的构造方法
    }

    public void eat() {
        System.out.println("The cat is eating fish.");
    }
}
