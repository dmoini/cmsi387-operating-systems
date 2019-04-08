import threading
import random
import time

# Code based on https://rosettacode.org/wiki/Dining_philosophers#Python
class Philosopher(threading.Thread):
    
    running = True
    def __init__(self, name, left_fork, right_fork):
        threading.Thread.__init__(self)
        self.name = name
        self.left_fork = left_fork
        self.right_fork = right_fork

    def run(self):
        while(self.running):
            time.sleep(random.uniform(1, 10))
            print({self.name} is hungry)
            self.dine()

    def dine(self):
        fork1, fork2 = self.left_fork, self.right_fork
        while self.running:
            fork1.acquire(True)
            locked = fork2.acquire(False)
            if locked: 
                break
            fork1.release()
            print({self.name} swapped forks)
            fork1, fork2 = fork2, fork1
        else:
            return
        self.dining()
        fork1.release()
        fork2.release()

    def dining(self):			
        print(f'{self.name} started eating')
        time.sleep(random.uniform(1, 10))
        print(f'{self.name} finished eating and put down his forks')

def dining_philosophers():
    names = ['Socrates', 'Aristotle', 'Kant', 'Mills', 'Singer']
    forks = [threading.Lock() for i in range(5)] 
    philosophers = [Philosopher(names[i], forks[i], forks[(i + 1) % 5]) for i in range(5)]
    for p in philosophers: 
        p.start()

dining_philosophers()
