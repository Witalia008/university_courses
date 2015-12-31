{-# LANGUAGE MultiParamTypeClasses, FunctionalDependencies #-}
{-# OPTIONS_GHC -fno-warn-duplicate-exports #-}
module Plans where
 
import Text.XML.HaXml.Schema.Schema (SchemaType(..),SimpleType(..),Extension(..),Restricts(..))
import Text.XML.HaXml.Schema.Schema as Schema
import Text.XML.HaXml.OneOfN
import qualified Text.XML.HaXml.Schema.PrimitiveTypes as Xs
 
-- Some hs-boot imports are required, for fwd-declaring types.
 
elementPlans :: XMLParser PlansType
elementPlans = parseSchemaType "Plans"
elementToXMLPlans :: PlansType -> [Content ()]
elementToXMLPlans = schemaTypeToXML "Plans"
 
data PlanType = PlanType
        { planType_id :: Xs.XsdString
        , planType_planname :: Xs.XsdString
        , planType_provider :: Xs.XsdString
        , planType_payroll :: Xs.NonNegativeInteger
        , planType_callprices :: CallpricesType
        , planType_smsprice :: Xs.NonNegativeInteger
        , planType_parameters :: ParametersType
        }
        deriving (Eq,Show)
instance SchemaType PlanType where
    parseSchemaType s = do
        (pos,e) <- posnElement [s]
        a0 <- getAttribute "id" e pos
        commit $ interior e $ return (PlanType a0)
            `apply` parseSchemaType "planname"
            `apply` parseSchemaType "provider"
            `apply` parseSchemaType "payroll"
            `apply` parseSchemaType "callprices"
            `apply` parseSchemaType "smsprice"
            `apply` parseSchemaType "parameters"
    schemaTypeToXML s x@PlanType{} =
        toXMLElement s [ toXMLAttribute "id" $ planType_id x
                       ]
            [ schemaTypeToXML "planname" $ planType_planname x
            , schemaTypeToXML "provider" $ planType_provider x
            , schemaTypeToXML "payroll" $ planType_payroll x
            , schemaTypeToXML "callprices" $ planType_callprices x
            , schemaTypeToXML "smsprice" $ planType_smsprice x
            , schemaTypeToXML "parameters" $ planType_parameters x
            ]
 
data PlansType = PlansType
        { plansType_plan :: [PlanType]
        }
        deriving (Eq,Show)
instance SchemaType PlansType where
    parseSchemaType s = do
        (pos,e) <- posnElement [s]
        commit $ interior e $ return PlansType
            `apply` many (parseSchemaType "plan")
    schemaTypeToXML s x@PlansType{} =
        toXMLElement s []
            [ concatMap (schemaTypeToXML "plan") $ plansType_plan x
            ]
 
data ParametersType = ParametersType
        { parametersType_favouriteNumber :: Xs.NonNegativeInteger
        , parametersType_tarification :: Xs.NonNegativeInteger
        , parametersType_applyCost :: Xs.NonNegativeInteger
        }
        deriving (Eq,Show)
instance SchemaType ParametersType where
    parseSchemaType s = do
        (pos,e) <- posnElement [s]
        commit $ interior e $ return ParametersType
            `apply` parseSchemaType "favouriteNumber"
            `apply` parseSchemaType "tarification"
            `apply` parseSchemaType "applyCost"
    schemaTypeToXML s x@ParametersType{} =
        toXMLElement s []
            [ schemaTypeToXML "favouriteNumber" $ parametersType_favouriteNumber x
            , schemaTypeToXML "tarification" $ parametersType_tarification x
            , schemaTypeToXML "applyCost" $ parametersType_applyCost x
            ]
 
data CallpricesType = CallpricesType
        { callpricesType_inside :: Xs.NonNegativeInteger
        , callpricesType_outside :: Xs.NonNegativeInteger
        , callpricesType_landline :: Xs.NonNegativeInteger
        }
        deriving (Eq,Show)
instance SchemaType CallpricesType where
    parseSchemaType s = do
        (pos,e) <- posnElement [s]
        commit $ interior e $ return CallpricesType
            `apply` parseSchemaType "inside"
            `apply` parseSchemaType "outside"
            `apply` parseSchemaType "landline"
    schemaTypeToXML s x@CallpricesType{} =
        toXMLElement s []
            [ schemaTypeToXML "inside" $ callpricesType_inside x
            , schemaTypeToXML "outside" $ callpricesType_outside x
            , schemaTypeToXML "landline" $ callpricesType_landline x
            ]
