import Plans
import System.IO
import Text.XML.HaXml.Validate
import Text.XML.HaXml
import Text.XML.HaXml.Parse
import Text.XML.HaXml.Posn
import Text.XML.HaXml.Schema.Schema
import Text.XML.HaXml.Lex
import Text.XML.HaXml.XmlContent.Parser
import Text.ParserCombinators.Poly.Plain
import Text.XML.HaXml.Validate

main :: IO ()
main = do
    let dtdname = "xml/plans.dtd"
    dtdcont <- readFile dtdname
    let Just dtd = dtdParse dtdname dtdcont

    let fname = "xml/plans.xml"
    xmlText <- readFile fname
    let (Document _ _ root _) = xmlParse "(No Document)" xmlText
    let (Right plans) = fst $ runParser elementPlans [CElem root noPos]
    print $ validate dtd root
    -- print plans
    let planArr = plansType_plan plans
    mapM print planArr

    return ()