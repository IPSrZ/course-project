public final class Session {
    private final int id;
    private final String clientName;
    private final Computer computer; // aggregation: created outside
    private boolean active;
    private int minutes;

    public Session(int id, String clientName, Computer computer) {
        this.id = id;
        this.clientName = clientName;
        this.computer = computer;
        this.active = false;
        this.minutes = 0;
        System.out.println("[ctor] Session created: id=" + id + " client=" + clientName);
    }

    public boolean start() {
        if (computer == null) {
            System.out.println("  [rule] no computer attached");
            return false;
        }
        if (computer.isBroken()) {
            System.out.println("  [rule] computer broken, refuse start");
            return false;
        }
        if (active) {
            System.out.println("  [rule] session already active");
            return false;
        }
        if (!computer.isOn()) {
            if (!computer.powerOn()) {
                return false;
            }
        }
        active = true;
        minutes = 0;
        System.out.println("  session " + id + " started for " + clientName);
        return true;
    }

    public boolean addTime(int minutesToAdd) {
        if (!active) {
            System.out.println("  [rule] session not active");
            return false;
        }
        if (minutesToAdd <= 0) {
            System.out.println("  [rule] minutes must be > 0");
            return false;
        }
        minutes += minutesToAdd;
        System.out.println("  added " + minutesToAdd + " min, total " + minutes);
        return true;
    }

    public boolean end() {
        if (!active) {
            System.out.println("  [rule] session not active");
            return false;
        }
        active = false;
        System.out.println("  session " + id + " ended, minutes=" + minutes);
        return true;
    }

    public void printStatus() {
        System.out.println(this);
        if (computer != null) {
            System.out.println("  uses computer: " + computer.name());
        } else {
            System.out.println("  no computer");
        }
    }

    public int id() {
        return id;
    }

    public boolean isActive() {
        return active;
    }

    @Override
    public String toString() {
        return "Session #" + id + " client=" + clientName
                + (active ? " ACTIVE" : " idle")
                + " minutes=" + minutes;
    }
}
