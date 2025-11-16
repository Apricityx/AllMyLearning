package learning.animals;

public abstract class Puppy implements Comparable<Puppy> {
    private String name;
    private int age;
    public Puppy(int age,String name){
        System.out.println("小狗的名字是 : " + name );
        System.out.println("小狗的年龄是 : " + age );
        this.name = name;
        this.age = age;
    }
    abstract public void eat();

    @Override
    public int compareTo(Puppy p){
        return this.age - p.age;
    }

    public String getName(){
     return this.name;
    }

    public int getAge(){
     return this.age;
    }
}
