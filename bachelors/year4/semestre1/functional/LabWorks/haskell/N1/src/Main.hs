{-# LANGUAGE OverloadedStrings #-}
import Database.PostgreSQL.Simple as PG
import Database.PostgreSQL.Simple.Time
import Database.PostgreSQL.Simple.Types
import Control.Monad
import Control.Applicative
import GHC.Int

class EntityBean entity where
    insert :: entity -> PG.Connection -> IO Int64
    update :: entity -> PG.Connection -> IO Int64
    delete :: entity -> PG.Connection -> IO Int64


data Role = Role {
    role_id :: Int,
    role_name :: String
} deriving (Read)
instance EntityBean Role where
    insert role conn = execute conn "insert into roles (rolename) values (?)" [role_name role]
    update role conn = execute conn "update roles set rolename = ? where id = ?" (role_name role, role_id role)
    delete role conn = execute conn "delete from roles where id=?" [role_id role]


data User = User {
    user_id :: Int,
    user_name :: String,
    user_password :: String,
    user_role :: Role
} deriving (Read)
instance EntityBean User where
    insert user conn = execute conn "insert into users (username, password, roleid) values (?,?,?)"
        (user_name user, user_password user, role_id $ user_role user)
    update user conn = execute conn "update users set username = ?, password = ?, roleid = ? where id=?"
        (user_name user, user_password user, role_id $ user_role user, user_id user)
    delete user conn = execute conn "delete from users where id = ?" [user_id user]


data License = License {
    license_id :: Int,
    license_conds :: String,
    license_expires :: Date,
    license_rules :: String
} deriving (Read)
instance EntityBean License where
    insert lic conn = execute conn "insert into licenses (cond, expires, rules) values (?,?,?)"
        (license_conds lic, license_expires lic, license_rules lic)
    update lic conn = execute conn "update licenses set cond = ?, expires = ?, rules = ? where id = ?"
        (license_conds lic, license_expires lic, license_rules lic, license_id lic)
    delete lic conn = execute conn "delete from licenses where id = ?" [license_id lic]


data Service = Service {
    svc_id :: Int,
    svc_name :: String,
    svc_author :: User,
    svc_antn :: String,
    svc_type :: Int,
    svc_version :: String,
    svc_conds :: License
} deriving (Read)
instance EntityBean Service where
    insert svc conn = execute conn
        "insert into services (sname, author, atxt, stype, version, conditions) values (?,?,?,?,?,?)"
        (svc_name svc, user_id $ svc_author svc, svc_antn svc,
        svc_type svc, svc_version svc, license_id $ svc_conds svc)
    update svc conn = execute conn
        "update services set sname=?, author=?, atxt=?, stype=?, version=?, conditions=? where id=?"
        (svc_name svc, user_id $ svc_author svc, svc_antn svc,
        svc_type svc, svc_version svc, license_id $ svc_conds svc, svc_id svc)
    delete svc conn = execute conn "delete from services where id=?" [svc_id svc]


data Change = Change {
    change_id :: Int,
    change_svc :: Service,
    change_text :: String
} deriving (Read)
instance EntityBean Change where
    insert change conn = execute conn "insert into changes (service, changetext) values (?,?)"
        (svc_id $ change_svc change, change_text change)
    update change conn = execute conn "update changes set service=?, changetext=? where id=?"
        (svc_id $ change_svc change, change_text change, change_id change)
    delete change conn = execute conn "delete from changes where id=?" [change_id change]


data Stat = Stat {
    stat_id :: Int,
    stat_service :: Service,
    stat_date :: Date,
    stat_nvisits :: Int
} deriving (Read)
instance EntityBean Stat where
    insert stat conn = execute conn "insert into stats (service, whendate, nvisits) values (?,?,?)"
        (svc_id $ stat_service stat, stat_date stat, stat_nvisits stat)
    update stat conn = execute conn "update stats set service=?, whendate=?, nvisits=? where id=?"
        (svc_id $ stat_service stat, stat_date stat, stat_nvisits stat, stat_id stat)
    delete stat conn = execute conn "delete from stats where id=?" [stat_id stat]


runCommand :: EntityBean a => PG.Connection -> a -> String -> IO Int64
runCommand conn obj comm
    | comm == "update" = update obj conn
    | comm == "insert" = insert obj conn
    | comm == "delete" = delete obj conn

main :: IO ()
main = do
    conn <- PG.connect defaultConnectInfo {
        connectDatabase = "hlab1",
        connectUser = "postgres",
        connectPassword = "password",
        connectHost = "localhost",
        connectPort = 5432
    }

    -- Role Role{role_id=10,role_name="Dummy2"} update
    content <- getLine
    let [table, object, command] = words content

    case table of
        "Role" -> do
            let obj = read object :: Role
            runCommand conn obj command
        "User" -> do
            let obj = read object :: User
            runCommand conn obj command
        "License" -> do
            let obj = read object :: License
            runCommand conn obj command
        "Service" -> do
            let obj = read object :: Service
            runCommand conn obj command
        "Change" -> do
            let obj = read object :: Change
            runCommand conn obj command
        "Stat" -> do
            let obj = read object :: Stat
            runCommand conn obj command

    return ()