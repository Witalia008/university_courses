{-# LANGUAGE OverloadedStrings #-}
module Main where

import Control.Monad    (msum)
import Data.Char         (toLower)
import Happstack.Server
import Text.Blaze ((!))
import qualified Text.Blaze.Html5 as H
import qualified Text.Blaze.Html5.Attributes as A

appTemplate :: String -> [H.Html] -> H.Html -> H.Html
appTemplate title headers body =
    H.html $ do
        H.head $ do
            H.title (H.toHtml title)
            H.meta  ! A.httpEquiv "Content-Type"
                    ! A.content "text/html;charset=utf-8"
            sequence_ headers
        H.body $ do
            body

helloBlaze :: ServerPart Response
helloBlaze =
    ok $ toResponse $
        appTemplate "Hello, Blaze!"
                    [H.meta ! A.name "keywords"
                            ! A.content "happstack, blaze, html" ]
                    (H.p $ do
                        "Hello, "
                        H.b "blaze-html!")

main :: IO ()
main = simpleHTTP nullConf $ helloBlaze