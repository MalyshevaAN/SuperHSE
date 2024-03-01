DROP TABLE IF EXISTS "USERS";
DROP TABLE IF EXISTS "SHOP";
DROP TABLE IF EXISTS "WARDROBE";
DROP TABLE IF EXISTS "CURRENT_APPEARENCE";
DROP TABLE IF EXISTS "LEVELS";

CREATE TABLE "USERS" (
    "USER_ID"	INTEGER NOT NULL UNIQUE,
    "USERNAME"	varchar(100) NOT NULL,
    "BALANCE"	INTEGER NOT NULL DEFAULT 0,
    PRIMARY KEY("USER_ID" AUTOINCREMENT)
);

CREATE TABLE "SHOP" (
    "TYPE"	TEXT NOT NULL,
    "ITEM_ID"	INTEGER NOT NULL UNIQUE,
    "ITEM_NAME"	TEXT NOT NULL,
    "COST"	INTEGER NOT NULL,
    "PATH_TO_IMAGE"	TEXT NOT NULL,
    PRIMARY KEY("ITEM_ID" AUTOINCREMENT)
);

CREATE TABLE "WARDROBE" (
    "USER_ID"	INTEGER NOT NULL UNIQUE,
    "ITEMS_ID"	TEXT NOT NULL,
    FOREIGN KEY("USER_ID") REFERENCES "USERS"("USER_ID")
);

CREATE TABLE "CURRENT_APPEARENCE" (
    "USER_ID"	INTEGER NOT NULL UNIQUE,
    "SKIN"	INTEGER NOT NULL DEFAULT 1,
    FOREIGN KEY("USER_ID") REFERENCES "USERS"("USER_ID"),
    FOREIGN KEY("SKIN") REFERENCES "SHOP"("ITEM_ID")
);

CREATE TABLE "LEVELS" (
    "USER_ID"	INTEGER NOT NULL,
    "LVL_NUM"	INTEGER NOT NULL,
    "STATUS"	INTEGER NOT NULL DEFAULT 0,
    "BEST_TIME"	NUMERIC,
    "BEST_CASH"	INTEGER,
    FOREIGN KEY("USER_ID") REFERENCES "USERS"("USER_ID")
);

INSERT INTO "SHOP" ("TYPE", "ITEM_NAME", "COST", "PATH_TO_IMAGE") VALUES ('SKIN', 'Ivan Kalinin', 0, 'https://github.com/MalyshevaAN/SuperHSE/blob/main/assets/images/ivankalinin.png?raw=true');
INSERT INTO "SHOP" ("TYPE", "ITEM_NAME", "COST", "PATH_TO_IMAGE") VALUES ('SKIN', 'Mr. Khrabroff', 0, 'https://github.com/MalyshevaAN/SuperHSE/blob/main/assets/images/khrabrov.png?raw=true');
INSERT INTO "SHOP" ("TYPE", "ITEM_NAME", "COST", "PATH_TO_IMAGE") VALUES ('SKIN', 'Mr. Antipoff', 0, 'https://github.com/MalyshevaAN/SuperHSE/blob/main/assets/images/antipov.png?raw=true');
INSERT INTO "SHOP" ("TYPE", "ITEM_NAME", "COST", "PATH_TO_IMAGE") VALUES ('SKIN', 'Anna Gladkaya', 0, 'https://github.com/MalyshevaAN/SuperHSE/blob/main/assets/images/annaglad.png?raw=true');
INSERT INTO "SHOP" ("TYPE", "ITEM_NAME", "COST", "PATH_TO_IMAGE") VALUES ('SKIN', 'Egor', 0, 'https://github.com/MalyshevaAN/SuperHSE/blob/main/assets/images/egor_with_headphones.png?raw=true');
INSERT INTO "SHOP" ("TYPE", "ITEM_NAME", "COST", "PATH_TO_IMAGE") VALUES ('SKIN', 'Sergey Kopel Kopeliovich', 0, 'https://github.com/MalyshevaAN/SuperHSE/blob/main/assets/images/kopel.png?raw=true');