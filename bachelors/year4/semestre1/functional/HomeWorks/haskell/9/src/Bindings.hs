module Bindings (Ball(..), display, reshape, keyboardMouse, idle, animate) where

import Graphics.UI.GLUT
import Data.IORef
import Display

reshape :: ReshapeCallback
reshape size = do
    viewport $= (Position 0 0, size)
    postRedisplay Nothing

keyboardMouse :: IORef (GLfloat, GLfloat) -> KeyboardMouseCallback
keyboardMouse pos key Down _ _ = case key of
    (SpecialKey KeyLeft    ) -> pos $~! \(x, y) -> (x-0.1, y)
    (SpecialKey KeyRight) -> pos $~! \(x, y) -> (x+0.1, y)
    (SpecialKey KeyUp    ) -> pos $~! \(x, y) -> (x, y+1.1)
    (SpecialKey KeyDown    ) -> pos $~! \(x, y) -> (x, y-1.1)
    _ -> return ()

keyboardMouse _ _ _ _ _ = return ()

