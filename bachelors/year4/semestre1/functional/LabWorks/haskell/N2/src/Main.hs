{-# OPTIONS_GHC -threaded #-}
import Control.Parallel
import Control.Monad
import Data.Maybe
import Data.List
import Data.Char
import qualified BitStack as BSt
import CodeTree
import FreqTable
import Control.Parallel
import Control.Parallel.Strategies
import qualified Data.ByteString.Lazy as B
import Data.Binary.Put
import Data.Binary.Get

parBuffSize = 100

encryptFiles :: [String] -> [B.ByteString] -> B.ByteString
encryptFiles names conts =
    let freql = withStrategy (parBuffer parBuffSize rdeepseq) $ map calcFreqBs conts;
        freqt = mergeTables freql;
        ctree = foldTableToTree freqt;
        coded = withStrategy (parBuffer parBuffSize rseq) $ map (encodeStringBs ctree BSt.empty) conts
    in    runPut $ do
        -- Write frequency table
        writeTable freqt
        -- Write files' names with their compressed content
        putWord32be $ genericLength names
        mapM (\(name, content) -> do
            putWord32be $ genericLength name
            mapM (putWord16be . fromIntegral . ord) name
            BSt.writeCode content
            flush) (zip names coded)
        flush

decryptFiles :: B.ByteString -> ([String], [B.ByteString])
decryptFiles _data = runGet decr _data
    where decr = do
        -- Read frequency table and build tree
        tbl <- readTable
        let ctree = foldTableToTree tbl
        -- Read names and contents
        cnt <- getWord32be
        files <- mapM (\_ -> do
            nlen <- getWord32be
            name_ <- mapM (\_ -> getWord16be) [1..nlen]
            let name = map (chr . fromIntegral) name_
            content <- BSt.readCode
            return (name, content)) [1..cnt]
        let (names, encrc) = unzip files;
            contents = withStrategy (parBuffer parBuffSize rseq) $ map (decodeStringBs ctree) encrc
        return (names, contents)

main :: IO ()
main = do
    {-let l = reverse [0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1]
    let blst = foldl (\acc x -> x `BSt.push` acc) BSt.empty l
    BSt.print blst
    -- print $ calcFreq "Hello, World! My name is Vitalii!"
    let a = calcFreq "Hello, World!";
        b = calcFreq "My name is Vitalii!";
        c = mergeFreq a b;
        treeA = foldTableToTree a;
        treeC = foldTablesToTree [a, b]
    -- print cs
    print c
    -- print b
    -- print c
    print $ treeA
    -- print $ foldTablesToTree [a, b]
    -- print $ foldTableToTree c
    -- print $ encodeChar treeA ',' BSt.empty
    -- BSt.print $ encodeString treeC "Hello, World!" BSt.empty
    -- BSt.print $ encodeString treeC "My name is Vitalii! " BSt.empty
    BSt.print $ encodeString treeC "Hello, World!" $ encodeString treeC "My name is Vitalii!" BSt.empty-}

    let folder_name = "brave_new_world"
    let names = map (\name -> folder_name ++ "/" ++ name) $ map (\i -> show i ++ ".txt") [1..18]
    conts <- mapM B.readFile names
    let res = encryptFiles names conts
    B.writeFile "out.arc" res

    fileC <- B.readFile "out.arc"
    let (names_, conts) = decryptFiles fileC;
        names = map (\name -> folder_name ++ "_new/" ++ (drop (length folder_name + 1) name)) names_
    mapM (\(name, cont) -> B.writeFile name cont) (zip names conts)

    return ()