import java.util.Random;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Created by Witalia on 22.10.2014.
 */
public class DeadLock {
    public static void main(String[] args) {
        AtomicInteger buffer = new AtomicInteger(0);
        Consumer consumer = new Consumer(buffer);
        Producer producer = new Producer(buffer);
        consumer.setProducer(producer);
        producer.setConsumer(consumer);
        consumer.start();
        producer.start();
        while (true) {
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if (consumer.getIterationsCount() == 0 &&
                    producer.getIterationsCount() == 0) {
                System.out.println("Deadlock occurred.");
                System.exit(-1);
            }
        }
    }
}

class ConsumerProducer extends Thread {
    protected AtomicInteger itemCount;
    protected final Integer BUFFER_SIZE = 3;
    protected int iterationsCount;
    private boolean sleeping = true;
    protected boolean canGoOn;

    public boolean isCanGoOn() {
        return canGoOn;
    }

    public void setCanGoOn(boolean canGoOn) {
        this.canGoOn = canGoOn;
    }


    public int getIterationsCount() {
        int res = iterationsCount;
        iterationsCount = 0;
        return res;
    }

    public ConsumerProducer(AtomicInteger buffer) {
        itemCount = buffer;
    }

    public void sleep() throws InterruptedException {
        sleeping = true;
        while (sleeping == true) {
            this.sleep(100);
        }
    }

    public void wakeUp() {
        sleeping = false;
    }
}

class Consumer extends ConsumerProducer {

    public void setProducer(Producer producer) {
        this.producer = producer;
    }

    Producer producer;

    Consumer(AtomicInteger buffer) {
        super(buffer);
    }

    private void removeItemFromBuffer() {
        System.out.println("Removing from buffer");
    }

    @Override
    public void run() {
        try {
            while (true) {
                ++iterationsCount;
                if (itemCount.get() == 0) {
                    System.out.println("Consumer going to sleep");
                    sleep();
                }
                removeItemFromBuffer();

                int cur = itemCount.get() - 1;
                while (canGoOn == false);
                itemCount.set(cur);
                System.out.println("Consumer: " + itemCount);

                if (itemCount.get() == BUFFER_SIZE - 1) {
                    producer.wakeUp();
                }
            }
        } catch (InterruptedException ex) {
            ex.printStackTrace();
        }
    }
}

class Producer extends ConsumerProducer {
    Consumer consumer;

    public void setConsumer(Consumer consumer) {
        this.consumer = consumer;
    }

    Producer(AtomicInteger buffer) {
        super(buffer);
    }

    private void produceItem() {
        System.out.println("Producing item");
    }
    private void putItemIntoBuffer() {
        System.out.println("Putting into buffer");
    }

    @Override
    public void run() {
        try {
            while (true) {
                ++iterationsCount;
                produceItem();
                if (itemCount.get() == BUFFER_SIZE) {
                    System.out.println("Producer going to sleep");
                    sleep();
                }
                putItemIntoBuffer();

                int cur = itemCount.get() + 1;
                if (itemCount.get() > 0 && consumer.isCanGoOn() == false) {
                    consumer.setCanGoOn(true);
                    sleep(1000);
                }
                itemCount.set(cur);
                System.out.println("Producer: " + itemCount);

                if (itemCount.get() == 1) {
                    consumer.wakeUp();
                }
            }
        } catch (InterruptedException ex) {
            ex.printStackTrace();
        }
    }
}