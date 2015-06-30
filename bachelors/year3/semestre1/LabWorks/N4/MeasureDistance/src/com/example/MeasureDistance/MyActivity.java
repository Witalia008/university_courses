package com.example.MeasureDistance;

import Jama.Matrix;
import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.widget.*;

import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

public class MyActivity extends Activity {
    private TextView walkedLengthTextView;
    private TextView history;
    // For testing purposes
    private TextView accAll;
    private TextView accX;
    private TextView accY;
    private TextView accZ;
    // ---
    private CheckBox displacementChecker;
    static SensorManager sensorService;
    private double wayPassed;
    private boolean running;
    private AccelerometerProcessor accelerometer = new AccelerometerProcessor();
    private GyroscopeProcessor gyroscope = new GyroscopeProcessor();
    private SensorEventListener mySensorEventListener = new SensorEventListener() {

        @Override
        public void onSensorChanged(SensorEvent event) {
            switch (event.sensor.getType()) {
                case Sensor.TYPE_ACCELEROMETER:
                    accelerometer.setRotation(gyroscope.getRotation());

                    accelerometer.onSensorChanged(event);

                    wayPassed += accelerometer.getLastMoveLength();

                    if (running) {
                        DecimalFormat decimalFormat = new DecimalFormat("Walked #.000 m");
                        walkedLengthTextView.setText(decimalFormat.format(
                                displacementChecker.isChecked()
                                ? accelerometer.getDisplacement()
                                : wayPassed
                        ));
                    }

                    Matrix cur = accelerometer.getAcceleration();
                    accAll.setText("All: " + cur.normF());
                    accX.setText("X: " + cur.get(0, 0));
                    accY.setText("Y: " + cur.get(0, 1));
                    accZ.setText("Z: " + cur.get(0, 2));
                    break;
                case Sensor.TYPE_GYROSCOPE:
                    gyroscope.onSensorChanged(event);
                    break;
                default:
                    break;
            }
        }

        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }
    };

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.main);

        InitializeSensorService();
        InitializeApp();
    }

    private void InitializeSensorService() {
        sensorService = (SensorManager) getSystemService(Context.SENSOR_SERVICE);

        sensorService.registerListener(mySensorEventListener,
                sensorService.getDefaultSensor(Sensor.TYPE_ACCELEROMETER),
                SensorManager.SENSOR_DELAY_FASTEST);
        sensorService.registerListener(mySensorEventListener,
                sensorService.getDefaultSensor(Sensor.TYPE_GYROSCOPE),
                SensorManager.SENSOR_DELAY_FASTEST);
    }

    private void InitializeApp() {
        walkedLengthTextView = (TextView) findViewById(R.id.lengthMessage);
        history = (TextView) findViewById(R.id.history);
        displacementChecker = (CheckBox) findViewById(R.id.displCheck);

        // For testing purposes
        accAll = (TextView) findViewById(R.id.accAll);
        accX = (TextView) findViewById(R.id.accX);
        accY = (TextView) findViewById(R.id.accY);
        accZ = (TextView) findViewById(R.id.accZ);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        sensorService.unregisterListener(mySensorEventListener);
    }

    public void stopClicked(View view) {
        running = false;
        DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
        Date date = new Date();
        history.setText(dateFormat.format(date) + ": Length = " + wayPassed + "\n" + history.getText());
    }

    public void startClicked(View view) {
        running = true;
        wayPassed = 0;
    }

    public void resetClicked(View view) {
        stopClicked(view);
        accelerometer.reset();
        gyroscope.reset();
    }
}