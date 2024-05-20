import java.util.Date;// 构造方法：

abstract class puppy {
    static void get_time() { // 静态方法，可以直接通过类名调用
        System.out.println("The time is " + new Date());
    }

    private final String name;
    private final int age; // final关键字修饰代表常量

    public puppy(String arg_name, int arg_age) { //puppy的构造方法，构造方法中可以直接访问类的私有属性
        name = arg_name;
        System.out.println("A new puppy named " + this.name + " is born!");
        age = arg_age;
        System.out.println("The puppy is " + this.age + " years old.");
    }


    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }
}

