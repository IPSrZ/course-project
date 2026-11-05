import java.lang.ref.WeakReference;

public final class Main {
    public static void main(String[] args) {
        System.out.println("=== 1. Composition + aggregation + rule ===");
        Computer pc = new Computer(1, "PC-01", "RTX-4060");
        pc.printStatus();

        System.out.println("-- correct: start session --");
        Session session = new Session(101, "Ivan", pc);
        session.start();
        session.addTime(60);
        session.printStatus();
        pc.printStatus();

        System.out.println("-- violate: start again --");
        session.start();

        System.out.println("-- violate: repair while already ok, then break and fix --");
        pc.finishRepair();
        pc.requestRepair("GPU overheat");
        session.end();

        System.out.println("-- violate: start while broken --");
        session.start();
        pc.finishRepair();
        session.start();
        session.end();
        pc.powerOff();

        System.out.println();
        System.out.println("=== 2. References vs copies ===");
        Computer first = new Computer(2, "PC-02", "i5-12400");
        Computer second = first; // вторая ссылка на ТОТ ЖЕ объект
        System.out.println("first == second: " + (first == second));
        second.powerOn();
        System.out.println("after second.powerOn():");
        first.printStatus(); // изменение видно через first
        first.powerOff();

        System.out.println();
        System.out.println("=== 3. AutoCloseable / try-with-resources ===");
        try (IssueLog log = new IssueLog("Смены киберклуба")) {
            log.write("сеанс 101: Ivan на PC-01, 60 мин");
            log.write("ремонт PC-01: GPU overheat");
        } // здесь гарантированно вызван close()
        System.out.println("-- after try block: close() already called --");

        System.out.println();
        System.out.println("=== 4. Garbage collector (WeakReference) ===");
        System.out.println("-- compare with LR2: there dtor fired on leaving the block --");
        Computer temp = new Computer(3, "PC-03", "Ryzen-5");
        WeakReference<Computer> watcher = new WeakReference<>(temp);
        System.out.println("watcher alive before null: " + (watcher.get() != null));
        System.out.println("-- leave 'scope': set last strong reference to null --");
        temp = null;
        System.out.println("watcher alive right after null (GC not forced yet): "
                + (watcher.get() != null));
        System.gc();
        System.runFinalization();
        try {
            Thread.sleep(200);
        } catch (InterruptedException ignored) {
            Thread.currentThread().interrupt();
        }
        System.out.println("watcher alive after System.gc(): " + (watcher.get() != null));
        System.out.println("-- unlike LR2, leaving the block alone did NOT destroy the object --");

        System.out.println();
        System.out.println("=== done ===");
    }
}
