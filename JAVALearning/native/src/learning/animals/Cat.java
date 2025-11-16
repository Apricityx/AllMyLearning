package learning.animals;
import learning.utils.MyLogger;
public class Cat extends Puppy {
    public Cat(int age,String name){
        super(age,name);
    }
    @Override
    public void eat() {
        MyLogger.log("猫在吃鱼");
    }
}
