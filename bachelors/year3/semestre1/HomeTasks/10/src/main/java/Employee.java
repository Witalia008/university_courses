import java.io.Serializable;

/**
 * Created by Witalia on 23.10.2014.
 */
public class Employee implements Serializable {
    private int number;
    private String name;

    public Employee(int number, String name) {

        this.number = number;
        this.name = name;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getNumber() {

        return number;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "Employee{" +
                "number=" + number +
                ", name='" + name + '\'' +
                '}';
    }
}
