{-# LANGUAGE OverloadedStrings #-}
module Main where

import Control.Monad    (msum)
import Happstack.Server
    ( Response, ServerPart, Method(POST)
    , BodyPolicy(..), decodeBody, defaultBodyPolicy
    , dir, look, nullConf, ok, simpleHTTP
    , toResponse, methodM
    )
import Text.Blaze ((!), toValue)
import qualified Text.Blaze.Html5 as H hiding (map)
import qualified Text.Blaze.Html5.Attributes as A
import qualified Text.Blaze.XHtml1.FrameSet.Attributes as B

main :: IO ()
main = simpleHTTP nullConf $ handlers

myPolicy :: BodyPolicy
myPolicy = (defaultBodyPolicy "/tmp/" 0 1000 1000)

handlers :: ServerPart Response
handlers =
    do  decodeBody myPolicy
        msum [ dir "table" $ tablePart
             , indexForm
             ]

indexForm :: ServerPart Response
indexForm = ok $ toResponse $
    H.html $ do
        H.head $ do
            H.title "Generate tables"
        H.body $ do
            H.form  ! A.enctype "multipart/form-data"
                    ! A.method "POST"
                    ! A.action "/table" $ do
            H.label "Table Caption: "   >> H.input  ! A.type_ "text"
                                                    ! A.name "caption" >> H.br
            H.label "Columns number: "  >> H.input  ! A.type_ "number"
                                                    ! A.name "columnsn" >> H.br
            H.label "Rows number: "     >> H.input  ! A.type_ "number"
                                                    ! A.name "rowsn"    >> H.br
            H.label "Background color: ">> H.input  ! A.type_ "text"
                                                    ! A.name "bgColour" >> H.br
            H.input ! A.type_ "submit"
                    ! A.name "upload"

tableGen :: String -> Int -> Int -> String -> ServerPart Response
tableGen caption coln rown bgCol = ok $ toResponse $
    H.html $ do
        H.head $ do
            H.title "Table"
        H.body $ do
            H.table ! B.bgcolor (toValue bgCol) ! B.border "1" $ do
                H.caption $ H.toHtml caption
                sequence_ $ map (\i -> H.tr $
                    sequence_ $ map (\j -> (H.td . H.toHtml . show) (i+j)) [1..coln]
                    ) [1..rown]


tablePart :: ServerPart Response
tablePart =
    do methodM POST
       caption  <- look "caption"
       columnsn <- look "columnsn"
       rowsn    <- look "rowsn"
       bgColour <- look "bgColour"
       tableGen caption (read columnsn) (read rowsn) bgColour
