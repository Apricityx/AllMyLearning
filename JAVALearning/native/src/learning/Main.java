package learning;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;

import learning.object.TrianglePlus;
import learning.reference.ReferenceTest;
import learning.animals.*;
import learning.utils.MyLogger;

public class Main {
    public static void main(String[] args) { // 主函数
        Dog d = new Dog(2,"狗1");
        Rabbit r = new Rabbit(3,"兔1");
        Cat c = new Cat(1,"猫1");
        c.eat();
        d.eat();
        r.eat();
        List<Puppy> Animals = new ArrayList<Puppy>();
        Animals.add(c);
        Animals.add(r);
        Animals.add(d);
        for (int i=0;i<3;i++){
            System.out.println(Animals.get(i).getName());
        }
        MyLogger.log("Comparable排序后：");
        Collections.sort(Animals);
        for (int i=0;i<3;i++){
            System.out.println(Animals.get(i).getName());
        }
        MyLogger.log("使用Comparator");
        Animals.sort(new Comparator<Puppy>(){
           @Override
            public int compare(Puppy p1,Puppy p2){
            return p1.getAge() - p2.getAge();
           }
        });
        for (int i=0;i<3;i++){
            System.out.println(Animals.get(i).getName());
        }
        try{
        String content = Files.readString(Path.of("example.txt"));
        }
        catch(IOException e){

        }
//        Thread t1 = new Thread(()->{
//            learning.utils.MyLogger.debug("Creating " + "t1");
//            try {
//                Thread.sleep(1000);
//            } catch (InterruptedException e) {
//                throw new RuntimeException(e);
//            }
//            learning.utils.MyLogger.debug("Exiting " + "t1");
//
//            }, "t1");
//        Thread t2 = new Thread(()->{
//            learning.utils.MyLogger.debug("Creating" + "t2");
//            learning.utils.MyLogger.debug("Exiting " + "t2");
//
//            }, "t2");
//        t1.start();
////        try {
////            t1.join(); // 等待t1线程结束
////        } catch (InterruptedException e) {
////            throw new RuntimeException(e);
////        }
//        t2.start();

//        RunnableDemo t3 = new RunnableDemo("t3");
//        RunnableDemo t4 = new RunnableDemo("t4");
//        t3.start();
//        t4.start();
//        Cat cat = new Cat("Tom", 3) {
//            @Override
//            public void eat() {
//                System.out.println("The cat is eating mouse.");
//            }
//        };
//        cat.eat();
//        Cat cat2 = new Cat("Jerry", 2);
//        cat2.eat();
//        // compareTo的返回结果是当前对象与参数对象的比较结果
//        // 当前对象小于参数对象返回-1
//        // 当前对象等于参数对象返回0
//        // 当前对象大于参数对象返回1
//        StringBuilder sb = new StringBuilder("123321");
//        StringBuilder sb2 = new StringBuilder("123321");
//        System.out.println(sb.compareTo(sb2) == 0);
//        Map<String, String> env = new HashMap<>(System.getenv());
//        env.put("test", "test");
//        System.out.println(env.get("test"));
//        System.out.println(env.keySet());
//        printColor(Color.RED);
//        TrianglePlus triangle = new TrianglePlus(3, 4, 5, () -> System.out.println("LAMBDA表达式执行完成"));
//        System.out.println(triangle.getArea());
//        new ReferenceTest();
//    }
//
//    public enum Color {
//        RED, GREEN, BLUE;
//    }
//
//    public static void printColor(Color c) {
//        if (c == Color.RED) {
//            System.out.println("Color is RED");
//        } else if (c == Color.GREEN) {
//            System.out.println("Color is GREEN");
//        } else if (c == Color.BLUE) {
//            System.out.println("Color is BLUE");
//        }
    }
}

