import threading
import random
import time
 
# Dining philosophers, 5 Phillies with 5 forks. Must have two forks to eat.
#
# Deadlock is avoided by never waiting for a fork while holding a fork (locked)
# Procedure is to do block while waiting to get first fork, and a nonblocking
# acquire of second fork.  If failed to get second fork, release first fork,
# swap which fork is first and which is second and retry until getting both.
#  
# See discussion page note about 'live lock'.
 
class Philosopher(threading.Thread):
 
    running = True
 
    def __init__(self, name, left_fork, right_fork):
        threading.Thread.__init__(self)
        self.name = name
        self.left_fork = left_fork
        self.right_fork = right_fork
 
    def run(self):
        while(self.running):
            #  Philosopher is thinking (but really is sleeping).
            time.sleep(random.randint(3,13))
            print(f'{self.name} is hungry.')
            self.dine()
 
    def dine(self):
        fork1, fork2 = self.left_fork, self.right_fork
 
        while self.running:
            fork1.acquire(True)
            locked = fork2.acquire(False)
            if locked: 
                break
            fork1.release()
            print(f'{self.name} swapped forks')
            fork1, fork2 = fork2, fork1
        else:
            return
 
        self.dining()
        fork2.release()
        fork1.release()
 
    def dining(self):			
        print(f'{self.name} starts eating')
        time.sleep(random.uniform(1,10))
        print(f'{self.name} finished eating and leaves to think.')
 
def DiningPhilosophers():
    names = ['Socrates', 'Aristotle', 'Kant', 'Mills', 'Singer']
    forks = [threading.Lock() for i in range(5)]
 
    philosophers = [Philosopher(names[i], forks[i % 5], forks[(i + 1) % 5]) for i in range(5)]
 
    # random.seed(507129)
    Philosopher.running = True
    for p in philosophers: 
        p.start()
    time.sleep(100)
    Philosopher.running = False
    print ('Now we are finishing.')
 
DiningPhilosophers()