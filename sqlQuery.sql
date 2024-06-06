CREATE TABLE IF NOT EXISTS "USERS" (
    "USER_ID"	INTEGER NOT NULL UNIQUE,
    "USERNAME"	varchar(100) NOT NULL,
    "HASHED_PASSWORD"	varchar(100) NOT NULL,
    "SALT"	varchar(100) NOT NULL,
    "BALANCE"	INTEGER NOT NULL DEFAULT 0,
    "CURRENT_SKIN"	INTEGER NOT NULL DEFAULT 1,
    PRIMARY KEY("USER_ID" AUTOINCREMENT),
    FOREIGN KEY("CURRENT_SKIN") REFERENCES "ITEMS"("ITEM_ID")
);

CREATE TABLE IF NOT EXISTS "ITEMS" (
    "TYPE"	INTEGER NOT NULL,
    "ITEM_ID"	INTEGER NOT NULL UNIQUE,
    "ITEM_NAME"	TEXT NOT NULL,
    "COST"	INTEGER NOT NULL,
    "PATH"	TEXT NOT NULL,
    PRIMARY KEY("ITEM_ID" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "SKINS" (
    "USER_ID"	INTEGER NOT NULL,
    "ITEM_ID"	INTEGER NOT NULL,
    "STATUS"    INTEGER NOT NULL DEFAULT 0,
    FOREIGN KEY("USER_ID") REFERENCES "USERS"("USER_ID"),
    FOREIGN KEY("ITEM_ID") REFERENCES "iTEMS"(ITEM_ID)
);

CREATE TABLE IF NOT EXISTS "LEVELS" (
    "USER_ID"	    INTEGER NOT NULL,
    "LVL_NUM"	    INTEGER NOT NULL,
    "STATUS"	    INTEGER NOT NULL DEFAULT 0,
    "BEST_LIVES"    INTEGER,
    "BEST_COINS"	INTEGER,
    FOREIGN KEY("USER_ID") REFERENCES "USERS"("USER_ID")
);

INSERT INTO "ITEMS" ("TYPE", "ITEM_NAME", "COST", "PATH") 
SELECT 0, 'Ivan Kalinin', 0, 'ivankalinin.png'
WHERE NOT EXISTS (SELECT 1 FROM "ITEMS" WHERE "ITEM_NAME" = 'Ivan Kalinin');

INSERT INTO "ITEMS" ("TYPE", "ITEM_NAME", "COST", "PATH") 
SELECT 0, 'Mr. Khrabroff', 10, 'khrabrov.png'
WHERE NOT EXISTS (SELECT 1 FROM "ITEMS" WHERE "ITEM_NAME" = 'Mr. Khrabroff');

INSERT INTO "ITEMS" ("TYPE", "ITEM_NAME", "COST", "PATH") 
SELECT 0, 'Mr. Antipoff', 10, 'antipov.png'
WHERE NOT EXISTS (SELECT 1 FROM "ITEMS" WHERE "ITEM_NAME" = 'Mr. Antipoff');

INSERT INTO "ITEMS" ("TYPE", "ITEM_NAME", "COST", "PATH") 
SELECT 0, 'Anna Gladkaya', 10, 'annaglad.png'
WHERE NOT EXISTS (SELECT 1 FROM "ITEMS" WHERE "ITEM_NAME" = 'Anna Gladkaya');

INSERT INTO "ITEMS" ("TYPE", "ITEM_NAME", "COST", "PATH") 
SELECT 0, 'Egor', 10, 'egor2.png'
WHERE NOT EXISTS (SELECT 1 FROM "ITEMS" WHERE "ITEM_NAME" = 'Egor');

INSERT INTO "ITEMS" ("TYPE", "ITEM_NAME", "COST", "PATH") 
SELECT 0, 'Sergey Kopel Kopeliovich', 10, 'kopel.png'
WHERE NOT EXISTS (SELECT 1 FROM "ITEMS" WHERE "ITEM_NAME" = 'Sergey Kopel Kopeliovich');

INSERT INTO "ITEMS" ("TYPE", "ITEM_NAME", "COST", "PATH")
SELECT 0, 'HSE Raven', 40, 'hse.png'
WHERE NOT EXISTS (SELECT 1 FROM "ITEMS" WHERE "ITEM_NAME" = 'HSE Raven');

INSERT INTO "ITEMS" ("TYPE", "ITEM_NAME", "COST", "PATH")
SELECT 0, 'sasha red', 40, 'red.png'
WHERE NOT EXISTS (SELECT 1 FROM "ITEMS" WHERE "ITEM_NAME" = 'sasha red');

INSERT INTO "ITEMS" ("TYPE", "ITEM_NAME", "COST", "PATH")
SELECT 0, 'sasha blue', 0, 'blue.png'
WHERE NOT EXISTS (SELECT 1 FROM "ITEMS" WHERE "ITEM_NAME" = 'sasha blue');

INSERT INTO "ITEMS" ("TYPE", "ITEM_NAME", "COST", "PATH")
SELECT 0, 'sasha white', 0, 'white.png'
WHERE NOT EXISTS (SELECT 1 FROM "ITEMS" WHERE "ITEM_NAME" = 'sasha white');

INSERT INTO "ITEMS" ("TYPE", "ITEM_NAME", "COST", "PATH")
SELECT 0, 'sasha purple', 0, 'purple.png'
WHERE NOT EXISTS (SELECT 1 FROM "ITEMS" WHERE "ITEM_NAME" = 'sasha purple');