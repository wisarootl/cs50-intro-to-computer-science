-- Keep a log of any SQL queries you execute as you solve the mystery.


-- get the crime_scene_reports on the day of the crime
SELECT  id, description
FROM crime_scene_reports
WHERE (year = 2021 AND day = 28 AND month = 7 AND street = "Humphrey Street");

-- get the interviews on the day of the crime
SELECT id, name, transcript
FROM interviews
WHERE (year = 2021 AND day = 28 AND month = 7);
--id 161, Ruth    | Sometime within <TEN MINUTES> of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you
--                  have <SECURITY FOOTAGE> from the '<EMMAS BAKERY PARKING LOT>, you might want to look for cars that left the parking lot in that time frame.
--id 162, Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning <BEFORE 10:15 AM>, before I arrived at "EMMA's bakery", I was walking
--                  by the <ATM ON LEGGETT STREET> and saw the thief there withdrawing some money.
--id 163, Raymond | As the thief was leaving the bakery, they called someone who talked to them for <LESS THAN 60 SECONDS>. In the call, I heard the thief
--                  say that they were planning to take the <EARLIEST FLIGHT> out of Fiftyville <tomorrow July 29, 2021>. The thief then asked the person
--                  on the other end of the phone to purchase the flight ticket. <ACCOMPLICE BOUGHT THE FLIGHT>
--id 193, Emma    | I'm the bakery owner, and soemone came in, suspiciously whispering into a <PHONE FOR 30 MINUTES>. They <NEVER BOUGHT ANYTHING>.


-- from Eugene, get all atm withdrawals transaction on Leggett Street before 10:15 AM
SELECT id, account_number
FROM atm_transactions
WHERE (year = 2021 AND month = 7 AND day = 28 AND atm_location ="Leggett Street" AND transaction_type = "withdraw");

-- find details of owner of the account on that day
SELECT name, phone_number, passport_number, license_plate FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
    (SELECT account_number FROM atm_transactions WHERE
    (year = 2021 AND month = 7 AND day = 28 AND atm_location ="Leggett Street" AND transaction_type = "withdraw")));

-- get car license_plate for the cars that was left the lot between 10:15 and 10:25 on that day
SELECT license_plate
FROM bakery_security_logs
WHERE (year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = "exit");

-- find car owner
SELECT name, phone_number, passport_number
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
                    SELECT account_number
                    FROM atm_transactions
                    WHERE (year = 2021 AND month = 7 AND day = 28 AND atm_location ="Leggett Street" AND transaction_type = "withdraw")))
                    AND license_plate IN (
                        SELECT license_plate
                        FROM bakery_security_logs
                        WHERE (year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = "exit")
                        );

-- get all the phone calls on the crime day with durations under 60 seconds
SELECT caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- compare the phone numbers of the caller with the previous numbers of those who withdrew money at LEGGETT street
-- and left the bakery after robbery

SELECT name, phone_number, passport_number
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE (year = 2021 AND month = 7 AND day = 28 AND atm_location ="Leggett Street" AND transaction_type = "withdraw")))
    AND license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE (year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = "exit"))
    AND phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE (year = 2021 AND month = 7 AND day = 28 AND duration < 60));


-- compare the passports to those who took earliest flight the next day
SELECT id
FROM flights
WHERE (year = 2021 AND month = 7 AND day = 29)
ORDER BY HOUR LIMIT 1;

-- match it all to get the name of the thief
SELECT name, phone_number
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE (year = 2021 AND month = 7 AND day = 28 AND atm_location ="Leggett Street" AND transaction_type = "withdraw")))
    AND license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE (year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = "exit"))
    AND phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
    AND passport_number IN (
        SELECT passport_number
        FROM passengers
        WHERE flight_id = (
            SELECT id
            FROM flights
            WHERE (year = 2021 AND month = 7 AND day = 29)
            ORDER BY HOUR
            LIMIT 1));

-- find Bruces phone number to the person he called
SELECT name
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE caller = "(367) 555-5533" AND year = 2021 AND month = 7 AND day = 28 AND duration < 60);

-- get city of the flights desination airport
SELECT city
FROM airports
WHERE id IN (
    SELECT destination_airport_id
    FROM flights
    WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29
    ORDER BY HOUR
    LIMIT 1);