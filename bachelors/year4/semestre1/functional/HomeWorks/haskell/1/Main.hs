import Text.Printf
import Control.Monad
import Data.List

size = 8

validMove :: (Int, Int) -> (Int, Int) -> Bool
validMove (x1, y1) (x2, y2) =
    let a = abs (x1 - x2);
        b = abs (y1 - y2)
    in    a + b == 3 && abs (a - b) == 1

getMoves :: (Int, Int) -> [(Int, Int)]
getMoves prev =
    [(i, j) | i <- [0..(size-1)], j <- [0..(size-1)], validMove prev (i, j)]

path :: (Int, Int) -> [(Int, Int)] -> [(Int, Int)] -> IO Bool
path _ [] p = do
    forM [0..(size-1)] $ \i -> do
        forM [0..(size-1)] $ \j -> do
            let Just id = (i, j) `elemIndex` p
            printf "%02d " (id::Int)
        putStrLn ""
    putStrLn ""
    return True
path prev notV v = do
    let posMoves = getMoves prev \\ v
    foldl (\acc x -> do
            val <- acc
            if val then return True else (path x (delete x notV) (x:v))
        ) (return False) posMoves

main :: IO ()
main = do
    let
        board = [(x, y) | x <- [0..(size-1)], y <- [0..(size-1)]]
        start = (0, size `div` 2)
    path start (delete start board) [start]
    return ()
