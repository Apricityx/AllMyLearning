package learning.animals;
import learning.utils.MyLogger;

public class Rabbit extends Puppy {
    public Rabbit(int age, String name){
        super(age,name);
    }
    @Override
    public void eat() {
        MyLogger.log("兔在吃草");
    }
}
