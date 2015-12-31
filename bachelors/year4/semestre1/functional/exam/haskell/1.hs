data Tree a = Leaf a | Branch ([Tree a])

tree_sum :: Tree Int -> Int
tree_sum (Leaf x) = x
tree_sum (Branch sons) =
    foldl (\acc x -> acc + (tree_sum x)) 0 sons

main :: IO ()
main = do
    print $ tree_sum (Branch [Leaf 4, Leaf 7, Branch [Leaf 5]])
