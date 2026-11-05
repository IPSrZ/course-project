public final class Computer {
    private final int id;
    private final String name;
    private final Hardware hardware; // composition: created inside
    private boolean on;

    public Computer(int id, String name, String hardwareModel) {
        this.id = id;
        this.name = name;
        this.hardware = new Hardware(hardwareModel);
        this.on = false;
        System.out.println("[ctor] Computer created: id=" + id + " name=" + name);
    }

    public boolean powerOn() {
        if (hardware.isBroken()) {
            System.out.println("  [rule] cannot power on, hardware broken");
            return false;
        }
        if (on) {
            System.out.println("  [rule] already on");
            return false;
        }
        on = true;
        System.out.println("  " + name + " powered on");
        return true;
    }

    public boolean powerOff() {
        if (!on) {
            System.out.println("  [rule] already off");
            return false;
        }
        on = false;
        System.out.println("  " + name + " powered off");
        return true;
    }

    public boolean requestRepair(String reason) {
        if (on) {
            powerOff();
        }
        return hardware.markBroken(reason);
    }

    public boolean finishRepair() {
        return hardware.markFixed();
    }

    public void printStatus() {
        System.out.println(this);
        hardware.inspect();
    }

    public int id() {
        return id;
    }

    public String name() {
        return name;
    }

    public boolean isOn() {
        return on;
    }

    public boolean isBroken() {
        return hardware.isBroken();
    }

    @Override
    public String toString() {
        return "Computer #" + id + " " + name + (on ? " ON" : " OFF");
    }

    @Override
    protected void finalize() throws Throwable {
        System.out.println("[finalize] Computer: id=" + id + " name=" + name);
        super.finalize();
    }
}
