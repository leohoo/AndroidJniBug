package jp.co.normee.bugjni;

public class Worker {

    private static final String TAG = "TEST";
    public static final int STEP = 20000;

    void work(float [] output) {
        for(int i = 0; i< STEP; i++) {
            output[0] += (float)Math.random();
        }
        output[1] = STEP;
    }
}
