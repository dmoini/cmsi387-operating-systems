
public class BoundedBufferTests {

    public static void main(String[] args) {
        Object test = new Object();
        try {
            BoundedBuffer b = new BoundedBuffer();
            b.insert(test);
            b.retrieve();
        } catch (InterruptedException ie) {
            System.out.println("Interrupted...");
        }
    }
}
