reverse_list :: [a] -> [a]
reverse_list [] = []
reverse_list (h:t) = (reverse_list t) ++ [h]

main :: IO ()
main = do
    print $ reverse_list [1..10]
