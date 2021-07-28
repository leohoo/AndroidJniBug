package jp.co.normee.bugjni;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import jp.co.normee.bugjni.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "TEST";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        int r = nativeTest(new Worker());

        Log.d(TAG, String.format("r = %d", r));
        Log.d(TAG, "==============================");

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(String.format("looped %d times", r));
    }

    public native int nativeTest(Object worker);
}

