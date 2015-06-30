package sched;

public class Results {
    public String schedulingType;
    public String schedulingName;
    public int compuTime;

    public Results(String schedulingType, String schedulingName, int compuTime) {
        this.schedulingType = schedulingType;
        this.schedulingName = schedulingName;
        this.compuTime = compuTime;
    }

    @Override
    public String toString() {
        return "Scheduling Type: " + schedulingType + "\n"
                + "Scheduling Name: " + schedulingName + "\n"
                + "Simulation run Time: " + compuTime;
    }
}
