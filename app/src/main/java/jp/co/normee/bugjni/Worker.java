package jp.co.normee.bugjni;

public class Worker {

    public static final int STEP = 9000;
    float sum;
    void work() {
        for(int i = 0; i< STEP; i++) {
            sum += (float)Math.random();
        }
    }
}
