module Display (Ball(..), display, idle, animate) where

import Graphics.UI.GLUT
import Graphics.UI.GLUT.Objects
import Control.Monad
import GHC.Float
import Data.IORef
import VectorUtil
import Cube

points :: Int -> [(GLfloat, GLfloat, GLfloat)]
points n = [(sin(2*pi*k/n'), cos(2*pi*k/n'), 0) | k <- [1..n']]
    where n' = fromIntegral n

data Ball = Ball {
    ball_pos :: PosType,
    ball_vel :: PosType,
    ball_r :: GLfloat,
    ball_m :: GLfloat
}

drawBall :: Ball -> Color3 GLfloat -> IO ()
drawBall ball col = preservingMatrix $ do
    color col
    let pos = ball_pos ball
    translate pos
    renderObject Solid $ Sphere' (realToFrac $ ball_r ball) 100 100


display :: IORef (GLfloat, GLfloat) -> IORef Ball -> IORef Ball -> DisplayCallback
display pos b1 b2 = do
    clear [ColorBuffer, DepthBuffer]
    loadIdentity
    (x', y') <- get pos
    translate $ Vector3 x' 0 0
    rotate y' $ Vector3 1 0 0
    preservingMatrix $ do
        ball1 <- get b1
        drawBall ball1 (Color3 1 0 0)
        ball2 <- get b2
        drawBall ball2 (Color3 0 0 1)
    swapBuffers

idle :: IdleCallback
idle = do
    postRedisplay Nothing

animate :: IORef Ball -> IORef Ball -> TimerCallback
animate b1 b2 = do
    moveBall b1
    moveBall b2
    postRedisplay Nothing
    fl <- collided b1 b2
    if fl then changeVelocities b1 b2 else
        addTimerCallback 16 $ animate b1 b2

changeVelocities :: IORef Ball -> IORef Ball -> IO ()
changeVelocities b1 b2 = do
    ball1 <- get b1
    ball2 <- get b2
    let vel1 = ball_vel ball1;
        vel2 = ball_vel ball2;
        vel = vel1 `sub` vel2;
    return ()

collided :: IORef Ball -> IORef Ball -> IO Bool
collided b1 b2 = do
    ball1 <- get b1
    ball2 <- get b2
    return $ (ball_pos ball1) `dist` (ball_pos ball2) < (ball_r ball1 + ball_r ball2)

moveBall :: IORef Ball -> IO ()
moveBall b = do
    ball <- get b
    let pos = ball_pos ball;
        vel = ball_vel ball
    writeIORef b $ Ball (pos `add` vel) vel (ball_r ball) (ball_m ball)
