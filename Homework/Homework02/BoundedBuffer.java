public class BoundedBuffer {
    private static Object[] buffer = new Object[20]; // arbitrary size
    private static int numOccupied = 0;
    private static int firstOccupied = 0;
    /*
     * invariant: 0 <= numOccupied <= buffer.length 0 <= firstOccupied <
     * buffer.length buffer[(firstOccupied + i) % buffer.length] contains the
     * (i+1)th oldest entry, for all i such that 0 <= i < numOccupied
     */

    public class Producer extends Thread {
        public synchronized void insert(Object o) throws InterruptedException {
            while (true) {
                while (numOccupied == buffer.length)
                    wait();
                buffer[(firstOccupied + numOccupied) % buffer.length] = o;
                numOccupied++;
                System.out.println("Producer produced: " + numOccupied);

                // in case any retrieves are waiting for data, wake them
                if (numOccupied == 1) {
                    System.out.println("\nnotifyAll called for Producer\n");
                    notifyAll();
                }
                Thread.sleep(500);

            }
        }

        public void run() {
            System.out.println("\nRunning producer thread.\n");
            int n = 5;
            // while (numOccupied <= buffer.length) {
            // System.out.println("Producer numOccupied: " + numOccupied);
            try {
                insert(n);
            } catch (InterruptedException ie) {
                System.out.println("Producer thread has been interrupted.");
            }
            // }
        }
    }

    public class Consumer extends Thread {
        public synchronized Object retrieve() throws InterruptedException {
            while (numOccupied == 0)
                // wait for data
                wait();
            Object retrieved = buffer[firstOccupied];
            buffer[firstOccupied] = null; // may help garbage collector
            firstOccupied = (firstOccupied + 1) % buffer.length;
            numOccupied--;
            // in case any inserts are waiting for space, wake them
            // notifyAll();
            if (numOccupied == 19) {

                notifyAll();
                System.out.println("\nnotifyAll called for Consumer\n");
            }
            Thread.sleep(700);

            return retrieved;

        }

        public void run() {
            System.out.println("\nRunning consumer thread.\n");

            // System.out.println("Consumer start: " + numOccupied);

            while (numOccupied >= 0) {
                System.out.println("Consumer consumed: " + numOccupied);

                try {
                    retrieve();
                } catch (InterruptedException ie) {
                    System.out.println("Comsumer thread has been interrupted.");
                }

            }
            System.out.println("End of consumer thread");

        }
    }

    public static void main(String[] args) throws InterruptedException {
        // Test
        Producer p = new BoundedBuffer().new Producer();
        Consumer c = new BoundedBuffer().new Consumer();
        p.start();
        c.start();
        c.join();
        p.join();

    }
}