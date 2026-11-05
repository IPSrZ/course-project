public final class Hardware {
    private final String model;
    private boolean broken;
    private String lastReason = "";

    public Hardware(String model) {
        this.model = model;
        this.broken = false;
        System.out.println("[ctor] Hardware created: " + model);
    }

    public void inspect() {
        System.out.print("  Hardware " + model + (broken ? " BROKEN" : " OK"));
        if (!lastReason.isEmpty()) {
            System.out.print(" (" + lastReason + ")");
        }
        System.out.println();
    }

    public boolean markBroken(String reason) {
        if (broken) {
            System.out.println("  [rule] already broken, refuse");
            return false;
        }
        if (reason == null || reason.isEmpty()) {
            System.out.println("  [rule] reason required");
            return false;
        }
        broken = true;
        lastReason = reason;
        System.out.println("  marked broken: " + reason);
        return true;
    }

    public boolean markFixed() {
        if (!broken) {
            System.out.println("  [rule] not broken, nothing to fix");
            return false;
        }
        broken = false;
        lastReason = "";
        System.out.println("  marked fixed");
        return true;
    }

    public boolean isBroken() {
        return broken;
    }

    public String model() {
        return model;
    }

    @Override
    public String toString() {
        return "Hardware " + model + (broken ? " BROKEN" : " OK")
                + (lastReason.isEmpty() ? "" : " (" + lastReason + ")");
    }

    @Override
    protected void finalize() throws Throwable {
        System.out.println("[finalize] Hardware: " + model);
        super.finalize();
    }
}
