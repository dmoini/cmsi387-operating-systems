public class BoundedBuffer {
    private Object[] buffer = new Object[20]; // arbitrary size
    private int numOccupied = 0;
    private int firstOccupied = 0;
    /* invariant: 0 <= numOccupied <= buffer.length
       0 <= firstOccupied < buffer.length
       buffer[(firstOccupied + i) % buffer.length]
       contains the (i+1)th oldest entry,
       for all i such that 0 <= i < numOccupied  */

    public class Producer extends Thread {
        public synchronized void insert(Object o) throws InterruptedException {
            while(numOccupied == buffer.length) {
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
            boolean fullBuffer = numOccupied == 20;
            int n = 5;
            while (!fullBuffer) {
                System.out.println(numOccupied);
                try {
                    insert(n);
                } catch (InterruptedException ie) {
                    System.out.println("Thread has been interrupted.");
                }
            }
        }
    }

    public class Consumer extends Thread {
        public synchronized Object retrieve() throws InterruptedException {
            while(numOccupied == 0) {
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
            // {}
            return retrieved;
        }
        
        public void run()  {
            System.out.println("Running consumer thread.");
            boolean emptyBuffer = numOccupied == 0;
            while (!emptyBuffer) {
                try {
                    System.out.println(retrieve());
                } catch (InterruptedException ie) {
                    System.out.println("Thread has been interrupted.");
                }
            }
        }    
    }
    
    
    
    
    // public synchronized void insert(Object o) throws InterruptedException {
    //     while(numOccupied == buffer.length)
    //         // wait for space
    //         wait();
    //     buffer[(firstOccupied + numOccupied) % buffer.length] = o;
    //     numOccupied++;
    //     // in case any retrieves are waiting for data, wake them
    //     // if (numOccupied == 1) {
    //     notifyAll();
    //     // }   
    // }

    // public synchronized Object retrieve() throws InterruptedException {
    //     while(numOccupied == 0)
    //         // wait for data
    //         wait();
    //     Object retrieved = buffer[firstOccupied];
    //     buffer[firstOccupied] = null; // may help garbage collector
    //     firstOccupied = (firstOccupied + 1) % buffer.length;
    //     numOccupied--;
    //     // in case any inserts are waiting for space, wake them
    //     // if (numOccupied == 19) {
    //     notifyAll();
    //     // {}
    //     return retrieved;
    // }

    public static void main(String[] args) {
        Producer p = new BoundedBuffer().new Producer();
        Consumer c = new BoundedBuffer().new Consumer();
        p.run();
        c.run();
    }
}
  