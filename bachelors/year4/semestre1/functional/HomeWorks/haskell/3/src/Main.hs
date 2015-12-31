module Main where

import System.IO
import System.Random
import System.Random.Shuffle
import Data.List

data Graph = Graph {
    graph_n :: Int,
    graph_M :: [[Int]]
} deriving (Show)

inf = 1000000000
genersCnt = 100
genersNum = 100
mutationProb = 0.2

pathLength :: Graph -> [Int] -> Int
pathLength g path = pathLength' g (path ++ [path!!0])
    where
        pathLength' _ [] = 0
        pathLength' _ [_] = 0
        pathLength' g (a:b:rest) =
            graph_M g !! a !! b + pathLength' g (b:rest)

randGener :: Int -> IO [Int]
randGener n = shuffleM [0..(n-1)]

initGeners :: Int -> IO [[Int]]
initGeners n = mapM (\_ -> randGener n) [1..genersCnt]

getBest :: [(Int, Int)] -> [[Int]] -> [[Int]]
getBest seq old = foldl (\acc (_, sec) -> old!!sec : acc) [] (take (length seq `div` 2) seq)

crosseng :: [Int] -> [Int] -> [Int]
crosseng fst lst =
    let n2 = genericLength fst `div` 2;
        init = take n2 fst
    in    foldl (\acc el ->
            if el `elem` acc then acc
            else (el:acc)
        ) init lst

randomDiff :: (RandomGen g) => g -> Int -> Int -> Int
randomDiff g n x =
    let (y, g1) = randomR (0, n-1) g
    in    if y == x then randomDiff g1 n x else y

getNewGener :: [[Int]] -> IO [[Int]]
getNewGener gener =
    let n = genericLength gener
    in    foldl (\acc _ -> do
            res <- acc
            gen <- newStdGen
            let i = randomDiff gen n n;
                j = randomDiff gen n i
            return $ crosseng (gener!!i) (gener!!j) : res
        ) (return []) [1..genersCnt]

mutateSingle :: [Int] -> IO [Int]
mutateSingle gn = do
    gen <- newStdGen
    let n = genericLength gn;
        i = randomDiff gen n n;
        j = randomDiff gen n i;
        gi = gn!!i;
        gj = gn!!j
    return $ map (\(idx, x) ->
            if idx == i then gj else
            if idx == j then gi else x
        ) $ zip [0..] gn

mutate :: [[Int]] -> IO [[Int]]
mutate gener = mapM (\el -> do
        gen <- newStdGen
        let p = fst $ random gen :: Float
        if p > mutationProb then return el else mutateSingle el
    ) gener

getB :: [[Int]] -> Graph -> Int
getB geners g =
    let (res, _) = foldl (\(res, res_l) (el, i) ->
            let c_l = pathLength g el in
            if c_l < res_l then (i, c_l) else (res, res_l)
        ) (-1, inf) $ zip geners [0..]
    in res


findBestPath :: Graph -> IO [Int]
findBestPath g@(Graph n _) = do
    geners <- foldl (\acc _ -> do
            gener <- acc
            let seq = sort $ zip (map (pathLength g) gener) [0..]
            ngen <- getNewGener (getBest seq gener)
            mutate ngen
        ) (initGeners n) [1..genersNum] :: IO [[Int]]
    return $ geners!!(getB geners g)

main :: IO ()
main = do
    withFile "input.txt" ReadMode (\handle -> do
            n <- read <$> hGetLine handle :: IO Int
            s <- lines <$> hGetContents handle
            let mM = map (map read . words) $ s :: [[Int]];
                g = Graph n mM
            print g

            bp <- findBestPath g
            print $ pathLength g bp
            print $ bp
        )
    return ()