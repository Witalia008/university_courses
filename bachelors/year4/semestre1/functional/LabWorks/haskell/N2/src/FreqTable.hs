module FreqTable where

import Data.List
import Data.Maybe
import Data.Char
import Control.Monad
import qualified Data.Map as Map
import qualified Data.ByteString.Lazy as B
import qualified Data.ByteString.Lazy.Char8 as C
import Data.Binary.Put
import Data.Binary.Get

type FreqTable = Map.Map Char Int

addFreq :: Int -> Char -> FreqTable -> FreqTable
addFreq val key tbl =
    let    found = fromMaybe 0 $ Map.lookup key tbl
    in    Map.insert key (found+val) tbl

calcFreq :: String -> FreqTable
calcFreq s = foldr (addFreq 1) Map.empty s

calcFreqBs :: B.ByteString -> FreqTable
calcFreqBs s = C.foldr (addFreq 1) Map.empty s

mergeFreq :: FreqTable -> FreqTable -> FreqTable
mergeFreq lst1 lst2 = foldr (\(key, val) -> addFreq val key) lst1 $ Map.toList lst2

mergeTables :: [FreqTable] -> FreqTable
mergeTables = foldl1 mergeFreq

writeTable :: FreqTable -> Put
writeTable tbl = do
    putWord32be $ fromIntegral $ Map.size tbl
    mapM (\(key, val) -> do
        putWord16be $ fromIntegral $ ord key
        putWord32be $ fromIntegral val
        ) $ Map.toList tbl
    flush

readTable :: Get (FreqTable)
readTable = do
    len <- getWord32be
    lst <- mapM (\_ -> do
        keyC <- getWord16be
        val <- getWord32be
        return (chr $ fromIntegral keyC, fromIntegral val)) [1..len]
    return $ Map.fromList lst