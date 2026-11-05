public final class IssueLog implements AutoCloseable {
    private final String title;
    private boolean closed;

    public IssueLog(String title) {
        this.title = title;
        this.closed = false;
        System.out.println("[+] журнал открыт: " + title);
    }

    public void write(String line) {
        if (closed) {
            System.out.println("  [rule] journal already closed");
            return;
        }
        System.out.println("    " + line);
    }

    @Override
    public void close() {
        if (closed) {
            return;
        }
        closed = true;
        System.out.println("[-] журнал закрыт: " + title);
    }

    @Override
    public String toString() {
        return "IssueLog{" + title + (closed ? ", closed" : ", open") + "}";
    }
}
