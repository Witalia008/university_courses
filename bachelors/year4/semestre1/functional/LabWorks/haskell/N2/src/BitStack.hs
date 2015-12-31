module BitStack where

import Prelude hiding (print)
import Data.Word
import Data.List
import Data.Bits
import Data.Binary.Put
import Data.Binary.Get

data BitStack = NullStack | BitStack {
    leng :: Int,
    _data :: [Word8]
} deriving (Eq, Show)

empty = BitStack 0 []

-- Word8 is actually 1 bit
push :: Word8 -> BitStack -> BitStack
push _ NullStack = NullStack
push bit bl@(BitStack len lst)
    | bit > 1 = bl
    | otherwise =
        let lenm = len `mod` 8;
            rem = if lenm == 0 then lst else tail lst;
            fst = if lenm == 0 then 0 else head lst;
            nel = fst .|. (rotate bit len)
        in    BitStack (len+1) (nel:rem)

top :: BitStack -> Word8
top NullStack = 0
top (BitStack len lst)
    | len == 0 = -1
    | otherwise =
        let nlen = (len-1) `mod` 8
        in (rotate (head lst) (-nlen)) .&. 1

pop :: BitStack -> BitStack
pop NullStack = NullStack
pop bl@(BitStack len lst)
    | len == 0 = bl
    | otherwise =
        let nlen = (len-1) `mod` 8;
            nlst = if nlen == 0 then tail lst else lst
        in (BitStack (len-1) nlst)

print :: BitStack -> IO ()
print NullStack = return ()
print bl
     | leng bl == 0 = putStrLn ""
     | otherwise = do
        putStr $ show (top bl) ++ " "
        print $ pop bl

writeCode :: BitStack -> Put
writeCode (BitStack len lst) = do
    putWord32be $ fromIntegral len
    putWord32be $ genericLength lst
    mapM putWord8 lst
    flush

readCode :: Get (BitStack)
readCode = do
    len <- getWord32be
    llen <- getWord32be
    lst <- mapM (\_ -> getWord8) [1..llen]
    return $ BitStack (fromIntegral len) lst