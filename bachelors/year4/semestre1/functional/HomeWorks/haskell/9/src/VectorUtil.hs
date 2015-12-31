module VectorUtil where

import Graphics.UI.GLUT


type PosType = Vector3 GLfloat

add :: PosType -> PosType -> PosType
(Vector3 a1 a2 a3) `add` (Vector3 b1 b2 b3) = Vector3 (a1+b1) (a2+b2) (a3+b3)

sub :: PosType -> PosType -> PosType
(Vector3 a1 a2 a3) `sub` (Vector3 b1 b2 b3) = Vector3 (a1-b1) (a2-b2) (a3-b3)

neg :: PosType -> PosType
neg (Vector3 x y z) = (Vector3 (-x) (-y) (-z))

mult :: PosType -> GLfloat -> PosType
mult (Vector3 x y z) c = (Vector3 (x*c) (y*c) (z*c))

dot :: PosType -> PosType -> GLfloat
dot (Vector3 a1 a2 a3) (Vector3 b1 b2 b3) = a1*b1+a2*b2+a3*b3

cross :: PosType -> PosType -> PosType
cross (Vector3 a1 a2 a3) (Vector3 b1 b2 b3) = (Vector3 (a2*b3-a3*b2) (a3*b1-a1*b3) (a1*b2-a2*b1))

dist :: PosType -> PosType -> GLfloat
(Vector3 a1 a2 a3) `dist` (Vector3 b1 b2 b3) = sqrt $ (^2)(a1-b1) + (^2)(a2-b2) + (^2)(a3-b3)

mag :: PosType -> GLfloat
mag = sqrt . sq_mag

sq_mag :: PosType -> GLfloat
sq_mag v = v `dot` v

normalize :: PosType -> PosType
normalize v
    | (mag v) /= 0 = mult v (1 / mag v)
    | otherwise    = (Vector3 0 0 0)

angle_between :: PosType -> PosType -> GLfloat
angle_between a b
    | result < -1 = acos (-1) -- clamping to avoid floating point issues
    | result > 1 = acos 1
    | otherwise = acos result
        where result = (VectorUtil.normalize a) `dot` (VectorUtil.normalize b)

proj :: PosType -> PosType -> GLfloat
proj a b = (mag a) * (cos (angle_between a b))
