import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

public class Fork {
  
  private static final int NO_ONE = -1;
  
  private final int id;
  private int whoHasMe;
  private final ReentrantLock lock;
  private final Condition notBeingUsed;

  public Fork(int id) {
    this.id = id;
    this.whoHasMe = NO_ONE;
    this.lock = new ReentrantLock(); //Mutex em Java + Conditions
    this.notBeingUsed = this.lock.newCondition();
  }

  public void acquire(int philosopherID) {
    try {
      this.lock.lock();
      while (this.whoHasMe != NO_ONE) {
        try {
          this.notBeingUsed.await();
        } catch (InterruptedException e) {
          throw new RuntimeException(e);
        }
      }
      this.whoHasMe = philosopherID;
    } finally {
      this.lock.unlock();
    }
  }

  public void release(int philosopherID) {
    try {
      this.lock.lock();
      if (this.whoHasMe != philosopherID) {
        throw new RuntimeException("Somebody coded wrong!");
      }
      this.whoHasMe = NO_ONE;
      this.notBeingUsed.notify();
    } finally {
      this.lock.unlock();
    }
  }
  
  public int getID() {
    return this.id;
  }

  public String toString() {
    return "" + this.id;
  }
}
