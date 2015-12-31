qsort :: Ord a => [a] -> [a]
qsort [] = []
qsort [x] = [x]
qsort (pivot:rest) =
    let
        lower = filter (<pivot) rest;
        upper = filter (>=pivot) rest;
    in
        qsort lower ++ [pivot] ++ qsort upper;

main :: IO ()
main = do
    print $ qsort [10,9..1]
