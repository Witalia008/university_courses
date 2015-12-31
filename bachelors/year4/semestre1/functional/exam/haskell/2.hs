import System.IO
import Data.Char
import System.Random
import Control.Monad
import Data.Maybe

insert :: Int -> FilePath -> FilePath -> IO ()
insert num f1 f2 = do
    contents <- readFile f1
    let
        nums = map (read) (lines contents) :: [Int];
    withFile f2 WriteMode (\h -> do
        n <- foldl (\acc x -> do
                a <- acc
                let val = fromMaybe 0 a;
                if isJust a && val < x
                    then do
                        hPutStrLn h $ show val
                        hPutStrLn h $ show x
                        return $ Nothing
                    else do
                        hPutStrLn h $ show x
                        return $ a
            ) (return $ Just num) nums
        if isJust n
            then hPutStrLn h $ show (fromMaybe 0 n)
            else return ()
        return ()
        )

insertion :: [Int] -> [String] -> IO String
insertion [] [h1, h2] = return h1
insertion (a:r) [h1, h2] = do
    insert a h1 h2
    insertion r [h2, h1]


main :: IO ()
main = do
    gen <- getStdGen
    let
        n = 100;
        arr = take n $ randomRs (-1000000,1000000) gen :: [Int]
    writeFile "file.txt" (unlines (map show arr))


    contents <- readFile "file.txt"
    let
        nums = map (read) (lines contents) :: [Int]

    let files = ["h1.txt", "h2.txt"]
    forM files (\file -> do
            writeFile file ""
        )

    res <- insertion nums files
    print res

    return ()
