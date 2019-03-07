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
            while (numOccupied == buffer.length) {
                // wait for space
                System.out.println("Producer about to begin waiting");
                wait();
                System.out.println("Producer waiting");
            }
            buffer[(firstOccupied + numOccupied) % buffer.length] = o;
            numOccupied++;
            // in case any retrieves are waiting for data, wake them
            // if (numOccupied == 1) {
            notifyAll();
            // }
        }

        public void run() {
            System.out.println("Running producer thread.");
            System.out.println("Producer numOccupied START: " + numOccupied);
            int n = 5;
            while (numOccupied < buffer.length) {
                System.out.println("Producer numOccupied: " + numOccupied);
                try {
                    insert(n);
                } catch (InterruptedException ie) {
                    System.out.println("Producer thread has been interrupted.");
                }
            }
        }
    }

    public class Consumer extends Thread {
        public synchronized Object retrieve() throws InterruptedException {
            while (numOccupied == 0) {
                // wait for data
                System.out.println("Consumer about to begin waiting");
                wait();
                System.out.println("Consumer waiting");
            }
            Object retrieved = buffer[firstOccupied];
            buffer[firstOccupied] = null; // may help garbage collector
            firstOccupied = (firstOccupied + 1) % buffer.length;
            numOccupied--;
            // in case any inserts are waiting for space, wake them
            // if (numOccupied == 19) {
            notifyAll();
            // }
            return retrieved;
        }

        public void run() {
            System.out.println("Running consumer thread.");
            // System.out.println("Consumer numOccupied START: " + numOccupied);
            while (numOccupied != 0) {
                System.out.println("Consumer numOccupied: " + numOccupied);
                try {
                    Object r = retrieve();
                    // System.out.println("Retrieved: " + r);
                } catch (InterruptedException ie) {
                    System.out.println("Comsumer thread has been interrupted.");
                }
            }
        }
    }

    public static void main(String[] args) {
        Producer p = new BoundedBuffer().new Producer();
        Producer p2 = new BoundedBuffer().new Producer();
        Consumer c = new BoundedBuffer().new Consumer();
        p.run();
        p2.run();
        c.run();
    }
}