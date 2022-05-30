PRAGMA foreign_keys = OFF;

-- Schema: typing_training
ATTACH "typing_training.sqlite" AS "typing_training";
BEGIN;
CREATE TABLE "tasks"(
  "id" INTEGER PRIMARY KEY NOT NULL,
  "name" VARCHAR(80),
  "content" TEXT,
  "output_line" VARCHAR(20),
  "output_order" VARCHAR(20),
  "line_end_key" VARCHAR(20),
  "repeat_task" INTEGER
);

CREATE TABLE "users"(
"id" INTEGER PRIMARY KEY NOT NULL,
"name" VARCHAR(80),
"password" TEXT
);

CREATE TABLE "lines"(
"id" INTEGER PRIMARY KEY NOT NULL,
"line" TEXT NOT NULL
);

CREATE TABLE "typing_durations"(
"id" INTEGER PRIMARY KEY NOT NULL,
"user_id" INTEGER NOT NULL,
"line_id" INTEGER NOT NULL,
"duration" INTEGER,
"datetime" TEXT,
CONSTRAINT "fk_typing_durations_users1"
    FOREIGN KEY("user_id")
    REFERENCES "users"("id")
    ON DELETE CASCADE
    ON UPDATE CASCADE,
CONSTRAINT "fk_typing_durations_lines1"
    FOREIGN KEY("line_id")
    REFERENCES "lines"("id")
    ON DELETE CASCADE
    ON UPDATE CASCADE
);


--CREATE TABLE "measuring_conditions"(
--  "id" INTEGER PRIMARY KEY NOT NULL,
--  "gain_factor" INTEGER NOT NULL,
--  "exposition" INTEGER NOT NULL,
--  CONSTRAINT "fk_calibrations_measuring_conditions1"
--    FOREIGN KEY("gain_factor")
--    REFERENCES "gain_factors"("gain_factor")
--    ON DELETE RESTRICT
--    ON UPDATE RESTRICT
--);
--CREATE INDEX "measuring_conditions.fk_calibrations_measuring_conditions1_idx" ON "measuring_conditions" ("gain_factor");

COMMIT;
