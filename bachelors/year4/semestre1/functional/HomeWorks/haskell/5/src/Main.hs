module Main where

import System.IO
import Data.Maybe
import Control.Applicative
import Data.List
import qualified Data.Set as Set
import qualified Data.Map as Map

type AdjList = Map.Map Int [Int]

addEdge :: Int -> Int -> AdjList -> AdjList
addEdge from to adj =
    let found =  fromMaybe [] $ Map.lookup from adj
    in     Map.insert from (to:found) adj

printPaths :: [Int] -> Int -> Int -> AdjList -> IO ()
printPaths path v f adj
    | v == f = print $ reverse (v:path)
    | otherwise =
        let tos = fromMaybe [] $ Map.lookup v adj
        in mapM_ (\to ->
            if to `elem` path then return ()
            else printPaths (v:path) to f adj
            ) tos

main :: IO ()
main = do
    withFile "input.txt" ReadMode (\handle -> do
        s <- lines <$> (hGetContents handle)
        let [n, m] = map read . words $ (s!!0) :: [Int]
        let [fr, to] = map read . words $ (s!!1) :: [Int]
        let lst = map (map read . words) $ drop 2 s :: [[Int]];
            adj = foldl (\acc [from, to] -> addEdge from to (addEdge to from acc)) Map.empty lst
        printPaths [] fr to adj
        )
    return ()