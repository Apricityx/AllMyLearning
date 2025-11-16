package learning.animals;
import learning.utils.MyLogger;

public class Dog extends Puppy {
    public Dog(int age, String name){
        super(age,name);
    }
    @Override
    public void eat() {
        MyLogger.log("狗在吃骨头");
    }
}
