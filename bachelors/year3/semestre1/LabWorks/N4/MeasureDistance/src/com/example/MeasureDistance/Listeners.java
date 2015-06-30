package com.example.MeasureDistance;

import Jama.Matrix;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Witalia on 11.10.2014.
 */


abstract class MySensorProcessor {
    protected static final double NS2S = 1.0 / 1000000000;
    protected float timestamp;
    protected static final double EPSILON_ACC = 1e-1;
    protected static final double EPSILON_GYRO = 1e-3;

    abstract public void onSensorChanged(SensorEvent event);
    abstract public void reset();
}

class AccelerometerProcessor extends MySensorProcessor {
    private Matrix lastMove;
    private Matrix position;
    private Matrix velocity;
    private Matrix gravity;
    private Matrix acceleration;
    private Matrix rotation;
    private List<Matrix> trajectory;
    private boolean initial;

    AccelerometerProcessor() {
        reset();
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (initial == false) {
            final double dT = (event.timestamp - timestamp) * NS2S;

            if (acceleration.normF() > EPSILON_ACC) {
                lastMove = velocity.times(dT)
                        .plus(acceleration.times(dT * dT * 0.5));
                velocity.plusEquals(acceleration.times(dT));
            } else {
                lastMove = new Matrix(1, 3);
            }
        }
        initial = false;

        acceleration = filter(new Matrix(new double[][]{{
                event.values[0],
                event.values[1],
                event.values[2]
        }})).times(rotation);

        position.plusEquals(lastMove);
        trajectory.add(position);
        timestamp = event.timestamp;
    }

    private Matrix filter(Matrix data) {
        final double alpha = 0.8;

        Matrix res = new Matrix(1, 3);

        for (int i = 0; i < 3; ++i) {
            gravity.set(0, i, gravity.get(0, i) * alpha
                    + (1 - alpha) * data.get(0, i)
            );
        }

        for (int i = 0; i < 3; ++i) {
            res.set(0, i, data.get(0, i) - gravity.get(0, i));
        }

        return res;
    }

    public double getLastMoveLength() {
        return lastMove.normF();
    }

    public double getDisplacement() {
        return position.normF();
    }

    public void setRotation(Matrix rotation) {
        this.rotation = rotation;
    }

    public List<Matrix> getTrajectory() {
        return trajectory;
    }

    public Matrix getAcceleration() {
        return acceleration;
    }

    @Override
    public void reset() {
        lastMove = new Matrix(1, 3);
        position = new Matrix(1, 3);
        gravity = new Matrix(1, 3);
        velocity = new Matrix(1, 3);
        acceleration = null;
        rotation = Matrix.identity(3, 3);
        trajectory = new ArrayList<Matrix>();
        initial = true;
    }
}

class GyroscopeProcessor extends MySensorProcessor {
    private Matrix rotation;

    GyroscopeProcessor() {
        reset();
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (timestamp != 0) {
            final double dT = (event.timestamp - timestamp) * NS2S;
            double[] angles = new double[] {
                    -event.values[0] * dT,
                    -event.values[1] * dT,
                    -event.values[2] * dT
            };

            double[][] sincos = new double[][] {
                    {Math.sin(angles[0]), Math.cos(angles[0])},
                    {Math.sin(angles[1]), Math.cos(angles[1])},
                    {Math.sin(angles[2]), Math.cos(angles[2])}
            };

            Matrix Rx = new Matrix(new double[][] {
                    {1.0f,  0.0f,            0.0f},
                    {0,     sincos[0][1],    -sincos[0][0]},
                    {0,     sincos[0][0],    sincos[0][1]}
            });

            Matrix Ry = new Matrix(new double[][]{
                    {sincos[1][1],  0,  sincos[1][0]},
                    {0,             1,  0},
                    {-sincos[1][0], 0,  sincos[1][1]}
            });

            Matrix Rz = new Matrix(new double[][]{
                    {sincos[2][1],  -sincos[2][0],  0},
                    {sincos[2][0],  sincos[2][1],   0},
                    {0,             0,              1}
            });

            if (new Matrix(new double[][]{angles}).normF() > EPSILON_GYRO) {
                Matrix deltaRotation = Rx.times(Ry).times(Rz);
                rotation = rotation.times(deltaRotation);
            }
        }
        timestamp = event.timestamp;
    }

    @Override
    public void reset() {
        rotation = Matrix.identity(3, 3);
    }

    public Matrix getRotation() {
        return rotation;
    }
}
