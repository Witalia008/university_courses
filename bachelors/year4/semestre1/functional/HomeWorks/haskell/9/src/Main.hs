module Main where

import Graphics.UI.GLUT
import Data.IORef
import Bindings

main :: IO ()
main = do
    (_progName, _args) <- getArgsAndInitialize
    -- use DepthBuffer and DoubleBuffer
    initialDisplayMode $= [WithDepthBuffer, DoubleBuffered]
    _windows <- createWindow "Hello World"
    reshapeCallback $= Just reshape
    depthFunc $= Just Less

    -- Balls' coords
    let pos1 = Vector3 (-0.1::GLfloat) (-1) (-1);
        vel1 = Vector3 (0::GLfloat) 0.03 0
    ball1 <- newIORef $ Ball pos1 vel1 0.1 1
    let pos2 = Vector3 (0::GLfloat) 0 (-1);
        vel2 = Vector3 (0::GLfloat) 0.01 0
    ball2 <- newIORef $ Ball pos2 vel2 0.1 1

    -- IO Ref variables
    pos <- newIORef (0, 0)

    keyboardMouseCallback $= Just (keyboardMouse pos)
    idleCallback $= Just idle
    displayCallback $= display pos ball1 ball2

    addTimerCallback 16 $ animate ball1 ball2
    mainLoop