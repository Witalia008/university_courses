module CodeTree where

import FreqTable
import Data.List
import Data.Maybe
import Data.Char
import qualified BitStack as BSt
import qualified Data.Map as Map
import qualified Data.ByteString.Lazy as B
import qualified Data.ByteString.Lazy.Char8 as C


data CodeTree = NullTree | Node {
    val :: (Maybe Char, Int),
    left :: CodeTree,
    right :: CodeTree
} deriving (Eq, Show)

mapToNodeList :: FreqTable -> [CodeTree]
mapToNodeList tbl = map (\(key, val) -> Node (Just key, val) NullTree NullTree) $ Map.toList tbl

combineNodes :: CodeTree -> CodeTree -> CodeTree
combineNodes l@(Node (_, lc) _ _) r@(Node (_, rc) _ _) = Node (Nothing, lc+rc) l r

getMinNode :: [CodeTree] -> CodeTree
getMinNode lst = foldl1 (\acc el -> if (snd $ val el) < (snd $ val acc) then el else acc) lst

foldListToTree :: [CodeTree] -> CodeTree
foldListToTree lst
    | len < 1 = NullTree
    | len == 1 = head lst
    | otherwise =
        let fst = getMinNode lst;
            rem1 = delete fst lst;
            snd = getMinNode rem1;
            rem = delete snd rem1
        in foldListToTree $ combineNodes fst snd : rem
    where len = length lst

foldTableToTree :: FreqTable -> CodeTree
foldTableToTree = foldListToTree . mapToNodeList

foldTablesToTree :: [FreqTable] -> CodeTree
foldTablesToTree = foldTableToTree . mergeTables

encodeChar :: CodeTree -> Char -> BSt.BitStack -> BSt.BitStack
encodeChar NullTree _ _ = BSt.NullStack
encodeChar tree ch st
    | fst (val tree) == Just ch = st -- if this node holds desired char
    | otherwise =
        if inL /= BSt.NullStack then BSt.push 0 inL
        else if inR /= BSt.NullStack then BSt.push 1 inR
        else BSt.NullStack
    where
        inL = encodeChar (left tree) ch st
        inR = encodeChar (right tree) ch st


encodeString :: CodeTree -> BSt.BitStack -> String -> BSt.BitStack
encodeString tree st str = foldr (encodeChar tree) st str

encodeStringBs :: CodeTree -> BSt.BitStack -> B.ByteString -> BSt.BitStack
encodeStringBs tree st str = C.foldr (encodeChar tree) st str

decodeChar :: CodeTree -> BSt.BitStack -> (Maybe Char, BSt.BitStack)
decodeChar NullTree st = (Nothing, st)
decodeChar tree st
    | isJust tVal = (tVal, st)
    | otherwise = if bit == -1 then (Nothing, st) else
        if bit == 0 then
            decodeChar (left tree) stRem
        else decodeChar (right tree) stRem
    where
        tVal = fst $ val tree
        bit = BSt.top st
        stRem = BSt.pop st

decodeString :: CodeTree -> BSt.BitStack -> String
decodeString tree st
    | st == BSt.empty = ""
    | otherwise = ch : decodeString tree stRem
    where (Just ch, stRem) = decodeChar tree st

decodeStringBs :: CodeTree -> BSt.BitStack -> B.ByteString
decodeStringBs tree st
    | st == BSt.empty = B.empty
    | otherwise = C.cons ch $ decodeStringBs tree stRem
    where (Just ch, stRem) = decodeChar tree st